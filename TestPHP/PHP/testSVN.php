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

define('TEMPLATE_DATA_SVN_PATH', 'svn://192.168.1.10/MyRepo/trunk/Template');

define('TEMPLATE_DATA_LOCAL_PATH', '/myweb/www/SVNWorking/Template/In/');
define('TEMPLATE_DATA_LOCAL_FILE_1', 'ConstantTemplate.xlsx');
define('TEMPLATE_DATA_LOCAL_FILE_2', 'ObjectTemplate.xlsx');
define('MIDDLE_PATH', 'Common/');
define('TEMPLATE_DATA_LOCAL_FILE_3', 'Template.txt');

try {
	
	// login SVN Server
	svn_auth_set_parameter(SVN_AUTH_PARAM_DEFAULT_USERNAME, 'justin');
	svn_auth_set_parameter(SVN_AUTH_PARAM_DEFAULT_PASSWORD, 'kang14');

	// ------------------------------------------------------------------------------------
	// by php-pecl api

	// checkout to TEMPLATE_DATA_LOCAL_PATH
	$ret = svn_checkout(TEMPLATE_DATA_SVN_PATH, TEMPLATE_DATA_LOCAL_PATH);
	var_dump($ret);
	echo '<br>';
	
	// update
	$ret = svn_update(TEMPLATE_DATA_LOCAL_PATH);
	var_dump($ret);
	echo '<br>';

	// cleanup
	$ret = svn_cleanup(TEMPLATE_DATA_LOCAL_PATH);
	var_dump($ret);
	echo '<br>';
	
	// TEMPLATE_DATA_LOCAL_FILE_1 check
	$ret = svn_log( TEMPLATE_DATA_LOCAL_PATH.TEMPLATE_DATA_LOCAL_FILE_1 );
	if( false == $ret ) {
		echo 'Failed to execute svn_log() function !!!';
		echo '<br>';

		// file svn add TEMPLATE_DATA_LOCAL_FILE_1
		$ret = svn_add( TEMPLATE_DATA_LOCAL_PATH.TEMPLATE_DATA_LOCAL_FILE_1 );
		var_dump($ret);
		echo '<br>';

		if( true == $ret ) {
			// commit
			$msg = "Commit delete for ".TEMPLATE_DATA_LOCAL_FILE_1." !!!";
			echo $msg.'<br>';
			$ret = svn_commit( $msg, TEMPLATE_DATA_LOCAL_PATH.TEMPLATE_DATA_LOCAL_FILE_1 );
			var_dump($ret);
			echo '<br>';
		}
	}
	else {
		var_dump($ret);
		echo '<br>';
	}

	// TEMPLATE_DATA_LOCAL_FILE_2 check
	$ret = svn_log( TEMPLATE_DATA_LOCAL_PATH.TEMPLATE_DATA_LOCAL_FILE_2 );
	if( false == $ret ) {
		echo 'Failed to execute svn_log() function !!!';
		echo '<br>';

		// file svn add TEMPLATE_DATA_LOCAL_FILE_2
		$ret = svn_add( TEMPLATE_DATA_LOCAL_PATH.TEMPLATE_DATA_LOCAL_FILE_2 );
		var_dump($ret);
		echo '<br>';

		if( true == $ret ) {
			// commit
			$msg = "Commit delete for ".TEMPLATE_DATA_LOCAL_FILE_2." !!!";
			echo $msg.'<br>';
			$ret = svn_commit( $msg, TEMPLATE_DATA_LOCAL_PATH.TEMPLATE_DATA_LOCAL_FILE_2 );
			var_dump($ret);
			echo '<br>';
		}
	}
	else {
		var_dump($ret);
		echo '<br>';
	}
	
	// cleanup
	$ret = svn_cleanup(TEMPLATE_DATA_LOCAL_PATH);
	var_dump($ret);
	echo '<br>';

	$ret = svn_log( TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH.TEMPLATE_DATA_LOCAL_FILE_3 );
	if( false != $ret ) {
		echo 'Failed to execute svn_log() function !!!';
		echo '<br>';
	}
	var_dump($ret);
	echo '<br>';
	
	// delete
	$ret = svn_delete( TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH.TEMPLATE_DATA_LOCAL_FILE_3 );
	var_dump($ret);
	echo '<br>';
	
	if( true == $ret ) {
		// commit
		$msg = "Commit delete for ".TEMPLATE_DATA_LOCAL_FILE_3." !!!";
		$ret = svn_commit( $msg, TEMPLATE_DATA_LOCAL_PATH );
		var_dump($ret);
		echo '<br>';	
	}
	
	// file 디렉토리 존재 체크 & 생성
	if( !is_dir( TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH ) ) {
		mkdir( TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH, 0777 );
		chkmod( TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH, 0777 );
		$ret = svn_add( TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH );
		if( false == $ret ) {
			echo "<font color=red><b>Failed to add to SVN Server !!! </b></font>"; echo '<br>';
			return;
		}		
	}	
	
	// file creation
	$file = fopen( TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH.TEMPLATE_DATA_LOCAL_FILE_3, "w" );
	if ( !$file ) {
		echo "<p>Unable to open remote file for writing.\n";
		exit;
	}
	
	// Write the data here
	fwrite( $file, 'Hello !!! Template ^^' );
	fclose( $file );
	chkmod( $file, 0777 );
	
	// file svn add
	$ret = svn_add( TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH.TEMPLATE_DATA_LOCAL_FILE_3 );
	var_dump($ret);
	echo '<br>';	
			
	// commit
	$msg = "Commit add for ".TEMPLATE_DATA_LOCAL_FILE_3." !!!";
	$ret = svn_commit($msg, TEMPLATE_DATA_LOCAL_PATH);
	var_dump($ret);
	echo '<br>';
	
	// cleanup
	$ret = svn_cleanup(TEMPLATE_DATA_LOCAL_PATH);
	var_dump($ret);
	echo '<br>';

	// revert
	$ret = svn_revert( TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH.TEMPLATE_DATA_LOCAL_FILE_3 );
	var_dump($ret);
	echo '<br>';

	// status		
	$status = svn_status( TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH.TEMPLATE_DATA_LOCAL_FILE_3, SVN_ALL );
	$cmt_rev = $status[0]["cmt_rev"];
	$cmt_date = $status[0]["cmt_date"];
	
	echo 'URL: '.TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH.TEMPLATE_DATA_LOCAL_FILE_3;
	echo '<br>';	
	echo '마지막 커밋 리비전 : ' . $cmt_rev;
	echo '<br>';
	echo '마지막 커밋 일시 : ' . date('Y-m-d H:i:s', $cmt_date);
	echo '<br>';
	echo 'Update Complete !!!';
	echo '<br>';
	
	// ------------------------------------------------------------------------------------
	// by shell command execute
/*	
	// checkout
	$cmd = 'svn checkout 2>&1 '.'--username u4us72 --password kang14 '.TEMPLATE_DATA_SVN_PATH.' '.TEMPLATE_DATA_LOCAL_PATH;
	echo $cmd . '<br>';
	$ret = shell_exec($cmd);
	var_dump($ret);	
	echo '<br>';
*/
/*	
	// update
	$cmd = 'svn update 2>&1 '.TEMPLATE_DATA_LOCAL_PATH;
	echo $cmd . '<br>';
	$ret = shell_exec($cmd);
	var_dump($ret);	
	echo '<br>';
*/
/*
	// cleanup
	$cmd = 'svn cleanup 2>&1 --username u4us72 --password kang14 '.TEMPLATE_DATA_LOCAL_PATH;
	echo $cmd . '<br>';
	$ret = shell_exec($cmd);
	var_dump($ret);
	echo '<br>';
*/
/*
	// delete
	$cmd = 'svn delete 2>&1 '.TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH.TEMPLATE_DATA_LOCAL_FILE_3;
	echo $cmd . '<br>';
	$ret = shell_exec($cmd);
	var_dump($ret);
	echo '<br>';
	
	if( $ret != null ) {
		// commit
		$msg = "'Commit delete for Template.txt file !!!'";
		$cmd = "svn commit -m $msg --username u4us72 --password kang14 " . TEMPLATE_DATA_LOCAL_PATH;
		echo $cmd . '<br>';
		$ret = shell_exec($cmd);
		var_dump($ret);
		echo '<br>';	
	}
*/
/*
	// file 디렉토리 존재 체크 & 생성
	if( !is_dir( TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH ) ) {
		mkdir( TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH, 0777 );
		chmod( TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH, 0777 ); 
		
		// add
		$cmd = 'svn add 2>&1 ' .TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH;
		echo $cmd . '<br>';
		$ret = shell_exec($cmd);
		var_dump($ret);	
		echo '<br>';
		
		if( $ret != null ) {
			// commit
			$msg = "'Commit add for Template directory !!! - path:'".TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH;
			$cmd = "svn commit -m $msg --username u4us72 --password kang14 ".TEMPLATE_DATA_LOCAL_PATH;
			echo $cmd . '<br>';
			$ret = shell_exec($cmd);
			var_dump($ret);
			echo '<br>';	
		}
	}	
	
	// file creation
	$file = fopen( TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH.TEMPLATE_DATA_LOCAL_FILE_3, "w" );
	if (!$file) {
		echo "<p>Unable to open remote file for writing.\n";
		exit;
	}
	
	// Write the data here
	fwrite( $file, 'Hello !!! Template ^^' );
	fclose( $file );
	chmod( $file, 0777 ); 
*/	
/*
	// add
	$cmd = 'svn add 2>&1 ' .TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH.TEMPLATE_DATA_LOCAL_FILE_3;
	echo $cmd . '<br>';
	$ret = shell_exec($cmd);
	var_dump($ret);	
	echo '<br>';
	
	if( $ret != null ) {
		// commit
		$msg = "'Commit add for Template file !!!'";
		$cmd = "svn commit -m $msg --username u4us72 --password kang14 ".TEMPLATE_DATA_LOCAL_PATH;
		echo $cmd . '<br>';
		$ret = shell_exec($cmd);
		var_dump($ret);
		echo '<br>';	
	}	
*/
/*		
	// cleanup
	$cmd = 'svn cleanup 2>&1 --username u4us72 --password kang14 '.TEMPLATE_DATA_LOCAL_PATH;
	echo $cmd . '<br>';
	$ret = shell_exec($cmd);
	var_dump($ret);
	echo '<br>';
*/
/*
	// revert
	$cmd = 'svn revert 2>&1 '.TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH.TEMPLATE_DATA_LOCAL_FILE_3;
	echo $cmd . '<br>';
	$ret = shell_exec($cmd);
	var_dump($ret);
	echo '<br>';
*/
/*	
	// status
	$cmd = 'svn status 2>&1 -u --username u4us72 --password kang14 '.TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH;
	echo $cmd . '<br>';
	$ret = shell_exec($cmd);
	var_dump($ret);
	echo '<br>';
*/
/*	
	// info
	$cmd = 'svn info 2>&1 '.TEMPLATE_DATA_LOCAL_PATH.MIDDLE_PATH.TEMPLATE_DATA_LOCAL_FILE_3;
	echo $cmd . '<br>';
	$ret = shell_exec($cmd);
	var_dump($ret);
	echo '<br>';	
*/	
	
} catch (Exception $e) {

	echo "Excepted Remote File !!!";
	echo "<br>";
	var_dump( Utility::GetExceptionDataString( $e ) );
}

?>
