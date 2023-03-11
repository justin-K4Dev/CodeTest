//
// Promise
//

'use strict';

/*
// Example 1
// Promise 를 처리하는 함수 선언
var _promise1 = function (param) {
    
    return new Promise(function (resolve, reject) {
        
        // 비동기를 표현하기 위해 setTimeout 함수를 사용 
        setTimeout(function () {
 
            // 파라메터가 참이면, 
            if (param) {
                
                // 해결됨 
                resolve("Success");
            }

			// 파라메터가 거짓이면, 
            else {
                
                // 실패 
                reject(Error("Failed !!!"));
            }
        }, 3000);
    });
};

// Using the then method
_promise1(true)
.then(function (text) {
    // 성공시
    console.log(text);
    return 'Final logic~';
}, function (e) { // <- 비권장 !!!
    // 실패시 
    console.error(e);
});
// Output:
// Success

// Chaining
// Because the then method returns a Promise, you can easily chain then calls.
// catched in Chaining !!!
_promise1(true)
.then(JSON.parse)
.catch(function () {
    var errMsg = 'Catched Error !!!';
    console.log(errMsg);
    return 'Final logic~';
})
.then(function (text) {
    console.log(text);
});
// Output:
// Catched Error !!! - JSON.parse error
// Final logic~
*/


/*
// Example 2
// Promise in Function
function getPromise() {
    return new Promise(function (resolve, reject) {
        reject(new Error("Rejected error"))
    })
    .then(function (result) {
        console.log('Result 1 ' + result);
        return result;
    });
}

getPromise()
.then(function (finalResult) {
    console.log("Final result " + finalResult)
})
.catch(function (e) {
    console.log("Catched " + e)
});
// Output:
// Catched handler Rejected error
*/


/*
// You can also use chaining to implement one function with a Promise-based API on top of another such function.
function fetch_current_data() {
    // The fetch() API returns a Promise.  This function
    // exposes a similar API, except the fulfillment
    // value of this function's Promise has had more
    // work done on it.
    return fetch("current-data.json").then((response) => {
        if (response.headers.get("content-type") != "application/json") {
            throw new TypeError();
        }
        var j = response.json();
        // maybe do something with j
        return j; // fulfillment value given to user of
              // fetch_current_data().then()
    });
}
*/


/*
//
// 여러개의 비동기 작업들이 존재하고 이들이 모두 완료 되었을때
// 작업을 진행하고 싶다면 Promise.all API 를 활용 !!!
//
var promise2 = new Promise(function (resolve, reject) {
    
    // 비동기를 표현하기 위해 setTimeout 함수를 사용 
    setTimeout(function () {
        
        // 해결됨 
        console.log("첫번째 Promise 완료");
        resolve("11111");

    }, Math.random() * 20000 + 1000);
});

var promise3 = new Promise(function (resolve, reject) {
    
    // 비동기를 표현하기 위해 setTimeout 함수를 사용 
    setTimeout(function () {
        
        // 해결됨 
        console.log("두번째 Promise 완료");
        resolve("222222");

    }, Math.random() * 10000 + 1000);
});


Promise.all([promise2, promise3]).then(function (values) {
    console.log("모두 완료됨", values);
});
*/


//
//  Promise 객체를 바로 생성할 경우
//
/*
var _promise4 = new Promise(function (resolve, reject) {
    
    // 여기에서는 무엇인가 수행 
    
    // 50프로 확률로 resolve 
    if (+new Date() % 2 === 0) {
        resolve("Stuff worked!");
    }
    else {
        reject(Error("It broke"));
    }
});

_promise4.then(function (text) {
    // 성공시
    console.log(text);
}, function (error) {
    // 실패시 
    console.error(error);
});
*/


/*
new Promise(function (resolve, reject) {
    
    // 50프로 확률로 resolve 
    if (+new Date() % 2 === 0) {
        resolve("Stuff worked!");
    }
    else {
        reject(Error("It broke"));
    }

}).then(function (text) {
    // 성공시
    console.log(text);
}, function (error) {
    // 실패시 
    console.error(error);
});
*/


/*
var promise5 = function () {
    
    return new Promise(function (resolve, reject) {
        
        // 비동기를 표현하기 위해 setTimeout 함수를 사용 
        setTimeout(function () {
            
            // 해결됨 
            console.log("첫번째 Promise 완료");
            resolve("11111");

        }, Math.random() * 20000 + 1000);
    });
};

var promise6 = function () {
    
    return new Promise(function (resolve, reject) {
        
        // 비동기를 표현하기 위해 setTimeout 함수를 사용 
        setTimeout(function () {
            
            // 해결됨 
            console.log("두번째 Promise 완료");
            resolve("2222");

        }, Math.random() * 10000 + 1000);
    });
};

// promise5, promise6 는 함수 이므로 함수 형태로 넘겨야 함 !!!
Promise.all([promise5(), promise6()]).then(function (values) {
    console.log("모두 완료됨", values);
});
*/


