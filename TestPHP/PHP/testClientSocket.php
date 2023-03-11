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

?>

<br><br>

<?php

require_once 'Lib/Utility.php';

echo "<h2>TCP/IP Client</h2>\n";

define("_IP",    "192.168.1.10");
define("_PORT",  "20000");


try {
	/* Create a TCP/IP socket. */
	$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
	if ($socket === false) {
	    echo "socket_create() failed: reason: " . socket_strerror(socket_last_error()) . "\n";
	}
	else {
	    echo "OK.\n";
	}
	
	echo "Attempting to connect to " . _IP . " on port " . _PORT;
	$result = socket_connect($socket, _IP, _PORT);
	if ($result === false) {
	    echo "socket_connect() failed.\nReason: ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
	}
	else {
	    echo "OK.\n";
	}
	
	$in = "Request Echo Message !!!";
	$out = '';
	
	socket_write($socket, $in, strlen($in));
	echo "OK.\n";
	
	echo "Reading response:\n\n";
	while ($out = socket_read($socket, 2048)) {
	    echo $out;
	}
	
	echo "Closing socket...";
	socket_close($socket);
	echo "OK.\n\n";
} 
catch (Exception $e) {	
	echo "Excepted Remote File !!!";
	echo "<br>";
	var_dump( Utility::GetExceptionDataString( $e ) );
}

?>