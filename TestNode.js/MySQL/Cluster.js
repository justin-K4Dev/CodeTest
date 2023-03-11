//
// Cluster
//

var mysql = require('mysql');

var config = {
    host : '192.168.1.131',
    user : 'root',
    password : 'kang14',
    connectionLimit : 10
};

var masterConfig = {
    host : '192.168.1.131',
    user : 'root',
    password : 'kang14',
    connectionLimit : 10
};

var slave1Config = {
    host : '192.168.1.132',
    user : 'root',
    password : 'kang14',
    connectionLimit : 10
};

var slave2Config = {
    host : '192.168.1.133',
    user : 'root',
    password : 'kang14',
    connectionLimit : 10
};

/*
// create
var poolCluster = mysql.createPoolCluster();

// add configurations
poolCluster.add(config); // anonymous group
poolCluster.add('MASTER', masterConfig);
poolCluster.add('SLAVE1', slave1Config);
poolCluster.add('SLAVE2', slave2Config);

// remove configurations
poolCluster.remove('SLAVE*'); // By target group : SLAVE1-2

// Target Group : ALL(anonymous, MASTER, SLAVE1-2), Selector : round-robin(default)
poolCluster.getConnection(function (err, connection) { });

// Target Group : MASTER, Selector : round-robin
poolCluster.getConnection('MASTER', function (err, connection) { });

// Target Group : SLAVE1-2, Selector : order
// If can't connect to SLAVE1, return SLAVE2. (remove SLAVE1 in the cluster)
poolCluster.on('remove', function (nodeId) {
    console.log('REMOVED NODE : ' + nodeId); // nodeId = SLAVE1 
});

poolCluster.getConnection('SLAVE*', 'ORDER', function (err, connection) { });

// of namespace : of(pattern, selector)
poolCluster.of('*').getConnection(function (err, connection) { });

var pool = poolCluster.of('SLAVE*', 'RANDOM');
pool.getConnection(function (err, connection) { });
pool.getConnection(function (err, connection) { });

// close all connections
poolCluster.end(function (err) {
  // all connections in the pool cluster have ended
});
*/

//
// PoolCluster Option
//

var clusterConfig = {
    removeNodeErrorCount: 1, // Remove the node immediately when connection fails.
    defaultSelector: 'ORDER'
};

var poolCluster = mysql.createPoolCluster(clusterConfig);



//
// Shard Clustering
//

var m1Config = {
    host : '192.168.1.131',
    user : 'root',
    password : 'kang14',
    connectionLimit : 10
};

var m1s1Config = {
    host : '192.168.1.132',
    user : 'root',
    password : 'kang14',
    connectionLimit : 10
};

var m2Config = {
    host : '192.168.1.131',
    user : 'root',
    password : 'kang14',
    connectionLimit : 10
};

var m2s1Config = {
    host : '192.168.1.132',
    user : 'root',
    password : 'kang14',
    connectionLimit : 10
};

// create
var poolCluster = mysql.createPoolCluster();

// add configurations
poolCluster.add('M1', m1Config);
poolCluster.add('M1-S1', m1s1Config);
poolCluster.add('M2', m2Config);
poolCluster.add('M2-S1', m2s1Config);

// first DB proc
 new Promise(function (resolve, reject) {
        
    poolCluster.getConnection('M1', function (err, connection) {
            
        if (err) {
            reject("Failed connect to DB !!!");
        }
            
        console.log('ConnectionID: ', connection._clusterId);
            
        // And done with the connection.
        connection.release();
            
        resolve('Completed DB 1 !!!');
    });
})
.then(function (text) {
    // 성공시
    console.log(text);
}, function (error) {
    // 실패시 
    console.error(error);
});

// second DB Proc
new Promise(function (resolve, reject) {
        
    pool.getConnection('M1-S*', function (err, connection) {
 
        if (err) {
            reject("Failed connect to DB !!!");
        }
            
        pool.query('SELECT 1 + 1 as solution', function (err, rows, fields) {
            if (err) throw err;
            
            console.log('The solution is: ', rows[0].solution);
        });
            
        // And done with the connection.
        connection.release();

        resolve('Completed DB 2 !!!');
    });
})
.then(function (text) {
    // 성공시
    console.log(text);
    
}, function (error) {
    // 실패시 
    console.error(error);
});

