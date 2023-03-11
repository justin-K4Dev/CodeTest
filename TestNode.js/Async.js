// 
//  WaterFall
//
//  Install npm async !!!

var async = require('async');
var mySQL = require('mysql');


// 실행될 1개이상의 함수를 포함하는 배열 혹은 오브젝트 형식으로 구성됩니다.
// 설정한 함수는 callback인자가 전달되며 이것을 실행시켜줘야 다음 task으로
// 넘어갈 수 있습니다.
//      callback [optional]
//
// 모든 함수의 실행이 끝나면 한번 실행이 되고,
// 각 함수의 callback에 넘긴 값들을 모두 받아볼 수 있습니다. 

/*
async.parallel([
  // 첫번째 실행
  // 다음 task으로 이동하기 위해서는 callback을 실행해야하고,
  // 사용방법은 callback(에러, 결과값[, 결과값#2...]) 형태로 사용됩니다.
  // -----------------------------------------------------
    function (callback) {
        setTimeout(function () {
            console.log('--- async.parallel::ste#1 ---');
            // 다음 task으로 이동하기 위해 callback 실행
            // one값 전달
            callback(null, 'one');
        }, 200);
    },
    function (callback) {
        setTimeout(function () {
            console.log('--- async.parallel::ste#2 ---');
            // 다음 task으로 이동하기 위해 callback 실행
            // two값 전달
            callback(null, 'two');
        }, 100);
    },
],
// 모든 task를 끝내고, 아래 callback으로 에러와 배열인자가 전달됩니다.
// ------------------------------------------------------
function (err, results) {
    console.log('--- async parallel result #1 ---');
    console.log(arguments);
});
*/

/*
async.parallel([
    function (callback) {
        // 사용자 정보
        doRequest1(query, callback);
    },
    function (callback) {
        // 사용자 주문정보
        doRequest2(query2, callback);
    },
    function (callback) {
        // 사용자 기타정보
        doRequest3(query3, callback);
    },
],
// 모든 자료를 한번에 모아서 받을 수 있습니다.
function (err, results) {
    if (err) {
        renderError(err);
    } else {
        renderHTML(results[0], results[1], results[2]);
    }
});
*/

// 실행될1개이상의 함수를 포함하는 배열형식으로 구성됩니다.
// 설정한 함수는 callback인자가 전달되며
// 이것을 실행시켜줘야 다음 task으로 넘어갈 수 있습니다.
//      callback [optional]
//
// 모든 함수의 실행이 끝나면 한번 실행이 되고,
// 각 함수의 callback에 넘긴 값들을 모두 받아볼 수 있습니다.

/*
async.waterfall([
    function (callback) {
        console.log('--- async.waterfall #1 ---');
        // 여기서도 series, parallel과 마찬가지로
        // callback의 실행은 다음 task 으로 넘기기 위한것입니다.
        //
        // parallel의 다른점은
        // callback의 결과가 다음 task으로 전달되는 점입니다.
        callback(null, 'one', 'two');
    },
  // 첫번째 task에서 전달된 one, two 값을 인자로 받게 됩니다.
    function (arg1, arg2, callback) {
        console.log('--- async.waterfall #2 ---');
        console.log(arguments);
        callback(null, 'three');
    },
    function (arg1, callback) {
        console.log('--- async.waterfall #3 ---');
        console.log(arguments);
        // 마지막 task의 callback에 전달한 인수값이
        // 마지막 callback에 전달됩니다.
        callback(null, 'done');
    }
],
// 마지막 함수에서 callback으로 전달한 인자가 넘어옵니다.
function (err, results) {
    console.log('--- async.waterfall result #1 ---');
    console.log(arguments);
});
*/


// 실행될1개이상의 함수를 포함하는 배열 혹은 오브젝트 형식으로 구성됩니다.
// 설정한 함수는 callback인자가 전달되며 이것을 실행시켜줘야 다음 task으로 넘어갈 수 있습니다.
//      callback [optional]
//
// 모든 함수의 실행이 끝나면 한번 실행이 되고,
// 각 함수의 callback에 넘긴 값들을 모두 받아볼 수 있습니다.

