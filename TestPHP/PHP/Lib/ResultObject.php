<?php
///////////////////////////////////////////////////////////////////////////////
/// @file ResultObject.php
/// @title 성공실패여부, 메세지, 결과데이터를 담는 구조체 클래스
/// @brief 
/// 사용법
/*
public function IsLogined( )
{
	if ( null == $this->_account ) {
		return new ResultObject(
			false
			, ERROR_CODE::NOT_LOGINED_USER
			, "Not found userKey !!!"
		);
	}

	return new ResultObject(true, ERROR_CODE::SUCCESS);
}

$result = IsLogined();
if($result->DATA != true)
//if($result->ERROR_CODE != ERROR_CODE::SUCCESS)
{
	echo $result->MESSAGE;
	log($result->DATA);
	return;
}

*/
/// @author giman
/// @date 2014. 2. 5. 오후 2:45:28
///////////////////////////////////////////////////////////////////////////////
final class ResultObject
{
	private $_data;
	private $_errorCode;
	private $_message;
	
	function __construct($data, $err_code, $msg = '' )
	{
		$this->_data = $data;
		$this->_errorCode = $err_code;
		$this->_message = $msg;
	}
	
	function GetData()
	{
		return $this->_data;
	}
	
	function GetErrorCode()
	{
		return $this->_errorCode;
	}
	
	function GetMessage()
	{
		return $this->_message;
	}
}