/*
// 즉시 Promise 생성 사용 가능
function startWithValue(value) {
    return Promise.resolve(value);
} 
// error 처리시 Promise 생성 사용 가능
function startWithError(error) {
    return Promise.reject(error);
}
*/


//
// Promise Anti-patterns
//

/*
// Nested Promises
//
// You get a whole bundle of promises nested in eachother:
loadSomething().then(function(something) {
    loadAnotherthing().then(function(another) {
                    DoSomethingOnThem(something, another);
    });
});
//
// To fix :
Promise
.all([loadSomething(), loadAnotherThing()])
.spread(function(something, another) {
    DoSomethingOnThem(something, another);
});
// Much simpler.
// The promise returned by q.all will resolve with an array of the results that is passed to then().
// The spread() method will split this array up amongst the parameters.
*/


/*
// The Broken Chain
//
// You have code like :
function anAsyncCall() {
    var promise = doSomethingAsync();
    promise.then(function () {
        somethingComplicated();
    });
    
    return promise;
}
//
// To fix :
Promise
function anAsyncCall() {
    var promise = doSomethingAsync();
    return promise.then(function() {
        somethingComplicated()
    });   
}
// Always return the result of the final then().
*/


/*
// The Collection Kerfuffle
//
// You have an array of items and you want to do something asynchronous on each of them.
// So you find yourself doing something involving recursion.
function workMyCollection(arr) {
    var resultArr = [];
    function _recursive(idx) {
        if (idx >= resultArr.length)
            return resultArr;
        
        return doSomethingAsync(arr[idx]).then(function (res) {
            resultArr.push(res);
            return _recursive(idx + 1);
        });
    }
    
    return _recursive(0);
}
//
// To fix:
function workMyCollection(arr) {
    return q.all(arr.map(function (item) {
        return doSomethingAsync(item);
    }));
}
// Unlike the recursive non-solution, this will kick off all the async calls in parallel.
// Obviously much more time efficient.
//
// If you need to run your promises in series, you can use reduce.
function workMyCollection(arr) {
    return arr.reduce(function (promise, item) {
        return promise.then(function (result) {
            return doSomethingAsyncWithResult(item, result);
        });
    }, q());
}
// Not quite as tidy, but certainly tidier.
*/


/*
// The Ghost Promise
// 
// A certain method needs to do something asynchronous and sometimes it doesn't.
// So you create a promise even when you don't need one just to keep the two code paths consistent.
var promise;
if (asyncCallNeeded)
    promise = doSomethingAsync();
else
    promise = Q.resolve(42);

promise.then(function () {
    doSomethingCool();
});
// Not the worst anti-pattern here,
// but there is definitely a cleaner way - wrap the 'value or promise' with Q().
// Thismethod will take either a value or a promise and act accordingly.
Q(asyncCallNeeded ? doSomethingAsync() : 42)
    .then(function (value) {
        doSomethingGood();
    })
    .catch( 
    function (err) {
        handleTheError();
    }
);
// Note: I was originally advising using Q.when there.
// Thankfully Kris Kowal has put me straight in the comments below.
// Don't use Q.when, just use Q() - it is much cleaner.
*/


/*
// The Overly Keen Error Handler
//
// The then() method takes two parameters, the fulfilled handler and the rejected handler.
// You might be tempted to do something likethis:
somethingAsync.then(
    function () {
        return somethingElseAsync();
    },
    function (err) {
        handleMyError(err);
    }
);
// The problem with thisis that any errors occurring in the fulfilled handler
// does not get passed to the error handler.
//
// To fix, make sure the error handler is in a separate then :
somethingAsync
    .then(function () {
        return somethingElseAsync();
    })
    .then(null, function (err) {
        handleMyError(err);
    }
);
// Or use catch():
somethingAsync
    .then(function() {
        return somethingElseAsync();
    })
    .catch(function(err) {
        handleMyError(err);
    }
);
// This ensures any errors occuring in the chain will get handled.
*/


/*
// The Forgotten Promise
// 
// You call a method that returns a promise.
// However, you forget about this promise and create your own one.
var deferred = Q.defer();
doSomethingAsync().then(function (res) {
    res = manipulateMeInSomeWay(res);
    deferred.resolve(res);
}, function (err) {
    deferred.reject(err);
});

return deferred.promise;
// This really is defeating the point of promises - simplicity.
// A lot of pointless code here.
//
//To fix, just return the promise.
return doSomethingAsync()
.then(function (res) {
    return manipulateMeInSomeWay(res);
});
*/