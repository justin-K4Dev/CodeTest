
//
// Promise of BlueBird
//

'use strict';
var Promise = require('bluebird');

// Bluebird configuration !!!
Promise.config({
    // Enable warnings
    warnings: true,
    // Enable long stack traces
    longStackTraces: true,
    // Enable cancellation
    cancellation: true,
    // Enable monitoring
    monitoring: true
});


/*
// Example 1
// Catch handler by reject !!!
function getPromise1() {
    return new Promise(function (resolve, reject) {
        reject(new Error("Rejected error"))
    })
    .then(function (result) {
        console.log('Result 1 ' + result);
        return result;
    })
    .then(function (result) {
        console.log('Result 2 ' + result)
        return result;
    });
}

getPromise1()
.then(function (finalResult) {
    console.log("Final result " + finalResult)
})
.error(function (e) {
    console.log("Error handler " + e)
})
.catch(function (e) {
    console.log("Catch handler " + e)
});
// Output:
// Catch handler Rejected error
*/

/*
// Example 2
// Catch handler by throw Error !!!
function getPromise2() {
    return new Promise(function (resolve, reject) {
        throw new Error("Throw error")
    })
    .then(function (result) {
        console.log('Result 1 ' + result);
        return result;
    })
    .then(function (result) {
        console.log('Result 2 ' + result)
        return result;
    });
}

getPromise2().then(function (finalResult) {
    console.log("Final result " + finalResult)
})
.error(function (e) {
    console.log("Error handler " + e)
})
.catch(function (e) {
    console.log("Catch handler " + e)
});
// Output:
// Catch handler Throw error
*/

/*
// Example 3
// If you throw error instead of reject here outside the promise
// It will not be caught correctly unless you do a tradtional try/catch around the getPromise3() call
function getPromise3(someparameter) {
    if (!someparameter)
        throw new Error("Bad parameter")
    
    return new Promise(function (resolve, reject) {
        return 'ok';
    })
}

try { // this is ugly, we want to avoid this!
    getPromise3()
    .then(function (finalResult) {
        console.log("Final result " + finalResult)
    })
    .error(function (e) {
        console.log("Error handler " + e)
    })
    .catch(function (e) {
        console.log("Catch handler " + e)
    });
}
catch (exception) {
    console.log("ZOMG CRASH!")
}
// Output:
// ZOMG CRASH!
*/

/*
// Example 4
// Promise.reject will allow the error handler to work correctly
function getPromise4(someparameter) {
    if (!someparameter)
        return Promise.reject(new Error("Bad parameter"))
    
    return new Promise(function (resolve, reject) {
        resolve('ok');
    })
}

getPromise4()
.then(function (finalResult) {
    console.log("Final result " + finalResult)
})
.error(function (e) {
    console.log("Error handler " + e)
})
.catch(function (e) {
    console.log("Catch handler " + e)
});
// Output:
// Catch handler Bad parameter
*/


/*
// Example 5
// All toggether now
function getPromise(param) {
    if (!param) {
        return Promise.reject(Error('bad param'))
    }
    
    return new Promise(function (resolve, reject) {
        return resolve('foo');
    })
    .then(function (result) {
        console.log('Result 1 ' + result);
        // We don't need to call Promise.resolve here, the value is already resolved
        // We can just return it
        return result;
    })
    .then(function (result) {
        // We can also continue chaining thens as long as we either
        // 1 - return a value
        // 2 - return a promise
        console.log('Result 2 ' + result)
        // returning a value
        return result
    })
    .then(function (result) {
        console.log('Result 3 ' + result)
        // returning another promise
        return Promise.resolve(someOtherPromise)
    })
    .then(function (result) {
        console.log('Result 4 ' + result)
        return result + ' resolved'
    });
}

getPromise('something')
.then(function (finalResult) {
    console.log("Final result " + finalResult)
})
.error(function (e) {
    console.log("Error handler " + e)
})
.catch(function (e) {
    console.log("Catch handler " + e)
});

// Define another promise here
var someOtherPromise = new Promise(function (resolve, reject) {
    resolve('some other promise!');
});
*/


