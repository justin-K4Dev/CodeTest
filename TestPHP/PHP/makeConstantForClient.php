<?php
// set error report
error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);

// set locale
setlocale(LC_CTYPE, 'ko_KR.UTF-8');


include_once 'Config/TemplateConfig.inc';


// load the xslx file
require_once 'Lib/Excel/PHPExcel/IOFactory.php';
$objPHPExcel = PHPExcel_IOFactory::load(TemplateConfig::TEMPLATE_LOCAL_PATH.TemplateConfig::CONSTANT_TEMPLATE_FILE);

// post update date and revision
$now = date('Y-m-d H:i:s', time());
?>
<pre>
<?php
echo "Update Date : $now\n";
?>


<?php

	svn_auth_set_parameter(SVN_AUTH_PARAM_DEFAULT_USERNAME, TemplateConfig::TEMPLATE_SVN_AUTH_ID);
	svn_auth_set_parameter(SVN_AUTH_PARAM_DEFAULT_PASSWORD, TemplateConfig::TEMPLATE_SVN_AUTH_PW);

	$svnPath = TemplateConfig::CONSTANT_SVN_PATH;
	$ret = svn_checkout($svnPath, TemplateConfig::CONSTANT_LOCAL_PATH);
	if( false == $ret ) {
		echo "<font color=red><b>Failed to checkout from SVN Server !!! - SVNPath:$svnPath</b></font>"; echo '<br>';
		return;
	}
	
	$localPath = TemplateConfig::CONSTANT_LOCAL_PATH;
	$ret = svn_update(TemplateConfig::CONSTANT_LOCAL_PATH);
	if( false == $ret ) {
		echo "<font color=red><b>Failed to update from SVN Server !!! - LocalPath:$localPath</b></font>"; echo '<br>';
		return;
	}
	
	// make Constant CS file all !!!	
	$status = svn_status($localPath.TemplateConfig::CONSTANT_TEMPLATE_FILE, SVN_ALL);
	$revision = $status[0]['revision'];
	$now = date('Y-m-d H:i:s', time());
	$templateInfo = '';
	$templateInfo = $templateInfo."\n//Reference Template File : ".TemplateConfig::CONSTANT_TEMPLATE_FILE;
	$templateInfo = $templateInfo."\n//Revision : $revision\n//Update Date : $now\n\n";

	$len = strlen( TemplateConfig::CONSTANT_TEMPLATE_FILE );
	$cutLen = strlen( TemplateConfig::TEMPLATE_FILE );
	$sheetName = substr( TemplateConfig::CONSTANT_TEMPLATE_FILE, 0, $len - $cutLen );

	$objPHPExcel->setActiveSheetIndexByName($sheetName);
	$rowMax = $objPHPExcel->getActiveSheet()->getHighestRow();
	
	foreach( TemplateConfig::$g_TemplateCSOutFileList as $csFile => $v ) {
		
		// make constant type
		$buf = $templateInfo;
		$buf = $buf."using UnityEngine\n";
		$buf = $buf."System.Collections\n\n";
		
		foreach( $v as $info ) {
						
			$writeClass = '';
			$rowMax = $objPHPExcel->getActiveSheet()->getHighestRow();
			for( $i = 1; $i <= $rowMax; $i++) {
				$tType = $objPHPExcel->getActiveSheet()->getCell("B$i");

				if( $info == $tType ) {	
					if( $writeClass != $tType->getValue() )	{
						$buf = $buf."\nclass $tType\n{";

						$writeClass = $tType->getValue();						
					}
					
					$tName = $objPHPExcel->getActiveSheet()->getCell("C$i");
					$tValue = $objPHPExcel->getActiveSheet()->getCell("D$i");
					$tDesc = $objPHPExcel->getActiveSheet()->getCell("A$i");
						
					$buf = $buf."\n\t const $tName = $tValue;\t\t//$tDesc";
				}
				else {
					if( '' != $writeClass ) {
						$buf = $buf."\n}\n";
						
						$writeClass = '';
					}
				}
			}
		}
		
		// delete constant cs file
		$constantFilePath = TemplateConfig::CONSTANT_LOCAL_PATH.$csFile;
		$ret = svn_delete($constantFilePath);
		if( $ret == true ) {
			// commit
			$msg = "'Commit delete for $csFile file !!!'";
			$ret = svn_commit($msg, TemplateConfig::CONSTANT_LOCAL_PATH);
			if( false == $ret ) {
				echo "<font color=red><b>Failed to commit from SVN Server !!! - LocalPath:$constantFilePath</b></font>"; echo '<br>';
				return;
			}
		}
		
		// file creation of constant cs file
		$file = fopen($constantFilePath, "w");
		if (!$file) {
			echo "<font color=red><b>Failed to create $csFile file !!! - LocalPath:$constantFilePath</b></font>"; echo '<br>';
			return;
		}
		
		// write the data here
		fwrite($file, $buf);
		fclose($file);
		
		// file svn add
		$ret = svn_add($constantFilePath);
		if( false == $ret ) {
			echo "<font color=red><b>Failed to add to SVN Server !!! - LocalPath:$constantFilePath</b></font>"; echo '<br>';
			return;
		}
			
		// commit
		$msg = "'Commit add for $csFile !!!'";
		$ret = svn_commit($msg, $constantFilePath);
		if( false == $ret ) {
			echo "<font color=red><b>Failed to commit to SVN Server for add !!! - LocalPath:$constantFilePath</b></font>"; echo '<br>';
			return;
		}
		
		echo "<b> $csFile patch success !!! - LocalPath:$constantFilePath</b>"; echo '<br>';
	}
?>

<hr>
Update Complete!!
<br>
<a href="javascript:history.back();">Back</a>

</pre>