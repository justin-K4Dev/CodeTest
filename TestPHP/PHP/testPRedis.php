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

/*
	redis web site list
	
	http://www.redis.io/commands#generic
	http://minq.github.com/blog/2012/10/28/redis-commands/
	http://phpmaster.com/an-introduction-to-redis-in-php-using-predis/
	http://kerocat.tistory.com/1
*/

include_once 'Lib/Utility.php';

require_once 'Predis/Autoloader.php';
Predis\Autoloader::register();

try {

	$redis = new Predis \ Client(array (
		'host' => '127.0.0.1'
	));

	//////////////////////////////////////////////////////////////////////
	// Keys
	//////////////////////////////////////////////////////////////////////
	/*	
			// DEL key [key ...]
			$redis->set( "key1", "hello" );
			$redis->set( "key2", "world" );
			$redis->del( "key1", "key2", "key3" ); // or array( "key1", "key2", "key3" );
			$redis->del($keys);
			echo (($redis->exists( "key1" )) ? "true" : "false") . "<br>";			
			echo (($redis->exists( "key2" )) ? "true" : "false") . "<br>";
	*/
	// DUMP - not register !!!
	/*		
			// EXIST key
			$redis->set( "key1", "hello" );
			echo (($redis->exists( "key1" )) ? "true" : "false") . "<br>";
			echo (($redis->exists( "key2" )) ? "true" : "false") . "<br>";
	*/
	/*
			// EXPIRE key seconds
			$redis->set( "key1", "hello" );
			$redis->expire( "key1", 10 );
			$ttl = $redis->ttl("key1"); // 10 seconds
			var_dump($ttl);	
	*/
	/*
			// EXPIREAT key timestamp
			$redis->set( "key1", "hello" );
			$redis->expireat( "key1", strtotime("+1 week") ); // Unix timestamp (seconds since January 1, 1970)
			echo (($redis->exists( "key1" )) ? "true" : "false") . "<br>";
			$ttl = $redis->ttl("key1");
			var_dump($ttl);
	*/
	/*
			// KEYS pattern
			$param = array( 'one' => 1, 'two' => 2, 'three' => 3, 'four' => 4 );				
			$redis->mset( $param );		
			// supported glob-style patterns *, ?, []
			$retValue = $redis->keys( "*" );
			var_dump($retValue);
			$retValue = $redis->keys( "t??" );
			var_dump($retValue);
			$retValue = $redis->keys( "t[wh]o" );
			var_dump($retValue);
			$redis->del( 'one', 'two', 'three', 'four' );			
	*/
	/*
	 		// MIGRATE not test		
	*/
	/*
	 		// MOVE not test		
	*/
	/*
	 		// OBJECT not test		
	*/
	/*
			// PERSIST key
			// expires
			$redis->set( "key1", "hello" );
			$redis->expire( "key1", 10 );
			$ttl = $redis->ttl( "key1" ); // 10 seconds
			var_dump($ttl);		
			// never expires - remove the expiration from a key
			$redis->persist( "key1" );
			$ttl = $redis->ttl( "key1" ); // -1
			var_dump($ttl);
	*/
	/*
			// PEXPIRE not register
	*/
	/*
			// PEXPIREAT not register
	*/
	/*
			// PTTL not register
	*/
	/*
			// RANDOMKEY
			$randkey = $redis->randomkey();
			var_dump($randkey);
	*/
	/*
			// RENAME key newkey
			$redis->set( "key1", "hello" );
			$redis->rename( "key1", "key10" );
			$retValue = $redis->get( "key10" );
			var_dump($retValue);		
			echo (($redis->exists( "key1" )) ? "true" : "false") . "<br>";
	*/
	/*
			// RENAMENX key newkey - RENAME if Not eXists
			$redis->set( "key1", "hello" );
			$redis->set( "key2", "world" );
			$redis->renamenx( "key1", "key3" );
			$retValue = $redis->get( "key1" );
			var_dump($retValue);
			$retValue = $redis->get( "key2" );
			var_dump($retValue);
			$retValue = $redis->get( "key3" );
			var_dump($retValue);
	*/
	/*
			// RESTORE not register
	*/
	/*
			// SORT key [BY pattern][LIMIT offset count][GET pattern [GET pattern ...]][ASC|DESC][ALPHA][STORE destination]
			$list = "list type !!!";
			$redis->rpush($list, 1);
			$redis->lpush($list, 2);
			$redis->rpush($list, 3);
			$redis->lpush($list, 4);
			$redis->rpush($list, "5");
			$redis->rpush($list, "ace");
			$redis->rpush($list, "bool");
			$redis->rpush($list, "count");						
			$redis->rpush($list, "zoo");
			$redis->rpush($list, "poo");				
			
			$arList = $redis->lrange( $list, 0, -1 );
			echo "<pre>";
			print_r($arList);
			echo "</pre>";		
			
			echo "Basic Sort" . "<br>";
			$arList = $redis->sort( $list );
			echo "<pre>";
			print_r($arList);
			echo "</pre>";		
			
			echo "Sort - desc" . "<br>";		
			$arList = $redis->sort( $list, array( "sort" => "desc") );
			echo "<pre>";
			print_r($arList);
			echo "</pre>";		
			
			echo "Sort - asc" . "<br>";			
			$arList = $redis->sort( $list, array( "sort" => "asc") );
			echo "<pre>";
			print_r($arList);
			echo "</pre>";
			
			echo "Sort - limit 3 ~ 5" . "<br>";			
			$arList = $redis->sort( $list, array( "limit" => array( 3, 5 ) ) );
			echo "<pre>";
			print_r($arList);
			echo "</pre>";
			
			echo "Sort - alpha" . "<br>";			
			$arList = $redis->sort( $list, array( "alpha" => true ) );
			echo "<pre>";
			print_r($arList);
			echo "</pre>";
			
			echo "Sort - store in Cached List" . "<br>";			
			$redis->sort( $list, array( "store" => "Cached List" ) );
			$arList = $redis->lrange( "Cached List", 0, -1 );
			echo "<pre>";
			print_r($arList);
			echo "</pre>";
			$arList = $redis->lrange( "Cached List", 0, -1 );
			foreach ($arList as $i => $value) {
	    		$redis->rpop( "Cached List" );
			}
			
			$arList = $redis->lrange($list, 0, -1);
			foreach ($arList as $i => $value) {
	    		$redis->rpop( $list );
			}
			
			echo "Sort - get ( list & mset link )" . "<br>";				
			
			$redis->rpush($list, 1);
			$redis->lpush($list, 2);
			$redis->rpush($list, 3);
			$redis->lpush($list, 4);
			
	        $redis->mset( $sortget = array( "uid:1" => "foo",
	                                        "uid:2" => "hoge",
	                                        "uid:3" => "bar",
	                                        "uid:4" => "piyo" ) );             
	        $arList = $redis->sort( $list, array( "get" => "uid:*",
	                                              "alpha" => true ) );                	
			echo "<pre>";
			print_r($arList);
			echo "</pre>";
			
			$arList = $redis->lrange($list, 0, -1);
			foreach ($arList as $i => $value) {
	    		$redis->rpop( $list );
			}
			
			foreach ($sortget as $i => $value) {
	    		$redis->del( $i );
			}
			
			echo "Sort - by ( list & mset link )" . "<br>";
					
			$redis->rpush($list, 1);
			$redis->lpush($list, 2);
			$redis->rpush($list, 3);
			$redis->lpush($list, 4);
			
	        $redis->mset( $sortby = array( "uid:1" => 100,
	                                       "uid:2" => 200,
	                                       "uid:3" => 400,
	                                       "uid:4" => 300 ) );             
	        $arList = $redis->sort( $list, array( "by" => "uid:*",
	        									  "sort" => "desc" ) );                     	
			echo "<pre>";
			print_r($arList);
			echo "</pre>";
			
			$arList = $redis->lrange($list, 0, -1);
			foreach ($arList as $i => $value) {
	    		$redis->rpop( $list );
			}			
			
			foreach ($sortby as $i => $value) {
	    		$redis->del( $i );
			}
	*/
	/*
			// TTL key
			$redis->set( "key1", "hello" );
			$redis->expire( "key1", 60 );
			$ttl = $redis->ttl( "key1" ); // 60 seconds
			var_dump($ttl);	
	*/
	/*
			// TYPE key
			$redis->set( "key1", "hello" );	
			var_dump($redis->type( "key1" ));		
			$redis->del("key1");
			
			$redis->rpush("key2", 1);		
			var_dump($redis->type( "key2" ));			
			$redis->del("key2");
	*/
	//////////////////////////////////////////////////////////////////////
	// Strings
	//////////////////////////////////////////////////////////////////////
	/*		
			// APPEND key value
			$redis->set( "key1", "hello" );	
			$redis->append( "key1", " world");
			$retValue = $redis->get( "key1" );
			$redis->del( "key1" );
			var_dump($retValue);
	*/
	/*		
			// BITCOUNT key [start] [end] - not register
	*/
	/*		
			// BITOP operation, destkey, key [key ...] - not register
	*/
	/*
			// DECR key
			$redis->set( "key1", "10" );
			$retValue = $redis->decr( "key1" ); // 9
			$redis->del( "key1" );
			var_dump($retValue);
	*/
	/*
			// DECRBY key decrement
			$redis->set( "key1", "10" );
			$retValue = $redis->decrby( "key1", 5 ); // 5
			$redis->del( "key1" );
			var_dump($retValue);
	*/
	/*		
			// GET key
			$redis->set( "key1", 100 );
			$retValue = $redis->get( "key1" );
			$redis->del( "key1" );
			var_dump($retValue);				
	*/
	/*		
			// GETBIT key offeset
			$redis->set( "key1", "\x80\x00\00\x01" );
			$retValue = $redis->getbit( "key1", 0 );
			var_dump($retValue);			
			$retValue = $redis->getbit( "key1", 15 );
			var_dump($retValue);
			$retValue = $redis->getbit( "key1", 31 );
			var_dump($retValue);
			$retValue = $redis->getbit( "key1", 63 );
			var_dump($retValue);
			$redis->del( "key1" );
	*/
	/*
			// INCR key
			$redis->set( "key1", "10" );
			$retValue = $redis->incr( "key1" ); // 11
			$redis->del( "key1" );
			var_dump($retValue);
	*/
	/*
			// INCRBY key decrement
			$redis->set( "key1", "10" );
			$retValue = $redis->incrby( "key1", 5 ); // 15
			$redis->del( "key1" );
			var_dump($retValue);
	*/
	/*
			// INCRBYFLOAT key, decrement - not register
	*/
	/*
			// MGET key [key ...]
			$redis->set( "key1", "hello" );
			$redis->set( "key2", "world" );
			$retValue = $redis->mget( array( "key1", "key2" ) );
			$redis->del( array( "key1", "key2" ) );
			var_dump($retValue);				
	*/
	/*
			// MSET key value [key value ...]
			$redis->mset( array( "key1" => "hello", "key2" => "world" ) );
			$retValue = $redis->get( "key1" );
			var_dump($retValue);						
			$retValue = $redis->get( "key2" );
			var_dump($retValue);						
			$redis->del( array( "key1", "key2" ) );
	*/
	/*
			// MSETNX key value [key value ...] - Multi SET if Not eXists
			$redis->msetnx( array( "key1" => "hello", "key2" => "there" ) );		
			$redis->msetnx( array( "key2" => "there", "key3" => "world" ) ); // key2 not overwrite value 
			$retValue = $redis->mget( array( "key1", "key2", "key3" ) );
			$redis->del( array( "key1", "key2", "key3" ) );
			var_dump($retValue);
	*/
	/*		
			// PSETEX key milliseconds value - not register
	*/
	/*
			// SET key value
			$redis->set( "key1", "hello" );
			$retValue = $redis->get( "key1" );
			$redis->del( "key1" );	
			var_dump($retValue);
							
	*/
	/*		
			// SETBIT key offset value
			$redis->setbit( "key1", 7, 1 );				
			$redis->setbit( "key1", 7, 0 );
			$retValue = $redis->get( "key1" );			
			$redis->del( "key1" );		
			var_dump($retValue);
	*/
	/*
			// SETEX key seconds value
			$redis->setex( "key1", 10, "hello" );
			$ttl = $redis->ttl( "key1" );
			var_dump($ttl);		
			$retValue = $redis->get( "key1" );
			$redis->del( "key1" );			
			var_dump($retValue);	
	*/
	/*
			// SETNX key value - SET if Not eXists
			$redis->setnx( "key1", "hello" ); // true;
			$redis->setnx( "key1", "world" ); // false;		
			$retValue = $redis->get( "key1" );
			$redis->del( "key1" );			
			var_dump($retValue);	
	*/
	/*
			// SETRANGE key offset value
			$redis->set( "key1", "hello world" );
			$redis->setrange( "key1", 6, "redis" );
			$retValue = $redis->get( "key1" );
			$redis->del( "key1" );			
			var_dump($retValue);	
	*/
	/*
			// STRLEN key
			$redis->set( "key1", "hello world" );
			var_dump( $redis->strlen( "key1" ) ); // 11
			$redis->del( "key1" );			
	*/
	//////////////////////////////////////////////////////////////////////
	// Hashes
	//////////////////////////////////////////////////////////////////////
	/*		
			// HDEL key field [field ...]
			$redis->hset( "key1", "field1", "hello" );
			$redis->hdel( "key1", "field1" );
			echo (($redis->hexists( "key1", "field1" )) ? "true" : "false") . "<br>";			
	*/
	/*		
			// HEXISTS key field
			$redis->hset( "key1", "field1", "hello" );
			echo (($redis->hexists( "key1", "field1" )) ? "true" : "false") . "<br>";			
			$redis->hdel( "key1", "field1" );
	*/
	/*
			// HGET key field
			$redis->hset( "key1", "field1", "hello" );
			$retValue = $redis->hget( "key1", "field1" );			
			$redis->hdel( "key1", "field1" );
			var_dump($retValue);	
	*/
	/*
			// HGETALL key
			$redis->hset( "key1", "field1", "hello" );
			$redis->hset( "key1", "field2", "world" );
			$retValue = $redis->hgetall( "key1" );			
			$redis->hdel( "key1", "field1" );
			$redis->hdel( "key1", "field2" );
			var_dump($retValue);	
	*/		
	/*
			// HINCRBY key field increment
			$redis->hset( "key1", "field1", 5 );
			var_dump( $redis->hincrby( "key1", "field1", 1 ) ); // 6
			$redis->hdel( "key1", "field1" );				
	*/
	/*
			// HINCRBYFLOAT key field increment - not register
	*/
	/*
			// HKEYS key
			$redis->hset( "key1", "field1", "hello" );
			$redis->hset( "key1", "field2", "world" );
			$retValue = $redis->hkeys( "key1" );
			$redis->hdel( "key1", "field1" );
			$redis->hdel( "key1", "field2" );		
			var_dump($retValue);		
	*/
	/*
			// HLEN key
			$redis->hset( "key1", "field1", "hello" );
			$redis->hset( "key1", "field2", "world" );
			$retValue = $redis->hlen( "key1" ); // 2
			$redis->hdel( "key1", "field1" );
			$redis->hdel( "key1", "field2" );		
			var_dump($retValue);
	*/
	/*
			// HMGET key field [field ...]
			$redis->hset( "key1", "field1", "hello" );
			$redis->hset( "key1", "field2", "world" );
			$retValue = $redis->hmget( "key1", "field1", "field2" );
			$redis->hdel( "key1", "field1" );
			$redis->hdel( "key1", "field2" );		
			var_dump($retValue);
	*/
	/*
			// HMSET key field value [field value ...]
			$redis->hmset( "key1", "field1", 1, "field2", 2 );
			$redis->hmset( "key2", array( "field1" => 1, "field2" => 2 ) );
			$retValue = $redis->hkeys( "key1" );
			var_dump($retValue);		
			$retValue = $redis->hkeys( "key2" );
			var_dump($retValue);		
			$redis->hdel( "key1", "field1" );
			$redis->hdel( "key1", "field2" );	
			$redis->hdel( "key2", "field1" );
			$redis->hdel( "key2", "field2" );
	*/
	/*
			// HSET key field value
			$redis->hset( "key1", "field1", "hello" );
			$retValue = $redis->hget( "key1", "field1" );			
			$redis->hdel( "key1", "field1" );
			var_dump($retValue);	
	*/
	/*
			// HSETNX key field value - HSET if Not eXists
			$redis->hsetnx( "key1", "field1", "hello" ); // true
			$redis->hsetnx( "key1", "field1", "world" ); // false
			$retValue = $redis->hget( "key1", "field1" );			
			$redis->hdel( "key1", "field1" );
			var_dump($retValue);
	*/
	/*
			// HVALS key
			$redis->hset( "key1", "field1", "hello" );
			$redis->hset( "key1", "field2", "world" );
			$retValue = $redis->hvals( "key1" );			
			$redis->hdel( "key1", "field1" );
			$redis->hdel( "key1", "field2" );
			var_dump($retValue);
	*/
	//////////////////////////////////////////////////////////////////////
	// Lists
	//////////////////////////////////////////////////////////////////////
	/*		
			// BLPOP key [key ...] timeout
			$redis->rpush( "list", array ( "a", "b", "c" ) );
			$arList = $redis->lrange( "list", 0, -1 );		
			foreach ($arList as $i => $value) {
				$retValue = $redis->blpop( "list", 0 );
				var_dump($retValue);
			}
	*/
	/*	
			// BRPOP key [key ...] timeout
			$redis->rpush( "list", array ( "a", "b", "c" ) );
			$arList = $redis->lrange( "list", 0, -1 );		
			foreach ($arList as $i => $value) {
				$retValue = $redis->brpop( "list", 0 );
				var_dump($retValue);
			}		
	*/
	/*
			// BRPOPLPUSH source destination timeout
			$redis->rpush( "list1", array ( "a", "b", "c" ) );
			$arList = $redis->lrange( "list1", 0, -1 );		
			foreach ($arList as $i => $value) {
				$retValue = $redis->brpoplpush( "list1", "list2", 0 );
				var_dump($retValue);
			}		
			$arList = $redis->lrange( "list2", 0, -1 );		
			foreach ($arList as $i => $value) {
				$retValue = $redis->rpop( "list2" );
				var_dump($retValue);
			}		
	*/
	/*		
			// LINDEX key index
			$redis->lpush( "list", array ( "hello", "world" ) );
			var_dump($redis->lindex( "list", 0 ));
			var_dump($redis->lindex( "list", 1 ));
			$arList = $redis->lrange( "list", 0, -1 );		
			foreach ($arList as $i => $value) {
				$redis->rpop( "list" );
			}				
	*/
	/*		
			// LINSERT key BEFORE|AFTER pivot value
	        $redis->rpush( "list", "a", "c", "e" );
	        $redis->linsert( "list", "before", "c", "b" );
	        $redis->linsert( "list", "after", "c", "d" );
			$arList = $redis->lrange( "list", 0, -1 );		
			foreach ($arList as $i => $value) {
				$retValue = $redis->lpop( "list" );
				var_dump($retValue);
			}		
	*/
	/*   
	   		// LLEN key
	  		$redis->lpush( "list", array ( "hello", "world" ) );
			var_dump($redis->llen( "list" ));  			     		
			$arList = $redis->lrange( "list", 0, -1 );		
			foreach ($arList as $i => $value) {
				$redis->rpop( "list" );
			}				
	*/
	/*
			// LPOP key
	        $redis->rpush( "list", "a", "b", "c" );
			$arList = $redis->lrange( "list", 0, -1 );		
			foreach ($arList as $i => $value) {
				$retValue = $redis->lpop( "list" );
				var_dump($retValue);
			}		
	*/
	/*
			// LPUSH key value [value ...]
	        $redis->lpush( "list", "a", "b", "c" );
			$arList = $redis->lrange( "list", 0, -1 );		
			foreach ($arList as $i => $value) {
				$retValue = $redis->rpop( "list" );
				var_dump($retValue);
			}		
	*/
	/*
			// LPUSHX key value - LPUSH if not eXists
	        $redis->lpush( "list1", "hello", "world" );
	        $redis->lpushx( "list2", "hello" );
	        
			echo "List 1" . "<br>";		        
			$arList = $redis->lrange( "list1", 0, -1 );		
			foreach ($arList as $i => $value) {
				$retValue = $redis->rpop( "list1" );
				var_dump($retValue);
			}	
			echo "List 2" . "<br>";		        
			$arList = $redis->lrange( "list2", 0, -1 );		
			foreach ($arList as $i => $value) {
				$retValue = $redis->rpop( "list2" );
				var_dump($retValue);
			}	
	*/
	/*
			// LLANGE key start stop
	        $redis->rpush( "list", "one", "two", "three" );
	 		$retValue = $redis->lrange( "list", 0, 0 );
	 		var_dump($retValue);		       
	 		$retValue = $redis->lrange( "list", -3, 2 );
	 		var_dump($retValue);		               	
	 		$retValue = $redis->lrange( "list", -100, 100 );
	 		var_dump($retValue);
	  		$retValue = $redis->lrange( "list", 5, 10 );
	 		var_dump($retValue);			               	
			$arList = $redis->lrange( "list", 0, -1 );		
			foreach ($arList as $i => $value) {
				$retValue = $redis->rpop( "list" );
			}		
	*/
	/*		
			// LREM key count value
	        $redis->rpush( "list", "hello", "hello", "bye" );		
	        $redis->rpush( "list", "hello" );
	        $redis->lrem( "list", -2, "hello");		
			$arList = $redis->lrange( "list", 0, -1 );		
			foreach ($arList as $i => $value) {
				$retValue = $redis->rpop( "list" );
				var_dump($retValue);			
			}
	*/
	/*		
			// LSET key index value
	        $redis->rpush( "list", "one", "two", "three" );
			$arList = $redis->lrange( "list", 0, -1 );	
			foreach ($arList as $i => $value) {
				var_dump($value);			
			}		        		
	        $redis->lset( "list", 0, "four" );
	        $redis->lset( "list", -3, "five" );
			$arList = $redis->lrange( "list", 0, -1 );		
			foreach ($arList as $i => $value) {
				$retValue = $redis->lpop( "list" );
				var_dump($retValue);			
			}		
	*/
	/*		
			// LTRIM key start stop
	        $redis->rpush( "list", "one", "two", "three" );
			$arList = $redis->lrange( "list", 0, -1 );	
			foreach ($arList as $i => $value) {
				var_dump($value);			
			}		        		
	        $redis->ltrim( "list", 1, -2 );
			$arList = $redis->lrange( "list", 0, -1 );		
			foreach ($arList as $i => $value) {
				$retValue = $redis->lpop( "list" );
				var_dump($retValue);			
			}		
	*/
	/*
			// RPOP key start stop
	        $redis->rpush( "list", "one", "two", "three" );
			$arList = $redis->lrange( "list", 0, -1 );	
			foreach ($arList as $i => $value) {
				$retValue = $redis->rpop( "list" );
				var_dump($retValue);			
			}
	*/
	/*
			// RPOPLPUSH source destination
			$redis->rpush( "list1", array ( "a", "b", "c" ) );
			$arList = $redis->lrange( "list1", 0, -1 );		
			foreach ($arList as $i => $value) {
				$retValue = $redis->rpoplpush( "list1", "list2" );
				var_dump($retValue);
			}		
			$arList = $redis->lrange( "list2", 0, -1 );		
			foreach ($arList as $i => $value) {
				$retValue = $redis->lpop( "list2" );
				var_dump($retValue);
			}
	*/
	/*
			// RPUSH key value [value ...]
	        $redis->rpush( "list", "one", "two", "three" );
			$arList = $redis->lrange( "list", 0, -1 );	
			foreach ($arList as $i => $value) {
				$retValue = $redis->lpop( "list" );
				var_dump($retValue);			
			}	
	*/
	/*
			// RPUSHX key value - RPUSH if not eXists
	        $redis->rpush( "list1", "hello", "world" );
	        $redis->rpushx( "list2", "hello" );
	        
			echo "List 1" . "<br>";		        
			$arList = $redis->lrange( "list1", 0, -1 );		
			foreach ($arList as $i => $value) {
				$retValue = $redis->rpop( "list1" );
				var_dump($retValue);
			}	
			echo "List 2" . "<br>";		        
			$arList = $redis->lrange( "list2", 0, -1 );		
			foreach ($arList as $i => $value) {
				$retValue = $redis->rpop( "list2" );
				var_dump($retValue);
			}	
	*/
	//////////////////////////////////////////////////////////////////////
	// Sets
	//////////////////////////////////////////////////////////////////////
	/*
			// SADD key member [member ...]
			$redis->sadd( "set", array ( "a", "c" ) );
			$redis->sadd( "set", "c" );
			$arList = $redis->smembers( "set" );
			foreach ($arList as $i => $value) {
				$retValue = $redis->spop( "set" );
				var_dump($retValue);
			}
	*/		
	/*		
			// SCARD key
			$redis->sadd( "set", "hello", "world" );
			$retValue = $redis->scard( "set" );
			var_dump($retValue);
			$arList = $redis->smembers( "set" );
			foreach ($arList as $i => $value) {
				$retValue = $redis->spop( "set" );
				var_dump($retValue);
			}		
	*/
	/*		
			// SDIFF key [key ...]
			$redis->sadd( "set1", array ( "a", "b", "c" ) );
			$redis->sadd( "set2", array ( "c", "d", "e" ) );
			
			$arList = $redis->sdiff( "set1", "set2" );
			var_dump($arList);
			
			$arList = $redis->sdiff( "set2", "set1" );
			var_dump($arList);		
			
			$arList = $redis->smembers( "set1" );
			foreach ($arList as $i => $value) {
				$redis->spop( "set1" );
			}		
			$arList = $redis->smembers( "set2" );
			foreach ($arList as $i => $value) {
				$redis->spop( "set2" );
			}		
	*/
	/*	
			// SDIFFSTORE destination key [key ...]
			$redis->sadd( "set1", array ( "a", "b", "c", "d" ) );
			$redis->sadd( "set2", array ( "c", "d", "f" ) );
			
			$arList = $redis->sdiffstore( "set3", "set1", "set2" );
			var_dump($arList);
					
			$arList = $redis->smembers( "set1" );
			foreach ($arList as $i => $value) {
				$redis->spop( "set1" );
			}		
			$arList = $redis->smembers( "set2" );
			foreach ($arList as $i => $value) {
				$redis->spop( "set2" );
			}		
			$arList = $redis->smembers( "set3" );
			foreach ($arList as $i => $value) {
				$retValue = $redis->spop( "set3" );
				var_dump($retValue);			
			}			
	*/
	/*
			// SINTER key [key ...]
			$redis->sadd( "set1", array ( "a", "b", "c" ) );
			$redis->sadd( "set2", array ( "c", "d", "e" ) );
			
			$arList = $redis->sinter( "set1", "set2" );
			var_dump($arList);
					
			$arList = $redis->smembers( "set1" );
			foreach ($arList as $i => $value) {
				$redis->spop( "set1" );
			}		
			$arList = $redis->smembers( "set2" );
			foreach ($arList as $i => $value) {
				$redis->spop( "set2" );
			}			
	*/
	/*		
			// SINTERSTORE destination key [key ...]
			$redis->sadd( "set1", array ( "a", "b", "c", "d" ) );
			$redis->sadd( "set2", array ( "c", "d", "f" ) );
			
			$arList = $redis->sinterstore( "set3", "set1", "set2" );
			var_dump($arList);
					
			$arList = $redis->smembers( "set1" );
			foreach ($arList as $i => $value) {
				$redis->spop( "set1" );
			}		
			$arList = $redis->smembers( "set2" );
			foreach ($arList as $i => $value) {
				$redis->spop( "set2" );
			}		
			$arList = $redis->smembers( "set3" );
			foreach ($arList as $i => $value) {
				$retValue = $redis->spop( "set3" );
				var_dump($retValue);			
			}	
	*/
	/*
			// SISMEMBER key member
			$redis->sadd( "set", array ( "one", "two", "three" ) );		
			echo (($redis->sismember( "set", "two" )) ? "true" : "false") . "<br>";		
			$arList = $redis->smembers( "set" );
			foreach ($arList as $i => $value) {
				$retValue = $redis->spop( "set" );
			}
	*/
	/*
			// SMOVE source destination member
			$redis->sadd( "set1", array ( "one", "two" ) );
			$redis->sadd( "set2", array ( "three" ) );
			
			$redis->smove( "set1", "set2", "two" );
			
			echo "Set 1" . "<br>";			
			$arList = $redis->smembers( "set1" );
			foreach ($arList as $i => $value) {
				$retValue = $redis->spop( "set1" );
				var_dump($retValue);			
			}
			echo "Set 2" . "<br>";			
			$arList = $redis->smembers( "set2" );
			foreach ($arList as $i => $value) {
				$retValue = $redis->spop( "set2" );
				var_dump($retValue);			
			}		
	*/
	/*
			// SPOP key
			$redis->sadd( "set", array ( "one", "two", "three" ) );
			$arList = $redis->smembers( "set" );
			foreach ($arList as $i => $value) {
				$retValue = $redis->spop( "set" );
				var_dump($retValue);			
			}
	*/
	/*
			// SRANDMEMBER key [count]
			$redis->sadd( "set", array ( "one", "two", "three", "four", "five" ) );
			
			$retValue = $redis->srandmember( "set" );
			var_dump($retValue);			
			
			$arList = $redis->smembers( "set" );
			foreach ($arList as $i => $value) {
				$retValue = $redis->spop( "set" );
			}
	*/
	/*		
			// SREM key key
			$redis->sadd( "set", array ( "one", "two", "three", "four", "five" ) );
			
			$retValue = $redis->srem( "set", array( "two", "four" ) );
			var_dump($retValue);			
			
			$arList = $redis->smembers( "set" );
			foreach ($arList as $i => $value) {
				$retValue = $redis->spop( "set" );
				var_dump($retValue);
			}
	*/
	/*
			// SUNION key [key ...]
			$redis->sadd( "set1", array ( "a", "b", "c" ) );
			$redis->sadd( "set2", array ( "c", "d", "e" ) );
			
			$arList = $redis->sunion( "set1", "set2" );
			var_dump($arList);
					
			$arList = $redis->smembers( "set1" );
			foreach ($arList as $i => $value) {
				$redis->spop( "set1" );
			}		
			$arList = $redis->smembers( "set2" );
			foreach ($arList as $i => $value) {
				$redis->spop( "set2" );
			}
	*/
	/*		
			// SUNIONSTORE destination key [key ...]
			$redis->sadd( "set1", array ( "a", "b", "c", "d" ) );
			$redis->sadd( "set2", array ( "c", "d", "f" ) );
			
			$arList = $redis->sunionstore( "set3", "set1", "set2" );
			var_dump($arList);
					
			$arList = $redis->smembers( "set1" );
			foreach ($arList as $i => $value) {
				$redis->spop( "set1" );
			}		
			$arList = $redis->smembers( "set2" );
			foreach ($arList as $i => $value) {
				$redis->spop( "set2" );
			}		
			$arList = $redis->smembers( "set3" );
			foreach ($arList as $i => $value) {
				$retValue = $redis->spop( "set3" );
				var_dump($retValue);			
			}	
	*/
	//////////////////////////////////////////////////////////////////////
	// Sorted Sets
	//////////////////////////////////////////////////////////////////////
	/*
			// ZADD key score member [score member ...]
			$redis->zadd( "zset", 1, "a", 2, "b", 3, "c",  5, "e", 4, "d" );
			$redis->zadd( "zset", 6, "f");
			$arList = $redis->zrange( "zset", 0, -1 );
			foreach ($arList as $i => $value) {
				$redis->zrem( "zset", $value );
				var_dump($value);			
			}		
	*/
	/*		
			// ZCARD key
			$redis->zadd( "zset", 1, "a", 2, "b", 3, "c", 4, "d", 5, "e" );
			$retValue = $redis->zcard( "zset" );
			var_dump($retValue);
			$arList = $redis->zrange( "zset", 0, -1 );
			foreach ($arList as $i => $value) {
				$redis->zrem( "zset", $value );
				var_dump($value);			
			}					
	*/
	/*
			// ZCOUNT key min max - inf: infinity, (: Exclusive
			$redis->zadd( "zset", 10, "a", 30, "b", 50, "c", 70, "d", 100, "e" );
			$retValue = $redis->zcount( "zset", 10, 70 );
			var_dump($retValue);
			$retValue = $redis->zcount( "zset", 31, "+inf" );
			var_dump($retValue);
			$retValue = $redis->zcount( "zset", "-inf", 69 );
			var_dump($retValue);		
			$retValue = $redis->zcount( "zset", 10, "(31" );
			var_dump($retValue);	
					
			$arList = $redis->zrange( "zset", 0, -1 );
			foreach ($arList as $i => $value) {
				$redis->zrem( "zset", $value );
				var_dump($value);			
			}	
	*/
	/*
			// ZINCRBY key increment memeber
			$redis->flushdb();
			$redis->zadd( "zset", 10, "a", 30, "b", 50, "c", 70, "d", 100, "e" );
			$retValue = $redis->zincrby( "zset", 1, "b" );
			var_dump($retValue);
			$retValue = $redis->zincrby( "zset", -0.7, "c" );
			var_dump($retValue);
					
			$arList = $redis->zrange( "zset", 0, -1 );
			foreach ($arList as $i => $value) {
				$redis->zrem( "zset", $value );
				var_dump($value);			
			}		
	*/
	/*
			// ZINTERSTORE destination numkeys key [key ...][WEIGHTS weight[weight ...]][AGGREGATE SUM|MIN|MAX]
			$redis->zadd( "zset1", 1, "a", 2, "b", 3, "c" );
			$redis->zadd( "zset2", 1, "b", 2, "c", 3, "d" );
			
	//		$options = array( "aggregate" => "min" );
	//		$options = array( "aggregate" => "max" );
			$options = array( "aggregate" => "sum" );
	//     	$options = array( "weights" => array( 2, 3 ) );		
			$redis->zinterstore( "zset3", 2, "zset1", "zset2", $options);
					
			echo "ZSet 1" . "<br>";
			$arList = $redis->zrange( "zset1", 0, -1, "withscores" );
			foreach ($arList as $i => $value) {
				$redis->zrem( "zset1", $value );
				var_dump($value);
			}
			echo "ZSet 2" . "<br>";			
			$arList = $redis->zrange( "zset2", 0, -1, "withscores" );
			foreach ($arList as $i => $value) {
				$redis->zrem( "zset2", $value );
				var_dump($value);				
			}
			echo "ZSet 3" . "<br>";							
			$arList = $redis->zrange( "zset3", 0, -1, "withscores" );
			foreach ($arList as $i => $value) {
				$redis->zrem( "zset3", $value );
				var_dump($value);			
			}	
	*/
	/*		
			// ZRANGE key start stop [WITHSCORES]
			$redis->zadd( "zset", 1, "a", 2, "b", 3, "c" );
	 		$retValue = $redis->zrange( "zset", 0, 0 );
	 		var_dump($retValue);		       
	 		$retValue = $redis->zrange( "zset", -3, 2 );
	 		var_dump($retValue);		               	
	 		$retValue = $redis->zrange( "zset", -100, 100, array( "withscores" => true ) );
	 		var_dump($retValue);
	  		$retValue = $redis->zrange( "zset", 5, 10 );
	 		var_dump($retValue);			               	
			$arList = $redis->zrange( "zset", 0, -1, "withscores" );
			var_dump($retValue);
			foreach ($arList as $i => $value) {
				$redis->zrem( "zset", $value );
				var_dump($value);
			}	
	*/
	/*
			// ZRANGEBYSCORE key min max [WITHSCORES][LIMIT offset count] - inf: infinity, (: Exclusive
			$redis->zadd( "zset", -10, "a", 0, "b", 10, "c", 20, "d", 20, "e", 30, "f" );
			
			$retValue = $redis->zrangebyscore( "zset", -10, 10 );
	 		var_dump($retValue);
			$retValue = $redis->zrangebyscore( "zset", "-inf", 15 );
	 		var_dump($retValue);
			$retValue = $redis->zrangebyscore( "zset", 10, "(20" );
	 		var_dump($retValue);
	 		$retValue = $redis->zrangebyscore( "zset", -100, 100, array( "withscores" => true ) );
	 		var_dump($retValue); 		
	 		$retValue = $redis->zrangebyscore( "zset", -10, 30, array( "limit" => array( 1, 4 ) ) );
	 		var_dump($retValue); 		
	 		$retValue = $redis->zrangebyscore( "zset", -10, 30, array( "limit" => array( "offset" => 1, "count" => 4 ) ) );
	 		var_dump($retValue);
	 			
			$arList = $redis->zrange( "zset", 0, -1, "withscores" );
			foreach ($arList as $i => $value) {
				$redis->zrem( "zset", $value );
			}	
	
	/*
			// ZRANK key member
			$redis->zadd( "zset", -10, "a", 0, "b", 10, "c", 20, "d", 20, "e", 30, "f" );
			
			var_dump( $redis->zrank( "zset", "a" ) );
			var_dump( $redis->zrank( "zset", "d" ) );
			
			$arList = $redis->zrange( "zset", 0, -1, "withscores" );
			foreach ($arList as $i => $value) {
				$redis->zrem( "zset", $value );
			}	
	*/
	/*
			// ZREM key member [member ...]
			$redis->zadd( "zset", 1, "a", 2, "b", 3, "c", 4, "d", 5, "e" );
			$arList = $redis->zrange( "zset", 0, -1 );
			foreach ($arList as $i => $value) {
				$redis->zrem( "zset", $value );
				var_dump($value);			
			}			
	*/
	/*
			// ZREMRANGEBYRANK key start stop
			$redis->zadd( "zset", -10, "a", 0, "b", 10, "c", 20, "d", 20, "e", 30, "f" );
			
			var_dump( $redis->zremrangebyrank( "zset", 0, 1 ) );
	
			$arList = $redis->zrange( "zset", 0, -1 );
			foreach ($arList as $i => $value) {
				$redis->zrem( "zset", $value );
				var_dump($value);			
			}		
	*/
	/*
			// ZREMRANGEBYSCORE key min max
			$redis->zadd( "zset", -10, "a", 0, "b", 10, "c", 20, "d", 20, "e", 30, "f" );
			
			var_dump( $redis->zremrangebyscore( "zset", 5, 20 ) );
			var_dump( $redis->zremrangebyscore( "zset", 5, "(20" ) );
	
			$arList = $redis->zrange( "zset", 0, -1 );
			foreach ($arList as $i => $value) {
				$redis->zrem( "zset", $value );
				var_dump($value);			
			}	
	*/
	/*	
			// ZREVRANGE key min max [WITHSCORES]
			$redis->zadd( "zset", -10, "a", 0, "b", 10, "c", 20, "d", 20, "e", 30, "f" );
			
			$retValue = $redis->zrevrange( "zset", -10, 10 );
	 		var_dump($retValue);
	 		$retValue = $redis->zrevrange( "zset", -100, 100, array( "withscores" => true ) );
	 		var_dump($retValue); 		
	 			
			$arList = $redis->zrange( "zset", 0, -1, "withscores" );
			foreach ($arList as $i => $value) {
				$redis->zrem( "zset", $value );
			}	
	*/
	/*
			// ZREVRANGEBYSCORE key min max [WITHSCORES][LIMIT offset count] - inf: infinity, (: Exclusive
			$redis->zadd( "zset", -10, "a", 0, "b", 10, "c", 20, "d", 20, "e", 30, "f" );
			
			$retValue = $redis->zrevrangebyscore( "zset", -10, -10 );
	 		var_dump($retValue);
			$retValue = $redis->zrevrangebyscore( "zset", 10, -10 );
	 		var_dump($retValue);
			$retValue = $redis->zrevrangebyscore( "zset", 20, 30 );
	 		var_dump($retValue);
	 		$retValue = $redis->zrevrangebyscore( "zset", "+inf", 15);
	 		var_dump($retValue);
	  		$retValue = $redis->zrevrangebyscore( "zset", "(30", 15);
	 		var_dump($retValue);			
	 		$retValue = $redis->zrevrangebyscore( "zset", 100, -100, array( "withscores" => true ) );
	 		var_dump($retValue); 		
	 		$retValue = $redis->zrevrangebyscore( "zset", 30, -10, array( "limit" => array( 1, 4 ) ) );
	 		var_dump($retValue); 		
	 		$retValue = $redis->zrevrangebyscore( "zset", 30, -10, array( "limit" => array( "offset" => 1, "count" => 4 ) ) );
	 		var_dump($retValue);
	 			
			$arList = $redis->zrange( "zset", 0, -1, "withscores" );
			foreach ($arList as $i => $value) {
				$redis->zrem( "zset", $value );
			}			
	*/
	/*
			// ZREVRANK key member
			$redis->zadd( "zset", -10, "a", 0, "b", 10, "c", 20, "d", 20, "e", 30, "f" );
			
			var_dump( $redis->zrevrank( "zset", "a" ) );
			var_dump( $redis->zrevrank( "zset", "d" ) );
			
			$arList = $redis->zrange( "zset", 0, -1, "withscores" );
			foreach ($arList as $i => $value) {
				$redis->zrem( "zset", $value );
			}			
	*/
	/*
			// ZSCORE key member
			$redis->zadd( "zset", -10, "a", 0, "b", 10, "c", 20, "d", 20, "e", 30, "f" );
			
			var_dump( $redis->zscore( "zset", "a" ) );
			var_dump( $redis->zscore( "zset", "d" ) );
			
			$arList = $redis->zrange( "zset", 0, -1, "withscores" );
			foreach ($arList as $i => $value) {
				$redis->zrem( "zset", $value );
			}		
	*/
	/*
			// ZUNIONSTORE destination numkeys key [key ...][WEIGHTS weight[weight ...]][AGGREGATE SUM|MIN|MAX]
			$redis->zadd( "zset1", 1, "a", 2, "b", 3, "c" );
			$redis->zadd( "zset2", 1, "b", 2, "c", 3, "d" );
			
	//		$options = array( "aggregate" => "min" );
	//		$options = array( "aggregate" => "max" );
			$options = array( "aggregate" => "sum" );
	//     	$options = array( "weights" => array( 2, 3 ) );		
			$redis->zunionstore( "zset3", 2, "zset1", "zset2", $options);
					
			echo "ZSet 1" . "<br>";
			$arList = $redis->zrange( "zset1", 0, -1, "withscores" );
			foreach ($arList as $i => $value) {
				$redis->zrem( "zset1", $value );
				var_dump($value);
			}
			echo "ZSet 2" . "<br>";			
			$arList = $redis->zrange( "zset2", 0, -1, "withscores" );
			foreach ($arList as $i => $value) {
				$redis->zrem( "zset2", $value );
				var_dump($value);				
			}
			echo "ZSet 3" . "<br>";							
			$arList = $redis->zrange( "zset3", 0, -1, "withscores" );
			foreach ($arList as $i => $value) {
				$redis->zrem( "zset3", $value );
				var_dump($value);			
			}	
	*/
	//////////////////////////////////////////////////////////////////////
	// Pub/Sub
	//////////////////////////////////////////////////////////////////////	
	/*
			// PSUBSCRIBE pattern [pattern ...] - Predis not understand !!!
	*/
	/*
			// PUBLISH channel message - Predis not understand !!!
			
			for( $i = 0; $i < 1000; $i++ )
			{
				$message = sprintf("hello world ! count:%d", $i);
				$redis->publish( "channel:1", $message ) );
			}
	*/
	/*
			// PUNSUBSCRIBE [pattern [pattern ...]] - Predis not understand !!!
	*/
	/*				
			// SUBSCRIBE channel [channel ...]
			// UNSUBSCRIBE [channel [channel ...]]
		
			$pubsub = $redis->pubSub();
			$pubsub->subscribe("channel:1");
			
			foreach ($pubsub as $message) {
				
	    		switch ($message->kind) {
	        		
	        		case "subscribe":
	            		echo "Subscribed to { $message->channel }\n";
	            	break;
	            	
	        		case "message":
	            		if ($message->channel == 'control_channel') {
	                		if ($message->payload == 'quit_loop') {
	                    		echo "Aborting pubsub loop...\n";
	                    		$pubsub->unsubscribe();
	                		} else {
	                    		echo "Received an unrecognized command: {$message->payload}.\n";
	                		}
	            		} else {
	                		echo "Received the following message from {$message->channel}:\n",
	                             "  {$message->payload}\n\n";
	            		}
	            	break;
	    		}
	    		
	    		var_dump( $message );
			}			
	*/
	//////////////////////////////////////////////////////////////////////
	// Transactions
	//////////////////////////////////////////////////////////////////////
	/*
			// DISCARD		
			$redis->multi();
			$redis->set( "foo", "bar" );
			echo (($redis->exists( "foo" )) ? "true" : "false") . "<br>";  
			$redis->discard(); // with multi command
			echo (($redis->exists( "foo" )) ? "true" : "false") . "<br>";
			$redis->del( "foo" );
	*/
	/*
			// EXEC
	        $redis->multi();
	        $redis->echo("foo");
	        $redis->echo("poo");
	        var_dump( $redis->exec() );
	*/
	/*
	        // MULTI
			$redis->multi();
			$redis->set( "foo", "bar" );
	        var_dump( $redis->exec() );
			$redis->del( "foo" );		  
	*/
	/*
	        // UNWATCH
	        $redis2 = new Predis\Client(array('host'=>'127.0.0.1'));
	
	        $redis->set( "foo", "bar" );
	  		var_dump( $redis->get( "foo" ) );
	  		             
	        $redis->watch( "foo" );
			$redis->unwatch();
			
	  		$redis->multi();
	  		$redis->get( "foo" );
	
	        $redis2->set( "foo", "hello" );
	  		var_dump( $redis->get( "foo" ) );
	  		
			echo "Exec ~" . "<br>";
	        var_dump( $redis->exec() );
	        
	  		var_dump( $redis->get( "foo" ) );        
	
			$redis->del( "foo" );
			$redis->del( "hoge" );
	*/
	/*
	        // WATCH key [key ...]
	        $redis2 = new Predis\Client(array('host'=>'127.0.0.1'));
	
	        $redis->mset( "foo", "bar", "hoge", "piyo" );
	  		var_dump( $redis->get( "foo" ) );
	             
	        $redis->watch( "foo", "hoge" );
	        $redis->multi();
	                		
	        $redis2->set( "foo", "hello" ); // WATCH Key to access when running, its EXEC process will fail !!!
	                                        // but SET process success only.
	  		var_dump( $redis->get( "foo" ) );
	  		  		
			echo "Exec ~" . "<br>";
	        var_dump( $redis->exec() );
	        
	  		var_dump( $redis->get( "foo" ) );
	             
			$redis->del( "foo" );
			$redis->del( "hoge" );
	*/
	//////////////////////////////////////////////////////////////////////
	// Scripting
	//////////////////////////////////////////////////////////////////////		

	//////////////////////////////////////////////////////////////////////
	// Connection
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	// Server
	//////////////////////////////////////////////////////////////////////
	/*	
			// SELECT index
    		$parameters = array(
            	'host' => '127.0.0.1',
            	'port' => 6379,
            	'iterable_multibulk' => true,
            	'read_write_timeout' => 2,
        	);

        	$options = array(
          		'profile' => '2.6',
        	);

        	$client = new Predis\Client( $parameters, $options );
        	var_dump( $client->select( 10 ) );
        	$client->flushdb();
	*/
	//////////////////////////////////////////////////////////////////////
	// Etc
	//////////////////////////////////////////////////////////////////////				
			
			// PIPELINE
	/*		
			$redis->set( "testkey:0", 10 );
			$redis->set( "testkey:1", 10 );
			$redis->set( "testkey:2", 10 );
			for( $i = 0; $i < 10; $i++ ) {
		
				$pipe = $redis->pipeline();
		
				$pipe->get( "testkey:0" );
				$pipe->get( "testkey:1" );
				$pipe->get( "testkey:2" );
				$replies = $pipe->execute();
			
				$testkey0 = $replies[0] + 5;
				$testkey1 = $replies[1] + 5;
				$testkey2 = $replies[2] + 5;
		
				$pipe->set( "testkey:0", $testkey0 );
				$pipe->set( "testkey:1", $testkey1 );
				$pipe->set( "testkey:2", $testkey2 );
				$pipe->execute();
				
				var_dump( $redis->get( "testkey:0" ) );
				var_dump( $redis->get( "testkey:1" ) );
				var_dump( $redis->get( "testkey:2" ) );
	
			}
			$redis->del( "testkey:0" );
			$redis->del( "testkey:1" );F
			$redis->del( "testkey:2" );
	*/
	/*
			$replies = $redis->pipeline( function ($pipe) {
	    												      for ($i = 0; $i < 10; $i++) {
	        	                                                  $pipe->set( "key:$i", str_pad( $i, 4, "0", 0 ) );
	        	                                                  $pipe->get( "key:$i" );
	    												      }
										 } );
										 
			var_dump( $replies );
			
			$replies = $redis->pipeline( function ($pipe) {
	    												      for ($i = 0; $i < 10; $i++) {
	        	                                                  $pipe->del( "key:$i", str_pad( $i, 4, "0", 0 ) );
	    												      }
										 } );		
		
			var_dump( $replies );								 				
	*/
	/*
			// CLUSTER
			// Developers can customize the distribution strategy used by the client
			// to distribute keys among a cluster of servers simply by creating a class
			// that implements Predis\Distribution\DistributionStrategyInterface.
		
			use Predis\Connection\PredisCluster;
			use Predis\Cluster\Distribution\DistributionStrategyInterface;
			use Predis\Cluster\Hash\HashGeneratorInterface;	
		
			class NaiveDistributionStrategy implements DistributionStrategyInterface, HashGeneratorInterface 
			{    
				private $nodes;    
				private $nodesCount;    
			
				public function __construct() 
				{        
					$this->nodes = array();        
					$this->nodesCount = 0;    
				}
			
				public function add($node, $weight = null) 
				{
					$this->nodes[] = $node;
					$this->nodesCount++;
				}
			
				public function remove($node) 
				{
					$this->nodes = array_filter($this->nodes, function ($n) use ($node) {
						return $n !== $node;
					});        
				
					$this->nodesCount = count($this->nodes);
				}
			
				public function get($key)    
				{
					if (0 === $count = $this->nodesCount) {
						throw new RuntimeException('No connections');        
					}        
				
					return $this->nodes[$count > 1 ? abs($key % $count) : 0];    
				}    
			
				public function hash($value)    
				{        
					return crc32($value);
				}    
			
				public function getHashGenerator()    
				{
					return $this;    
				}
			}
		
			echo "Cluster Test" . "<br>";	
		
			$multiple_servers = array( array( 'host' => '127.0.0.1', 
	                                     	  'port' => 6379,
	                                  	      'database' => 0,
	                                	      'alias' => 'first' ),
	                             	   array( 'host' => '127.0.0.1',
	                               	          'port' => 6380,
	                                          'database' => 0,
	                                          'alias' => 'second' ),
	                                   array( 'host' => '127.0.0.1',
	                                          'port' => 6381,
	                                          'database' => 0,
	                                          'alias' => 'third' ) );	
	
			
			$redis = new Predis\Client(array('host'=>'127.0.0.1'));
			
			// CLUSTER
			$options = array( 'cluster' => function () {        
										   		$distributor = new NaiveDistributionStrategy();
												$cluster = new PredisCluster($distributor);
												return $cluster;
											} );
			
			$client = new Predis\Client($multiple_servers, $options);
			
			for ($i = 0; $i < 100; $i++) {
				
				$client->set( "key:$i", str_pad( $i, 4, '0', 0 ) );
				var_dump( $client->get( "key:$i" ) );
			}
			
			$server1 = $client->getClientFor( "first" )->info();
			$server2 = $client->getClientFor( "second" )->info();
			$server3 = $client->getClientFor( "third" )->info();		
			
			var_dump( $server1 );
			var_dump( $server2 );
			var_dump( $server3 );
			
			for ($i = 0; $i < 100; $i++) {    
			
				$client->del( "key:$i" );
			}											
	*/

	//////////////////////////////////////////////////////////////////////
	// Quick Start
	//////////////////////////////////////////////////////////////////////			
	/*		
			// SET & GET, and EXISTS
			$redis->set( "texi_car", "set: value" );
			$value = $redis->get( "texi_car" );	
			var_dump($value);
			echo (($redis->exists( "texi_car" )) ? "true" : "false") . "<br>";
	*/
	/*
	  		// EXPIRE , EXPIREAT , TTL, and PERSIST
			// set the expiration for next week
			$redis->set( "expire in 1 week", "I have data for a week" );
			$redis->expireat( "expire in 1 week", strtotime("+1 week") );
			$ttl = $redis->ttl( "expire in 1 week" ); // will be 604800 seconds
			var_dump($ttl);
			// set the expiration for one hour
			$redis->set("expire in 1 hour", "I have data for an hour");
			$redis->expire("expire in 1 hour", 3600);
			$ttl = $redis->ttl("expire in 1 hour"); // will be 3600 seconds
			// never expires
			$redis->set("never expire", "I want to leave forever!");
			// never expires - remove the expiration from a key
			$redis->persist("expire in 1 hour");
			$ttl = $redis->ttl("expire in 1 hour"); // -1
			var_dump($ttl);
	*/
	/*		
			// DEL
			$redis->del( "never expire" );
			echo (($redis->exists( "never expire" )) ? "true" : "false") . "<br>";		
			$redis->del( "expire in 1 hour" );
			echo (($redis->exists( "expire in 1 hour" )) ? "true" : "false") . "<br>";
	*/
	/*		
			// INCR (INCRBY) and DECR (DECRBY)
			// increment the number of views by 1 for an article
			// with id 234
			$redis->incr( "article_views_234" );
			$value = $redis->get( "article_views_234" );	
			var_dump($value);		
			// increment views for article 237 by 5
			$redis->incrby( "article_views_237", 5 );
			$value = $redis->get( "article_views_237" );	
			var_dump($value);			
			// decrement views for article 237
			$redis->decr( "article_views_237" );
			$value = $redis->get( "article_views_237" );	
			var_dump($value);			
			// decrement views for article 237 by 3
			$redis->decrby( "article_views_237", 3 );
			$value = $redis->get( "article_views_237" );	
			var_dump($value);
	*/
	/*
	 		// HSET, HGET and HGETALL, HINCRBY, and HDEL
			$redis->hset( "taxi_car", "brand", "Toyota" );
			$redis->hset( "taxi_car", "model", "Yaris" );
			$redis->hset( "taxi_car", "license number", "RO-01-PHP" );
			$redis->hset( "taxi_car", "year of fabrication", 2010 );
			$redis->hset( "taxi_car", "nr_starts", 0 );
			echo "taxi_car - License number: " . $redis->hget( "taxi_car", "license number" ) . "<br>";
			
			$redis->hmset( "bus_car", array( "brand" => "Toyota",
			                                 "model" => "Yaris" ,
			                                 "license number" => "RO-02-PHP",
			                                 "year of fabrication" => 2010,
			                                 "nr_starts" => 0 ) );                    
			echo "bus_car - License number: " . $redis->hget( "bus_car", "license number" ) . "<br>";
			
			// remove license number
			$redis->hdel( "taxi_car", "license number" );
			$redis->hdel( "bus_car", "license number" );
			// increment number of starts
			$redis->hincrby("taxi_car", "nr_starts", 1);
			
			$taxi_car = $redis->hgetall("taxi_car");		                               
			echo "All info about taxi_car";
			echo "<pre>";
			var_dump($taxi_car);
			echo "</pre>";
	*/
	/*	
			// LPUSH, RPUSH, LPOP, RPOP, LLEN, LRANGE
			$list = "PHP Frameworks List";
			$redis->rpush($list, "Symfony 2");
			$redis->rpush($list, "Symfony 1.4");
			$redis->lpush($list, "Zend Framework");
			
			echo "Number of frameworks in list: " . $redis->llen($list) . "<br>";
			
			$arList = $redis->lrange($list, 0, -1);
			echo "<pre>";
			print_r($arList);
			echo "</pre>";
			
			// the last entry in the listF
			echo $redis->rpop($list) . "<br>";
			
			// the first entry in the list
			echo $redis->lpop($list) . "<br>";
	*/
	
/*	
	class KEY
	{
		const OBJECT = "object";
		const ID = "id";
		const POSITION = "position";
	} 
	
	
		$userInfo = array();
		
		$userInfo[PROTOCOL\KEY::ID] = 100;
		$userInfo[PROTOCOL\KEY::POSITION] = "300";
		$areaTitle = "good friend";
		$areaPW = "";
		
	
		$redis->sadd( "area_test", array( KEY::OBJECT.sprintf( ":%s", $userInfo[PROTOCOL\KEY::ID] ),
		                                  KEY::OBJECT.":$areaTitle",
		                                  KEY::OBJECT.":$areaPW",
										  KEY::OBJECT.sprintf( ":%s", $userInfo[PROTOCOL\KEY::POSITION] ) ) );
		$arList = $redis->smembers( "area_test" );
		foreach ($arList as $i => $value) {
			$retValue = $redis->spop( "area_test" );
			var_dump($retValue);
		}										 
*/												 
	
    	$g_RDSServerList = array( 
 									'127.0.0.1',
								);	
/*	
		// PIPELINE example
		$redis->set( "key1", "hello" );
		$redis->set( "key2", "world" );	
		
		$result = false;
		for ( $i = 0; 
		      $i < count( $g_RDSServerList ); 
			  $i++ ) {  			
			
			$pl = $redis->pipeline();
            $pl->exists( "key3" );
            $result = $pl->execute();			            
		}
		
		var_dump( $result );		

		$redis->del( "key1", "key2", "key3" ); // or array( "key1", "key2", "key3" );
*/
/*
		// PIPELINE example			
		$result = array();
		for ( $i = 0; 
		      $i < count( $g_RDSServerList ); 
			  $i++ ) {  			
			
			$pl = $redis->pipeline();
            $pl->keys( "*" );
            $keyList = $pl->execute();
            if ( 0 < count( $keyList ) ) {
     			foreach( $keyList[0] as $k => $v ) {
     				$pl->smembers( $v );
           		 	$arList = $pl->execute();     				
     				if ( 0 < count( $arList ) ) {
     					$result[$v] = $arList[1];
     				}

     			}     			      	
            }
		}
		
		var_dump($result);
*/
/*
		$key = 'AREA#211138#test_area';
		$ch = crc32($key)%count($g_RDSServerList);
		var_dump( $ch );
*/
/*
		$enterUserInfo = array();
		$enterUserInfo['user_id'] = 'justin';
		$enterUserInfo['nickname'] = '?섑븯??;
		$enterUserInfo['profile_image'] = 'image.jpg';
	
		$enterMemberInfo = 'user_id'.sprintf( ":%s", $enterUserInfo['user_id'] )
		                   .','.'nickname'.sprintf( ":%s", $enterUserInfo['nickname'] )
						   .','.'profile_image'.sprintf( ":%s", $enterUserInfo['profile_image'] )
						   ;	
		var_dump( $enterMemberInfo );
*/	
			
} catch (Exception $e) {

	echo "Excepted Predis !!!";
	echo "<br>";
	var_dump( Utility::GetExceptionDataString( $e ) );
}

?>
