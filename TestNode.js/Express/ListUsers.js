
//  
//  List Users
//  


/*
users.json file

{
   "user1" : {
      "name" : "mahesh",
	  "password" : "password1",
	  "profession" : "teacher",
	  "id": 1
   },
   "user2" : {
      "name" : "suresh",
	  "password" : "password2",
	  "profession" : "librarian",
	  "id": 2
   },
   "user3" : {
      "name" : "ramesh",
	  "password" : "password3",
	  "profession" : "clerk",
	  "id": 3
   }
} 
 */ 

var express = require('express');
var app = express();
var fs = require("fs");

app.get('/listUsers', function (req, res) {
    fs.readFile(__dirname + "/" + "users.json", 'utf8', function (err, data) {
        console.log(data);
        res.end(data);
    });
})

var server = app.listen(8081, function () {
    
    var host = server.address().address
    var port = server.address().port
    
    console.log("Example app listening at http://%s:%s", host, port)

})


// Now try to access defined API using http://127.0.0.1:8081/listUsers on local machine.