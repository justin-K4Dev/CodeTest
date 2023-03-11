<?php
 
require_once 'Config/Launch.php';
require_once 'Lib/Log.php';


// 게임 서버 접속 정보 설정

class CONFIG
{
	static public $g_ClientVersionPatchURLList = array(  /// @brief 우선 임시로 넣어둠 !!! 테스트시 김동춘 기술PM 에게 정식 URL 받아야 됨 !!! - justin 2013. 8. 22. 오후 2:05:12
													  SERVER_VERSION_TYPE::BETA => 'http://we-mclient.gscdn.com/wesports/download.html'
													, SERVER_VERSION_TYPE::REAL => 'http://we-mclient.gscdn.com/wesports/download.html'
													, SERVER_VERSION_TYPE::REVIEW => 'http://we-mclient.gscdn.com/wesports/download.html'
											);	

    const UIDMOD = 10; // Manual Shard Key 를 생성을 위한 MOD 연산값 ( 10개 이하의 Shard 구성 설정값 )
      
    // Player DB 접속 & 계정 정보
    const MG_DB_ID = CONNECTION_STRING::MG_DB_ID;
    const MG_DB_PW = CONNECTION_STRING::MG_DB_PW;
    const MONGOS_YN = 'Y';
    const MG_DB_NAME = "WeSports";    
	    
    /// 결제 기록 DB 정보
    const PAYMENT_DB_ADDR = CONNECTION_STRING::PAYMENT_DB_ADDR; 
    const PAYMENT_DB_ID = CONNECTION_STRING::PAYMENT_DB_ID;
    const PAYMENT_DB_PW = CONNECTION_STRING::PAYMENT_DB_PW;
    const PAYMENT_DB_NAME = 'Payment';
    
    /// 게임 관리 DB 정보
    const GAME_MANAGEMENT_DB_ADDR = CONNECTION_STRING::GAME_MANAGEMENT_DB_ADDR;
    const GAME_MANAGEMENT_DB_ID = CONNECTION_STRING::GAME_MANAGEMENT_DB_ID;
    const GAME_MANAGEMENT_DB_PW = CONNECTION_STRING::GAME_MANAGEMENT_DB_PW;
    const GAME_MANAGEMENT_DB_NAME = 'GameManagement';
									
    // Log DB 접속 & 계정 정보
	const WEMADE_LOG_RECEIVER_IP = CONNECTION_STRING::WEMADE_LOG_RECEIVER_IP;
	const WEMADE_LOG_RECEIVER_PORT = CONNECTION_STRING::WEMADE_LOG_RECEIVER_PORT;
	const WEMADE_LOG_RECEIVER_BILLING_IP = CONNECTION_STRING::WEMADE_LOG_RECEIVER_BILLING_IP;
	const WEMADE_LOG_RECEIVER_BILLING_PORT = CONNECTION_STRING::WEMADE_LOG_RECEIVER_BILLING_PORT;
	const WEMADE_LOG_FILE_PATH = '/wemade/wemadelog/'; // chmod 777 - 파일 속성 지정
	
	// 게임 서버 로그 파일 작성 경로
    const LOG_PATH = '/myweb/log/'; // chmod 777 - 파일 속성 지정
}


class LOG_CONFIG {

	/// @author justin 2013. 11. 4. 오후 12:41:35
	/// @brief Log 설정 정보
	///

	static public $g_LogLevelFlagList = array( LOG_LEVEL::DEBUG, LOG_LEVEL::INFO, LOG_LEVEL::WARN, LOG_LEVEL::ERROR, LOG_LEVEL::FATAL, LOG_LEVEL::EXCEPTION );
	static public $g_LogTypeList = array();
	static public $g_UserNoList = array();
}
g_GetLog()->Configure( LOG_CONFIG::$g_LogLevelFlagList, LOG_CONFIG::$g_LogTypeList, LOG_CONFIG::$g_UserNoList );

?>