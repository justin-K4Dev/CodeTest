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
require_once 'testClass.php';
*/


$ttype = 'GENERAL';
$buf;
$buf[$ttype][] = array('name' => 'a', 'value' => 'b', 'desc' => 'c');
$buf[$ttype][] = array('name' => 1, 'value' => 2, 'desc' => 3);

var_dump($buf);



/*
$data = "";

if ( true == isset( $data ) )
	print( "Set value" );
else
	print( "Not set value" );
*/


/*
$filename = 'ssh2.sftp://Resource id #27/wemade/service/www/WeMe/img/13_1.jpg';


$posStart = strrpos( $filename, '/' ) + 1;
$posEnd = strlen( $filename );

$filename = substr( $filename, $posStart, $posEnd - $posStart );
var_dump( $filename );

$posStart = strrpos( $filename, '_' ) + 1;
$posEnd = strrpos( $filename, '.' );
$count = substr( $filename, $posStart, $posEnd - $posStart );
$count = (int) $count + 1;
var_dump( $count );
*/

/*
const DATA = "abcd";

$data = DATA."ef";

$dataList[] = array ( DATA."ef" );
$dataList[] = array ( DATA."ef" );


var_dump($dataList);
*/

/*
const A = 'a';

$data['a'] = 100;
$data['b'] = 200;

$dataList = array( DATA."$data[a]" );

var_dump($dataList);
*/

// var_dump( (int) microtime( true ) );

/*
class Object
{

static public $g_dataList = array( "A" => array( "1,1,1,1", "2,2,2,2" ), 
                                   "B" => array( "3,3,3,3" ),
                                 );

	const _1 = 100;	
}

var_dump( Object::$g_dataList );
var_dump( count( Object::$g_dataList ) );

$value = 0.1;

var_dump( $value );
*/

/*
	$array = array( "1" => 10 );
	
	if ( $array === true )
		print ( "true" );
	else if ( $array === false )
		print ( "false" );
	else
		print ( "array" );
*/		

/*
	try {
	
	var_dump( g_GetNetwork()->GetCOMMAND() );
	echo "<br>";
	var_dump( g_GetNetwork()->GetCOMMAND() );
		
	}
	catch (Exception $e) {

		echo "Excepted Function !!!";
		echo "<br>";
		echo $e->getMessage();
	}	
*/


function Data2Arr($data, $sp=null, $kvsp=null)
{
    if ($data == null || strlen(trim($data)) == 0) {
        return array();
    }
    
    if ($sp == null) $sp = ',';
    if ($kvsp == null) $kvsp = ':';
    
	$datas = explode($sp, $data);
	$arr = array();
	foreach ($datas as $kv) {
		if (strpos($kv, $kvsp)) {
			list($k, $v) = explode($kvsp, $kv);
		}
		else {
		    LTLog()->Error(GetUserId(), ERR::MESSAGE, "Data2Arr Error($data)");
		    $k = $kv;
		    $v = 1;
		}
		$arr[trim($k)] = trim($v);
	}
	return $arr;
}

function CallProtocolHandler($cmd, $userID)
{
	$fileName = strtolower($cmd);
	$path = "../logic/$fileName.php";
	
	$functionName = "Handle_$cmd()";
	
	$result = array ( $path, $functionName );					
	return $result;
}

/*	
	try {
	
		var_dump( CallProtocolHandler( "Login_List", "ID" ) );
		
	}
	catch (Exception $e) {

		echo "Excepted Predis !!!";
		echo "<br>";
		echo $e->getMessage();
	}	
*/
/*
	$params = 'email=u4us72@gmail.com,deviceInfo=andrioid,marketKind=5,amount=10,productID=cp_gold_1000,productName=1000?꾩렮維쀯옙占퐌ayTool=2,packageName=?꾩렮維쀯옙源띿삕?좑옙000)';
	
	$datas = array();
	$datas = Data2Arr($params, null, '=');
	
	var_dump($datas);
*/

class MESSAGE_ID
{	
	const MEMBER_SIGN_UP = "MEMBER_SIGN_UP";
	
}

class MESSAGE_STRING
{
	static public $MEMBER_SIGN_UP = array( MESSAGE_ID::MEMBER_SIGN_UP => "테스트 메시지 !!!" );
}

//	var_dump( MESSAGE_STRING::$MEMBER_SIGN_UP[MESSAGE_ID::MEMBER_SIGN_UP] );


?>
