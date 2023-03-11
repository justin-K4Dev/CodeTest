<?php

// set error report
error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);

// set locale
setlocale(LC_CTYPE, 'ko_KR.UTF-8');

$now = date('Y-m-d H:i:s', time());
echo "Update Date : $now";
echo '<br>';


require_once './Lib/Utility.php';
require_once './Lib/MySQL.php';


// template file path definition
define('TEMPLATE_DATA_LOCAL_PATH', '/myweb/www/SVNWorking/Template/In/');
define('CONSTANT_TEMPLATE_FILE', 'ConstantTemplate.xlsx');
define('OBJECT_TEMPLATE_FILE', 'ObjectTemplate.xlsx');

// login SVN Server
svn_auth_set_parameter(SVN_AUTH_PARAM_DEFAULT_USERNAME, 'justin');
svn_auth_set_parameter(SVN_AUTH_PARAM_DEFAULT_PASSWORD, 'kang14');


// load the xslx file
require_once 'Lib/Excel/PHPExcel/IOFactory.php';

function g_GetColumnIndexByName($excel, $name) {
	$colMax =  PHPExcel_Cell::columnIndexFromString($excel->getActiveSheet()->getHighestColumn());
	for ( $i = 0; $i <= $colMax; $i++) {
		$value = $excel->getActiveSheet()->getCellByColumnAndRow($i, 1)->getValue();
		if($name == $value)
			return $i;
	}
	return -1;
}

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 2014. 10. 21. 오후 3:18:23
/// @brief
///        상수형 (Constant) Template include file 만들기 
///////////////////////////////////////////////////////////////////////////////

$objPHPExcel = PHPExcel_IOFactory::load(TEMPLATE_DATA_LOCAL_PATH.CONSTANT_TEMPLATE_FILE);

$buf = "<?php";

// post update date and revision
$status = svn_status(TEMPLATE_DATA_LOCAL_PATH.CONSTANT_TEMPLATE_FILE, SVN_ALL);
$revision = $status[0]['revision'];
$now = date('Y-m-d H:i:s', time());
$buf = $buf."\n//Revision : $revision\n//Update Date : $now\n";

// make $buf
// parse Constant style2
$sheetName = 'Constant';
$objPHPExcel->setActiveSheetIndexByName($sheetName);
$writeClass = '';
$rowMax = $objPHPExcel->getActiveSheet()->getHighestRow();
for( $i = 3; $i <= $rowMax; $i++ ) {
	$tType = $objPHPExcel->getActiveSheet()->getCell("B$i");

	if( $writeClass != $tType->getValue() )	{
		if($i != 3 ) {
			$buf = $buf."\n}\n";
		}
			
		$buf = $buf."\nclass $tType\n{";
	}
		
	$tName = $objPHPExcel->getActiveSheet()->getCell("C$i");
	$tValue = $objPHPExcel->getActiveSheet()->getCell("D$i");
	
	if( is_numeric( $tValue->getValue() ) == false ) {
		$tValue = '"'.$tValue.'"';
	}
	
	$tDesc = $objPHPExcel->getActiveSheet()->getCell("A$i");

	$buf = $buf."\n\t const $tName = $tValue;\t\t//$tDesc";

	$writeClass = $tType->getValue();
}
$buf = $buf."\n}\n";

// close
$buf = $buf."?>";

define('TEMPLATE_DATA_LOCAL_SCRIPT_PATH', '/myweb/www/SVNWorking/Template/Out/');
define('TEMPLATE_DATA_LOCAL_SCRIPT_FILE', 'ConstantTemplate.inc');

// put to file
$file = fopen(TEMPLATE_DATA_LOCAL_SCRIPT_PATH.TEMPLATE_DATA_LOCAL_SCRIPT_FILE , 'w') ; 
fwrite($file ,  iconv( 'UTF-8' ,'UTF-8', $buf)); 
fclose($file);

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 2014. 10. 21. 오후 3:18:23
/// @brief
///        객체형 (Object) Template register to MySQL Server
///////////////////////////////////////////////////////////////////////////////

$dbMySQL = new MySQLDB;

$dbMySQL->SetDBServerInfo( "192.168.1.10:3306", "root", "kang14", "");

$sth = $dbMySQL->Query( "show databases" );

$dataList = array();
$dataList[] = $sth->fetchAll();

$foundDB = false;
foreach ( $dataList[0] as $k => $v ) {
	
	if( $v['Database'] == 'db_game_template' ) {
		$foundDB = true;
	}
}

if( false == $foundDB ) {
	$sth = $dbMySQL->Query( "create database db_game_template;" );
}
	
$sth = $dbMySQL->Query( "use db_game_template;" );
$sth = $dbMySQL->Query( "ALTER SCHEMA db_game_template DEFAULT CHARACTER SET utf8;" );

$objPHPExcel = PHPExcel_IOFactory::load(TEMPLATE_DATA_LOCAL_PATH.OBJECT_TEMPLATE_FILE);

