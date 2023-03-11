<?php

require_once 'Lib/Log.php';


function GetDB()
{
    global $g_DBConnector;
    if ($g_DBConnector == null) {
        $g_DBConnector = new MySQLDB();
    }
    ($g_DBConnector instanceof MySQLDB);
    return $g_DBConnector;
}


class MySQLDB {
	
	private $_dbServerInfo;
	private $_dbh;
	
	public function SetDBServerInfo( $serverAddr, $uid, $pwd, $dbname )
	{
		$this->_dbServerInfo = array();
		$this->_dbServerInfo["server_addr"] = $serverAddr;
		$this->_dbServerInfo["uid"] = $uid;
		$this->_dbServerInfo["pwd"] = $pwd;
		$this->_dbServerInfo["db_name"] = $dbname;
	}

	public function ConnectDB()
	{
		if ($this->_dbh != null) {
			return $this->_dbh;
		}
		
		if ( isset($this->_dbServerInfo) == false ) {
			g_GetLog()->Write( LOG_LEVEL::ERROR, LIB_LOG_TYPE::DATABASE, LIB_ERROR_CODE::ERROR, "Not set DB Info !!!" );
			return null;
		}
		
		$serverAddr = $this->_dbServerInfo["server_addr"];
		$uid = $this->_dbServerInfo["uid"];
		$pwd = $this->_dbServerInfo["pwd"];
		$dbname = $this->_dbServerInfo["db_name"];	
		
		try {			
			$this->_dbh = new PDO("mysql:host=$serverAddr;dbname=$dbname", $uid, $pwd, array(PDO::MYSQL_ATTR_INIT_COMMAND => "SET NAMES 'UTF8'",
					                                                                         PDO::ATTR_PERSISTENT => true));
			$this->_dbh->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
				
		} catch (PDOException $err) {
			
			$errMsg = sprintf( "Failed to connect MySQL Server !!! # ServerAddr:%s, ID:%s, PW:%s, DBName:%s - (EM:%s)",
							   $serverAddr, $uid, $pwd, $dbname,
					           $err->getMessage() );			
			
		    g_GetLog()->Write( LOG_LEVEL::ERROR, LIB_LOG_TYPE::DATABASE, LIB_ERROR_CODE::ERROR, $errMsg );
			return null;
		}
		
		return $this->_dbh;
	}

	public function Query($query) {
		$dbh = $this->ConnectDB();
		if ($dbh == null) {
			$errMsg = sprintf("Query:%s", $query);
		    g_GetLog()->Write( LOG_LEVEL::ERROR, LIB_LOG_TYPE::DATABASE, LIB_ERROR_CODE::ERROR, $errMsg );
			return false;
		}
		return $dbh->query($query);
	}

	public function QuerySafe($statement, $args = null) {
		$dbh = $this->ConnectDB();
		if ($dbh == null) {
			return false;
		}

		$sth = $dbh->prepare($statement);
		try {
			if ($sth->execute($args) == false) {
				return false;
			}
		} catch (PDOException $err) {
		    $errMsg = sprintf( "Query:%s (args:%s) - (EM:%s)", $statement, var_export($args, true), Utility::GetExceptionDataString($err) );
		    g_GetLog()->Write( LOG_LEVEL::ERROR, LIB_LOG_TYPE::DATABASE, LIB_ERROR_CODE::ERROR, $errMsg );
			return false;
		}
		return $sth;
	}

	public function GetRowCount($stmt) {
		return $stmt->rowCount();
	}
	public function GetNextRowData($stmt) {
		return $stmt->fetch();
	}
	public function GetFieldData($rowdata, $key) {
		return $rowdata[$key];
	}
	public function GetAllData($stmt) {
		return $stmt->fetchAll();
	}
}
?>
