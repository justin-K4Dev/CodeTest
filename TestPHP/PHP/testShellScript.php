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



try {
	
	$command_capture = "cd /myweb/www/BASH";
    $command_capture2 = "./tcpdump.sh $capture_name $sleep";

    if (!($connection = ssh2_connect( "127.0.0.1", 22 ))) {
        echo "fail: unable to establish connection";
    } 

    if (!ssh2_auth_password($connection, "root", "kang14")) {
        echo "fail: unable to authenticate";
    }

    $stream = ssh2_shell($connection);

    fwrite($stream, $command_capture. PHP_EOL);
    sleep(1);
    fwrite($stream, $command_capture2 . PHP_EOL);
    sleep(5);
    
	$data="";
    while (true){
        $data .= stream_get_contents($stream);
        if (strpos($data,"XOXO") !== false) {
            echo "okay: command finished\n";
            break;
        }
    }
    echo $data;
    fclose($stream);

} catch (Exception $e) {

	echo "Excepted Shell Script !!!";
	echo "<br>";
	var_dump( Utility::GetExceptionDataString( $e ) );
}




?>