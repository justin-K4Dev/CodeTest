<?php
require_once 'Lib/Utility.php';
require_once 'Lib/Log.php';


///////////////////////////////////////////////////////////////////////////////
/// @file Mongodb.php
/// @class 
/// @brief
/// 
/// @author giman
/// @date 2014. 2. 7. 오후 2:18:45
///////////////////////////////////////////////////////////////////////////////
class MongoDBConnector 
{
	protected $_mongosYN;
	protected $_dbServerList;
	protected $_mdbID;
	protected $_mdbPW;
	protected $_mdbName;
	private $_dbconn;

	///////////////////////////////////////////////////////////////////////////////
	/// @brief 연결정보 셋팅
	/// @return 
	/// @param 
	///
	/// @author giman
	/// @date 2014. 2. 7. 오후 2:19:51
	///////////////////////////////////////////////////////////////////////////////
	public function SetConnectionInfo( $mongosYN, $dbServerList, $dbID, $dbPW, $dbName ) 
	{
		$this->_mongosYN = $mongosYN;
		$this->_dbServerList = $dbServerList;
		$this->_mdbID = $dbID;
		$this->_mdbPW = $dbPW;
		$this->_mdbName = $dbName;
	}
	
	///////////////////////////////////////////////////////////////////////////////
	/// @brief 샤딩키 생성
	/// @return
	/// @param
	///
	/// @author giman
	/// @date 2014. 2. 7. 오전 11:07:54
	///////////////////////////////////////////////////////////////////////////////
	public function GetMDBClusterHashKey( $data )
	{
		if ( null == $data )
			throw new Exception("MongoDB Cluster Hash error !!!", LIB_ERROR_CODE::ERROR);
	
		return Utility::ModObjectKey($data, count($this->_dbServerList));
	}
	

	///////////////////////////////////////////////////////////////////////////////
	/// @brief 디비 연결하기
	/// @return
	/// @param
	///
	/// @author giman
	/// @date 2014. 2. 7. 오후 2:20:19
	///////////////////////////////////////////////////////////////////////////////
	private function GetConnect($ch, $dbName = null)
	{
		/// @brief 기본 디비명 셋팅 - giman 2014. 2. 7. 오후 3:03:38
		if( $dbName == null )
			$dbName = $this->_mdbName;
	
		/// @brief 이미 연결이 되어 있으면 그냥 반환 - giman 2014. 2. 7. 오후 3:38:34
		if( $this->_dbconn != null )
			return $this->_dbconn->{ $dbName };;
	
		///////////////////////////////////////////////////////////////////////////////
		/// @author giman
		/// @date 2014. 2. 7. 오후 3:09:51
		/// @brief 커넥션 스트링 만들기
		///////////////////////////////////////////////////////////////////////////////
		/// @brief 서버 주소 커넥션 스트링 만들기 (매뉴얼 샤딩일 경우는 cluster hash key에 맞는 서버주소만 반환) - giman 2014. 2. 7. 오후 3:09:59
		$address = implode(",", $this->_dbServerList);
		if( 'N' == $this->_mongosYN )
			$address = $this->_dbServerList[$ch];
	
		/// @brief 계정정보 유무에 따라 커넥션 스트링 생성 - giman 2014. 2. 7. 오후 3:10:40
		$connectionString = sprintf("mongodb://%s", $address);
		if (strlen($this->_mdbID) > 0 && strlen($this->_mdbPW) > 0)
			$connectionString = sprintf("mongodb://%s:%s@%s", $this->_mdbID, $this->_mdbPW, $address);
	
		///////////////////////////////////////////////////////////////////////////////
		/// @author giman
		/// @date 2014. 2. 7. 오후 3:11:09
		/// @brief 디비 연결
		///////////////////////////////////////////////////////////////////////////////
		$mdb = new MongoClient( $connectionString );
		$mdb->setReadPreference( MongoClient::RP_PRIMARY_PREFERRED );
		$this->_dbconn = $mdb;
	
	
		/// @brief 연결에 실패했을 경우 - giman 2014. 2. 7. 오후 2:27:12
		if ( null == $this->_dbconn )
		{
			throw new Exception(
					sprintf( "Mongo Server connect failure !!! ")
					, LIB_ERROR_CODE::ERROR
			);
		}
	
		return $this->_dbconn->{ $dbName };;
	}
	
