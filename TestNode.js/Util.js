//
// Utility
//


// util.inherits
const util = require('util');
const EventEmitter = require('events');

function MyStream() {
    EventEmitter.call(this);
}

util.inherits(MyStream, EventEmitter);

MyStream.prototype.write = function onWrite(data) {
    this.emit('data', data);
}

var stream = new MyStream();

console.log(stream instanceof EventEmitter); // true
console.log(MyStream.super_ === EventEmitter); // true

stream.on('data', function oData(data) {
    console.log(`Received data: "${data}"`);
});
stream.write('It works!'); // Received data: "It works!"

