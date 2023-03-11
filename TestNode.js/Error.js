
/*
 *  Error
 */ 

var fs = require("fs");

fs.readFile('input2.txt', function (err, data) {
    if (err) {
        console.log(err); // no such file or directory - error !!!
        return;
    }
    console.log(data.toString());
});
console.log("Program Ended");
