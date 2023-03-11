<?php

require_once 'Lib/Log.php';

class MC
{
	/// @brief Key테이블(어느 key가 사용중인지 체크용 (key이름과 expireDate 조합)(실 운영땐 필요없을듯) - giman 2014. 2. 14. 오후 5:01:57
	static public $KEYTABLE = array();
	
    static private $_mch;
    
    static public function GetMC($key)
    {
        $ch = crc32($key) % count( SERVER_LIST::$g_MCServerList );

        if (MC::$_mch != null && array_key_exists($ch, MC::$_mch)) {
            return MC::$_mch[$ch];
        }
        
        if (MC::$_mch == null) {
            MC::$_mch = array();
        }

        MC::$_mch[$ch] = new Memcached;
        $list = SERVER_LIST::$g_MCServerList;
        if (MC::Connect( MC::$_mch[$ch], $list[$ch], 11211 ) == false) {
			g_GetLog()->Write( LOG_LEVEL::ERROR, LOG_TYPE::DATABASE, ERROR_CODE::MC_CONNECT_FAILURE, sprintf( "Memcached Server connect failure !!! (MCServer:%s)", $list[$ch] ) );
			return null;
        }
        
        ///////////////////////////////////////////////////////////////////////////////
        /// @author giman
        /// @date 2014. 2. 24. 오후 2:41:03
        /// @brief 키테이블 관리
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief 키 기록 - giman 2014. 2. 14. 오후 4:59:01
        MC::$KEYTABLE = MC::$_mch[$ch]->get("KEYTABLE");
        
        /// @brief 값 없는 키 제거하기 - giman 2014. 2. 24. 오후 2:40:59
        if(MC::$KEYTABLE != null)
        	MC::$KEYTABLE = array_filter(MC::$KEYTABLE);
        
        return MC::$_mch[$ch];
    }
    
    static private function Connect($instance, $host , $port)
    {
    	$servers = $instance->getServerList();
    	if(is_array($servers)) {
    		foreach ($servers as $server)
    			if($server['host'] == $host and $server['port'] == $port)
    				return true;
    	}
    	return $instance->addServer($host , $port);
    }    
    
    static private function MakeMCKey($key_code, $key_value)
    {
        return sprintf("%s_%s", $key_code, $key_value);
    }
    static public function Get($key_code, $key_value)
    {
        $key = MC::MakeMCKey($key_code, $key_value);
        $hMC = MC::GetMC($key);
        if( null == $hMC ) {
        	return false;
        }
                
        $result = $hMC->get($key);
        return $result;
    }
    static public function Set($key_code, $key_value, $value, $expSec=0)
    {
        $key = MC::MakeMCKey($key_code, $key_value);
        $hMC = MC::GetMC($key);
        if( null == $hMC ) {
        	return false;
        }
        
        $result = $hMC->set($key, $value, false, $expSec);
        
        /// @brief 키 기록 - giman 2014. 2. 14. 오후 4:59:01
        MC::$KEYTABLE[$key] = "Set ".$expSec;
        $hMC->set("KEYTABLE", MC::$KEYTABLE);
        
        return $result;
    }
    static public function Add($key_code, $key_value, $value, $expSec=0)
    {
        $key = MC::MakeMCKey($key_code, $key_value);
        $hMC = MC::GetMC($key);        
        if( null == $hMC ) {
        	return false;
        }        
        
        $result = $hMC->add($key, $value, false, $expSec);
        
        /// @brief 키 기록 - giman 2014. 2. 14. 오후 4:59:01
        MC::$KEYTABLE[$key] = "Add ".$expSec;
        $hMC->set("KEYTABLE", MC::$KEYTABLE);
        
        return $result;
    }
    static public function Inc($key_code, $key_value, $value)
    {
        $key = MC::MakeMCKey($key_code, $key_value);
        $hMC = MC::GetMC($key);
        if( null == $hMC ) {
        	return false;
        }        
        
        $result = $hMC->increment($key, $value);
        
        /// @brief 키 기록 - giman 2014. 2. 14. 오후 4:59:01
        MC::$KEYTABLE[$key] = "Inc";
        $hMC->set("KEYTABLE", MC::$KEYTABLE);
        
        return $result;
    }
    static public function Dec($key_code, $key_value, $value)
    {
        $key = MC::MakeMCKey($key_code, $key_value);
        $hMC = MC::GetMC($key);
        if( null == $hMC ) {
        	return false;
        }
                
        $result = $hMC->decrement($key, $value);
        
        /// @brief 키 기록 - giman 2014. 2. 14. 오후 4:59:01
        MC::$KEYTABLE[$key] = "Dec";
        $hMC->set("KEYTABLE", MC::$KEYTABLE);
        
        return $result;
    }
    static public function Del($key_code, $key_value)
    {
        $key = MC::MakeMCKey($key_code, $key_value);
        $hMC = MC::GetMC($key);
        if( null == $hMC ) {
        	return false;
        }        
        
        $result = $hMC->delete($key);
        
        /// @brief 키 기록 - giman 2014. 2. 14. 오후 4:59:01
        unset(MC::$KEYTABLE[$key]);
        $hMC->set("KEYTABLE", MC::$KEYTABLE);
        
        return $result;
    }
}

?>