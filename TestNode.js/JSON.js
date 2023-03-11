


var fs = require('fs');

fs.readFile('./data.json', function (err, data) {
    if (err) {
        console.log( "Failed to read Json file !!! - " + err);
    }
    
    var jsonData = JSON.parse(data.toString().replace(/^\uFEFF/, ''));
    
    // region 목록 읽기
    var regionList = jsonData["REGION_LIST"];
    
    for (var regionKey in regionList) {
        
        // region 정보 읽기
        var regionInfo = regionList[regionKey];        
        var regionID = regionInfo["regionId"];
        var serverList = regionInfo["serverList"];

        for (var serverKey in serverList) {
            
            // server 정보 읽기
            var serverInfo = serverList[serverKey];
            
            console.log(serverInfo["serverId"]
                       , serverInfo["name"]
                       , serverInfo["port"]        
                       , serverInfo["limitUsers"]);
        }
    }

    var objectList = [];
    objectList.push({ 'port': 1, 'host': 2, 'tag' : { 'RID' : 3, 'SID' : 4 } });
    
    for (var i = 0; i < objectList.length; ++i) {
        var object = objectList[i];
        console.log(object.port, object.host, object.tag);
    }
    
});