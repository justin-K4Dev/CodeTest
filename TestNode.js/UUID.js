'use strict';

var Promise = require('bluebird');
var uuid = require('node-uuid');
var mySQLPoolCluster = require('./BlueBird/MySQL.js');

var s1Config = {
    host : '192.168.1.131',
    user : 'root',
    password : 'kang14',
    connectionLimit : 10
};

mySQLPoolCluster.add('0', s1Config);


// profiling varchar(36) based UUID  
function profileVarcharUUID() {
    
    var startTime, endTime;

    mySQLPoolCluster.getSQLConnection('0')
    .then(function (connection) {
        console.log("Success connect to DB - TargetShardID : " + connection._clusterId);
        
        mySQLPoolCluster.beginTransaction(connection);
        return connection;
    })
    .then(function (connection) {
        console.log("Start Transaction - TargetShardID : " + connection._clusterId);
        
        var objectUUID;
        startTime = +new Date;
        
        for (var i = 0; i < 10000; ++i) {
            var UUID = uuid.v4();
            var name = 'kang' + Math.floor(Math.random() * 100);
            
            var query = connection.format('insert into test.tbl_uuid_varchar set uuid=?, name=?', [UUID, name]);
            mySQLPoolCluster.queryAsync(connection, query)
            .catch(function (e) {
            })
            .finally(function () {
                if (i === 50000) {
                    objectUUID = UUID;
                }
                return [connection, objectUUID];
            });
        }
    })
    .then(function (values) {
        console.log("Success insert query to DB !!!");
        
        var connection = values[0];
        var objectUUID = values[1];
        
        var query = connection.format('select * test.tbl_uuid_varchar where uuid=?', [objectUUID]);
        return mySQLPoolCluster.queryAsync(connection, query);
    })
    .then(function (values) {
        console.log("Success select query to DB !!!");
        
        endTime = +new Date();
                
        return mySQLPoolCluster.commitAll();
    })
    .catch(function (e) {
        console.log("Catched handler : " + e);
        if (e) {
            mySQLPoolCluster.rollbackAll();
        }
    })
    .finally(function () {
        console.log('Elapsed Time : ' + endTime - startTime + ' ms');
        return mySQLPoolCluster.releaseAll();
    });
}


