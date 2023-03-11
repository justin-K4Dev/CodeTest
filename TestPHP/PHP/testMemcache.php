<?php session_start(); ?>
<pre>

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


    $presessdata = @$_SESSION["data"];
	$_SESSION["data"] = @$_SESSION["data"] + 1;
	print_r($_SESSION);
	
	$memcache = new Memcache;
	$memcache->connect("127.0.0.1", 11211);
	print_r($memcache->getStats());
	$items = array('key1' => 'value1',
                   'key2' => 'value2',    
                   'key3' => 'value3');

	foreach ($items as $k => $v) {    
    	$memcache->set($k, $v);
	}

	var_dump($memcache->get(array('key1', 'key3')));
	var_dump($memcache->get('key2'));
	var_dump($memcache->get('key4'));
?>

	SESSION: <?php echo $_SESSION["data"]; 

?>
