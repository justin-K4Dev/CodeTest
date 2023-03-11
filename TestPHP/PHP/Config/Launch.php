<?php

///////////////////////////////////////////////////////////////////////////////
/// @file Launch.php
/// @title 서버 런칭 버전 정보
/// @brief
///
/// @author justin
/// @date 2013. 8. 27. 오후 6:29:34
///////////////////////////////////////////////////////////////////////////////

// 서버 버전 종류 구분
class SERVER_VERSION_TYPE
{
	const BETA = 'Beta';
	const REAL = 'Real';
	const REVIEW = 'Review';
}

class LAUNCH
{
	const VERSION = SERVER_VERSION_TYPE::BETA;

	const ADMIN_VERSION = '20140219.0.0.0'; // 운영 시스템 버전
	const GAME_SERVER_VERSION = 2014010901;	// 게임 서버 버젼
}


///////////////////////////////////////////////////////////////////////////////
/// @file Launch.php
/// @title 주요 서버 접속 정보 기록
/// @brief
///
/// @author justin
/// @date 2013. 8. 27. 오후 6:29:34
///////////////////////////////////////////////////////////////////////////////

class CONNECTION_STRING
{
	const MG_DB_ID = '';
	const MG_DB_PW = '';
	
	const PAYMENT_DB_ADDR = '127.0.0.1';
	const PAYMENT_DB_ID = 'root';
	const PAYMENT_DB_PW = 'gimanokok';
	
	const GAME_MANAGEMENT_DB_ADDR = '127.0.0.1';
	const GAME_MANAGEMENT_DB_ID = 'root';
	const GAME_MANAGEMENT_DB_PW = 'gimanokok';	

	const GAME_PROXY_SERVER_URL = 'http://172.20.9.64:20000/GameProxy.php';				//	운영 프록시 서버 URL
	
	const WEMADE_LOG_RECEIVER_IP = '172.20.56.34'; //'10.10.5.41';
	const WEMADE_LOG_RECEIVER_PORT = 10014;
	const WEMADE_LOG_RECEIVER_BILLING_IP = '10.10.5.41';
	const WEMADE_LOG_RECEIVER_BILLING_PORT = 20000;
		
	const SVN_USERNAME = 'giman';
	const SVN_PASSWORD = 'gimanokok';

	const MG_LOG_DB_HOST = "mongodb://192.168.56.101:27017";
}


class SERVER_LIST {
	
	// Game Template 서버 목록
	static public $g_GameTemplateServerList = array(
			'127.0.0.1:3306',
	);
	
	// Memcache 서버 목록
	static public $g_MCServerList = array(
			'127.0.0.1',
	);
	
	// Game DB 서버 목록
	static public $g_MGDBServerList = array(
			'127.0.0.1:40000',
			'127.0.0.1:40001',
	);
	
	// Admin DB 서버 목록
	static public $g_AdminDBServerList = array(
			
			'default' => array(),
			
			'AdminAccount' => array(
					'db'		=> 'AdminAccount',
					'master'	=> '192.168.56.101:3306',
					'slave'		=> '192.168.56.101:3306',
					'standby'	=> '192.168.56.101:3306',
					'user'		=> 'root',
					'pass'		=> 'hapi0328',
			),

	);	
}
?>