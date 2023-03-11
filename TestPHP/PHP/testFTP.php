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


/*
try {

	$ftp_server = "192.168.1.10";
	$ftp_user = "ftp-user";
	$ftp_pass = "ftp-user";

	// Connect to firewall
	$conn_id = ftp_connect($ftp_server, 21) or die("Couldn't connect to $ftp_server");

	// Open a session to an external ftp site
	 $login_result = ftp_login ($conn_id, $ftp_user, $ftp_pass); 

	// Check open
	 if ((!$conn_id) || (!$login_result)) { 
			echo "Ftp-connect failed!"; die; 
		} else {
			 echo "Connected.";
		 }
	 
	// turn on passive mode transfers
	 ftp_pasv ($conn_id, true) ;
*/

/*
try {

	$ftp_server = "192.168.1.10";
	$ftp_user = "ftp-user";
	$ftp_pass = "ftp-user";

	$connection = ssh2_connect( $ftp_server, 22 );

	ssh2_auth_password( $connection, $ftp_user, $ftp_pass );

	$sftp = ssh2_sftp( $connection );

	$stream = fopen( "ssh2.sftp://$sftp/home/ftp-user/UploadFile.txt", 'wb' );
	if ( null != $stream ) {
		
		$uploadImage = 'example contents';
		fwrite( $stream, $uploadImage, strlen( $uploadImage ) );
		fclose( $stream );

		echo "Success write file by FTP !!! <br>";
	}

	if ( true == unlink( "ssh2.sftp://$sftp/home/ftp-user/UploadFile.txt" ) ) {
		echo "Success delete file by FTP !!! <br>";
	}
*/

try {
	
	$ftp_server = "192.168.1.10";
	$ftp_user = "ftp-user";
	$ftp_pass = "ftp-user";	
	
	// The path to the FTP file, including login arguments
	$ftp_path = "ftp://$ftp_user:$ftp_pass@$ftp_server/UploadFile.txt";
 
	// Allows overwriting of existing files on the remote FTP server
	$stream_options = array('ftp' => array('overwrite' => true));
 
	// Creates a stream context resource with the defined options
	$stream_context = stream_context_create( $stream_options );
 
	// Opens the file for writing and truncates it to zero length 
	$fh = fopen( $ftp_path, 'wb', 0, $stream_context );
	if ( null != $fh ) {

		// Writes contents to the file
		fputs($fh, 'example contents');
     
		// Closes the file handle
		fclose($fh);

		echo "Success FTP !!!";	
	}
	else {
		die('Could not open file.');
	}

} catch (Exception $e) {

	echo "Excepted FTP !!!";
	echo "<br>";
	var_dump( Utility::GetExceptionDataString( $e ) );
}

?>
