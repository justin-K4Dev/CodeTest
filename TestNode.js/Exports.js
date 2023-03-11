//
// Exports
//

var player = require('./Player.js');

var id = 'justin';
var password = 'kang14';
player.Login(id, password);

var accessToken = 1000;
player.Logout(accessToken);

var playerId = player.Load(id);
console.log('PlayerID - ' + playerId);


player.ServerInfo.RK = 1;
player.ServerInfo.SK = 1;

console.log('Player.RK - ' + player.ServerInfo.RK);
console.log('Player.SK - ' + player.ServerInfo.SK);

