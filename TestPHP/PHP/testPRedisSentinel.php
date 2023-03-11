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

require_once 'Lib/Utility.php';
require_once 'Lib/SentinelBackedReplication.php';

/**
 * This is a temporary development test script used in Sentinel support development
 */
 
try {

	$sentinelConnections = array( 'tcp://192.168.1.110:26379' );

	$sentinel = new SentinelBackedReplication( $sentinelConnections, 'rds1Master', 'kang14' );
	$client = new Predis\Client($sentinel);
	
	echo "Slave: " .  $client->get('test') . "<br>";
	$client->set('test',time());
	echo "Master: " .  $client->get('test') . "<br>";
	echo "Slave: " .  $client->get('test') . "<br>";
	
} catch (Exception $e) {

	echo "Excepted Predis !!!";
	echo "<br>";
	var_dump( Utility::GetExceptionDataString( $e ) );
}

?>