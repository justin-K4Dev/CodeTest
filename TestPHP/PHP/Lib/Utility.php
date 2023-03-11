<?php

class Utility
{
	static public function GetInteger($data, $name, $default = 0)
	{
		if ( isset($data[$name]) ) {
			return (int)$data[$name];
		}
		
		return (int)$default;
	}
	
	static public function GetFloat($data, $name, $default = 0.0)
	{
		if ( isset($data[$name]) ) {
			return (float)$data[$name];
		}
		
		return (float)$default;
	}	
	
	static public function GetString($data, $name, $default = '')
	{
		if ( isset($data[$name]) ) {
			if ((string)$data[$name] == "0") {
				return "";
			}
			return trim((string)$data[$name]);
		}
		
		return (string)$default;
	}
	
	static public function GetValue($data, $name, $default = null)
	{
		if ( isset($data[$name]) ) {
			return $data[$name];	
		}
		
		return $default;
	}
	
	static public function Data2Array( $data, $sp=null, $kvsp=null )
	{
		if ($data == null || strlen(trim($data)) == 0) {
			return array();
		}
		
		if ($sp == null) $sp = ',';
		if ($kvsp == null) $kvsp = ':';
		
		$datas = explode($sp, $data);
		$arr = array();
		foreach ($datas as $kv) {
			if (strpos($kv, $kvsp)) {
				list($k, $v) = explode($kvsp, $kv);
			}
			else {			
				g_GetLog()->Write( LOG_LEVEL::ERROR, LOG_TYPE::SYSTEM, ERROR_CODE::DATA_CONVERT_ERROR, "Data -> Array convert error !!!" );
				$k = $kv;
				$v = 1;
			}
			$arr[trim($k)] = trim($v);
		}
		
		return $arr;		
	}
	
	static public function Array2Data( $arr, $sp=null, $kvsp=null )
	{
		if ($arr == null || count($arr) == 0) {
			return "";
		}
		
		if ($sp == null) $sp = ',';
		if ($kvsp == null) $kvsp = ':';
		
		$datas = "";

		foreach ($datas as $k => $v) {
			$rep .= "&$k=$v";
		}		
					
		return $datas;		
	}	
	
	static public function GetNowTime()
	{
		if ( isset($GLOBALS['NOWTIME'] ) == false) {
			$GLOBALS['NOWTIME'] = time();        
		}
		
		return $GLOBALS['NOWTIME'];
	}
	
	static public function GetOneDaySecond() 
	{
		return 24 * 3600;
	}
	
	static public function GetMidnightTime($tm) 
	{
		return strtotime(date("Y-m-d 00:00:00", $tm));
	}
	
	static public function Time2String($tm)
	{
		if($tm == null || $tm == 0)
			return null;
		return date("Y-m-d H:i:s", $tm);
	}
	
	static public function GetWeek( $tm )
	{
		return date('oW', $tm);
	}
	
	const Minutely = 1;
	const Hourly = 2;
	const Daily = 3;
	const Weekly = 4;	
		
	static public function GetWeekByTime( $resetDayOfWeek, $resetHour, $tm) 
	{
		// return date('oW', $tm - (($resetDayOfWeek - 1) * 24 * 3600 + $resetHour * 3600));
	
		// 클라이언트 테스트를 위해 한주를 하루 단위로 바꾸기 위한 임시 코드
		/* 5분
		$now = $tm;
		$minute = (int)date('i', $tm);
		$m = $minute % 10;
		if ($m >= 0 && $m < 5) {
			$minute = ((int)($minute/10))*10 + 5;
		}
		else {
			$now += 300;
			$minute = (int)date('i', $now);
			$minute = ((int)($minute/10))*10;
		}
		
		return date('Y', $now).date('m', $now).date('d', $now).date('H', $now).sprintf("%02d", $minute); */
		
		//* 하루
		$time = $tm - (12 * 3600);
		return date('Y', $time).date('m', $time).date('d', $time); //*/
	}
	
	static public function GetThisWeek($resetDayOfWeek, $resetHour) 
	{
		return Utility::GetWeekByTime($resetDayOfWeek, $resetHour, Utility::GetNowTime());
	}
	
	static public function GetNextResetTime($timeType, $resetDayOfWeek, $resetHour)
	{
		$nextResetTime = '';
		
		if( Utility::Minutely == $timeType ) {
			
			$now = Utility::GetNowTime();
			$now += 60 * $resetHour;
			$minute = (int)date('i', $now);
			
			$nextResetTime = strtotime(date(sprintf("Y-m-d H:%02d:00", $minute), $now));
			
			/*
				$now = Utility::GetNowTime();
				$minute = (int)date('i', $now);
				$m = $minute % $resetHour;
				if ($m >= 0 && $m < $resetHour) {
					$minute = ((int)( $minute/$resetHour )) * $resetHour + $resetHour;
				}
				else {
					$now += 60 * $resetHour;
					$minute = (int)date('i', $now);
					$minute = ((int)( $minute / $resetHour )) * $resetHour;
				}
				
				$nextResetTime = strtotime(date(sprintf("Y-m-d H:%02d:00", $minute), $now));
			*/			
		}
		else if( Utility::Hourly == $timeType ) {

			$now = Utility::GetNowTime();
			$h = date('H', $now);

			if( $h >= $resetHour ) {
				$resetHour += $resetHour;
			}
			
			$nextResetTime = strtotime(date(sprintf("Y-m-d %02d:00:00", $resetHour), Utility::GetNowTime()));
		}
		else if( Utility::Daily == $timeType ) {
			
			$now = Utility::GetNowTime();
			$h = date('H', $now);
			
			$targetTime = Utility::GetNowTime();
			if ($h >= 12) {
				$targetTime += (24 * 3600);
			}
			
			$nextResetTime = strtotime(date("Y-m-d 12:00:00", $targetTime));			
		}
		else if( Utility::Weekly == $timeType ) {
			
			$now = Utility::GetNowTime();
			$w = date('w', $now);
			$h = date('H', $now);
			$d = 0;
			
			if ($w != $resetDayOfWeek || $h >= $resetHour) {
				$d = ($w < $resetDayOfWeek) ? ($resetDayOfWeek - $w) : (7 - ($w - $resetDayOfWeek));
			}
			
			$nextResetTime = strtotime(date(sprintf("Y-m-d %2d:00:00", $resetHour), Utility::GetNowTime() + $d * 24 * 3600));
		}
		
		return $nextResetTime;
	}
	
	static public function IsToday($tm)
	{
		$now = GetNowTime();
	
		$d1 = date("Ymd", $tm);
		$d2 = date("Ymd", $now);
	
		if($d1 != $d2){
			return false;
		}
	
		return true;
	}
		
	static public function MakeMD5()
	{
		$args = func_get_args();
		$datas = array();
		foreach ($args as $val) {
			$datas[] = $val;	
		}
		
		$text = implode('', $datas);
		return md5($text);		
	}
	
	static public function ModObjectKey($objKey, $mod)
	{
		return (int)bcmod($objKey, (string)$mod);
	}	
	
	static public function GetExceptionDataString(Exception $e)
	{
		$rtnval = "";
		do {
			$rtnval .= sprintf( "EC:%s, MSG:%s, FN:%s, LN:%s, TRACE:\n%s\n", $e->getCode(), $e->getMessage(), $e->getFile(), $e->getLine(), $e->getTraceAsString() );
		} while($e = $e->getPrevious());
		return $rtnval;
	}	
}

?>