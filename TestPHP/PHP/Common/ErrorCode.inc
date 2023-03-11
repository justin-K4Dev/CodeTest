<?php

//////////////////////////////////////////////////////////////////////////////
/// @file ErrorCode.php
/// @title User Error constants 정의
/// @brief
///
/// @author justin
/// @date 2013. 11. 6. 오후 6:32:34
///////////////////////////////////////////////////////////////////////////////
	
class ERROR_CODE
{
	const SUCCESS = 0;
	
	// base system error 1 ~ 1000
	const RUNTIME_ERROR = 500;	//PHP 런타임 에러 발생시
	const DB_INFO_NOT_FOUND = 1;
	const DB_CONNECT_FAILURE = 2;
	const DB_QUERY_FAILURE = 3;
	const DB_CLUSTER_HASH_ERROR = 4;
	const DB_INSERT_ERROR = 5;
	const DB_INCREASE_ERROR = 6;
	const DB_UPDATE_ERROR = 7;
	const DB_REMOVE_ERROR = 8;
	const LOCK_FAILURE = 10;
	const MC_CONNECT_FAILURE = 11;
	const DATA_CONVERT_ERROR = 12;
	const INVALID_SIGNATURE = 13;
	const HTTP_ERROR = 14;
	const INVALID_COMMAND = 15;
	const NOT_FOUND_TEMPLATE = 16;
	const JSON_NOT_EXIST_STATUS = 17;
}

?>
