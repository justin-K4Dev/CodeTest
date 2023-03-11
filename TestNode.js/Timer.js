//
//  Timer
//

function printHello() {
    console.log("Hello, World!");
}
// Now call above function after 2 seconds
var t = setTimeout(printHello, 2000);

// Now clear the timer
clearTimeout(t);


function printNodeJS() {
    console.log("Hello, Node.js!");
}
// Now call above function after 2 seconds
setInterval(printNodeJS, 2000);