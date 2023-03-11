<?php

header('Content-Encoding: utf-8');

require_once 'Common/ErrorCode.inc';
require_once 'Lib/Memcached.php';
require_once 'Lib/Log.php';


function g_GetNetwork()
{
	global $g_Network;
	if ($g_Network == null) {
		$g_Network = new Network;
	}

	($g_Network instanceof Network);

	return $g_Network;
}


class Network
{
	private $_commandKey;
	private $_bodyKey;
	private $_errorCodeKey;
	private $_errorMessageKey;
	
	private $_addBody = array();
	
	private $_jsonRecvBuffer;
	
	private $_httpErrorCode;
	private $_httpErrorMsg;
	private $_httpErrorCodeFromCallUrl;
	
	private $_socket;
	private $_socketErrorCode;
			
    function __construct()
    {
        $this->Init();
    }
	
	function Init()
	{	
		$this->_jsonRecvBuffer = json_decode( file_get_contents( "php://input" ), true );
		$this->_result = array();
	}
	
	public function SetHeaderInfo( $cmdKey, $bodyKey, $errorCodeKey, $errorMessageKey )
	{
		$this->_commandKey = $cmdKey;
		$this->_bodyKey = $bodyKey;
		$this->_errorCodeKey = $errorCodeKey;
		$this->_errorMessageKey = $errorMessageKey;
	}
	
	public function GetCommand()
	{
		if ( isset($this->_jsonRecvBuffer[$this->_commandKey] ) == false ) {
			return null;
		}
		
		return $this->_jsonRecvBuffer[$this->_commandKey];
	}
	
	public function GetValue($name)
	{
		if ( isset($this->_jsonRecvBuffer[$this->_bodyKey][$name] ) == false ) {
			return null;			
		}
		
		return $this->_jsonRecvBuffer[$this->_bodyKey][$name];
	}

	public function AckPacket($body)
	{
		$msg[$this->_commandKey] = $this->GetCommand();
		$msg[$this->_bodyKey] = $body;
		
		$jsonPacket = json_encode($msg);
		print( $jsonPacket );
		
		/// 로그에 클라로 보내는 값 출력 @brief  - giman 2013. 10. 23. 오후 5:30:04
		g_GetLog()->Write( LOG_LEVEL::INFO, LOG_TYPE::LOG, ERROR_CODE\System::SUCCESS,	sprintf( "Send : %s", $jsonPacket ) );
	}
	
	public function CallProtocolHandler()
	{
		/// @brief 로그에 클라가 보내준 값 출력  - giman 2013. 9. 27. 오후 4:22:49
		g_GetLog()->Write( LOG_LEVEL::INFO, LOG_TYPE::LOG, ERROR_CODE\System::SUCCESS, sprintf( "Recv : %s", file_get_contents( "php://input" ) ) );
		
		$cmd = $this->GetCommand();
		require_once "Logic/$cmd.php";
		$functionName = "return Handle_$cmd();";
		return eval( $functionName );		
	}
	
	///////////////////////////////////////////////////////////////////////////////
	/// @brief HTTP 관련 함수
	/// @author justin
	/// @date 2013. 8. 28. 오후 9:46:25
	///////////////////////////////////////////////////////////////////////////////	
	
	public function RequestHTTPByPOST( $url, $body, $timeout = 30 )
	{
		$params = json_encode( $body );
		
		$ch = curl_init();
		curl_setopt( $ch, CURLOPT_URL, $url );
		curl_setopt( $ch, CURLOPT_POST, 1 );
		curl_setopt( $ch, CURLOPT_POSTFIELDS, $params );
		curl_setopt( $ch, CURLOPT_RETURNTRANSFER, true );
		
		if ($timeout > 0) {
			curl_setopt( $ch, CURLOPT_CONNECTTIMEOUT, $timeout );
			curl_setopt( $ch, CURLOPT_TIMEOUT, $timeout );
		}
		
		$result = curl_exec( $ch );
		
		$errNo = curl_errno( $ch );
		$this->SetLastHttpErrorCode( $errNo );
		
		$errMsg = curl_error( $ch );
		$this->SetLastHttpErrorMsg( $errMsg );		
		
		$httpcode = curl_getinfo( $ch, CURLINFO_HTTP_CODE );
		$this->SetLastHttpCodeFromCallUrl( $httpcode );
		
		curl_close( $ch );
		
		$result = json_decode( $result, true );
				
		return $result;		
	}
	
	public function SetLastHttpErrorCode( $errorCode )
	{
		$this->_httpErrorCode = $errorCode;
	}
	
	public function GetLastHttpErrorCode()
	{
		return $this->_httpErrorCode;
	}
	
	public function SetLastHttpErrorMsg( $errorMsg )
	{
		$this->_httpErrorMsg = $errorMsg;
	}
	
	public function GetLastHttpErrorMsg()
	{
		return $this->_httpErrorMsg;
	}	
	
	public function SetLastHttpCodeFromCallUrl( $errorCode )
	{
		$this->_httpErrorCodeFromCallUrl = $errorCode;
	}
	
	public function GetLastHttpCodeFromCallUrl()
	{
		return $this->_httpErrorCodeFromCallUrl;
	}

	///////////////////////////////////////////////////////////////////////////////
	/// @brief TCP 관련 함수
	/// @author justin
	/// @date 2013. 8. 28. 오후 9:46:25
	///////////////////////////////////////////////////////////////////////////////
	
	public function ConnectTCP( $address, $port, $timeout )
	{
		if( null != $this->_socket ) {
			
			$this->CloseTCP();
		}
				
		$socket = socket_create( AF_INET, SOCK_STREAM, SOL_TCP );
		if( null == $socket) {
			
			$socketError = socket_last_error();
			$this->SetLastSocketErrorCode( $socketError );
			return false;
		}
		else {
			socket_set_option( $socket, SOL_SOCKET, SO_SNDTIMEO, $timeout );
			restore_error_handler();	//php socket 에러가 캐치가 안되서 한 꼼수
			$connected = @socket_connect( $socket, $address, $port );
			set_error_handler("g_ErrorHandler");		//php socket 에러가 캐치가 안되서 한 꼼수
			if( false == $connected ) {
					
				socket_close( $socket );
					
				$socketError = socket_last_error();
				$this->SetLastSocketErrorCode( $socketError );
					
				return false;
			}
		
			$this->_socket = $socket;
		}

		return true;
	}
	
	public function SendTCPPacket( $packet )
	{
		$sent = socket_write($this->_socket, $packet);
		if( false === $sent ) {
			
			$socketError = socket_last_error();
			$this->SetLastSocketErrorCode( $socketError );

			return false;
		}
				
		return true;
	}
	
	public function CloseTCP()
	{
		if ( null != $this->_socket ) {
			socket_close( $this->_socket );
			$this->_socket = null;
		}
	}
	
	public function SetLastSocketErrorCode( $errorCode )
	{
		$this->_socketErrorCode = $errorCode;
	}
	
	public function GetLastSocketErrorCode()
	{
		return $this->_socketErrorCode;
	}
	
	public function GetLastSocketErrorMessage()
	{
		$errorCode = $this->GetLastSocketErrorCode();
		if( 0 >= $errorCode)
			return '';
		
		return socket_strerror( $errorCode );
	}
}

?>