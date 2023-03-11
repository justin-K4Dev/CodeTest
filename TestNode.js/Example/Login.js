
'use strict';
var uuid = require('node-uuid');
var Promise = require('bluebird');
var mySQLPoolCluster = require('../BlueBird/MySQL');

Promise.config({
    // Enable warnings
    warnings: false,
    // Enable long stack traces
    longStackTraces: true,
    // Enable cancellation
    cancellation: true,
    // Enable monitoring
    monitoring: true
});


var m1Config = {
    host : '192.168.1.131',
    user : 'root',
    password : 'kang14',
    connectionLimit : 2,
    acquireTimeout : 5,
    debug : false
};

var s1Config = {
    host : '192.168.1.132',
    user : 'root',
    password : 'kang14',
    connectionLimit : 5,
    acquireTimeout : 5,
    debug : false
};

var s2Config = {
    host : '192.168.1.133',
    user : 'root',
    password : 'kang14',
    connectionLimit : 2,
    acquireTimeout : 5,
    debug : false
};

mySQLPoolCluster.add('0', s1Config);
//mySQLPoolCluster.add('1', s1Config);
//mySQLPoolCluster.add('2', s2Config);

// 계정 관련 정보 등록
function createAccountInfo(platformType, platformID, accountUUID, regionID, serverID, level, outCallback) {
    
    var err;
    
    var shardKey = platformType + ':' + platformID;
    var shardID = mySQLPoolCluster.makeShardID(shardKey.toString(), mySQLPoolCluster.getNodeCount());
    
    mySQLPoolCluster.getSQLConnection(shardID)
    .then(function (connection) {
        console.log("Success connect to DB - TargetShardID : " + connection._clusterId);
        
        return mySQLPoolCluster.beginTransaction(connection);
    })
    .then(function (connection) {
        console.log("Start Transaction - TargetShardID : " + connection._clusterId);
        
        var query = connection.format('call AccountDB.sp_platform_i(?, ?, ?)', [accountUUID, platformType, platformID]);
        return mySQLPoolCluster.queryAsync(connection, query);
    })
   .then(function (values) {
        console.log("Success query sp_platform_i to AccountDB");
        
        var shardKey = accountUUID;
        var shardID = mySQLPoolCluster.makeShardID(shardKey.toString(), mySQLPoolCluster.getNodeCount());
        
        return mySQLPoolCluster.getSQLConnection(shardID);
    })
    .then(function (connection) {
        console.log("Success connect to DB - TargetShardID : " + connection._clusterId);
        
        return mySQLPoolCluster.beginTransaction(connection);
    })
    .then(function (connection) {
        console.log("Start Transaction - TargetShardID : " + connection._clusterId);
        
        var query = connection.format('call AccountDB.sp_account_i(?)', [accountUUID]);
        return mySQLPoolCluster.queryAsync(connection, query);
    })
    .then(function (values) {
        console.log("Success query sp_account_i to AccountDB");
        
        return mySQLPoolCluster.commitAll();
    })
    .catch(function (e) {
        console.log("Catched handler : " + e);
        if (e) {
            mySQLPoolCluster.rollbackAll();
            err = e;
        }
    })
    .finally(function () {
        if (outCallback)
            outCallback(err, accountUUID);

        mySQLPoolCluster.releaseAll();
    });
}

