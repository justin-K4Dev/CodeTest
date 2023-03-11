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

try {

	// Getting the title of a remote page
	// For example, you can use code below to to open a file from a remote web server and extract title of the page.

	$file = fopen('http://192.168.1.10:8080/PHP/Common/Remote.inc', 'r');
	if (!$file) {
    	echo '<p>Unable to open remote file.\n';
    	exit;
	}
	while (!feof ($file)) {
    	$line = fgets ($file, 1024);
    	
    	print_r($line);
 	}
	
	fclose($file);
	
	echo '<br>';
	
	// Reading the contents of a remote file
	// fread function can be used to read content of remote file.
	// This is shown in example below.
	// You should collect the data together in chunks as shown in the example below
	// because reading will stop after a packet is available.
	
	$handle = fopen('http://192.168.1.10:8080/PHP/Common/Remote.inc', 'rb');
	$contents = '';
	while (!feof($handle)) {
		$contents .= fread($handle, 8192);

		print_r($contents);		
	}
	
	fclose($handle);
	
	echo '<br>';
	
	// reading the contents of a file into array
	// file function returns the file in an array.
	// Each element of the array corresponds to a line in the file,
	// with the newline still attached.
	// Each line in the resulting array will include the line ending,
	// so you still need to use rtrim() if you do not want the line ending present.
	
	// Get a file into an array.  In this example we’ll go through HTTP to get
	// the HTML source of a URL.
	$lines = file('http://192.168.1.10:8080/PHP/Config/Remote.inc');
	
	// Loop through our array, show HTML source as HTML source; and line numbers too.
	foreach ($lines as $line_num => $line) {
		echo "Line #<b>{$line_num}</b> : " . htmlspecialchars($line) . "<br/>\n";	
	}
	
	echo '<br>';	
	
	// reading the contents of a file into a string
	// file_get_contents() returns the file in a string.
	// This is the preferred way to read the contents of a file into a string.
	// It will use memory mapping techniques if supported by your OS to enhance performance.
	
	$content_string = file_get_contents('http://192.168.1.10:8080/PHP/Common/Remote.inc');
	print_r($content_string);
	
	echo '<br>';	
	
	// Storing data on a remote server
	// You can also write to files on an FTP server (provided that you have connected as a user with the correct access rights).
	// You can only create new files using this method; if you try to overwrite a file that already exists, the fopen() call will fail.
	// You need to specify the username and password within the URL, such as ‘ftp://user:password@ftp.example.com/path/to/file’.

	$file = fopen ("ftp://ftp-user:ftp-user@192.168.1.10/Remote.inc", "wa");
	if (!$file) {
		echo "<p>Unable to open remote file for writing.\n";
		exit;
	}
	/* Write the data here. */
	fwrite ($file, $_SERVER['HTTP_USER_AGENT'] . "\n");
	fclose ($file);
	
	print_r($_SERVER['HTTP_USER_AGENT']);	
	
	
} catch (Exception $e) {

	echo "Excepted Remote File !!!";
	echo "<br>";
	var_dump( Utility::GetExceptionDataString( $e ) );
}

?>

    
    
    
		
   
    