/*
async.series([
  // 첫번째 실행
  // async의 프로세스 흐름을 도와줄 수 있는 callback이 전달됩니다.
  // 이를 이용하여 흐름을 제어할 수 있는것입니다.
  // 즉, 다음 task으로 이동하기 위해서는 callback을 실행해야 합니다.
  // 사용방법은 callback(에러, 결과값) 형태로 사용됩니다.
  // -----------------------------------------------------
    function (callback) {
        console.log('--- async.series::ste#1 ---');
        // 다음 task으로 이동하기 위해 실행
        // 첫번째 인수로 에러
        // 두번째부터는 마지막 callback에 전달할 값들을 설정할 수 있습니다.
        // 예) callback(null, 'one' [, value ...]);
        // ---------------------------------------------------------
        callback(null, 'one');
    // 예) 첫번째 인수로 에러를 발생시킬 경우
    // 만약 이곳에서 첫번째 인수를 new Error('error message')를 전달하면
    // 선언된 tasks의 동작은 여기서 멈추고,
    // 마지막 callback으로 프로세스 진행이 넘어갑니다.
    // ----------------------------------------------------------
    // callback(new Error('error message'), null);
    },
  // 두번째 실행
  // -----------
    function (callback) {
        console.log('--- async.series::ste#2 ---');
        // 다음 task으로 이동하기 위해 실행
        // 에러는 null, 전달할 결과값은 'two'
        callback(null, 'two');
    }
],
// 모든 task를 끝내고, 아래 callback으로 에러와 배열인자가 전달됩니다.
// ------------------------------------------------------
function (err, results) {
    console.log('--- async.series result ---');
    console.log(arguments);
});
*/
/*
async.series({
    one: function (callback) {
        setTimeout(function () {
            console.log('--- async series::ste#1-1 ---');
            callback(null, 200);
        }, 200);
    },
    two: function (callback) {
        setTimeout(function () {
            console.log('--- async series::ste#1-2 ---');
            callback(null, 100);
        }, 100);
    }
},
function (err, results) {
    console.log('--- async series result ---');
    console.log(arguments);
});
*/


var uuid = require('node-uuid');

var s1Config = {
    host : '192.168.1.131',
    user : 'root',
    password : 'kang14',
    connectionLimit : 10
};

var s2Config = {
    host : '192.168.1.132',
    user : 'root',
    password : 'kang14',
    connectionLimit : 10
};

var s3Config = {
    host : '192.168.1.133',
    user : 'root',
    password : 'kang14',
    connectionLimit : 10
};

var poolCluster = mySQL.createPoolCluster();

// add configurations
poolCluster.add('0', s1Config);
poolCluster.add('1', s2Config);
poolCluster.add('2', s3Config);

var connectionList = new Array();
var tansactedConnectionList = new Array();

