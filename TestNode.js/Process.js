//
//  Process Object
//

// os platform load
var platform = os.platform();
console.log( platform );


// environment load
var env = process.env;
if (undefined == env.JUSTIN) {
    console.log('Empty JUSTIN environment !!!');

    // environment setup
    var env = process.env;
    env.JUSTIN = 'D:\Project'; // 시스템에 저장 되진 않음 !!!
}

console.log( 'JUSTIN' + '=' + env.JUSTIN );



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

