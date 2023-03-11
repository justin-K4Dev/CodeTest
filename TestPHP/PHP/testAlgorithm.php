<?php

// set error report
error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);

// set locale
setlocale(LC_CTYPE, 'ko_KR.UTF-8');

$now = date('Y-m-d H:i:s', time());
echo "Update Date : $now";
echo "<br";


$latitude = 180.000000;
$longitude = 180.000000;

$sectorList = array();

for( $y = 0; 
     $y <= 5;
     $y += 1 ) {

	for( $x = 0;
         $x <= 5;
         $x += 1 ) {
     	
        $sectorID = floor ( ( $x * $x / 2 ) + ( $y * $y / 2 ) );
        var_dump( $sectorID );
        
        $value = array( 'sector_id' => $sectorID,
        		        'top'    => floor( ( ( $x * $x ) / 2 ) ),
        		        'bottom' => floor( ( ( $x * $x ) / 2 ) + 1 ),
        		        'left'   => floor( ( ( $y * $y ) / 2 ) ),
        		        'right'  => floor( ( ( $y * $y ) / 2 ) + 1 ) );
        
        if( isset( $sectorList[$sectorID] ) == true ) {

        	echo 'Already Sector ID !!!' . '<br>';
        	var_dump( $value );
        	
        	continue;
        }
        
		$sectorList[$sectorID] = $value;
		
		var_dump( $value );		
	}     	
}

var_dump( $sectorList );






?>
