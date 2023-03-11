//
// Player module
//

function Player ( value ) {
    'name' : value,
    'list' : { 'egoing': 10, 'k8805': 6, 'sorialgi': 80},
    'show' : function () {
        for (var name in this.list) {
            document.write(name + ':' + this.list[name] + "<br />");
        }
    }
}



exports.Player.Login = function (id, password) {
    this.id = id;
    this.password = password;
}

exports.Logout = function (accessToken) {
    return accessToken + 100;
}

function Load(id) {
    return 'Player::' + id;
}
exports.Load = Load;

function Update(value) {

    
}


exports.ServerInfo = { 'RK': 0, 'SK': 0 };


