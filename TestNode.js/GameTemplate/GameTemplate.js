//
// GameTemplate Module
//





poolRedis.getClient(function (client, done) {
    client.get('key', function (err, value) {
        console.log('value from redis is:', value);
        done();
    });
});







