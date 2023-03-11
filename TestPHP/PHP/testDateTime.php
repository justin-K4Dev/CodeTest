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

try {
	
	// 이번 주 특정 요일 & 시간을 경과 했는지 체크 하기
	$dayOfWeek = 2;
	
	$tm = Utility::GetNowTime();
	var_dump("현재시간: ".$tm);
	echo "<br>";

	var_dump("밤12시: ".Utility::GetMidnightTime($tm) );
	echo "<br>";

	// 이번 주 기준요일이 화요일, 오전 4시일 경우 현재 시간을 비교 하여
	// 이번 주에 해당 하는지 체크 하기
	$tm = Utility::GetNowTime();
	var_dump("현재시간정보: ".Utility::Time2String( $tm ) );
	echo "<br>";
	var_dump("현재주개수: ".Utility::GetWeek( $tm ) );
	echo "<br>";
	var_dump("화요일-오전4시일 경우 주개수: ".Utility::GetWeekByTime( 2, 4, $tm ) );
	echo "<br>";
	var_dump("목요일-오전4시일 경우 주개수: ".Utility::GetThisWeek( 5, 4 ) );
	echo "<br>";
	
	$tm = Utility::GetNextResetTime( Utility::Weekly, 2, '5:00' );
	var_dump("다음주 화요일-오전5시 시간정보: ".Utility::Time2String( $tm ) );
	echo "<br>";

	// 현재 시간으로 요일 정보 얻기
	$dayOfWeekList = array("일","월","화","수","목","금","토");
	$date = date( 'Y-m-d' );
	var_dump( $dayOfWeekList[(int)date('w', strtotime($date))] );
	echo "<br>";
	
	// 특정 요일 & 시간에 포함 하는지 체크 하기
	$resetDayOfWeek = 2;
	$resetStartTime = '4:00';
	$resetEndTime = '4:50';
		
	var_dump( "StartTime: ".$resetStartTime );
	echo "<br>";
	$resetStartTime = strtotime( $resetStartTime );

	var_dump( "EndTime: ".$resetEndTime );
	echo "<br>";
	$resetEndTime = strtotime( $resetEndTime );
	
	$currTime = date( 'H:i' );
	var_dump("CurrTime: ".$currTime);
	echo "<br>";
	$currTime = strtotime( $currTime );

	if( $resetStartTime < $currTime && $currTime < $resetEndTime ) {
		echo "Now !!! - ".date( 'H:i', $currTime );
		echo "<br>";
	}

	$tm = Utility::GetNextResetTime( Utility::Minutely, -1, 15 );
	var_dump("매 15분후 시간정보: ".Utility::Time2String( $tm ) );
	echo "<br>";
	
	$hourly = 12;
	$tm = Utility::GetNextResetTime( Utility::Hourly, -1, $hourly );
	var_dump("매 $hourly 시간후 시간정보: ".Utility::Time2String( $tm ) );
	echo "<br>";

} catch (Exception $e) {

	echo "Excepted DateTime !!!";
	echo "<br>";
	var_dump( Utility::GetExceptionDataString( $e ) );
}

?>