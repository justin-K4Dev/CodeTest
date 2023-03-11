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

/*
    memcached web site list
   
	http://memcached.org/
	http://libevent.org/

*/

require_once 'Lib/SmartLock.php';


function g_TestFunction()
{
	SmartLock( 1, 100 );
}

g_TestFunction();
	
?>

