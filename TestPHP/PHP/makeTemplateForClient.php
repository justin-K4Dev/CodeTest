<?php
// set error report
error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);

// set locale
setlocale(LC_CTYPE, 'ko_KR.UTF-8');

// get the xslx file from svn server
define('TEMPLATE_DATA_LOCAL_PATH', '/myweb/www/Template');
define('TEMPLATE_DATA_LOCAL_FILE', 'Template.xlsx');

// load the xslx file
require_once 'Lib/Excel/PHPExcel/IOFactory.php';
$objPHPExcel = PHPExcel_IOFactory::load(TEMPLATE_DATA_LOCAL_PATH.'/'.TEMPLATE_DATA_LOCAL_FILE);

// make $buf
function getColumnIndexByName($excel, $name) {
	$colmax =  PHPExcel_Cell::columnIndexFromString($excel->getActiveSheet()->getHighestColumn());
	for ($i=1; $i <= $colmax; $i++) {
		$value = $excel->getActiveSheet()->getCellByColumnAndRow($i, 1)->getValue();
		if($name == $value)
			return $i;
	}
	return -1;
}


// parse Sheet
$buf = "";
$sheetname = $_REQUEST["TemplateName"]; 
$objPHPExcel->setActiveSheetIndexByName($sheetname);
$colmax =  PHPExcel_Cell::columnIndexFromString($objPHPExcel->getActiveSheet()->getHighestColumn());
$rowmax = $objPHPExcel->getActiveSheet()->getHighestRow();
        
for ($i=1; $i <= $rowmax; $i++) {

	for ($j=0; $j <= $colmax; $j++) {
		$tvalue = $objPHPExcel->getActiveSheet()->getCellByColumnAndRow($j, $i)->getValue();
		$buf = $buf."$tvalue\t";
	}
	$buf = $buf."\n";
}


?>

<pre>
<?php echo $buf; ?>
</pre>
