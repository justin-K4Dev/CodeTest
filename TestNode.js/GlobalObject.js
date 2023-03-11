
//
//  __filename, __dirname
//

// Let's try to print the value of __filename
console.log(__filename);

// Let's try to print the value of __dirname
console.log(__dirname);



//
//  Timer
//

function printHello() {
    console.log("Hello, World!");
}
// Now call above function after 2 seconds
var t = setTimeout(printHello, 2000);

// Now clear the timer
clearTimeout(t);


function printNodeJS() {
    console.log("Hello, Node.js!");
}
// Now call above function after 2 seconds
setInterval(printNodeJS, 2000);



//
//  Console Object
//
console.info("Program Started");

var counter = 10;
console.log("Counter: %d", counter);

console.time("Getting data");
//
// Do some processing here...
// 
console.timeEnd('Getting data');

console.info("Program Ended")



//
//  Process Object
//

//
process.on('exit', function (code) {
    
    // Following code will never execute.
    setTimeout(function () {
        console.log("This will not run");
    }, 0);
    
    console.log('About to exit with code:', code);
});
console.log("Program Ended");

// Printing to console
process.stdout.write("Hello World!" + "\n");

// Reading passed parameter
process.argv.forEach(function (val, index, array) {
    console.log(index + ': ' + val);
});

// Getting executable path
console.log(process.execPath);

// Platform Information 
console.log(process.platform);

// Print the current directory
console.log('Current directory: ' + process.cwd());

// Print the process version
console.log('Current version: ' + process.version);

// Print the memory usage
console.log(process.memoryUsage());


//
// Global object
//
global.myData = null; // 사용자 전역 변수 생성 !!!

