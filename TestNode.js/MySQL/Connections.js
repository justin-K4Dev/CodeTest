//
// Connections
//

var mysql = require('mysql');


//
// Basic Connection
//

var connection = mysql.createConnection({
    host : '192.168.1.131',
    user : 'root',
    password : 'kang14'
});

connection.connect();

connection.query('SELECT 1 + 1 AS solution', function (err, rows, fields) {
    if (err) throw err;
    
    console.log('The solution is: ', rows[0].solution);
});

connection.end();

//
// Establishing connections
//

var connection = mysql.createConnection({
    host     : '192.168.1.131',
    user : 'root',
    password : 'kang14'
});

connection.connect(function (err) {
    if (err) {
        console.error('error connecting: ' + err.stack);
        return;
    }
    
    console.log('connected as id ' + connection.threadId);
});

connection.end();

var connection = mysql.createConnection({
    host     : '192.168.1.131',
    user : 'root',
    password : 'kang14'
});

connection.query('SELECT 1', function (err, rows) {
    // connected! (unless `err` is set)
    console.log('connected as id ' + connection.threadId);
});


//
// Terminating connections
//

connection.end(function (err) {
    if (err) {
        console.error('error disconnecting: ' + err.stack);
        return;
    }
    
    // The connection is terminated now
    console.log('disconnected as id ' + connection.threadId);
});


//
// An alternative way to end the connection is to call the destroy() method.
// This will cause an immediate termination of the underlying socket.
// Additionally destroy() guarantees that no more events
// or callbacks will be triggered for the connection.
//
connection.destroy();



//
// Pooling connections
//

var pool = mysql.createPool({
    connectionLimit : 10,
    host            : '192.168.1.131',
    user            : 'root',
    password        : 'kang14'
});

pool.query('SELECT 1 + 1 as solution', function (err, rows, fields) {
    if (err) throw err;
    
    console.log('The solution is: ', rows[0].solution);
});

// Closing all the connections in pool
pool.end(function (err) {
  // all connections in the pool have ended
});


pool.getConnection(function (err, connection) {
    // Use the connection
    connection.query('SELECT 1 + 100 as solution', function (err, rows) {
        
        // And done with the connection.
        connection.release();

        // Don't use the connection here, it has been returned to the pool.
        console.log('The solution is: ', rows[0].solution);
    });
});


//
// Pool events - connection
// The pool will emit a connection event when a new connection is made within the pool.
// If you need to set session variables on the connection before it gets used,
// you can listen to the connection event.
pool.on('connection', function (connection) {
    connection.query('SET SESSION auto_increment_increment=1')
});

//
// Pool events - enqueue
// The pool will emit an enqueue event when a callback has been queued to wait for an available connection.
pool.on('enqueue', function () {
    console.log('Waiting for available connection slot');
});


