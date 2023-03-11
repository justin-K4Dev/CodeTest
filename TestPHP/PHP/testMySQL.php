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
	
require_once 'Lib/Utility.php';
require_once 'Lib/MySQLDB.php';


	
 	// MySQL DB 연동 테스트 예제
/*
	$dbMySQL = new MySQLDB;
 	$dbh = $dbMySQL->ConnectDB();
	if ($dbh == null) {
		return;
	}
		
	$nickname = '하하하';
							
	$sqlQuery = sprintf("call usp_account_by_nickname_s( @i_nickname )");
	$sth = $dbh->prepare($sqlQuery);
			
	try {
		$dbh->query( sprintf( "set @i_nickname = '%s'", $nickname ) );
						
		if ($sth->execute() == false) {
			$errMsg = sprintf( "Query:%s", $sqlQuery );
			print( $errMsg );			
		}
		
		$dataList = array();		
		$dataList = $sth->fetchAll();
		
		var_dump( $dataList );
		
		if ( 0 < count( $dataList ) ) {
			$errMsg = sprintf( "Already registered Nickname !!! (Nickname:%s)", $nickname );
			print( $errMsg );
		}
		
		print( "success !!!" );
			
		$sth->closeCursor();
		unset($sth);		
	}
	catch (PDOException $err) {
		$errMsg = Utility::GetExceptionDataString($err);
		print ( $errMsg );
	}	
*/
/* 	
	$dbMySQL = new MySQLDB;
 	$dbh = $dbMySQL->ConnectDB();
	if ($dbh == null) {
		return;
	}
	
	$userNo = 1;
	$userID = 'justin72';
	$userPW = 'kang14';	
	
	$sqlQuery = sprintf( "call usp_account_d( @o_result, @i_user_no, @i_user_id, @i_password )" );
	$sth = $dbh->prepare($sqlQuery);
			
	try {
		$dbh->query( sprintf( "set @i_user_no = %s", $userNo ) );
		$dbh->query( sprintf( "set @i_user_id = '%s'", $userID ) );
		$dbh->query( sprintf( "set @i_password = '%s'", $userPW ) );
						
		if ($sth->execute() == false) {
			$errMsg = sprintf( "Query:%s", $sqlQuery );
			print ( $errMsg );				
		}
		
		$dataList = array();		
		$dataList[] = $sth->fetchAll();
			
		$outResult = $dataList[0][0]['o_result'];
		
		var_dump( $dataList );
		
		if( 0 != $outResult ) {
			if( 1 == $outResult ) {
				$errMsg = sprintf( "Not register User No !!! (UserNo:%s)", $userNo );				
				print ( $errMsg );	
			}
			else if ( 2 == $outResult ) {
				$errMsg = sprintf( "Not registered User ID !!! (UserID:%s)", $userID );
				print ( $errMsg );				
			}
			else if ( 3 == $outResult ) {
				$errMsg = sprintf( "Not match Password !!! (PW:%s)", $userPW );
				print ( $errMsg );			
			}				
		}
									
		$sth->closeCursor();
		unset($sth);		
	}
	catch (PDOException $err) {
		$errMsg = Utility::GetExceptionDataString($err);
		print ( $errMsg );	
	} 	
*/	 	

	$dbMySQL = new MySQLDB;
 	$dbh = $dbMySQL->ConnectDB();
	if ($dbh == null) {
		return;
	}

	$accountInfo = array( array ( 'uid' => 'eljjanggu', 'upw' => '1', 'nick' => '성정국' )
	                     ,array ( 'uid' => 'keenkeen', 'upw' => '1', 'nick' => '김응룡' )
						 ,array ( 'uid' => 'teagyun012', 'upw' => '1', 'nick' => '김태균' )
						 ,array ( 'uid' => 'tigersound1', 'upw' => '1', 'nick' => '김호성' )
						 ,array ( 'uid' => 'fxclimber', 'upw' => '1', 'nick' => '서은정' )
						 ,array ( 'uid' => 'proline1', 'upw' => '1', 'nick' => '엄두현' )
						 ,array ( 'uid' => 'baruzi', 'upw' => '1', 'nick' => '이승완' )
						 ,array ( 'uid' => 'astanya', 'upw' => '1', 'nick' => '인상철' )
						 ,array ( 'uid' => 'clansta', 'upw' => '1', 'nick' => '엄정학' )
						 ,array ( 'uid' => 'moonihan', 'upw' => '1', 'nick' => '한문희' )
						 ,array ( 'uid' => 'siders1', 'upw' => '1', 'nick' => '경헝선' )
						 ,array ( 'uid' => 'gauguin78', 'upw' => '1', 'nick' => '고경민' )
						 ,array ( 'uid' => 'duky99', 'upw' => '1', 'nick' => '김덕희' )
						 ,array ( 'uid' => 'dudckss', 'upw' => '1', 'nick' => '김영찬' )
						 ,array ( 'uid' => 'andjtdmfhgkw', 'upw' => '1', 'nick' => '김정호' )
						 ,array ( 'uid' => 'fullmoon108', 'upw' => '1', 'nick' => '김한희' )
						 ,array ( 'uid' => 'nyjdream', 'upw' => '1', 'nick' => '남유정' )
						 ,array ( 'uid' => 'codjjang2', 'upw' => '1', 'nick' => '박종화' )
						 ,array ( 'uid' => 'bbaik100', 'upw' => '1', 'nick' => '백보헌' )
						 ,array ( 'uid' => 'dict999', 'upw' => '1', 'nick' => '서승원' )

						 ,array ( 'uid' => 'artis3d', 'upw' => '1', 'nick' => '신광우' )
	                     ,array ( 'uid' => 'shinhaww', 'upw' => '1', 'nick' => '신동근' )
						 ,array ( 'uid' => 'bluezima', 'upw' => '1', 'nick' => '신동욱' )
						 ,array ( 'uid' => 'skywoogi', 'upw' => '1', 'nick' => '이상욱' )
						 ,array ( 'uid' => 'siaaano', 'upw' => '1', 'nick' => '이은이' )
						 ,array ( 'uid' => 'soriallhs', 'upw' => '1', 'nick' => '이효수' )
						 ,array ( 'uid' => 'sesjws', 'upw' => '1', 'nick' => '장우석' )
						 ,array ( 'uid' => 'changth', 'upw' => '1', 'nick' => '장재운' )
						 ,array ( 'uid' => 'klautz', 'upw' => '1', 'nick' => '장진식' )
						 ,array ( 'uid' => 'jrobinson', 'upw' => '1', 'nick' => '조성훈' )
						 ,array ( 'uid' => 'ozzywow', 'upw' => '1', 'nick' => '홍진국' )
						 ,array ( 'uid' => 'shubarub7', 'upw' => '1', 'nick' => '강건율' )
						 ,array ( 'uid' => 'kanggkh', 'upw' => '1', 'nick' => '강건호' )
						 ,array ( 'uid' => 'x-rockersj', 'upw' => '1', 'nick' => '강성준' )
						 ,array ( 'uid' => 'rulrulru', 'upw' => '1', 'nick' => '강은미' )
						 ,array ( 'uid' => 'kang30201', 'upw' => '1', 'nick' => '강현수' )
						 ,array ( 'uid' => 'leneia', 'upw' => '1', 'nick' => '고규환' )
						 ,array ( 'uid' => 'ryvius11202', 'upw' => '1', 'nick' => '김경모' )
						 ,array ( 'uid' => 'woongs17', 'upw' => '1', 'nick' => '김경웅' )
						 ,array ( 'uid' => 'crazydd1', 'upw' => '1', 'nick' => '김다희' )

						 ,array ( 'uid' => 'zpdldhs', 'upw' => '1', 'nick' => '김명현' )
	                     ,array ( 'uid' => 'cgkmk', 'upw' => '1', 'nick' => '김미경' )
						 ,array ( 'uid' => 'rurounimk', 'upw' => '1', 'nick' => '김민경' )
						 ,array ( 'uid' => 'stwds', 'upw' => '1', 'nick' => '김민진' )
						 ,array ( 'uid' => 'railbowsos', 'upw' => '1', 'nick' => '김아름' )
						 ,array ( 'uid' => 'rladlf554', 'upw' => '1', 'nick' => '김일' )
						 ,array ( 'uid' => 'truewar', 'upw' => '1', 'nick' => '김진실' )
						 ,array ( 'uid' => 'wls2564', 'upw' => '1', 'nick' => '김진훈' )
						 ,array ( 'uid' => 'picture56', 'upw' => '1', 'nick' => '김하나' )
						 ,array ( 'uid' => 'gurimeke', 'upw' => '1', 'nick' => '나지혜' )
						 ,array ( 'uid' => 'autuln', 'upw' => '1', 'nick' => '류성민' )
						 ,array ( 'uid' => 'mesus', 'upw' => '1', 'nick' => '문철현' )
						 ,array ( 'uid' => 'formatlove', 'upw' => '1', 'nick' => '박노현' )
						 ,array ( 'uid' => 'saiyuki1', 'upw' => '1', 'nick' => '박미연' )
						 ,array ( 'uid' => 'psw9358', 'upw' => '1', 'nick' => '박승원' )
						 ,array ( 'uid' => 'redjokerv', 'upw' => '1', 'nick' => '신재영' )
						 ,array ( 'uid' => 'jinky1001', 'upw' => '1', 'nick' => '오진경' )
						 ,array ( 'uid' => 'wwk1227', 'upw' => '1', 'nick' => '우황균' )
						 ,array ( 'uid' => 'bumsik2', 'upw' => '1', 'nick' => '윤범식' )
						 ,array ( 'uid' => 'dbsdhksdud', 'upw' => '1', 'nick' => '윤완영' )

						 ,array ( 'uid' => 'yoonicon83', 'upw' => '1', 'nick' => '이미애' )
	                     ,array ( 'uid' => 'ghltordllo', 'upw' => '1', 'nick' => '이슬' )
						 ,array ( 'uid' => 'rijun01', 'upw' => '1', 'nick' => '이승준' )
						 ,array ( 'uid' => 'dlwkddnj', 'upw' => '1', 'nick' => '이장원' )
						 ,array ( 'uid' => 'idury', 'upw' => '1', 'nick' => '이지수' )
						 ,array ( 'uid' => 'hellow2002', 'upw' => '1', 'nick' => '이천희' )
						 ,array ( 'uid' => 'layla12', 'upw' => '1', 'nick' => '임경빈' )
						 ,array ( 'uid' => 'oliviasay', 'upw' => '1', 'nick' => '임정애' )
						 ,array ( 'uid' => 'geenius', 'upw' => '1', 'nick' => '전승환' )
						 ,array ( 'uid' => 'day2story', 'upw' => '1', 'nick' => '전재홍' )
						 ,array ( 'uid' => 'reptilia1203', 'upw' => '1', 'nick' => '정인식' )
						 ,array ( 'uid' => 'vuvle', 'upw' => '1', 'nick' => '정진혁' )
						 ,array ( 'uid' => 'bd1982', 'upw' => '1', 'nick' => '정회성' )
						 ,array ( 'uid' => 'isp2536', 'upw' => '1', 'nick' => '주원영' )
						 ,array ( 'uid' => 'buggist', 'upw' => '1', 'nick' => '진백인' )
						 ,array ( 'uid' => 'dudooo', 'upw' => '1', 'nick' => '최은영' )
						 ,array ( 'uid' => 'islandwave', 'upw' => '1', 'nick' => '최중효' )
						 ,array ( 'uid' => 'ringling80', 'upw' => '1', 'nick' => '최현호' )
						 ,array ( 'uid' => 'jiyoungbaby', 'upw' => '1', 'nick' => '황지영' )
						 ,array ( 'uid' => 'smkang', 'upw' => '1', 'nick' => '강성민' )

						 ,array ( 'uid' => 'drawingm', 'upw' => '1', 'nick' => '문윤철' )
	                     ,array ( 'uid' => 'shini1999', 'upw' => '1', 'nick' => '신민석' )
						 ,array ( 'uid' => 'jdw1811', 'upw' => '1', 'nick' => '진동욱' )
						 ,array ( 'uid' => 'han880', 'upw' => '1', 'nick' => '한상현' )
						 ,array ( 'uid' => 'timgo', 'upw' => '1', 'nick' => '김아름' )
						 ,array ( 'uid' => 'shincj', 'upw' => '1', 'nick' => '김일' )
						 ,array ( 'uid' => 'amillia', 'upw' => '1', 'nick' => '김진실' )
						 ,array ( 'uid' => 'zoenzi', 'upw' => '1', 'nick' => '김진훈' )
						 ,array ( 'uid' => 'u4us72', 'upw' => '1', 'nick' => '김하나' )
						 ,array ( 'uid' => 'jinihorse', 'upw' => '1', 'nick' => '나지혜' )
						 ,array ( 'uid' => 'giman', 'upw' => '1', 'nick' => '류성민' )
						 ,array ( 'uid' => 'nemogrim', 'upw' => '1', 'nick' => '문철현' )
						 ,array ( 'uid' => 'bary0212', 'upw' => '1', 'nick' => '박노현' )
						 ,array ( 'uid' => 'p3wbears', 'upw' => '1', 'nick' => '윤기범' )
						 ,array ( 'uid' => 'beomsun96', 'upw' => '1', 'nick' => '황범순' )
						 ,array ( 'uid' => 'unity2real', 'upw' => '1', 'nick' => '이준일' )
						 ,array ( 'uid' => 'endof0611', 'upw' => '1', 'nick' => '장동연' )
						 ,array ( 'uid' => 'sungsu101', 'upw' => '1', 'nick' => '김성수' )
						 ,array ( 'uid' => 'anwnxor', 'upw' => '1', 'nick' => '황용재' )
						 ,array ( 'uid' => 'cobono', 'upw' => '1', 'nick' => '최석원' )
						);
	
	foreach( $accountInfo as $k => $v ) {

		$sqlQuery = sprintf( "call usp_account_i( @o_result, @i_user_id, @i_user_pw, @i_nickname, @o_user_no )" );
		$sth = $dbh->prepare($sqlQuery);
			
		try {
			$dbh->query( sprintf( "set @i_user_id = '%s'", $v['uid'] ) );
			$dbh->query( sprintf( "set @i_user_pw = '%s'", $v['upw'] ) );
			$dbh->query( sprintf( "set @i_nickname = '%s'", $v['nick'] ) );
							
			if ($sth->execute() == false) {
				$errMsg = sprintf( "Query:%s", $sqlQuery );
				print ( $errMsg );				
			}
			
			$dataList = array();		
			$dataList[] = $sth->fetchAll();
				
			$outResult = $dataList[0][0]['o_result'];
			if( 0 != $outResult ) {
				if( 1 == $outResult ) {
					$errMsg = sprintf( "Already registered ID !!! (UserID:%s)", $userID );				
					print ( $errMsg );	
				}
				else if ( 2 == $outResult ) {
					$errMsg = sprintf( "Already registered Nickname !!! (Nickname:%s)", $nickName );
					print ( $errMsg );			
				}
			}
			
			var_dump( $dataList );

			$outUserNo = $dataList[0][0]['o_user_no'];
			
			print($outUserNo);
							
			$sth->closeCursor();
			unset($sth);		
		}
		catch (PDOException $err) {
			$errMsg = Utility::GetExceptionDataString($err);
			print ( $errMsg );
		}
	}