/*
// Example 6
var value = 0;
function doUpdate(callback) {
    value++;
    callback(0, value);
}

function doActionAsync() {
    return new Promise(function (resolve, reject) {
        doUpdate(function (err, result) {
            if (err) {
                return reject(err);
            }
            resolve(result);
        });
    });
}

doActionAsync()
.then(function (value) {
    console.log("Step 1, Received Value : " + value)
})
.then(function (value) {
    console.log("Step 2, Received Value : " + value)
})
.catch(function (e) {
    console.log("Catch handler " + e)
});
// Output:
// Step 1, Received Value : 1
// Step 2, Received Value : 2
*/


/*
// Example 7
function doSomethingAsync(something) {
    return Promise.try(function () {
        if (!something) {
            throw new Error('Something is not valid');
        }
        return something;
    });
}

doSomethingAsync(1)
.then(function (value) {
    console.log("Step 1, Received Value : " + value)
    return ++value;
})
.then(function (value) {
    console.log("Step 2, Received Value : " + value)
    return value;
})
.catch(function (e) {
    console.log("Catch handler " + e)
});
// Output:
// Step 1, Received Value : 1
// Step 2, Received Value : 2
*/


/*
// 특정 값으로 Chain 을 이어갈 경우
somethingAsync().return(value);
somethingAsync().then( function() {
    return value;
});

// 특정 에러로 Chain 을 이어갈 경우
somethingAsync().throw(value);
somethingAsync().then( function() {
    throw value;
});
*/
 

/*
// .finally() function !!!
Promise.resolve('test')
.catch(console.error.bind(console))
.finally(function () {
    return 'finally';//이 값은 전달 되지 않으며 마지막에 사용할 경우에만 전달됨 !!!
})
.then(function (result) {
    console.log(result);
}).done(); // 명시적 종료 선언
*/


/*
// promise 반환 처리 !!!
var promise = somethingAsync();
if (checkCondition()) {
    promise = promise.then(function (result) {
        return anotherAsync(result);
    });
}
promise.then(function (result) {
    doSomethingWithResult(result);
});
*/


/*
// .all() function !!!
Promise
.all([
    pingAsync('ns1.example.com'),
    pingAsync('ns2.example.com'),
    pingAsync('ns3.example.com'),
    pingAsync('ns4.example.com')
])
.spread(function (first, second, third, fourth) {
    console.log(first, second, third, fourth);
});
*/


/*
// .any() function !!!
Promise
.any([
    pingAsync('ns1.example.com'),
    pingAsync('ns2.example.com'),
    pingAsync('ns3.example.com'),
    pingAsync('ns4.example.com')
])
.spread(function (first) {
    console.log(first);
});
*/


/*
// .some() function !!!
Promise
.some([
    pingAsync('ns1.example.com'),
    pingAsync('ns2.example.com'),
    pingAsync('ns3.example.com'),
    pingAsync('ns4.example.com')
], 2)
.spread(function (first, second) {
    console.log(first, second);
});
*/


/*
// .map() function !!!
Group.listAsync({ user: user.id })
.map( function(group) {
    return group.removeAsync(user.id);
})
.then( function() {
    return user.removeAsync();
});
*/


/*
// .map() function !!!
Group.listAsync({ user: user.id })
.filter( function(group) {
    return group.owner_id === user.id;
})
*/


/*
// .map() or filter() + concurrency 제한 설정
Group.listAsync({ user: user.id })
.filter( function(group) {
    return group.owner_id === user.id;
})
.map( function(group) {
    return group.removeAsync(user.id);
}, { concurrency: 1 });
*/


/*
// 하나씩 개별 처리 !!!
Group.listAsync({ user: user.id })
.reduce( function(promise, group) {
    return promise.then( function(groups) {
        return group.removeAsync(user.id)
               .then(function(group) {
                   groups.push(group);
               })
               .return(groups);
    });
},[]);
*/


/*
// .delay() function !!!
Promise
.delay(500)
.then(function () {
    return 'Hello world';
})
.delay(500)
.then(function (result) {
    console.log(result);
});
*/


/*
// .tap() function !!! - Promise Chain 연결을 하지만 결과값은 넘겨주지 않음 !!!
somethingAsync()
.tap(function (result_of_somethingAsync) {
    return anotherAsync(result_of_somethingAsync);
})
.then(function (result_of_somethingAsync) {
    console.log(result_of_somethingAsync);
});
*/