// 계정 관련 조회
function getAccountInfo(platformType, platformID, accountUUID, regionID, serverID, outCallback) {
    
    var err;
    
    var userUUID = 0;
    var unregDate;
    
    var shardKey = platformType + ':' + platformID;
    var shardID = mySQLPoolCluster.makeShardID(shardKey.toString(), mySQLPoolCluster.getNodeCount());

    mySQLPoolCluster.getSQLConnection(shardID)
    .then(function (connection) {
        console.log("Success connect to DB - TargetShardID : " + connection._clusterId);
                        
        var query = connection.format('call AccountDB.sp_platform_s(?, ?)', [platformType, platformID]);
        return mySQLPoolCluster.queryAsync(connection, query);
    })
    .then(function (values) {
        console.log("Success query sp_platform_s to AccountDB");
        
        var connection = values[0];
        
        if (values[1][0].length <= 0) {
            return;
        }

        var tbl_platform = values[1][0][0];        
        accountUUID = tbl_platform.account_uuid;
        
        var shardKey = accountUUID;
        var shardID = mySQLPoolCluster.makeShardID(shardKey.toString(), mySQLPoolCluster.getNodeCount());
        return mySQLPoolCluster.getSQLConnection(shardID);
    })
    .then(function (connection) {
        console.log("Success connect to DB - TargetShardID : " + connection._clusterId);
    
        var query = connection.format('call AccountDB.sp_account_s(?)', [accountUUID]);
        return mySQLPoolCluster.queryAsync(connection, query);
    })
    .then(function (values) {
        console.log("Success query sp_account_s to AccountDB");
    
        var connection = values[0];
        
        if (values[1][0].length <= 0) {
            return;
        }

        var tbl_account = values[1][0][0];

        var query = connection.format('call AccountDB.sp_user_by_account_server_s(?, ?, ?)', [accountUUID, regionID, serverID]);
        return mySQLPoolCluster.queryAsync(connection, query);
    })
    .then(function(values) {
        console.log("Success query sp_user_by_account_server_s to AccountDB");

        var connection = values[0];
        if (values[1][0].length > 0) {
            var tbl_user = values[1][0][0];
            userUUID = tbl_user.user_uuid;
        }
    })
    .catch(function (e) {
        console.log("Catched handler : " + e);
        err = e;
    })
    .finally(function () {
        if (outCallback)
            outCallback(err, accountUUID, userUUID, unregDate);
        
        mySQLPoolCluster.releaseAll();        
    });
}


// Player 추가
function addUserByAccount(accountUUID, userUUID, regionID, serverID, outCallback)
{
    var err;

    var shardKey = accountUUID;
    var shardID = mySQLPoolCluster.makeShardID(shardKey.toString(), mySQLPoolCluster.getNodeCount());

    mySQLPoolCluster.getSQLConnection(shardID)
    .then(function (connection){

        var query = connection.format('call AccountDB.sp_user_i(?, ?, ?, ?)', [userUUID, accountUUID, regionID, serverID]);
        return mySQLPoolCluster.queryAsync(connection, query);
    })
    .catch(function (e) {
        console.log("Catched handler : " + e);
        if (e) {
            err = e;
        }
    })
    .finally(function () {

        if (outCallback) {
            outCallback(err);
        }

        mySQLPoolCluster.releaseAll();
    });
}


// 다른 플랫폼 계정 체크
function getAccountByOtherPlatform(accountUUID, platformType, platformID, outCallback) { // 적용 1차
    
    var err;
    
    var shardKey = platformType + ':' + platformID;
    var shardID = mySQLPoolCluster.makeShardID(shardKey.toString(), mySQLPoolCluster.getNodeCount());
    
    var platformList = [];
    var userList = [];
    
    mySQLPoolCluster.getSQLConnection(shardID)
    .then(function (connection) {
        console.log("Success connect to DB - TargetShardID : " + connection._clusterId);
        
        var query = connection.format('call AccountDB.sp_platform_by_account_platform_s(?, ?)', [accountUUID, platformType]);
        return mySQLPoolCluster.queryAsync(connection, query);
    })
    .then(function (values) {
        console.log("Success query sp_platform_by_account_platform_s to AccountDB");
        
        var connection = values[0];
        
        if (values[1][0].length > 0) {
            platformList = values[1][0];
        }
        
        var shardKey = accountUUID;
        var shardID = mySQLPoolCluster.makeShardID(shardKey.toString(), mySQLPoolCluster.getNodeCount());
        return mySQLPoolCluster.getSQLConnection(shardID);
    })
    .then(function (connection) {
        console.log("Success connect to DB - TargetShardID : " + connection._clusterId);
        
        var query = connection.format('call AccountDB.sp_user_list_by_account_s(?)', [accountUUID]);
        return mySQLPoolCluster.queryAsync(connection, query);
    })
    .then(function (values) {
        console.log("Success query sp_user_list_by_account_s to AccountDB");
        
        var connection = values[0];
        
        if (values[1][0].length > 0) {
            userList = values[1][0];
        }
    })
    .catch(function (e) {
        console.log("Catched handler : " + e);
        err = e;
    })
    .finally(function () {
        if (outCallback)
            outCallback(err, platformList, userList);

        mySQLPoolCluster.releaseAll();
    });
}


