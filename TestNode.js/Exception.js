//
// Exception
//


/*
// uncaughtException
process.on('uncaughtException', function (err) {
    console.log('Caught exception: ' + err.stack);
});

setTimeout( function () {
    console.log('자.. 프로세스는 죽지 않았습니다.');
    setTimeout( function () {
        console.log('난 아직도 죽지 않았습니다.');
    }, 5000); // 5초 뒤에 또 실행
}, 5000); // 5초뒤에 실행

// 강제적으로 프로세스 에러 발생시킴
// 존재하지 않는 함수 실행

nonExistentFunc(); // or tow new Error('나 에러!!');
// 에러지점 이하의 코드는 실행되지 않습니다.
console.log('이 부분은 console에 보여지지 않습니다.');
*/


/*
// try ... catch
process.on('uncaughtException', function (err) {
    console.log('Caught exception: ' + err.stack);
});

setTimeout(function () {
    console.log('This will still run.');
    setTimeout(function () {
        console.log('This will still run~~');
    }, 3000);
}, 3000);

// 강제에러 -> try 로 해소함.
try {
    nonExistentFunc();
}
catch (e) {
 // tow 할경우에는 uncaugntException을 설정해야만
 // 등록된 callback이 모두 실행될때까지 프로세스가 죽지 않습니다.
 // 즉, try ~ catch 문은 uncaughtException과 짝을 이루어 같이 사용하셔야 합니다.
 // tow new Error(e); 
    throw new Error(e);
}

setTimeout(function () {
    console.log('2 second');
}, 2000);
*/


///