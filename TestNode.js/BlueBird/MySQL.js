//
// BlueBird with MySQL
//

'use strict';
var CRC32 = require('crc-32');
var Promise = require('bluebird');
var mySQL = require('mysql');

/*
// BlueBird API Doc 에 있는 예제 코드 인데
// getConnectionAsync() 함수가 undefined 로 TypeError 오류 발생 !!!
// getConnection() 함수로 수정해서 하면 disposer() 함수가 undefined 로 TypeError 오류 발생 !!!
// 오류 원인 추후 확인 필요 !!!
var pool = mySQL.createPool(m1Config);

function getSqlConnection() {
    return pool.getConnectionAsync().disposer(function (connection) {
        try {
            connection.release();
        } catch (e) { };
    });
}
*/

var poolCluster = mySQL.createPoolCluster();

module.exports = poolCluster;

poolCluster.connectionList = [];
poolCluster.transactedConnectionList = [];

poolCluster.makeShardID = function (key, count) {

    var shardID = CRC32.str(key) % count;
    return shardID;
}

poolCluster.getNodeCount = function () {
    return Object.keys(poolCluster._nodes).length;
}

poolCluster.getSQLConnection = function( shardID ) {
    
    return new Promise(function (resolve, reject) {
        
        poolCluster.getConnection(shardID, function (err, connection) {
            if (err) {
                return reject(err);
            }
            else {
                poolCluster.connectionList.push(connection);
                return resolve(connection);
            }
        });        
    });
}

poolCluster.queryAsync = function ( connection, statement ) {
    
    return new Promise(function (resolve, reject) {
        
        connection.query(statement, function ( err, rows, fields ) {
            if (err) {
                return reject(err);
            }
            else {
                var values = [connection, rows, fields];
                return resolve(values);
            }
        });
    });
}

poolCluster.beginTransaction = function(connection) {
    
    return new Promise(function (resolve, reject) {
        
        connection.beginTransaction(function(err) {
            if (err) {
                return reject(err);
            }
            else {
                poolCluster.transactedConnectionList.push(connection);
                return resolve(connection);
            }
        });
    });
}

poolCluster.rollback = function (connection) {
        
    return new Promise(function (resolve, reject) {
        
        connection.rollback(function (err) {
            if (err) {
                return reject(err);
            }
            else {
                
                for (var i = 0; i < poolCluster.transactedConnectionList.length; ++i) {
                    var conn = poolCluster.transactedConnectionList[i];
                    if (conn === connection) {
                        poolCluster.transactedConnectionList[i] = null;
                        break;
                    }
                }

                return resolve(connection);
            }
        });
    });
}

poolCluster.rollbackAll = function () {
    
    return new Promise(function (resolve, reject) {
        
        for (var i = 0; i < poolCluster.transactedConnectionList.length; ++i) {
            var connection = poolCluster.transactedConnectionList[i];
            if (null !== connection) {
                connection.rollback(function (err) {
                });
            }
        }
        
        poolCluster.transactedConnectionList = [];
        return resolve();
    });
}

poolCluster.commit = function (connection) {
        
    return new Promise(function (resolve, reject) {
        
        connection.commit(function (err) {
            if (err) {
                return reject(err);
            }
            else {
                for (var i = 0; i < poolCluster.transactedConnectionList.length; ++i) {
                    var conn = poolCluster.transactedConnectionList[i];
                    if (conn === connection) {
                        poolCluster.transactedConnectionList[i] = null;
                        break;
                    }
                }
                return resolve(connection);
            }
        });
    });
}

poolCluster.commitAll = function () {
    
    return new Promise(function (resolve, reject) {
        
        for (var i = 0; i < poolCluster.transactedConnectionList.length; ++i) {
            var connection = poolCluster.transactedConnectionList[i];
            if (null !== connection) {
                connection.commit(function (err) {
                });
            }
        }
        
        poolCluster.transactedConnectionList = [];
        return resolve();
    });
}

poolCluster.releaseAll = function () {
    
    return new Promise(function (resolve, reject) {
        
        for (var i = 0; i < poolCluster.connectionList.length; ++i) {
            var connection = poolCluster.connectionList[i];
            connection.release();
        }
        
        poolCluster.connectionList = [];
        return resolve();
    });
}