/*
// .bind() function !!! - 함수 Chain 내의 this 를 연결 !!!
somethingAsync()
.bind({})
.spread( function ( a, b ) {
    this.a = a;
    this.b = b;
    return anotherAsync( a, b );
})
.then( function(c) {
    return this.a + this.b + c;
})
*/


/*
// 10 초마다 실행 !!! 
var loop = function () {
    Worker.executeAsync()
    .catch(function () {
        console.error('error:', err);
    })
    .delay(10000)
    .then(loop);
};

loop();
*/


/*
// 긴 작업 목록을 10 개씩 나누어 실행
var traverseJobs = function (handleTenJobsAsync) {
    
    var limit = 10;    
    var loop = function (skip) {
        return listJobsAsync(limit, skip)
            .then(function (jobs) {
            if (jobs.lenght) {
                return handleTenJobsAsync(jobs)
                .then(function () {
                    return loop(skip + limit);
                });
            }
        });
    };

    return loop(0);
};

traverseJobs();
*/


/*
//
// connection pool & clustering for mySQL 
//
var mySQLPoolCluster = require('./MySQL.js');
var uuid = require('node-uuid');

var m1Config = {
    host : '192.168.1.131',
    user : 'root',
    password : 'kang14',
    connectionLimit : 10
};

mySQLPoolCluster.add('0', m1Config);

var shardKey = 1000000000;
var shardID = mySQLPoolCluster.makeShardID(shardKey.toString(), mySQLPoolCluster.getNodeCount());

mySQLPoolCluster.getSQLConnection(shardID)
.then(function (connection) {
    console.log("Success connect to DB - TargetShardID : " + connection._clusterId);
        
    mySQLPoolCluster.beginTransaction(connection);
    return connection;
})
.then(function (connection) {
    console.log("Start Transaction - TargetShardID : " + connection._clusterId);
    
    var objectUUID = uuid.v1();
    var name = 'kang' + Math.floor(Math.random() * 100);
    var point = Math.floor(Math.random() * 1000);
    
    var query = connection.format('insert into test.tbl_object set object_uuid=?, name=?, point=?', [objectUUID, name, point]);
    return mySQLPoolCluster.queryAsync(connection, query);
})
.then(function (values) {
    console.log("Success query 1 to DB !!!");
    
    var connection = values[0];

    var objectUUID = uuid.v1();
    var name = 'kang' + Math.floor(Math.random() * 100);
    var point = Math.floor(Math.random() * 1000);
    
    var query = connection.format('call test.usp_object_i(?, ?, ?)', [objectUUID, name, point]);
    return mySQLPoolCluster.queryAsync(connection, query);
})
.then(function (values) {
    console.log("Success call USP to DB !!!");

    return mySQLPoolCluster.commitAll();
})
.catch(function (e) {
    console.log("Catched handler : " + e);
    if (e) {
        mySQLPoolCluster.rollbackAll();
    }
})
.finally(function () {
    return mySQLPoolCluster.releaseAll();
});
*/


/*
//
// promise all & mySQL
//
var mySQLPoolCluster = require('./MySQL.js');
var config = {
    host : '192.168.1.131',
    user : 'root',
    password : 'kang14',
    connectionLimit : 10
};

mySQLPoolCluster.add('0', config);

function queryObjectInfo(shardID, statement, args) {
    
    return new Promise(function (resolve, reject) {
        
        mySQLPoolCluster.getSQLConnection(shardID)
        .tap(function (connection) { // tap 을 해도 값이 then 으로 넘어옴... 왜그럴까... !!!
            console.log("Success connect to DB - TargetShardID : " + connection._clusterId);
         
            var query = connection.format(statement, args);
            mySQLPoolCluster.queryAsync(connection, query)
            .then(function (values) {
                resolve(values);
            })
            .catch(function (e) {
                console.log('Catched Error handler: ' + e);
                resolve(null);
            });
        });
    });
}

Promise.all([
    queryObjectInfo('0', 'insert into test.tbl_object set object_uuid=?, name=?, point=?', [7000, '하하하', 1000]),
    queryObjectInfo('0', 'select * from test.tbl_object', []),
    queryObjectInfo('0', 'select * from test.tbl_object where object_uuid = ?', [4000]),
])
.catch(function (e) {
    console.log('Catched Error handler: ' + e);
})
.then(function (values) {
    console.log(values);
})
.finally(function () {
    mySQLPoolCluster.releaseAll();
});
*/