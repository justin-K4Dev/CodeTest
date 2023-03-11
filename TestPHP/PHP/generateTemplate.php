<?php
// set error report
error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);

// set locale
setlocale(LC_CTYPE, 'ko_KR.UTF-8');

?>

<html>
    <head>
        <title>509 Studio 코드 생성기</title>
    </head>
    <body>
    
    <legend><i>Checking Template Revision Info .....................</i></legend>
        
<?php

include_once 'Config/TemplateConfig.inc';

svn_auth_set_parameter(SVN_AUTH_PARAM_DEFAULT_USERNAME, TemplateConfig::TEMPLATE_SVN_AUTH_ID);
svn_auth_set_parameter(SVN_AUTH_PARAM_DEFAULT_PASSWORD, TemplateConfig::TEMPLATE_SVN_AUTH_PW);

$result = true;

foreach ( TemplateConfig::$g_TemplateFileList as $v ) {
	$svnFilePath = TemplateConfig::TEMPLATE_SVN_PATH.$v;
	$ret = svn_log( $svnFilePath );
	if( false == $ret ) {
		echo "<font color=red><b>Failed to load from SVN Server !!! - Template:$v, Path:$svnFilePath</b></font>"; echo '<br>';
		continue;
	}
	
	$localFilePath = TemplateConfig::TEMPLATE_LOCAL_PATH.$v;
	if( !file_exists( $localFilePath ) ) {
		echo "<font color=red><b>Failed to load from Local !!! - Template:$v, Path:.$localFilePath</b></font>"; echo '<br>';
		$result = false;
		continue;
	}
	$remoteRev = $ret[0]['rev'];
	
	$status = svn_status( $localFilePath, SVN_ALL );
	$localRev = $status[0]["cmt_rev"];
	$localDate = $status[0]["cmt_date"];
	
	if( $remoteRev != $localRev ) {
		echo "<font color=red><b>Not match Revision Code !!! - Template:$v, Revision:$remoteRev, Path:$svnFilePath</b></font>"; echo '<br>';
		echo "<font color=red><b>Not match Revision Code !!! - Template:$v, Revision:$localRev, Path:$localFilePath</b></font>"; echo '<br>';
		$result = false;
		continue;
	}
	
	echo "<b>$v Match Check Success</b>"; echo '<br>';
	echo "마지막 커밋 리비전: $localRev"; echo '<br>';
	echo "마지막 커밋 일시: ".date('Y-m-d H:i:s', $localDate); echo '<br>';
	echo "마지막 업데이트 일시(파일수정일): ".date('Y-m-d H:i:s', filemtime($localFilePath)); echo '<br>';
}

if( false == $result ) {
	echo "Please update Template from SVN Server !!! ..."; echo '<br>';
}

echo '<br>';

?>

<fieldset style = "height:42">
    <legend>Template Update from SVN</legend>
    <form method="post" action="updateTemplate.php">
    	<input type="submit" value="Update !!!"/>
    </form>
</fieldset>

<br>

<fieldset style = "height:42">
    <legend>Project-A Template PHP Code for Server</legend>
    <form method="post" action="makeTemplateForServer.php">
    	<input type="submit" value="Make Template PHP All"/>
    </form>
</fieldset>

<br>

<fieldset style = "height:42">
    <legend>Project-A Constant CS Code for Client</legend>
    <form method="post" action="makeConstantForClient.php">
    	<input type="submit" value="Make CS Constant Code All"/>
    </form>
</fieldset>

    </body>
</html>