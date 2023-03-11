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

require_once 'Predis/Autoloader.php';
Predis\Autoloader::register();

try {

	// Parameters require one master node specifically marked with `alias=master`.
	$parameters = ['tcp://192.168.1.111?alias=master&password=kang14', 'tcp://192.168.1.112?alias=slave-01&password=kang14'];
	$options    = ['replication' => true];

	$client = new Predis\Client( $parameters, $options );

	// Read operation.
	$exists = $client->exists('foo') ? 'yes' : 'no';
	$current = $client->getConnection()->getCurrent()->getParameters();
	echo "Read !!! - Does 'foo' exist on {$current->alias} ? $exists.";
	echo "<br>";
	
	// Write operation.
	$client->set('foo', 'bar');
	$current = $client->getConnection()->getCurrent()->getParameters();
	echo "Write !!! - Now 'foo' has been set to 'bar' on {$current->alias}!";
	echo "<br>";
	
	// Read operation.
	$bar = $client->get('foo');
	$current = $client->getConnection()->getCurrent()->getParameters();
	echo "Read !!! - We fetched 'foo' from {$current->alias} and its value is '$bar'.";
	echo "<br>";

	/*
		OUTPUT:
		Does 'foo' exist on slave? yes.
		Now 'foo' has been set to 'bar' on master!
		We fetched 'foo' from master and its value is 'bar'.
	*/
			
} catch (Exception $e) {

	echo "Excepted Predis !!!";
	echo "<br>";
	var_dump( Utility::GetExceptionDataString( $e ) );
}

?>