// parse Template
$sheetNameList = array('Object');
for ( $sheetIdx = 0; $sheetIdx < count($sheetNameList); $sheetIdx++ ) {
	$sheetName = $sheetNameList[$sheetIdx];

    $objPHPExcel->setActiveSheetIndexByName($sheetName);
    $colMax =  PHPExcel_Cell::columnIndexFromString($objPHPExcel->getActiveSheet()->getHighestColumn());
    $rowMax = $objPHPExcel->getActiveSheet()->getHighestRow();
    
    $templateIDName = "u_ID";    
    
    $tIDNameIdx = g_GetColumnIndexByName($objPHPExcel, $templateIDName);
    if( 0 > $tIDNameIdx ) {
    	echo "<font color=red><b>Not found $templateIDName field !!! # TemplateNameIdx:$tidNameIdx - SheetName:$sheetName </b></font>";
    	echo '<br>';
    	continue;
    }    
	
    // column header 정보 만들기
    $columnHeaderList = array();
    for ( $i = 0; $i <= $colMax; $i++) {
    	$columnName = $objPHPExcel->getActiveSheet()->getCellByColumnAndRow($i, 1)->getValue();
    	if( null == $columnName ) {
    		continue;
    	}
    	$prefix = substr( $columnName, 0, 1 );
    	if( 'n' == $prefix ) {
    		continue;
    	}
    	
    	if( 'u' == $prefix || 'i' == $prefix ) {
    		$columnHeader = array( $i, $prefix, "int", $columnName );
    	}
    	else if( 'f' == $prefix ) {
    		$columnHeader = array( $i, $prefix, "float", $columnName );
    	}
    	else if( 's' == $prefix ) {
    		$columnHeader = array( $i, $prefix, "nvarchar(1000)", $columnName );	
    	}
    	else {
    		echo "Unknown prefix of column !!! - Prefix:$prefix ColumnName:".$columnName;
    		echo "<br>";
    		continue;
    	}
    	
    	$columnHeaderList[] = $columnHeader;
    	
    	var_dump( $columnHeader );
    	echo "<br>";    	
    }
        
    $sth = $dbMySQL->Query( "drop table if exists ".$sheetName ); 
    
    // column header 정보로 table 생성 하기
    $tableCreationStatement = "create table ".$sheetName."( ";
    for ( $i = 0; $i < count($columnHeaderList); $i++ ) {
    	$columnHeader = array();
    	$columnHeader = $columnHeaderList[$i];
    	$tableCreationStatement = $tableCreationStatement.$columnHeader[3]." ".$columnHeader[2];
    	
    	// TemplateConfig::TEMPLATE_ID_NAME 일 경우 Not null 설정
    	if( $columnHeader[3] == $templateIDName ) {
    		$tableCreationStatement = $tableCreationStatement." NOT NULL";
    	}
    	
    	$tableCreationStatement = $tableCreationStatement.", ";    	
    }
	$tableCreationStatement = $tableCreationStatement." PRIMARY KEY "."($templateIDName)";
	$tableCreationStatement = $tableCreationStatement." ) ENGINE=InnoDB DEFAULT CHARSET=utf8;";
    
    $sth = $dbMySQL->Query( $tableCreationStatement );
    
    
   	// 생성된 table 내에  data 입력 하기
    $tidNameIdx = g_GetColumnIndexByName( $objPHPExcel, $templateIDName );
    
    $insertDataStatementList = ''; 
    for ( $i = 3; $i <= $rowMax; $i++ ) {

		$tid = $objPHPExcel->getActiveSheet()->getCellByColumnAndRow( $tidNameIdx, $i )->getValue();
		if( !$tid ) {
			echo "<font color=red><b>Failed to load Template ID !!! # TemplateNameIdx:$tidNameIdx - Template:$v, SheetName:$sheetName, TemplateIDName:$templateIDName</b></font>";
			echo '<br>';
			continue;
		}
		
		$insertHeaderStatement = "insert into ".$sheetName." ( ";
		$insertValueStatement = "values ( ";
		for ( $j = 0; $j < count($columnHeaderList); $j++ ) {
			$columnHeader = array();
			$columnHeader = $columnHeaderList[$j];
			
			$insertHeaderStatement = $insertHeaderStatement.$columnHeader[3];
			
			$value = $objPHPExcel->getActiveSheet()->getCellByColumnAndRow($columnHeader[0], $i)->getValue();
			if( "s" == $columnHeader[1] ) {
				$value = "'$value'";  //check non-number
			}
			$insertValueStatement = $insertValueStatement.$value;
			
			if( $j + 1 < count($columnHeaderList) ) {
				$insertHeaderStatement = $insertHeaderStatement.", ";
				$insertValueStatement = $insertValueStatement.", ";
			}
		}		
		$insertHeaderStatement = $insertHeaderStatement." )";
		$insertValueStatement = $insertValueStatement." )";
		
		echo $insertHeaderStatement." ".$insertValueStatement;
		echo "<br>";		
	  
		$insertDataStatementList = $insertDataStatementList.$insertHeaderStatement." ".$insertValueStatement;
		$insertDataStatementList = $insertDataStatementList."; ";
    }
        
    $sth = $dbMySQL->Query( $insertDataStatementList );   
}

?>

<hr/>
Update Complete !!!
<br/>
<a href="javascript:history.back();">Back</a>