// 해당 계정의 다른 플랫폼 추가
function addOtherPlatformByAccount(accountUUID, platformType, platformID, outCallback) {
    
    var err;
    var result;
    var platformList = [];
    
    // accountUUID 값이 없는 경우
    if ( undefined === accountUUID
        || 0 >= accountUUID) {
        result = 'EMPTY';
        
        if (outCallback)
            outCallback(err, result, platformList);
        
        return;
    }
    
    var foundAccount = false;
    var foundPlatformOfAccount = false;
    var foundPlatform = false;
    
    var shardKey = accountUUID;
    var shardID = mySQLPoolCluster.makeShardID(shardKey.toString(), mySQLPoolCluster.getNodeCount());
    
    mySQLPoolCluster.getSQLConnection(shardID)
    .then(function (connection) {
        console.log("Success connect to DB - TargetShardID : " + connection._clusterId);
        
        var query = connection.format('call AccountDB.sp_account_s(?)', [accountUUID]);
        return mySQLPoolCluster.queryAsync(connection, query);
    })
    .then(function (values) {
        console.log("Success query sp_account_s to AccountDB");
        
        var connection = values[0];
        
        if (values[1][0].length <= 0) {
            result = 'EMPTY';
            
            if (outCallback)
                outCallback(err, result, platformList);
            
            return;
        }
        
        foundAccount = true;
        
        var shardKey = platformType + ':' + platformID;
        var shardID = mySQLPoolCluster.makeShardID(shardKey.toString(), mySQLPoolCluster.getNodeCount());
        
        return mySQLPoolCluster.getSQLConnection(shardID);
    })
    .then(function (connection) {
        console.log("Success connect to DB - TargetShardID : " + connection._clusterId);
        
        var query = connection.format('call AccountDB.sp_platform_by_account_platform_s(?, ?)', [accountUUID, platformType]);
        return mySQLPoolCluster.queryAsync(connection, query);
    })
    .then(function (values) {
        console.log("Success query sp_platform_by_account_platform_s to AccountDB");
        
        var connection = values[0];
        if (values[1][0].length > 0) {
            foundPlatformOfAccount = true;
        }
        
        var query = connection.format('call AccountDB.sp_platform_s(?, ?)', [platformType, platformID]);
        return mySQLPoolCluster.queryAsync(connection, query);
    })
    .then(function (values) {
        console.log("Success query sp_platform_s to AccountDB");
        
        var connection = values[0];
        if (values[1][0].length > 0) {
            foundPlatform = true;
        }
        
        if (true == foundPlatformOfAccount 
            || true == foundPlatform) {
            result = 'OVERLAP_PLATFORM';
        } 
        else if (true == foundAccount) {            
            var query = connection.format('call AccountDB.sp_platform_by_account_platform_u(?, ?, ?)', [accountUUID, platformType, platformID]);
            return mySQLPoolCluster.queryAsync(connection, query);
        }
    })
    .then(function (values) {
        console.log("Success query sp_platform_by_account_platform_u to AccountDB");
        
        var returnValues = [];
        
        var connection = values[0];
        returnValues[0] = connection;
        
        if (values[1][0][0].result == 'OK') {
            result = 'CHANGE';
            returnValues[1] = result;
            
            return returnValues;
        }
        else {
            return mySQLPoolCluster.beginTransaction(connection);
        }
    })
    .then(function (values) {
        
        var returnValues = [];
        
        // connection 객체 여부 체크
        if (typeof values == 'object') {
            
            var connection = values;
            console.log("Start Transaction - TargetShardID : " + connection._clusterId);

            var next = 'INSERT';
            returnValues[0] = connection;
            returnValues[1] = next;
        }

        return returnValues;
    })
    .then(function (values) {
        
        var connection = values[0];
        
        var returnValues = [];
        returnValues[0] = connection;
        
        if ('INSERT' == values[1]) {
            result = 'ADD';

            var query = connection.format('call AccountDB.sp_platform_i(?, ?, ?)', [accountUUID, platformType, platformID]);
            return mySQLPoolCluster.queryAsync(connection, query);
        }
        else {
            return returnValues;
        }
    })
    .then(function (values) {
        var connection = values[0];
        
        var query = connection.format('call AccountDB.sp_platform_by_account_s(?)', [accountUUID]);
        return mySQLPoolCluster.queryAsync(connection, query)
    })
    .then(function (values) {
        console.log("Success query sp_platform_by_account_s to AccountDB");
        
        platformList = [];

        var connection = values[0];
        if (values[1][0].length > 0) {
            var tbl_platformList = values[1][0];    
            for (var idx in tbl_platformList) {
                var tbl_platform = tbl_platformList[idx];
                platformList[idx] = [];
                platformList[idx].platform_type = tbl_platform.platform_type;
                platformList[idx].platform_id = tbl_platform.platform_id;
            }
        }

        mySQLPoolCluster.commitAll();
    })
    .catch(function (e) {
        console.log("Catched handler : " + e);
        err = e;
        result = 'FAIL';

        mySQLPoolCluster.rollbackAll();
    })
    .finally(function () {
        
        if (outCallback)
            outCallback(err, result, platformList);

        mySQLPoolCluster.releaseAll();
    });
}


