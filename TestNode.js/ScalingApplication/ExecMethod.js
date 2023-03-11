
//
//  ExecMethod
//

const fs = require('fs');
const child_process = require('child_process');

// exec support.js
for (var i = 0; i < 3; i++) {
    var workerProcess = child_process.exec('node ./ScalingApplication/Support.js ' + i,
      function (error, stdout, stderr) {
        if (error) {
            console.log(error.stack);
            console.log('Error code: ' + error.code);
            console.log('Signal received: ' + error.signal);
        }
        console.log('stdout: ' + stdout);
        console.log('stderr: ' + stderr);
    });
    
    workerProcess.on('exit', function (code) {
        console.log('Child process exited with exit code ' + code);
    });
}


// exec command
var util = require('util')
var child_process = require('child_process').exec;

// exec shell command
var cmd = 'dir';
child_process(cmd, function (error, stdout, stderr) {
    console.log('stdout: ' + stdout);
    console.log('stderr: ' + stderr);
    if (error !== null) {
        console.log('exec error: ' + error);
    }
});


// send to options
var child_process = require('child_process').exec;
var cmd = 'dir';
var options = {
    timeout : '10000'
};
child_process(cmd, options, function (error, stdout, stderr) {
    console.log('stdout: ' + stdout);
    console.log('stderr: ' + stderr);
    if (error !== null) {
        console.log('exec error: ' + error);
    }
});


// send to environment
var env = process.env, varName, envCopy = {};
var child_process = require('child_process').exec;

for (varName in env) {
    envCopy[varName] = env[varName];
}

envCopy['CUSTOM_ENV_VAR'] = 'some value';
envCopy['CUSTOM_ENV_VAR_2'] = 'some other value';

child_process('dir', { env : envCopy }, function (error, stdout, stderr) {
    console.log('stdout: ' + stdout);
    console.log('stderr: ' + stderr);
    if (error !== null) {
        console.log('exec error: ' + error);
    }
});


// send to child.js
var child_process = require('child_process').exec;
child_process('node ./ScalingApplication/child.js', { env : { number : 1 } }, function (error, stdout, stderr) {
    console.log('stdout: ' + stdout);
    console.log('stderr: ' + stderr);
    if (error !== null) {
        console.log('exec error: ' + error);
    }
});
