/**
 * Created by justin on 2016-03-07.
 */

var targetObjId;

window.errorObj = window.errorObj || {};
errorObj.Error = function (outObjId, message, name, original) {
    this.original = original;
    targetObjId = outObjId;
    this.name = name || 'Error';
    this.message = message || 'A errorObj.Error was thrown!';
    (original)? this.stack = this.original.stack: this.stack = null;
    this.message += '<br>---STACK---<br>' + this.stack;
};

var ClassEmpty = function() {};
ClassEmpty.prototype = Error.prototype;
errorObj.Error.prototype = new ClassEmpty();
errorObj.Error.prototype.constructor = errorObj.Error;

window.onerror = printError;

function printError(msg, url, line){
    document.getElementById(targetObjId).innerHTML = msg+'<br>at: '+url+'<br>line: '+line;
    return true;
}