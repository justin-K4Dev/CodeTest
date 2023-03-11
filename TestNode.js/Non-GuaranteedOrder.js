// 
//  Non-Guaranteed Order
//

var fs = require("fs");

console.log("Start write File - target.txt");
fs.writeFile('target.txt', 'Hi~ Node.js !!!', function (err) {
    if (err) {
        return console.error(err);
    }
    console.log("target File written successfully!");
    
    // 아래 로직은 로직 작성 순서와 상관 없이 비동기 함수들이 호출됨 !!!
    // JavaScript 로 로직 설계시 동기 함수들을 적절히 사용해야
    // 로직 복잡도를 줄일 수 있음 !!!
    for (var i = 0; i < 5; i++) {
        
        //asynchronous open
        console.log("Open File - target.txt");
        fs.open('target.txt', 'r+', function (err, fd) {
            if (err) {
                return console.error(err);
            }
            console.log("target File opened successfully!");
        });
        
        //asynchronous read
        fs.readFile('target.txt', function (err, data) {
            if (err) {
                return console.error(err);
            }
            console.log("Asynchronous read: " + data.toString());
        });
        
        console.log("Start to get file info!");
        fs.stat('target.txt', function (err, stats) {
            if (err) {
                return console.error(err);
            }
            console.log(stats);
            console.log("Got file info successfully!");
            
            //check file type
            console.log("isFile ? " + stats.isFile());
            console.log("isDirectory ? " + stats.isDirectory());
        });
        
        //closing File 
        var buf = new Buffer(1024);
        
        console.log("Going to open an existing file");
        fs.open('target.txt', 'r+', function (err, fd) {
            if (err) {
                return console.error(err);
            }
            console.log("target File opened successfully!");
            console.log("Going to read the file");
            fs.read(fd, buf, 0, buf.length, 0, function (err, bytes) {
                if (err) {
                    console.log(err);
                }
                
                //print only read bytes to avoid junk.
                if (bytes > 0) {
                    console.log(buf.slice(0, bytes).toString());
                }
                
                //close the opened file.
                fs.close(fd, function (err) {
                    if (err) {
                        console.log(err);
                    }
                    console.log("target File closed successfully.");
                });
            });
        });
        
        //delete file
        console.log("Going to delete an existing file");
        fs.unlink('target.txt', function (err) {
            if (err) {
                return console.error(err);
            }
            console.log("target File deleted successfully!");
        });
        
        //write file
        fs.writeFile('target.txt', 'Hi~ Node.js !!!', function (err) {
            if (err) {
                return console.error(err);
            }
            console.log("target File written successfully!");
        });
    }//end of for
});