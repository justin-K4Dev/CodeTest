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

<br/>

// C/S Protocol
class Protocol {
	<?php
	
	// class 정보 읽어 오기
	include_once './Common/Protocol.inc';	
	
	$reflKey = new ReflectionClass( 'COMMAND' );
	$defkeys = $reflKey->getConstants();
	foreach ($defkeys as $key => $val) {
		echo "\tconst $key = \"$val\";\n";
	}
	
	?>	
}

<br/>

// GameObject
class GameObject {
	<?php

	// 원격 파일 include - php.ini 에 allow_url_include = On 설정 필요 !!! (보안상 권장 하지 않음)
	//                 Remote.inc 파일이 FTP Server Home Directory 경로에 있어야 한다 !!!
	//			       http 이용시 php 구문은 load 되지 않음 !!!

	include_once 'ftp://ftp-user:ftp-user@192.168.1.10:21/Remote.inc';
	
	$reflKey = new ReflectionClass( 'RemoteClass' );
	$defkeys = $reflKey->getConstants();
	foreach ($defkeys as $key => $val) {
		echo "\tconst $key = \"$val\";\n";
	}
/*	
	// 원격 파일 fopen - 이건 ReflectionClass 에서 처리 되지 않는다 !!!
	//               차후 가능한 방법을 찾아보자 !!!
	
	$file = fopen ("ftp://ftp-user:ftp-user@192.168.1.10/Remote.inc", "rb");
	if (!$file) {
		echo "<p>Unable to open remote file for reading.\n";
		exit;
	}
	
	$reflKey = new ReflectionClass( 'RemoteClass' );
	$defkeys = $reflKey->getConstants();
	foreach ($defkeys as $key => $val) {
		echo "\tconst string $key = \"$val\";\n";
	}
*/	
	?>
}

<br/>

<?php
	
	// class 정보 읽어 오기
	include_once './Common/Reflection.inc';
	
	$reflector = new ReflectionClass('ObjectGroup\BaseObject');
	
	echo $reflector->getNamespaceName() . '<br>';		

	$constants = $reflector->getConstants();
	var_dump( $constants );	
	echo '<br>';
	
	foreach ($constants as $key => $val) {
		echo "Constant: $val";
		echo "<br>";
	}
	
	$methods = $reflector->getMethods();
	var_dump( $methods );
	echo '<br>';
	
	foreach ($methods as $key => $val) {
		var_dump( $methods );
		echo "Function: $val";
		echo "<br>";
	}
	
	$comment = $reflector->getDocComment();
	var_dump( $comment );
	echo "<br>";
	echo "<br>";		
	
	
	// constants comments 읽어 오기
	include_once 'Lib/ConstantDocCommentsFilter.php';
	
	$constantDoc = new ConstantDocCommentsFilter('ObjectGroup\BaseObject');
	
	var_dump( $constantDoc->getDocComments() );
	echo "<br>";
	
	echo $constantDoc->getDocComment('MAX_OBJECT_COUNT');
	echo "<br>";
	
	echo $constantDoc->getDocComment('NAME');
	echo "<br>";	
	
?>