function doQuery(arg1, arg2, outCallback) {

    async.waterfall([
        // step 1
        function (callback) {
            console.log('--- async.waterfall #1 Start---');
            var aryArgs = Array.prototype.slice.call(arguments);
            console.log("arguments:", aryArgs);
            
            poolCluster.getConnection('0', function (err, connection) {
                if (err) {
                    // throw new Error("Failed connect to DB !!!"); <- can not catch !!!
                    callback(err, "Failed connect to DB !!!"); //<- go to finish callback function  
                }
                
                console.log('ConnectionID: ', connection._clusterId);
                
                // And done with the connection.
                connection.release();
                
                // 주의 !!! - 첫번째 매개변수가 null 아닌 경우 finish callback 함수를 호출 하게 됨 !!!
                // callback('1', '2', '3');
                callback(null, '1', '2');
            });
            
            console.log('--- async.waterfall #1 End ---');
        },
        // step 2
        function (arg1, arg2, callback) {
            console.log('--- async.waterfall #2 Start---');
            var aryArgs = Array.prototype.slice.call(arguments);
            console.log("arguments:", aryArgs);
            
            poolCluster.getConnection('0', function (err, connection) {
                if (err) {
                    callback(err, "Failed connect to DB !!!"); //<- go to finish callback function  
                }
                
                console.log('ConnectionID: ', connection._clusterId);
                
                connectionList.push(connection);
                
                connection.beginTransaction(function (err) {
                    if (err) {
                        callback(err, 'Failed transact to DB !!!'); //<- go to finish callback function  
                    }
                    
                    tansactedConnectionList.push(connection);
                    
                    var objectUUID = uuid.v1();
                    var name = 'kang' + Math.floor(Math.random() * 100);
                    var point = Math.floor(Math.random() * 1000);

                    var query = connection.format('insert into test.tbl_object set object_uuid=?, name=?, point=?', [objectUUID, name, point]);   
                    connection.query(query, function (err, rows, fields) {
                        if (err) {
                            callback(err, 'Failed query to DB !!!'); //<- go to finish callback function  
                        }
                        
                        console.log('The Query1 completion !!!');
                        
                        var objectUUID = uuid.v1();
                        var name = 'kang' + Math.floor(Math.random() * 100);
                        var point = Math.floor(Math.random() * 1000);
                        
                        var query = connection.format('call test.usp_object_is(?, ?, ?)', [objectUUID, name, point]);
                        connection.query(query, function (err, rows, fields) {
                            if (err) {
                                callback(err, "Failed query to DB !!!"); //<- go to finish callback function  
                            }
                            
                            console.log('The Query2 completion !!!');
                            
                            callback(null, '11', '12');
                        });
                    });                     
                });
            });
            
            console.log('--- async.waterfall #2 End---');
        },
        // step 3
        function (arg1, arg2, callback) {
            console.log('--- async.waterfall #3 Start---');
            var aryArgs = Array.prototype.slice.call(arguments);
            console.log("arguments:", aryArgs);            
                       
            poolCluster.getConnection('1', function (err, connection) {
                if (err) {
                    callback(err, "Failed connect to DB !!!"); //<- go to finish callback function
                }
                
                console.log('ConnectionID: ', connection._clusterId);
                
                connectionList.push(connection);
                
                connection.beginTransaction(function (err) {
                    if (err) {
                        callback(err, "Failed connect to DB !!!"); //<- go to finish callback function  
                    }
                    
                    tansactedConnectionList.push(connection);
                    
                    connection.query('SELECT 1 + 2 as Query3', function (err, rows, fields) {
                        if (err) {
                            callback(err, "Failed query to DB !!!"); //<- go to finish callback function
                        }
                        
                        console.log('The Query3 is: ', rows[0].Query3);
                        
                        callback(null, 'three');
                    });
                });
            });
            
            console.log('--- async.waterfall #3 End---');
        }
    ],
    // 마지막 함수에서 callback으로 전달한 인자가 넘어옵니다.
    function (err, results) {
        console.log('--- async.waterfall result ---');
                
        for (var idx in tansactedConnectionList) {
            var connection = tansactedConnectionList[idx];
            
            if (err) {
                connection.rollback(function (err) {
                    if (err) {
                        console.log(err, " Failed rollback to DB !!!");
                    }
                });
            }
            else {
                connection.commit(function (err) {
                    if (err) {
                        console.log(err, " Failed commit to DB !!!");
                    }
                });
            }
        }
        tansactedConnectionList = {};
        

        for (var idx in connectionList) {
            var connection = connectionList[idx];
            connection.release();
        }
        connectionList = {};

        outCallback(err, results);
    });
}

doQuery(100, 1000, function (err, result) {
    if (err) {
        console.log('Failed to query !!! - Err:' + err);
        return;
    }

    console.log('Success to query - Result:' + result);
});



