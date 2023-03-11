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


// template file path definition
define('TEMPLATE_DATA_LOCAL_PATH', '/myweb/www/SVNWorking/Template/In/');
define('CONSTANT_TEMPLATE_FILE', 'ConstantTemplate.xlsx');
define('OBJECT_TEMPLATE_FILE', 'ObjectTemplate.xlsx');
define('TEMPLATE_DATA_SCRIPT_OUT_PATH', '/myweb/www/SVNWorking/Template/Out/');


// load the xslx file
require_once 'Lib/Excel/PHPExcel/IOFactory.php';
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

var_dump( $buf );
echo "<br>"
		
define('TEMPLATE_DATA_CONSTANT_SCRIPT_FILE', 'ConstantTemplate.inc');

// put to file
$file = fopen(TEMPLATE_DATA_SCRIPT_OUT_PATH.TEMPLATE_DATA_CONSTANT_SCRIPT_FILE , 'w') ; 
fwrite($file ,  iconv( 'UTF-8' ,'UTF-8', $buf)); 
fclose($file);		


function g_GetColumnIndexByName($excel, $name) {
	$colmax =  PHPExcel_Cell::columnIndexFromString($excel->getActiveSheet()->getHighestColumn());
	for ($i=1; $i <= $colmax; $i++) {
		$value = $excel->getActiveSheet()->getCellByColumnAndRow($i, 1)->getValue();
		if($name == $value)
			return $i;
	}
	return -1;
}


// make Template Data
$objPHPExcel = PHPExcel_IOFactory::load(TEMPLATE_DATA_LOCAL_PATH.OBJECT_TEMPLATE_FILE);

$templateIDName = "u_ID";
$buf = $buf."\n\nclass TemplateSheet {";
$buf = $buf."\n\npublic static \$DATA = array(";
	
$sheetNameList = array('Object');
for ( $sheetIdx = 0; $sheetIdx < count($sheetNameList); $sheetIdx++ ) {
	$sheetName = $sheetNameList[$sheetIdx];
		
	$buf = $buf."\n\t'$sheetName' => array(";
	$colMax =  PHPExcel_Cell::columnIndexFromString($objPHPExcel->getActiveSheet()->getHighestColumn());
	$rowMax = $objPHPExcel->getActiveSheet()->getHighestRow();

	$tIDNameIdx = g_GetColumnIndexByName($objPHPExcel, $templateIDName);
		
	for( $i = 3; $i <= $rowMax; $i++ ) {
		$tID = $objPHPExcel->getActiveSheet()->getCellByColumnAndRow($tIDNameIdx, $i)->getValue();
		if( !$tID ) {
			echo "<font color=red><b>Failed to load Template ID !!! # TemplateNameIdx:$tIDNameIdx - Template:$v, SheetName:$sheetName, TemplateIDName:$templateIDName</b></font>"; echo '<br>';						
			continue;
		}
	
		$buf = $buf."\n\t\t '$tID' => array(";
		for( $j = 0 ; $j <= $colMax; $j++ ) {
			$tType = $objPHPExcel->getActiveSheet()->getCellByColumnAndRow($j, 1);
			$tValue = $objPHPExcel->getActiveSheet()->getCellByColumnAndRow($j, $i)->getValue();    //명확한 타입체크를 위해 getValue() 해야함

			if('n' == $tType->getValue()[0]) {
				continue;
			}
			else if($tValue === '') {	// 0 == '' 하면 true로 반환해서 ===로 비교함
				$tValue = 'null';
			}       //check null
			elseif( strpos( $tType, $templateIDName ) || is_numeric($tValue) == false ) {
				$tValue = "'$tValue'";  //check non-number
			}
			elseif( strpos( $tType, "Date" ) ) { //컬럼이름에 Date가 있으면 php용 시간값으로 변환
				$tValue = PHPExcel_Shared_Date::ExcelToPHP( $tValue );
			}
				
			if( $tType != '' ) {
				$buf = $buf."'$tType' => $tValue, ";
			}
		}
		
		$tDesc = $objPHPExcel->getActiveSheet()->getCell("A$i");
		$buf = $buf."\t\t),\t\t//$tDesc";					
	}
		
	$buf = $buf."\n\t),";
}
					
$buf = $buf."\n);\n\n}\n\n?>";

var_dump( $buf );
echo "<br>";
		
define('TEMPLATE_DATA_OBJECT_SCRIPT_FILE', 'ObjectTemplate.inc');

// put to file
$file = fopen(TEMPLATE_DATA_SCRIPT_OUT_PATH.TEMPLATE_DATA_OBJECT_SCRIPT_FILE , 'w') ; 
fwrite($file ,  iconv( 'UTF-8' ,'UTF-8', $buf)); 
fclose($file);

?>

<hr/>
Update Complete !!!
<br/>
<a href="javascript:history.back();">Back</a>