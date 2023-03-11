//
//  Query
//

var mysql = require('mysql');

var pool = mysql.createPool({
    connectionLimit : 10,
    host : '192.168.1.131',
    user : 'root',
    password : 'kang14'
});

// query with promise
new Promise(function (resolve, reject) {
    
    pool.getConnection(function (err, connection) {
        if (err) {
            return reject("Failed connect to DB !!!");
        }
        
        connection.query('SELECT 1 + 1 as solution', function (err, rows, fields) {
            if (err) {
                return reject("Failed query to DB !!!");
            }
            
            console.log('The solution is: ', rows[0].solution);
            resolve('Completed Query !!!');
        });

        // And done with the connection.    
        if (connection) {
            connection.release();
        }
    });
})
.then(function (text) {
    // 성공시
    console.log(text);
})
.catch(function (error) {
    // 실패시 
    console.error(error);
});