function getUserAllInfoFromGameDB(accountUUID, outCallback) {

    var err;

    var userList;
    
    var shardKey = accountUUID;
    var shardID = mySQLPoolCluster.makeShardID(shardKey.toString(), mySQLPoolCluster.getNodeCount());

    mySQLPoolCluster.getSQLConnection(shardID)
    .then(function (connection) {
        console.log("Success connect to DB - TargetShardID : " + connection._clusterId);
        
        var query = connection.format('call AccountDB.sp_account_s(?)', [accountUUID]);
        return mySQLPoolCluster.queryAsync(connection, query);
    })
    .then(function (values) {
        console.log("Success query sp_account_s to AccountDB");
        
        var connection = values[0];
        
        if (values[1][0].length <= 0) {
            return;
        }
    
        var query = connection.format('call AccountDB.sp_user_list_by_account_s(?)', [accountUUID]);
        return mySQLPoolCluster.queryAsync(connection, query);
    })
    .then(function (values) {
        console.log("Success query sp_user_list_by_account_s to AccountDB");
    
        var connection = values[0];
    
        if (values[1][0].length > 0) {
            userList = values[1][0];
        }
    })
    .catch(function (e) {
        console.log("Catched handler : " + e);
        err = e;
    })
    .finally(function () {
        if (outCallback)
            outCallback(err, userList);

        mySQLPoolCluster.releaseAll();
    });
}


var platFormType = 'IOS';
var platformID = 1;
var accountUUID = 1;
var userUUID = 1;
var regionID = 1;
var serverID = 1;


for (var i = 0; i < 3; ++i) {
    
    platformID += i;
    accountUUID += i;
    
    createAccountInfo(platFormType, platformID.toString(), accountUUID.toString(), regionID, serverID, 1, function (err, accUUID) {
        if (err) {
            console.log("Failed to create Account !!! - Error:" + err);
            return;
        }
 
        getAccountInfo(platFormType, platformID.toString(), 0, regionID, serverID, function (err, accUUID, usUUID, unregDate) {
            if (err) {
                console.log("Failed to get Account !!! - Error:" + err);
                return;
            }
            
            addUserByAccount(accUUID.toString(), userUUID++, regionID, serverID, function (err) {
                if (err) {
                    console.log("Failed to add User by Account !!! - Error:" + err);
                    return;
                }
                
                getAccountByOtherPlatform(accUUID.toString(), 'AOS', platformID.toString(), function (err, platformList, userList) {
                    if (err) {
                        console.log("Failed to get other platform by account !!! - Error:" + err);
                        return;
                    }
                    
                    addOtherPlatformByAccount(accUUID.toString(), 'AOS', platformID.toString(), function (err, result, platformList) {
                        if (err) {
                            console.log("Failed to add other platform by account !!! - Error:" + err);
                            return;
                        }
                        
                        console.log(platformList);
                        
                        getUserAllInfoFromGameDB(accUUID.toString(), function (err, userList) {
                            if (err) {
                                console.log("Failed to get user all info from GameDB !!! - Error:" + err);
                                return;
                            }
                            
                            console.log(userList);
                        });
                    });
                });
            });
        });
    });
}
