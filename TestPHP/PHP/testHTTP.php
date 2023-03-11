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

function SendByGET_1( $url, $timeOut = 30 ) {
	
	Echo __FUNCTION__.'<br>';

	$ch = curl_init();
	$opts[CURLOPT_URL] = $url;
	$opts[CURLOPT_RETURNTRANSFER] = true;

	if ($timeOut > 0) {
		$opts[CURLOPT_TIMEOUT] = $timeOut;
	}

	curl_setopt_array($ch, $opts);
	$result = curl_exec($ch);

	$httpcode = curl_getinfo($ch, CURLINFO_HTTP_CODE);

	SetLastCallURLHttpCode($httpcode);
	curl_close($ch);

	return $result;
}

function SendByPOST_1( $url, $body, $timeOut = 30 ) {
	
	Echo __FUNCTION__.'<br>';
	
	$params = json_encode( $body );
	
	$ch = curl_init();
	curl_setopt($ch, CURLOPT_URL, $url);
	curl_setopt($ch, CURLOPT_POST, 1);
	curl_setopt($ch, CURLOPT_POSTFIELDS, $params);
		
	if ($timeOut > 0) {
		curl_setopt($ch, CURLOPT_TIMEOUT, $timeOut);		
	}	
	
	$result = curl_exec($ch);
	curl_close($ch);
	
	$httpcode = curl_getinfo($ch, CURLINFO_HTTP_CODE);
	SetLastCallURLHttpCode($httpcode);	
	
	$result = json_decode( $result );
	
	return $result;
}

function SendByGET_2( $url, $opt ) {

	Echo __FUNCTION__.'<br>';
	
	$r = new HttpRequest( $url, HttpRequest::METH_GET );
	
	try {
		
    	$r->send();
    	
    	if ($r->getResponseCode() == 200) {
    		$errMsg = sprintf( 'Error HTTP GET Method !!! - ErrorCode:%s, Body:%s',
    				           $r->getResponseCode(), $r->getResponseBody() );
    		var_dump( $errMsg );
    		
    		return $r->getResponseCode();
    	}
	} 
	catch ( HttpException $ex ) {
    	echo $ex;
	}
}

function SendByPOST_2( $url, $opt, $body ) {

	Echo __FUNCTION__.'<br>';
	
	$result;
	
	$r = new HttpRequest( $url, HttpRequest::METH_POST );
	$r->setOptions( $opt );
	$r->addPostFields( $body );
	
	try {
		
	    $r->send();
	    
	    if ($r->getResponseCode() == 200) {
	    	$errMsg = sprintf( 'Error HTTP POST Method !!! - ErrorCode:%s, Body:%s',
	    			$r->getResponseCode(), $r->getResponseBody() );
	    	var_dump( $errMsg );
	    	
	    	$result['result'] = $r->getResponseCode();
	    	return;
	    }
	    	    
	} catch (HttpException $ex) {
	    echo $ex;
	}
	
	$result = $r->getResponseBody();
	
	return $result;
}


try {

	$uri = sprintf( '/1.0/checkauth/test?qid=%s', 10000000000 );
	$url = 'http://beta-ab.weme.wemade.com:10080'.$uri;
	$body = array ( "gameId" => "201133",      	// 문자열로된 게임코드
					"testUserId" => "test001",
					"accessToken" => "test001"	// test api 는 userId 와 accessToken 이 같으면 성공 다르면 실패
	);
	
	var_dump( $url );
	var_dump( $body );
	
	$result = SendByGET_1( $url );
	var_dump( $result );
	if( null == $result || false == isset($result['result']) || 0 != $result['result'] ) {
		$httpCode = GetLastCallURLHttpCode();
		$errMsg = sprintf( 'Error HTTP GET Method !!! - ErrorCode:%s', $httpCode );
		var_dump( $errMsg );
	}
/*	
	$result = SendByPOST_1( $url, json_encode( $body ) );
	var_dump( $result );
	if( null == $result || false == isset($result['result']) || 0 != $result['result'] ) {
		$httpCode = GetLastCallURLHttpCode();
		$errMsg = sprintf( 'Error HTTP POST Method !!! - ErrorCode:%s', $httpCode );
		var_dump( $errMsg );
	}
*/	
//	$opt = array( 'timeout' => 30 );
//	SendByGET_2( $url, $opt );
	
//	$opt = array( 'timeout' => 30 );
//	SendByPOST_2( $url, $opt, json_encode( $body ) );
	
} catch (Exception $e) {

	echo "Excepted HTTP !!!";
	echo "<br>";
	var_dump( Utility::GetExceptionDataString( $e ) );
}

?>
