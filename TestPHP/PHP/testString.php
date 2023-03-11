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

$text = "\t\tThese are a few words :) ...  ";
$binary = "\x09Example string\x0A";
$hello  = "ConstantTemplate.xlsx";
var_dump($text, $binary, $hello);

echo '<br>';

$trimmed = rtrim($text);
var_dump($trimmed);

echo '<br>';

$trimmed = rtrim($text, " \t.");
var_dump($trimmed);

echo '<br>';

$trimmed = trim($hello, "Template.xlsx");
var_dump($trimmed);

echo '<br>';

// trim the ASCII control characters at the end of $binary
// (from 0 to 31 inclusive)
$clean = rtrim($binary, "\x00..\x1F");
var_dump($clean);

echo '<br>';

$pos = strpos( $hello, "Template.xlsx" );
var_dump($pos);

echo '<br>';

$len = strlen( $hello );
$cutLen = strlen( "Template.xlsx" );

$trimmed = substr($hello, 0, $len - $cutLen);
var_dump($trimmed);

echo '<br>';

$fileName = "?/?_filename.inc";
$fileName = str_replace( "?", "Common", $fileName );
var_dump($fileName);

echo '<br>';

$fileName = "Common/Common_filename.inc";
$fileName = str_replace( "Common/Common_filename.inc", "Common/", $fileName );
var_dump($fileName);

echo '<br>';

$vowels = array("a", "e", "i", "o", "u", "A", "E", "I", "O", "U");
$filterContents = str_replace($vowels, "", "Hello World of PHP");
var_dump($filterContents);

echo '<br>';

$fileName = "Common/Common_filename.inc";
$pos = strpos( $fileName, "/" );
var_dump($pos);

$len = strlen( $fileName );
var_dump($len);

$trimmed = substr( $fileName, 0, $len - ($len - $pos) + 1 );
var_dump( $trimmed );

echo '<br>';

$email = 'email@email.com';
$email_array = explode('@', $email);
var_dump( $email_array );


?>