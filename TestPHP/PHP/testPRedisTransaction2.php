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
	redis web site list
	
	http://www.redis.io/commands#generic
	http://minq.github.com/blog/2012/10/28/redis-commands/
	http://phpmaster.com/an-introduction-to-redis-in-php-using-predis/
	http://kerocat.tistory.com/1
*/

include_once 'Lib/Utility.php';

require_once 'Predis/Autoloader.php';
Predis\Autoloader::register();

try {

		$redis = new Predis\Client(array (
			'host' => '127.0.0.1'
		));
												
				
	    // WATCH key [key ...]

		echo "Transaction Start" . "<br>";

//		var_dump( $redis->watch( 1 ) );

		while ( true ) {

			echo "1 Key Member List ~" . "<br>";

			$result = $redis->smembers( 1 );
			$redis->srem( 1, $result[0] );
			$value = ((int) $result[0]) + 1;

			$redis->sadd( 1, array( $value ) );

			var_dump( $redis->smembers( 1 ) );

			sleep( 1 );
		}
			
} catch (Exception $e) {

	echo "Excepted Predis !!!";
	echo "<br>";
	var_dump( Utility::GetExceptionDataString( $e ) );
}

?>
