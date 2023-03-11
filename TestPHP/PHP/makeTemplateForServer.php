<?php
// set error report
error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);

setlocale(LC_CTYPE, 'ko_KR.UTF-8');

include_once 'Config/TemplateConfig.inc';

function g_GetColumnIndexByName($excel, $name) {
	$colMax = PHPExcel_Cell::columnIndexFromString($excel->getActiveSheet()->getHighestColumn());
	for( $i = 0; $i <= $colMax; $i++ ) {
		$value = $excel->getActiveSheet()->getCellByColumnAndRow($i, 1)->getValue();
		if($name == $value) {
			return $i;
		}
	}
	
	return -1;
}

foreach( TemplateConfig::$g_TemplateOutFileList as $v ) {
	
	switch($v) {
		
		case TemplateConfig::GAME_TEMPLATE_OUT_FILE: {
			
			require_once 'Lib/Excel/PHPExcel/IOFactory.php';
			
			$path = TemplateConfig::TEMPLATE_LOCAL_PATH.TemplateConfig::CONSTANT_TEMPLATE_FILE;
			$objPHPExcel = PHPExcel_IOFactory::load($path);
			$buf = "<?php";
			
			$status = svn_status($path, SVN_ALL);
			$revision = $status[0]['revision'];
			$now = date('Y-m-d H:i:s', time());
			$buf = $buf."\n//Reference Template File : ".TemplateConfig::CONSTANT_TEMPLATE_FILE;
			$buf = $buf."\n//Revision : $revision\n//Update Date : $now\n";
			
			// make Constant Template Data			
			$len = strlen( TemplateConfig::CONSTANT_TEMPLATE_FILE );
			$cutLen = strlen( TemplateConfig::TEMPLATE_FILE );
			$sheetName = substr(TemplateConfig::CONSTANT_TEMPLATE_FILE, 0, $len - $cutLen);
							
			$objPHPExcel->setActiveSheetIndexByName($sheetName);
			
			$writeClass = '';
			$rowMax = $objPHPExcel->getActiveSheet()->getHighestRow();
			for( $i = 2; $i <= $rowMax; $i++) {
				$tType = $objPHPExcel->getActiveSheet()->getCell("B$i");
				
				if( $writeClass != $tType->getValue() )	{			
					if($i != 2) {
						$buf = $buf."\n}\n";
					}
									
					$buf = $buf."\nclass $tType\n{";
				}
			
				$tName = $objPHPExcel->getActiveSheet()->getCell("C$i");
				$tValue = $objPHPExcel->getActiveSheet()->getCell("D$i");
				$tDesc = $objPHPExcel->getActiveSheet()->getCell("A$i");
						
				$buf = $buf."\n\t const $tName = $tValue;\t\t//$tDesc";

				$writeClass = $tType->getValue();
			}
			$buf = $buf."\n}\n";
			
			// make Template Data
			$templateIDName = TemplateConfig::TEMPLATE_ID_NAME;
			$buf = $buf."\n\nclass TemplateSheet {";
			$buf = $buf."\n\npublic static \$DATA = array(";
				
			foreach( TemplateConfig::$g_TemplateFileList as $v ) {
				
				// pass constant Template !!!
				if( TemplateConfig::CONSTANT_TEMPLATE_FILE == $v ) {
					continue;	
				}
				
				$path = TemplateConfig::TEMPLATE_LOCAL_PATH.$v;
				$objPHPExcel = PHPExcel_IOFactory::load($path);
				
				$len = strlen( $v );
				$cutLen = strlen( TemplateConfig::TEMPLATE_FILE );
				$sheetName = substr( $v, 0, $len - $cutLen );		
				
				$objPHPExcel->setActiveSheetIndexByName($sheetName);
				
				$buf = $buf."\n\t'$sheetName' => array(";
				$colMax =  PHPExcel_Cell::columnIndexFromString($objPHPExcel->getActiveSheet()->getHighestColumn());
				$rowMax = $objPHPExcel->getActiveSheet()->getHighestRow();

				$tIDNameIdx = g_GetColumnIndexByName($objPHPExcel, $templateIDName);
					
				for( $i = 3; $i <= $rowMax; $i++ ) {
					$tID = $objPHPExcel->getActiveSheet()->getCellByColumnAndRow($tIDNameIdx, $i)->getValue();    //TemplateConfig::TEMPLATE_ID_NAME
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
						elseif( strpos( $tType, TemplateConfig::TEMPLATE_ID_NAME ) || is_numeric($tValue) == false ) {
							$tValue = "'$tValue'";  //check non-number
						}
						elseif( strpos( $tType, TemplateConfig::TEMPLATE_DATE_NAME ) ) { //컬럼이름에 Date가 있으면 php용 시간값으로 변환
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
			
			$fileName = TemplateConfig::GAME_TEMPLATE_OUT_FILE;
			$file = fopen( "/myweb/www/PHP/Template/$fileName.inc", 'w' );
			fwrite( $file,  iconv( 'UTF-8' ,'UTF-8', $buf ) );
			fclose( $file );
				
		} break;
	}
}

?>

<hr>
Update Complete!!
<br>
<a href="javascript:history.back();">Back</a>
