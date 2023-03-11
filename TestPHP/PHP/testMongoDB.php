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


// MongoDB 테스트 예제
try {


	// DB 연결 하기

	$mongo = new MongoClient( "mongodb://127.0.0.1" );
	$testDB = $mongo->test;

	// DB 선택 & Collection 선택
/*	
	$testDB = $mongo->test; // 암시적 DB 선택
	$testDB = $mongo->selectDB( 'test' ); // 명시적 DB 선택
	var_dump( $testDB );
	$collection = $testDB->user; // 암시적 Collection 선택
	$collection = $testDB->selectCollection( 'user' ); // 명시적 Collection 선택
	var_dump( $collection );
*/

	// Document 추가 하기
/*	
	$testDB->user->insert( array( 'title' => 'blog title' , 'content' => 'blog content', 'x' => 50 ) ,
	                       array( 'safe' => True ) ); // 안전 추가
*/
/*	                       
	// Timeout 설정                       
	$testDB->user->insert( array( 'title' => 'good' , 'content' => 'hi !!!', 'x' => 100 ) ,
	                       array( 'safe' => True,
						          'timeout' => True ) ); // 요청 최대 대기 시간 적용
*/
/*
	// 사용자 id 활용 - 사용자 '_id' 값을 입력시 중복된 경우 예외 발생 !!!
	$username = 'justin';
	$document = array( '_id' => hash( 'sha1', $username.time() ) , 
	                   'title' => 'bad' ,
                       'content' => 'bye !!!',
                       'x' => 150 );
                                          
	$testDB->user->insert( $document, 
	                       array( 'w' => True, 'socketTimeoutMS' => 200 ) ); // 요청 최대 대기 시간 지정 ( milli-second )

	$testDB->user->ensureIndex( 'title', array( 'unique' => true ) );
*/
/*
	// Unique index 설정후에 중복된 경우 예외 발생 !!!
	$username = 'justin';
	$document = array( '_id' => hash( 'sha1', $username.time() ) , 
	                   'title' => 'bad' ,
                       'content' => 'hi !!!',
                       'x' => 250 );
                                          
	$testDB->user->insert( $document, 
	                       array( 'w' => True, 'socketTimeoutMS' => 200 ) ); // 요청 최대 대기 시간 지정 ( milli-second )
*/
/*
	// 사용자 id
	$timestamp = new MongoDate( time() );
	
	$username = 'july';
	$document = array( '_id' => hash( 'sha1', $username.time() ) , 
	                   'title' => 'bad' ,
                       'content' => 'bye !!!',
                       'x' => 200,
                       'reg_date' => $timestamp );
                                          
	$testDB->user->insert( $document, 
	                       array( 'safe' => True, 'timeout' => 3000 ) );                  
*/
/*
	$document =  array( 'title' => 'saturday night movie', 'content' => 'drama' );
	$testDB->user->save( $document );
*/

	// Document 조회
/*
	$cursor = $testDB->user->find(); // 전체 조회
	while( $cursor->hasNext() ) {
		
		$data = $cursor->getNext();
		var_dump( $data );
	}
*/
/*
	$cursor = $testDB->user->find( array( 'title' => 'bad' ) ); // 조건 조회
	while( $cursor->hasNext() ) {
		
		$data = $cursor->getNext();
		var_dump( $data );
	}
*/
/*	
	$cursor = $testDB->user->find( array( 'title' => 'bad' ) ); // 조건 조회
	if ( $cursor->count() > 0 ) {
		foreach ( $cursor as $movie ) {
			var_dump( $movie );
		}
	}
*/
/*	
	$data = $testDB->user->findOne( array( 'title' => 'bad' ) ); // 조건 조회 & 단일 조회
	var_dump( $data );
*/
/*	
	// $gt  : 초과 하는 모든 항목
	$cursor = $testDB->user->find( array( 'x' => array( '$gt' => 100 ) ) );
	while( $cursor->hasNext() ) {
		
		$data = $cursor->getNext();
		var_dump( $data );
	}
*/
/*	
	// $lt  : 미만인 모든 항목	
	$cursor = $testDB->user->find( array( 'x' => array( '$lt' => 100 ) ) );
	while( $cursor->hasNext() ) {
		
		$data = $cursor->getNext();
		var_dump( $data );
	}
*/
/*	
	// $gte : 이상인 모든 항목
	$cursor = $testDB->user->find( array( 'x' => array( '$gte' => 100 ) ) );
	while( $cursor->hasNext() ) {
		
		$data = $cursor->getNext();
		var_dump( $data );
	}	
*/
/*	
	// $lte : 이하인 모든 항목
	$cursor = $testDB->user->find( array( 'x' => array( '$lte' => 100 ) ) );
	while( $cursor->hasNext() ) {
		
		$data = $cursor->getNext();
		var_dump( $data );
	}	
*/
/*
	$cursor = $testDB->user->find( array( 'x' => array( '$gte' => 100, '$lte' => 100 ) ) );
	while( $cursor->hasNext() ) {
		
		$data = $cursor->getNext();
		var_dump( $data );
	}	
*/
/*
	// $ne  : 같지 않는 모든 항목
	$cursor = $testDB->user->find( array( 'x' => array( '$ne' => 100 ) ) );
	while( $cursor->hasNext() ) {
		
		$data = $cursor->getNext();
		var_dump( $data );
	}		
*/
/*
	// 정규식 조회
	// $regex
	$cursor = $testDB->user->find( array( 'title' => array( '$regex' => 'a', '$options' => 'i' ) ) );
	while( $cursor->hasNext() ) {
		
		$data = $cursor->getNext();
		var_dump( $data );
	}		
*/	
/*
	// 특정 필드만 출력
	$cursor = $testDB->user->find( array(), array( 'title' => 1, 'x' => 1 ) );
	while( $cursor->hasNext() ) {
		
		$data = $cursor->getNext();
		var_dump( $data );
	}		
*/
/*
	$cursor = $testDB->user->find();
	$cursor->sort( array( 'x' => -1 ) ); // 내림 차순 정렬
//	$cursor->sort( array( 'x' => 1 ) ); // 오름 차순 정렬
	while( $cursor->hasNext() ) {
		
		$data = $cursor->getNext();
		var_dump( $data );
	}		
*/

/*
	$cursor = $testDB->user->find();
	$count = $cursor->count();
	var_dump( $count ); // 요소의 갯수 반환
*/
/*
	$cursor = $testDB->user->find();
	$cursor->skip( 2 ); // 앞쪽 2개 요소를 제외 시키고 적재 !!!
	while( $cursor->hasNext() ) {
		
		$data = $cursor->getNext();
		var_dump( $data );
	}		
*/
/*
	$cursor = $testDB->user->find();
	$cursor->limit( 3 ); // 앞쪽 3개 요소만 적재 !!!
	while( $cursor->hasNext() ) {
		
		$data = $cursor->getNext();
		var_dump( $data );
	}	
*/
/*
	$cursor = $testDB->user->find();
	$cursor->sort( array( 'x' => -1 ) )->skip( 1 )->limit( 2 ); // 복합 처리 !!!
	while( $cursor->hasNext() ) {
		
		$data = $cursor->getNext();
		var_dump( $data );
	}	
*/
/*
	$date = strtotime( '-1 week' ); // 1주일 전
//	$date = strtotime( '1 week' ); // 1주일 후
	var_dump( $date );
	$lastWeek = new MongoDate( $date ); //
	$cursor = $testDB->user->find( array( 'reg_date' => array( '$gt' => $lastWeek ) ) ); // 해당 시간을 초과 하는 모든 것 !!!
	while( $cursor->hasNext() ) {
		
		$data = $cursor->getNext();
		var_dump( $data );
	}	
*/
/*
	$startDate = new MongoDate( strtotime( '2011-05-01 22:00:00' ) );
	$endDate = new MongoDate( strtotime( '2014-05-01 22:00:00' ) );
	$cursor = $testDB->user->find( array( 'reg_date' => array( '$gte' => $startDate, 
	                                                           '$lte' => $endDate ) ) ); // 시간 구간에 해당하는 모든 것 !!!
	while( $cursor->hasNext() ) {
		
		$data = $cursor->getNext();
		var_dump( $data );
	}	
*/
	// Document 갱신
/*	
	// title 에 해당 document 를 content 로 갱신
	$testDB->user->update( array( 'title' => 'good' ), array( 'content' => 'action' ) );
*/
/*
	// document 내의 특정 필드만 갱신
	$testDB->user->update( array( 'title' => 'blog title' ),
	                              array( '$set' => array( 'content' => 'SF genre' ) ),
	                              array( 'safe' => True, // 안전 갱신 
								         'multiple' => True, // 조건에 맞으면 모두 적용
										 'timeout' => 2000 ) ); // 요청 최대 대기 시간
*/
/*
	// document 내에 필드명 ":" 사용 가능
	$cursor = $testDB->user->insert( array( 'title' => 'good title', 'content' => 'good content', "address:city" => 'Caprica' )
		                           , array( 'w' => True ) );

	// document 내의 특정 필드를 조회할 경우 "." 사용 가능 !!!
	$cursor = $testDB->user->find( array( 'address.city' => 'Caprica' ) );
	while( $cursor->hasNext() ) {
		
		$data = $cursor->getNext();
		var_dump( $data );
	}
*/
/*
	// document 내의 특정 필드도 함께 추가 ( document 내에 document 를 추가할 경우 array 형태로 등록 해야 함 !!! )
	$cursor = $testDB->user->insert( array( 'title' => 'good title', 'content' => 'good content', 'address' => array( 'city' => 'Caprica' ) )
		                           , array( 'w' => True ) );

	// document 내의 특정 필드를 조회
	$cursor = $testDB->user->find( array( 'address.city' => 'Caprica' ) );
	while( $cursor->hasNext() ) {
		
		$data = $cursor->getNext();
		var_dump( $data );
	}
*/
/*
	// document 내의 특정 필드를 갱신 & 추가
	$testDB->user->update( array( 'title' => 'bad' ),
		                   array( '$set' => array( 'content' => 'horror', 'y' => 600 ) ) );	
*/
/*	
	// document 내의 대상이 아닌 필드는 제거 하고 갱신 & 추가
	$testDB->user->update( array( 'title' => 'bad' ),
		                   array( 'content' => 'horror', 'y' => 600 ),
		                   array( 'upsert' => True ) );
*/
/*
	// $inc 지정된 필드값을 증가
	$testDB->user->update( array( 'content' => 'horror' ),
		                   array( '$inc' => array( 'y' => 1 ) ) );
*/
/*
	// $unset 지정된 필드 삭제
	$testDB->user->update( array( 'content' => 'horror' ),
		                   array( '$unset' => array( 'y' => True ) ) );
*/
/*
	// $rename 지정된 필드명 변경
	$testDB->user->update( array( 'content' => 'horror' ),
		                   array( '$rename' => array( 'content' => 'go back' ) ) );
*/

	// Document 삭제
/*
	$testDB->user->remove( array( 'go back' => 'horror' ),
		                   array( 'justOne' => True, // 한개만 삭제
						          'safe' => True,  // 안전한 삭제
								  'timeout' => 3000 ) ); // 요청 최대 대기 시간	
*/

	// Document 내에 여러 Data 추가
/*
	$address = array( 'street' => '13 Tannhauser Gate',
		              'city' => 'Caprica',
		              'state' => 'CC',
	                  'zipcode' => 512 );

	$testDB->user->update( array( 'title' => 'blog title' ),
		                   array( '$push' => array( 'address' => $address ) ) );
*/

	// Document 집계
/*
	// group 기본 - 반환 항목은 16MB 미만, 구분 되는 Key가 1만개 이하일 경우만 사용 가능 !!!
	$testDB->user->insert( array('category' => 'fruit', 'name' => 'apple') );
	$testDB->user->insert( array('category' => 'fruit', 'name' => 'peach') );
	$testDB->user->insert( array('category' => 'fruit', 'name' => 'banana') );
	$testDB->user->insert( array('category' => 'veggie', 'name' => 'corn') );
	$testDB->user->insert( array('category' => 'veggie', 'name' => "broccoli") );

	$keys = array( 'category' => 1 ); // Document 를 그룹 짓기 위한 키나 집합을 명세
	$initial = array( 'items' => array() ); // 기준 집계 연산 카운터로 집계 연산 전에 초기 값을 명세
	$reduce = "function ( obj, prev ) { prev.items.push( obj.name ); }"; // Document 를 집계 연산 하는 Reduce 로, 순회를 시작할 현재 Document 와 집계 연산 카운터를 인수로 받음

	$result = $testDB->user->group( $keys, $initial, $reduce );
	var_dump( $result );

	echo json_encode($result['retval']);
*/
/*
	// group 응용
	$testDB->user->save( array( 'user_id' => 'justin', 'gold' => 10, 'reg_date' => new MongoDate( time() ) ) );
	$testDB->user->save( array( 'user_id' => 'jully', 'gold' => 20, 'reg_date' => new MongoDate( time() ) ) );
	$testDB->user->save( array( 'user_id' => 'crazy', 'gold' => 30, 'reg_date' => new MongoDate( strtotime('2015-05-01 22:00:00') ) ) );

	// use all fields
	$keys = array( 'user_id' );

	// set intial values
	$initial = array( 'count' => 0, 'avg_gold' => 0, 'total_gold' => 0 );

	// JavaScript function to perform
	$reduce = 'function (obj, counter) { counter.count++; counter.total_gold += obj.gold; }';

	$condition = array( 'reg_date' => array( '$gt' => new MongoDate( strtotime('2013-05-01 22:00:00') ) ) ); // 질의 객체. 이 질의와 일치 하는 Document 만 그룹을 짓기 위해 사용
	
	$finalize = 'function (counter) { counter.avg_gold = Math.round( counter.total_gold / counter.count ); }'; // 항목을 반환 하기 전에 결과 집합에서 각 항목을 순회 하며 실행 하는 함수
	
	$lastAction = array( 'finalize' => $finalize, 'condition' => $condition );

	$result = $testDB->user->group( $keys, $initial, $reduce, $lastAction );

	var_dump($result);
*/
/*
	// distinct - 유일한 것들로 반환
	$testDB->user->insert( array( 'stuff' => 'bar', 'zip-code' => 10010 ) );
	$testDB->user->insert( array( 'stuff' => 'foo', 'zip-code' => 10010 ) );
	$testDB->user->insert( array( 'stuff' => 'bar', 'zip-code' => 99701 ), array('w' => 1) );

	$retval = $testDB->user->distinct( 'zip-code' );
	var_dump($retval);

	$retval = $testDB->user->distinct( 'zip-code', array( 'stuff' => 'foo' ) );
	var_dump($retval);

	$retval = $testDB->user->distinct( 'zip-code', array( 'stuff' => 'bar' ) );
	var_dump($retval);
*/
/*
	// count - Document 갯수 반환
	$testDB->user->insert(array( 'stuff' => 'bar', 'zip-code' => 10010) );
	$testDB->user->insert(array( 'stuff' => 'foo', 'zip-code' => 10010) );
	$testDB->user->insert(array( 'stuff' => 'bar', 'zip-code' => 99701), array('w' => 1) );

	$retval = $testDB->user->count( array('stuff' => 'bar') );
	var_dump($retval);
*/
/*
	// map reduce - map reduce 시스템 활용 ( JavaScript 연동 )
	$id = 'justin';
	$type = 'sale';
	$description = 'map reduce test';
	$testDB->user->insert(array( 'user_id' => $id, 
							     'type' => $type, 
							     'time' => new MongoDate(), 
							     'desc' => $description ) );

	// construct map and reduce functions
	$map = new MongoCode( 'function() { emit( this.user_id, 1 ); }' );
	$reduce = new MongoCode( 'function( k, vals ) { '.
						     'var sum = 0;'.
                             'for ( var i in vals ) {'.
                                 'sum += vals[i];'. 
                             '}'.
                             'return sum; }');

	$sales = $testDB->command( array( 'mapreduce' => 'user',
                                      'map' => $map,
                                      'reduce' => $reduce,
                                      'query' => array( 'type' => 'sale' ), // 제약 조건 설정
                                      'out' => array( 'merge' => 'user_list' ) ) ); // 지정된 Collection 으로 출력 !!!

	$users = $testDB->selectCollection( $sales['result'] )->find();

	while( $users->hasNext() ) {
		
		$data = $users->getNext();
		var_dump( $data );
	}
*/

/*
	// Spatial DB - 2D location 정보 등록

	$objTypeList = array( 'internet_cafe', 'restaurant', 'office', 'market', 'park' );
	$objTitleList = array( 'Position 1', 'Position 10', 'Position 100', 'Position 1000', 'Position 10000' );
	$objAddressList = array( array( '1' => '대한민국'
								   ,'2' => '경기도'
								   ,'3' => '성남시'
								   ,'4' => '분당구' ),
						     array( '1' => '대한민국'
								   ,'2' => '서울시'
								   ,'3' => '동작구'
								   ,'4' => '신대방동' ),
                             array( '1' => '대한민국'
								   ,'2' => '서울시'
								   ,'3' => '서초구'
								   ,'4' => '우면동' ),
                             array( '1' => '대한민국'
								   ,'2' => '서울시'
								   ,'3' => '양천구'
								   ,'4' => '목동' ),
		                    );


	// Spatial DB - 기본
	$geoDB = $mongo->geolocation;
	$poiColl = $geoDB->selectCollection( 'poi' );
	if ( null != $poiColl ) {
		$poiColl->drop();
	}

	$poiColl = $geoDB->selectCollection( 'poi' ); // 명시적 Collection 생성 및 선택

	MongoCursor::$timeout = -1; // 응답 대기 무한 설정
	
	// seed 생성
	srand( GetMicroTime() );

	$location = array();
	for( $i = 0; $i < 100000; $i++ ) {
		
		$location = array( ( rand( 0, 180000000 ) / 1000000 ), ( rand( 0, 180000000 ) / 1000000 ) );
		$address = $objAddressList[ rand( 0, count($objAddressList) - 1 ) ];

		$poiColl->insert( array( '_id' => ( 1000 + $i ), 
								 'address' => array( '1' => 'good' ),
			                     'obj_type' => $objTypeList[ rand( 0, sizeof( $objTypeList ) - 1 ) ],
                                 'obj_title' => $objTitleList[ rand( 0, sizeof( $objTitleList ) - 1 ) ],
							     'address' => array( '1' => $address['1']
												    ,'2' => $address['2']
												    ,'3' => $address['3']
												    ,'4' => $address['4'] ),
			                     'location' => $location ),
			              array( 'safe' => True ) );

		// Geo 색인 생성
		$poiColl->ensureIndex( array( 'location' => '2d' ) );
	}
*/

	// Spatial DB - 2D location query
/*
	echo "<br>" . "Near 기반 조회 !!!" . "<br>";

	$pos = array( 20.00000, 20.000000 );
	$msg = sprintf( "Latitude:%s, Longitude:%s", $pos[0], $pos[1] );
	echo "<br>" . "기준 위치: " . $msg . "<br>";

	$time_start = GetMicrotime();
	// POI 정보 조회 - 근거리 기준
 	$cursor = $geoDB->poi->find( array( 'use_flag' => 1, 'location' => array( '$near' => $pos ) ) )->limit(1000); // 근거리 설정

	$result = $cursor->count();
	if ( isset( $result['ok'] ) && $result['ok'] == 0 ) {
		var_dump( $result );
	}
	else {
		$count = 0;
		while( $cursor->hasNext() ) {

			$count++;
			echo $count."<br>";	

			$data = $cursor->getNext();
			var_dump( $data );
		}
	}

	$time_end = GetMicrotime();

	$time = $time_end - $time_start;
	echo "<br>"."Result count: $count Elapsed Time: $time seconds"."<br>";
*/
/*
	// Spatial DB - 2D location query

	echo "<br>" . "Center 기반 조회 !!!" . "<br>";

	$searchFilter = array();
	$searchFilter['obj_type'] = 'internet_cafe';
	$searchFilter['obj_title'] = 'Position 10';
	$searchFilter['address.1'] = '대한민국';
	$searchFilter['address.2'] = '서울시';
	$searchFilter['address.3'] = '동작구';
	$searchFilter['address.4'] = '신대방동';

	$center = array( 90.000, 90.000 );
	$radius = 10;

	$msg = sprintf( "Latitude:%s, Longitude:%s", $center[0], $center[1] );
	echo "<br>" . "기준 위치: " . $msg . " 범위: $radius" . "<br>";

	$searchFilter['location'] = array( '$within' => array( '$center' => array( $center, $radius ) ) );

	$time_start = GetMicrotime();
	$cursor = $geoDB->poi->find( $searchFilter )->limit( 1000 );

	$result = $cursor->count();
	if ( isset( $result['ok'] ) && $result['ok'] == 0 ) {
		var_dump( $result );
	}
	else {

		$count = 0;
		while( $cursor->hasNext() ) {

			$count++;
			echo $count."<br>";	

			$data = $cursor->getNext();
			var_dump( $data );
		}
	}

	$time_end = GetMicrotime();

	$time = $time_end - $time_start;
	echo "<br>"."Result count: $count Elapsed Time: $time seconds"."<br>";	
*/
/*
	// Spatial DB - Haystack

	echo "<br>" . "Haystack 기반 Near 조회 !!!" . "<br>";

	// Geo Haystack 색인 생성 - 주의: Haystack 으로 지정된 필드는 geoHaystack 검색시에만 검색 filter 값으로 사용해야 함 !!!
	var_dump( $poiColl->ensureIndex( array( 'location' => 'geoHaystack', 'obj_title' => 1 ),
						             array( 'bucketSize' => 1 ) ) );

	// POI 정보 조회 - 내용 + 거리 조건 제약 기준
	$location = array( 30.000000, 30.000000 );
	$msg = sprintf( "Latitude:%s, Longitude:%s", $location[0], $location[1] );
	echo "<br>" . "기준 위치: " . $msg . "<br>";

	$query = array( 'geoSearch' => 'poi',
		            'near' => $location,
		            'search' => array( 'obj_title' => 'Position 10' ),
		            'maxDistance' => 10,
		            'limit' => 1000 );

	$time_start = GetMicrotime();

	$geoDB = $mongo->geolocation;
	$response = $geoDB->command( $query );

	$time_end = GetMicrotime();
	
	$count = 0;
	if( $response['ok'] == 0 ) {
		var_dump( $response );
	}
	else {
		foreach( $response['results'] as $result ) {
			$count++;
			var_dump( $result );
		}

		var_dump( $response['stats'] );
	}

	$time = $time_end - $time_start;
	echo "<br>"."Result count: $count Elapsed Time: $time seconds"."<br>";
*/
/*
	// Spatial DB - geoNear

	echo "<br>" . "geoNear 기반 Near 조회 !!!" . "<br>";

	// POI 정보 조회 - 내용 + 거리 조건 제약 기준
	$location = array( 30.000000, 30.000000 );
	$msg = sprintf( "Latitude:%s, Longitude:%s", $location[0], $location[1] );
	echo "<br>" . "기준 위치: " . $msg . "<br>";

	$query = array( 'geoNear' => 'poi',
		            'near' => $location,
		            'num' => 1000 );

	$time_start = GetMicrotime();

	$response = $geoDB->command( $query );

	$time_end = GetMicrotime();
	
	$count = 0;
	foreach( $response['results'] as $result ) {
		$count++;
		var_dump( $result );
	}

	var_dump( $response );

	$time = $time_end - $time_start;
	echo "<br>"."Result count: $count Elapsed Time: $time seconds"."<br>";
*/





	// Community DB 테스트
/*
	$testDB = $mongo->test; // 암시적 DB 선택
	$testDB = $mongo->selectDB( 'test' ); // 명시적 DB 선택
	var_dump( $testDB );
	$fallower = $testDB->selectCollection( 'fallower' ); // 명시적 Collection 선택
	var_dump( $fallower );

	$fallower->insert( array( 'user' => 'u_1' , 'target_user' => 'u_1000' ) ,
	                   array( 'safe' => True ) ); // 안전 추가

	$fallower->insert( array( 'user' => 'u_1' , 'target_user' => 'u_1001' ) ,
	                   array( 'safe' => True ) ); // 안전 추가

	$fallower->insert( array( 'user' => 'u_1' , 'target_user' => 'u_1002' ) ,
	                   array( 'safe' => True ) ); // 안전 추가

	$fallower->insert( array( 'user' => 'u_1' , 'target_user' => 'u_1003' ) ,
	                   array( 'safe' => True ) ); // 안전 추가

	$fallowing = $testDB->selectCollection( 'fallowing' ); // 명시적 Collection 선택
	var_dump( $fallowing );

	$fallowing->insert( array( 'user' => 'u_1' , 'target_user' => 'u_1000' ) ,
	                    array( 'safe' => True ) ); // 안전 추가

	$fallowing->insert( array( 'user' => 'u_1' , 'target_user' => 'u_1001' ) ,
	                    array( 'safe' => True ) ); // 안전 추가

	$fallowing->insert( array( 'user' => 'u_1' , 'target_user' => 'u_1002' ) ,
	                    array( 'safe' => True ) ); // 안전 추가

	$fallowing->insert( array( 'user' => 'u_1' , 'target_user' => 'u_1003' ) ,
	                    array( 'safe' => True ) ); // 안전 추가

	$friend = $testDB->selectCollection( 'friend' ); // 명시적 Collection 선택
	var_dump( $friend );

	$friend->insert( array( 'user' => 'u_1' , 'target_user' => 'u_1000' ) ,
	                 array( 'safe' => True ) ); // 안전 추가

	$friend->insert( array( 'user' => 'u_1' , 'target_user' => 'u_1001' ) ,
	                 array( 'safe' => True ) ); // 안전 추가

	$friend->insert( array( 'user' => 'u_1' , 'target_user' => 'u_1002' ) ,
	                 array( 'safe' => True ) ); // 안전 추가

	$friend->insert( array( 'user' => 'u_1' , 'target_user' => 'u_1003' ) ,
	                 array( 'safe' => True ) ); // 안전 추가
*/



	echo "<br>" . "Test End !!!" . "<br>";

} catch (Exception $e) {
	var_dump( $e );
	echo "<br>";

	echo "Excepted Mongo !!!";
	echo "<br>";
	var_dump( Utility::GetExceptionDataString( $e ) );
}

?>