/* 
	$dbMySQL = new MySQLDB;
 	$dbh = $dbMySQL->ConnectDB();
	if ($dbh == null) {
		return;
	}
		
	$userID = 'justin72';
							
	$sqlQuery = sprintf("call usp_account_by_user_id_s( @i_user_id )");
	$sth = $dbh->prepare($sqlQuery);
			
	try {
		$dbh->query( sprintf( "set @i_user_id = '%s'", $userID ) );
						
		if ($sth->execute() == false) {
			$errMsg = sprintf( "Query:%s", $sqlQuery );
			print( $errMsg );			
		}
		
		$dataList = array();		
		$dataList = $sth->fetchAll();
		
		var_dump( $dataList );
		
		if ( 0 < count( $dataList ) ) {
			$errMsg = sprintf( "Already registered ID !!! (UserID:%s)", $userID );
			print( $errMsg );
		}
		
		print( "success !!!" );
			
		$sth->closeCursor();
		unset($sth);		
	}
	catch (PDOException $err) {
		$errMsg = Utility::GetExceptionDataString($err);
		print ( $errMsg );
	}	
*/
 /*
 	$a = 720919;
 	$b = "cp_gold_100";
 	$c = date("Y-m-d H:i:s", time());
		
	$dbMySQL = new MySQLDB;
 	$dbh = $dbMySQL->ConnectDB();
	if ($dbh == null) {
		return;
	}
							
	$sqlQuery = sprintf("call usp_test_i( @param_o, @param_a, @param_b, @param_c )");
	$sth = $dbh->prepare($sqlQuery);
				
	try {
		$dbh->query( sprintf( "set @param_a = %s", $a ) );
		$dbh->query( sprintf( "set @param_b = '%s'", $b ) );
		$dbh->query( sprintf( "set @param_c = '%s'", $c ) );

		if ($sth->execute() == false) {
			print( sprintf("Failed execute !!! - Query:%s, ArgList:a=%s,b=%s,c=%s", $a, $b, $c) );	
			return;
		}
		
		$datalist = $sth->fetchAll();
		
		$outParam = $datalist[0][0]['param_o'];		
		print($outParam);
	} 
	catch (PDOException $err) {
		print("Test exception !!! - ".Utility::GetExceptionDataString($err));
		return;
	}
*/
/*
	$userID = 720919;
	$logDate = date("Y-m-d H:i:s", time());
	$productID = 'cp_gold_1000';
	$amount = 10;
	$outTryID = 0;
	
	$dbMySQL = new MySQLDB;
 	$dbh = $dbMySQL->ConnectDB();
	if ($dbh == null) {
		return;
	}
							
	$sqlQuery = sprintf("call usp_payment_begin_i( @userID, @logDate, @productID, @amount, @outTryID )");
	$sth = $dbh->prepare($sqlQuery);
			
	try {
		$dbh->query( sprintf( "set @userID = %s", $userID ) );
		$dbh->query( sprintf( "set @logDate = '%s'", $logDate ) );
		$dbh->query( sprintf( "set @productID = '%s'", $productID ) );
		$dbh->query( sprintf( "set @amount = %s", $amount ) );		
						
		if ($sth->execute() == false) {
			print( sprintf("Failed execute !!! - Query:%s, ArgList:TryID=%s,UserID=%s", $sqlQuery, $outID, $userID) );					
			return;
		}
		
		$datalist = array();		
		$datalist[] = $sth->fetchAll();
								
		$outTryID = $datalist[0][0]['outTryID'];
		print($outTryID);
					
		$sth->closeCursor();
		unset($sth);		
	}
	catch (PDOException $err) {
		print("Test exception !!! - ".Utility::GetExceptionDataString($err));
		return;
	}
*/
/*	
	$tryID = 1;
	$orderID = 10;
	$userID = 720919;
	$logDate = '';
	$productID = 'cp_gold_1000'; 
	$packageName = ' 방울팩(1000)'; 
	$amount = 10;
	$addGold = 0;
	$finalGold = 0; 
	$purchaseTime = '';
	
	$dbMySQL = new MySQLDB;
 	$dbh = $dbMySQL->ConnectDB();
	if ($dbh == null) {
		return;
	}
		
	$sqlQuery = sprintf("call usp_payment_end_i( @tryID, @orderID, @userID, @logDate, @productID, @packageName, @amount, @addGold, @finalGold, @purchaseTime )");
	$sth = $dbh->prepare($sqlQuery);
		
	try {
			$dbh->query( sprintf( "set @tryID = %s", $tryID ) );	
			$dbh->query( sprintf( "set @orderID = %s", $orderID ) );
			$dbh->query( sprintf( "set @userID = %s", $userID ) );
			$dbh->query( sprintf( "set @logDate = %s", $logDate ) );
			$dbh->query( sprintf( "set @productID = %s", $productID ) );
			$dbh->query( sprintf( "set @packageName = %s", $packageName ) );			
			$dbh->query( sprintf( "set @amount = %s", $amount ) );			
			$dbh->query( sprintf( "set @addGold = %s", $addGold ) );
			$dbh->query( sprintf( "set @finalGold = %s", $finalGold ) );
			$dbh->query( sprintf( "set @purchaseTime = %s", $purchaseTime ) );
			
		if ($sth->execute() == false) {
			print( sprintf("Failed execute !!! - Query:%s, ArgList:UserID=%s", $sqlQuery, $userID) );
			return;
		}

		$paymentLoseList = $sth->fetchAll();
		
					
	} 
	catch (PDOException $err) {
		print("PaymentLog Exception !!! GetPaymentEndLog - ".Utility::GetExceptionDataString($err));	
		return;
	}
*/	
	
	
/*	 
	$userID = '720919';
	$paymentLoseList = array();
	
	$dbMySQL = new MySQLDB;
 	$dbh = $dbMySQL->ConnectDB();
	if ($dbh == null) {
		return;
	}
		
	$sqlQuery = sprintf("call usp_payment_lose_s( @userID )");
	$sth = $dbh->prepare($sqlQuery);
		
	try {
		$dbh->query( sprintf( "set @userID = %s", $userID ) );
		if ($sth->execute() == false) {
			print( sprintf("Failed execute !!! - Query:%s, ArgList:UserID=%s", $sqlQuery, $userID) );
			return;
		}

		$paymentLoseList = $sth->fetchAll();
		
		
					
		} catch (PDOException $err) {
			print("PaymentLog Exception !!! GetPaymentEndLog - ".Utility::GetExceptionDataString($err));	
		return;
	}
	
	foreach( $paymentLoseList as $k ) {
		 print($k['TRYID']);
		 print($k['ORDERID']);
		 print($k['EMAIL']);
		 print($k['LOGDATE']);
		 print($k['PRODUCTID']);
		 print($k['PAKAGENAME']);
		 print($k['AMOUNT']);
	}
*/	
	
?>
