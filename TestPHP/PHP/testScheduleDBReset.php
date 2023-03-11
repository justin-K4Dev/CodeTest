<?php

// set error report
error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);

// set locale
setlocale(LC_CTYPE, 'ko_KR.UTF-8');

$now = date('Y-m-d H:i:s', time());
echo "Update Date : $now";
echo "<br>";

include_once 'Lib/Utility.php';
include_once 'Lib/Memcached.php';
include_once 'Lib/Redis.php';


try {
	
	$port_1 = 6379;
	$port_2 = 6380;

	$memcache = new Memcached;
	$memcache->addServer( "127.0.0.1", 11211 );
	
	$activePort = 0;
	$currPort = $memcache->get( 'primary' );
	if( $currPort == $port_1 ) {
		$activePort = $port_2;
	}
	else {
		$activePort = $port_1;
	}
	$memcache->set( 'primary', $activePort );

	$rdsClient = new Predis \ Client(array (
			'host' => '127.0.0.1'
		,	'port' => $currPort
	));
	$rdsClient->flushdb();

	$rdsClient = new Predis \ Client(array (
			'host' => '127.0.0.1'
		,	'port' => $activePort
	));
	$rdsClient->Set( "myport", $activePort );

} catch (Exception $e) {

	echo "Excepted Process Start !!!";
	echo "<br>";
	var_dump( Utility::GetExceptionDataString( $e ) );
}

?>