	///////////////////////////////////////////////////////////////////////////////
	/// @brief 컬렉션 가져오기
	/// @return
	/// @param
	///
	/// @author giman
	/// @date 2014. 2. 7. 오전 11:06:31
	///////////////////////////////////////////////////////////////////////////////
	private function GetCollection($ch, $collection)
	{
		return $this->GetConnect( $ch )->selectCollection( $collection );;
	}
	
	///////////////////////////////////////////////////////////////////////////////
	/// @brief 샤드 컬렉션 설정하기
	/// @return 
	/// @param 
	///
	/// @author giman
	/// @date 2014. 2. 7. 오후 3:23:17
	///////////////////////////////////////////////////////////////////////////////
	public function EnsureShardCollection( $ch, $dbName, $collName, $key, $option = array() )
	{
		$fullShardCollName = $dbName.'.'.$collName;
		try 
		{
			$adminDB = $this->GetConnect($ch, "admin");
			
			$result = $adminDB->command( array( 'enableSharding'=> $dbName ) );
			$result = $adminDB->command( array( 'shardCollection'=> $fullShardCollName, 'key' => array( $key => 1 ), $option ) );
		}
		catch(Exception $e) 
		{
			/// @brief 예외 던지지 말고 기록만 할 것 - giman 2014. 2. 7. 오후 3:27:31
			g_GetLog()->Write( LOG_LEVEL::ERROR, LIB_LOG_TYPE::DATABASE, LIB_ERROR_CODE::ERROR, 
				sprintf( "Failed to shard Collection !!! # FullShardCollName:%s - (ECM: %s)", $fullShardCollName, Utility::GetExceptionDataString( $e ) ) );
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	/// @brief 인덱스 설정하기
	/// @return 
	/// @param 
	///
	/// @author giman
	/// @date 2014. 2. 6. 오후 7:28:04
	///////////////////////////////////////////////////////////////////////////////
	public function EnsureIndex($ch, $collection, $key, $options = array() ) 
	{
		try 
		{
			$coll = $this->GetCollection($ch, $collection);
			$ret = $coll->ensureIndex( $key, $options );
		} 
		catch (MongoException $exception) 
		{
			/// @brief 예외 던지지 말고 기록만 할 것 - giman 2014. 2. 7. 오후 3:27:31
			g_GetLog()->Write( LOG_LEVEL::ERROR, LIB_LOG_TYPE::DATABASE, LIB_ERROR_CODE::ERROR, 
			sprintf( "MongoDB EnsureIndex error !!! - (ECM: %s)", Utility::GetExceptionDataString( $e ) ) );
		}
	}
	
	///////////////////////////////////////////////////////////////////////////////
	/// @brief InsertData
	/// @return 
	/// @param 
	///
	/// @author giman
	/// @date 2014. 2. 7. 오후 3:57:17
	///////////////////////////////////////////////////////////////////////////////
	public function InsertData($ch, $collection, $data) 
	{
		$coll = $this->GetCollection( $ch, $collection );
		try {
			$ret = $coll->insert( $data, array ( "w" => true ) );
		} catch ( Exception $exception ) {
			throw new Exception(
					sprintf( "MongoDB Insert error !!!")
					, LIB_ERROR_CODE::ERROR
					, $exception
			);
		}
		
		/// @brief 몽고디비에서 에러를 리턴했을 때 - giman 2014. 2. 7. 오후 4:01:18
		if ($ret == null || array_key_exists('err', $ret) == false || $ret['err'] != null) 
		{
			throw new Exception(
					sprintf( "MongoDB Insert error !!! - %s", var_export($ret, true))
					, LIB_ERROR_CODE::ERROR
			);
		}

		/// @brief 성공시 _id 값 리턴 - giman 2014. 2. 7. 오후 4:02:16
		$rtnval = $data['_id'];
		
		/// @brief _id가 MongoID객체일 경우 객체가 아니라 문자열로 리턴하기 - giman 2014. 2. 7. 오후 4:03:22
		if ($data['_id'] instanceof MongoId)
			$rtnval = $data['_id']->{'$id'};

		return $rtnval;
	}
	
	///////////////////////////////////////////////////////////////////////////////
	/// @brief UpsertData
	/// @return 
	/// @param 
	///
	/// @author giman
	/// @date 2014. 2. 7. 오후 3:53:56
	///////////////////////////////////////////////////////////////////////////////
	public function UpsertData($ch, $collection, $key, $data) 
	{
		$affectedCount = 0;
		$coll = $this->GetCollection($ch, $collection);
		
		try {
			$option = array();
			$option["w"] = true;
			$option["upsert"] = true;
			
			$ret = $coll->update($key, $data, $option);
			$affectedCount = $ret["n"];
		} catch (Exception $exception) {
			throw new Exception(
					sprintf( "MongoDB Upsert error !!!")
					, LIB_ERROR_CODE::ERROR
					, $exception
			);	
		}
		
		return $affectedCount;
	}

	///////////////////////////////////////////////////////////////////////////////
	/// @brief UpdateData
	/// @return 영향 받은 document 수 반환
	/// @param 
	///
	/// @author giman
	/// @date 2014. 2. 7. 오후 4:15:41
	///////////////////////////////////////////////////////////////////////////////
	public function UpdateData($ch, $collection, $key, $data, $multiple = false) 
	{
		$affectedCount = 0;
		$coll = $this->GetCollection($ch, $collection);
		
		try {
			$option = array();
			$option["w"] = true;
			$option["multiple"] = $multiple;
			
			$ret = $coll->update($key, $data, $option);
			$affectedCount = $ret["n"];
		} catch (Exception $exception) {
			throw new Exception(
					sprintf( "MongoDB Update error !!!")
					, LIB_ERROR_CODE::ERROR
					, $exception
			);
		}
		
		return $affectedCount;
	}

	///////////////////////////////////////////////////////////////////////////////
	/// @brief RemoveData
	/// @return 
	/// @param 
	///
	/// @author giman
	/// @date 2014. 2. 7. 오후 4:30:08
	///////////////////////////////////////////////////////////////////////////////
	public function RemoveData($ch, $collection, $key) 
	{
		$affectedCount = 0;
		$coll = $this->GetCollection($ch, $collection);
		
		try {
			$option = array();
			$option["w"] = true;
			
			$ret = $coll->remove($key,  $option);
			$affectedCount = $ret["n"];
		} catch (Exception $exception) {
			throw new Exception(
					sprintf( "MongoDB Remvoe error !!!")
					, LIB_ERROR_CODE::ERROR
					, $exception
			);
		}
		
		return $affectedCount;
	}
	

	function SetValue($ch, $collection, $key, $data) {
		return $this->UpdateData($ch, $collection, $key, array (
			'$set' => $data
		));
	}
	function PushValue($ch, $collection, $key, $data) {
		return $this->UpdateData($ch, $collection, $key, array (
			'$push' => $data
		));
	}
	function AddToSetValue($ch, $collection, $key, $data) {
		return $this->UpdateData($collection, $key, array (
			'$addToSet' => $data
		));
	}
	function IncValue($ch, $collection, $key, $data) {
		foreach ($data as $k => $v) {
			$data[$k] = (int) $v;
		} // $inc는 int형만 증감 가능
		return $this->UpdateData($ch, $collection, $key, array (
			'$inc' => $data
		));
	}
	function DelValue($ch, $collection, $key, $data) {
		return $this->UpdateData($ch, $collection, $key, array (
			'$unset' => $data
		));
	}
	function PullValue($ch, $collection, $key, $data) {
		return $this->UpdateData($ch, $collection, $key, array (
			'$pull' => $data
		));
	}
	
	public function GetData($ch, $collection, $key, $field = array ()) {
		$coll = $this->GetCollection($ch, $collection);
		return $coll->findOne($key, $field);
	}
	public function GetDatas($ch, $collection, $key, $field = array ()) {
		$coll = $this->GetCollection($ch, $collection);
		return iterator_to_array($coll->find($key, $field));
	}
	public function GetCount($ch, $collection, $key) {
		$coll = $this->GetCollection($ch, $collection);
		return $coll->count($key);
	}
	public function GetOptionDatas($ch, $collection, $key, $field, $sort, $limit, $skip) {
		$coll = $this->GetCollection($ch, $collection);
		return iterator_to_array($coll->find($key, $field)->sort($sort)->limit($limit)->skip($skip));
	}
}
