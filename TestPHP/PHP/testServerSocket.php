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

include_once 'Lib/Utility.php';

echo "<h2>TCP/IP Server</h2>\n";

define("_IP",    "192.168.1.10");
define("_PORT",  "20000");

try {
	
	/* Allow the script to hang around waiting for connections. */
	set_time_limit(0);
	
	/* Turn on implicit output flushing so we see what we're getting
	 * as it comes in. */
	ob_implicit_flush();
	
	if (($sock = socket_create(AF_INET, SOCK_STREAM, SOL_TCP)) === false) {
	    echo "socket_create() failed: reason: " . socket_strerror(socket_last_error()) . "\n";
	}
	
	if (socket_bind($sock, _IP, _PORT) === false) {
	    echo "socket_bind() failed: reason: " . socket_strerror(socket_last_error($sock)) . "\n";
	}
	
	if (socket_listen($sock, 5) === false) {
	    echo "socket_listen() failed: reason: " . socket_strerror(socket_last_error($sock)) . "\n";
	}
	
	do {
	    if (($msgsock = socket_accept($sock)) === false) {
	        echo "socket_accept() failed: reason: " . socket_strerror(socket_last_error($sock)) . "\n";
	        break;
	    }
	    /* Send instructions. */
	    $msg = "\nWelcome to the PHP Test Server. \n" .
	        "To quit, type 'quit'. To shut down the server type 'shutdown'.\n";
	    socket_write($msgsock, $msg, strlen($msg));
	
	    do {
	        if (false === ($buf = socket_read($msgsock, 2048, PHP_NORMAL_READ))) {
	            echo "socket_read() failed: reason: " . socket_strerror(socket_last_error($msgsock)) . "\n";
	            break 2;
	        }
	        if (!$buf = trim($buf)) {
	            continue;
	        }
	        if ($buf == 'quit') {
	            break;
	        }
	        if ($buf == 'shutdown') {
	            socket_close($msgsock);
	            break 2;
	        }
	        $talkback = "PHP: You said '$buf'.\n";
	        socket_write($msgsock, $talkback, strlen($talkback));
	        echo "$buf\n";
	    } while (true);
	    socket_close($msgsock);
	} while (true);

	socket_close($sock);
} 
catch (Exception $e) {
	
	echo "Excepted Remote File !!!";
	echo "<br>";
	var_dump( Utility::GetExceptionDataString( $e ) );
}	

?>