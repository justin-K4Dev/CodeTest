<?php

require_once 'Lib/BitwiseFlag.php';
require_once 'Lib/Network.php';

// 로그 레벨 구분(BitFlag 체크를 위한 값 셋팅필요!) 
class LOG_LEVEL
{
	const DEBUG = 1;
	const INFO = 2;
	const WARN = 4;
	const ERROR = 8;
	const FATAL = 16;
	const EXCEPTION = 32;
}

// Log level 문자열 구분
class LOG_LEVEL_STRING
{
	static public $g_LogLevelStringList = array ( LOG_LEVEL::DEBUG => "DEBUG"
												, LOG_LEVEL::INFO => "INFO"
												, LOG_LEVEL::WARN => "WARN"
												, LOG_LEVEL::ERROR => "ERROR"
												, LOG_LEVEL::FATAL => "FATAL"
												, LOG_LEVEL::EXCEPTION => "EXCEPTION" );
}

// Lib log 구분
class LIB_LOG_TYPE
{
	const NETWORK = "NETWORK"; //Network
	const DATABASE = "DATABASE"; //Database
}


// Lib error 구분 
class LIB_ERROR_CODE
{
	const ERROR = 400; //Lib 오류
}

function g_GetLog()
{
	global $g_Log;
	if ($g_Log == null) {
		$g_Log = new Log();
	}

	($g_Log instanceof Log);

	return $g_Log;
}

class Log
{
	protected $_levelFlags;
	protected $_typeList;
	protected $_userNoList;
	
	function __construct() {
	
		$this->_logOutPath = '';
		$this->_levelFlags = new BitwiseFlag;
		$this->_typeList = array();
		$this->_userNoList = array();		
	}

	public function Configure( $logOutPath, $levelFlagList, $typeList, $userNoList )
	{
		$this->_logOutPath = $logOutPath;
		
		foreach ( $levelFlagList as $v ) {		
			$this->_levelFlags->SetFlag( $v, true );
		}

		$this->_typeList = $typeList;		
		$this->_userNoList = $userNoList;		
	}

	public function Write( $logLevel, $logType, $errCode, $logMsg )
	{		
		if( $this->_levelFlags->IsFlag( $logLevel ) != true ) {
			return;
		}

		if ( count( $this->_typeList ) > 0 ) {
			if( in_array( $logType, $this->_typeList ) != true ) {
				return;
			}
		}

		if ( count( $this->_userNoList ) > 0 ) {
			if( in_array( $userNo, $this->_userNoList ) != true ) {
				return;
			}
		}

		/// @brief 디버그 추적 로그메세지 작성 - giman 2014. 2. 6. 오후 5:00:34
		$dbgtrace = debug_backtrace(DEBUG_BACKTRACE_IGNORE_ARGS, 1);
		$file = "";
		$line = "";
		if( isset($dbgtrace[0]) == true )
		{
			$file = $dbgtrace[0]['file'];
			$line = $dbgtrace[0]['line'];
		}
		
		$userNoForLog = g_GetNetwork()->GetValue(g_GetNetwork()->GetUserNoKey());
	    $logData = sprintf( "%s\t%s\t%s\t%s\t%s(%s)\t%s\n",
		                    date("Y-m-d H:i:s", time()), $errCode, $_SERVER["REMOTE_ADDR"], $userNoForLog, $file, $line, $logMsg );
	    
		$date = date("Ymd", time());
		$logLevelStr = LOG_LEVEL_STRING::$g_LogLevelStringList[$logLevel];
		$filename = "log_{$logLevelStr}_{$logType}_{$date}.txt";
		file_put_contents($this->_logOutPath.$filename, $logData, FILE_APPEND);
	}
}

