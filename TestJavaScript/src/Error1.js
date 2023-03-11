/**
 * Created by justin on 2016-03-07.
 */

window.onerror = handleError;

var errorOutputHandleId;

function setErrorOutputHandleId(handleId) {
    errorOutputHandleId = handleId;
}

function handleError(msg, url, line)
{
    var msg = "An error has occurred in this dialog. Error: " + line + " " + msg;
    document.getElementById(errorOutputHandleId).innerHTML =  msg + '<br/>at: ' + url + '<br/>line: ' + line;

    return true;
}

