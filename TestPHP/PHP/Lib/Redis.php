<?php

require 'Predis/Autoloader.php';
Predis\Autoloader::register();

class RDS
{
    static private $_rdsh = null;
    static private function GetRedisH($ch)
    {
        $hosts = CONFIG::$RDSHOSTLIST;
        if (RDS::$_rdsh == null) {
            RDS::$_rdsh = array();
        }
        if (isset(RDS::$_rdsh[$ch]) == false) {
            RDS::$_rdsh[$ch] = new Predis\Client(array('host'=>$hosts[$ch]));
        }
        return RDS::$_rdsh[$ch];
    }

    private static function GetClusterHashFromKey($key)
    {
        $ch = crc32($key)%count(CONFIG::$RDSHOSTLIST);
        return $ch;
    }
    
    static function MGet($keys)
    {
        $keyDatas = array();
        foreach ($keys as $k) {
            $ch = RDS::GetClusterHashFromKey($k);
            $keyDatas[$ch][] = $k;
        }
        
        $result = array();
        foreach ($keyDatas as $ch => $keyList) {
            $datas = RDS::GetRedisH($ch)->mget($keyList);
            foreach ($keyList as $n => $kv) {
                $result[$kv] = $datas[$n];
            }
        }
        return $result;
    }
    static function Get($key)
    {
        return RDS::GetRedisH(RDS::GetClusterHashFromKey($key))->get($key);
    }
    static function Set($key, $val)
    {
        return RDS::GetRedisH(RDS::GetClusterHashFromKey($key))->set($key, $val);
    }
    static function Del($key)
    {
        return RDS::GetRedisH(RDS::GetClusterHashFromKey($key))->del($key);
    }
    
    static function SAdd($key, $val)
    {
        return RDS::GetRedisH(RDS::GetClusterHashFromKey($key))->sadd($key, $val);
    }
    static function SRem($key, $val)
    {
        return RDS::GetRedisH(RDS::GetClusterHashFromKey($key))->srem($key, $val);
    }
    static function SPop($key)
    {
        return RDS::GetRedisH(RDS::GetClusterHashFromKey($key))->spop($key);
    }
    static function SMembers($key)
    {
        return RDS::GetRedisH(RDS::GetClusterHashFromKey($key))->smembers($key);
    }
    static function MultiSAdd($keys, $val)
    {
        $keyDatas = array();
        foreach ($keys as $k) {
            $ch = RDS::GetClusterHashFromKey($k);
            $keyDatas[$ch][] = $k;
        }
        
        $result = array();
        foreach ($keyDatas as $ch => $keyList) {
            /*
            RDS::GetRedisH($ch)->multi();
            foreach ($keyList as $k) {
                RDS::GetRedisH($ch)->sadd($k, $val);
            }
            RDS::GetRedisH($ch)->exec();
            */
            $pl = RDS::GetRedisH($ch)->pipeline();
            foreach ($keyList as $k) {
                $pl->sadd($k, $val);
            }
            $pl->execute();
        }
    }
    
    //============================================================================================
    
    static function MakeUpdatedListKey($userId) {
        return CONFIG::RDSPREFIX.sprintf('UL:%s', $userId);
    }
    static function MakeScoreDataKey($userId) {
        return CONFIG::RDSPREFIX.sprintf('SD:%s', $userId);
    }
}
	
?>
