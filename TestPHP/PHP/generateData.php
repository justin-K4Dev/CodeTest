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
    
<fieldset>
    <legend>Project-A 서버용 공용코드 생성기</legend>
<?php
$filename = '/myweb/www/PHP/Template/TemplateGen.php';
if (file_exists($filename)) {
	include_once './Template/TemplateGen.php';
    echo "'$filename' was last created: " . date ("Y-m-d H:i:s", filemtime($filename));
}
else {
	echo "'$filename' not found file !!!";
}
?>
    <form method="post" action="makeTemplateForServer.php">
    <input type="submit" value="TemplateGen.php 파일 만들기"/>
    </form>
</fieldset>

<br/>

<fieldset>
    <legend>Project-A 클라이언트용 공용코드 생성기</legend>
    <form method="post" action="makeProtocolForClient.php">
    	<input type="submit" value="프로토콜 파일 만들기"/>
    </form>
    <form method="post" action="makeConstantForClient.php">
    	<input type="submit" value="상수값 파일 만들기"/>
    </form>
    <form method="post" action="makeTemplateForClient.php">
    	<select name="TemplateName">
    		<option>Map</option>
    		<option>Stage</option>
    		<option>StageInGame</option>
    		<option>Game</option>
    		<option>Character</option>
    		<option>Rank</option>
    		<option>Stuff</option>
    		<option>Skill</option>
    		<option>Shop</option>
    		<option>Event</option>
    		<option>Quest</option>
    		<option>DailyQuest</option>
    		<option>Prize</option>
    		<option>Supporter</option>
    		<option>ItemCode</option>
    		<option>DrawStuff</option>
    		<option>DrawCharacter</option>
    		<option>IconNaming</option>
    		<option>String-Ko</option>
    	</select>
    	<input type="submit" value="템플릿 csv 파일 만들기"/>
    </form>
</fieldset>

<br/>

<fieldset>
    <legend>템플릿 svn 업데이트</legend>
<?php
//---------- revision
define('TEMPLATE_DATA_LOCAL_FILE_PATH', '/myweb/www/Template/Template.xlsx');
if (file_exists(TEMPLATE_DATA_LOCAL_FILE_PATH)) {
	$status = @svn_status( TEMPLATE_DATA_LOCAL_FILE_PATH, SVN_ALL);
	$cmt_rev = $status[0]["cmt_rev"];
	$cmt_date = $status[0]["cmt_date"];
}
?>
    <form method="post" action="updateTemplate.php">
	마지막 커밋 리비전 : <?php echo $cmt_rev; ?><br/>
	마지막 커밋 일시 : <?php echo date('Y-m-d H:i:s', $cmt_date); ?><br/><br/>
	마지막 업데이트 일시(파일수정일) : <?php echo date('Y-m-d H:i:s', filemtime(TEMPLATE_DATA_LOCAL_FILE_PATH)); ?><br/>
    <input type="submit" value="업데이트하기"/>
    </form>
</fieldset>

    </body>
</html>