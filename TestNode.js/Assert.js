//
// Assert
//

var assert = require('assert');

var a = true;

assert(a);

assert(a, 'a는 true 값이어야 함!!!');

assert.ok(a, 'a는 true 값이어야 함!!!');

// shallow compare
assert.equal(a, 10, 'a는 10이어야 함!!!'); // JavaScript == 연산자와 동일한 기능

assert.equal('10', 10); // 성공

assert.notEqual('10', 10); // 실패

assert.equal({ a: 1 }, { a: 1 }); // 실패 - 배열 객체를 비교 하기 때문에 동일 할 수 없다 !!!


// deep compare
assert.strictEqual('10', 10, '문자열 10은 숫자 10과 같음!!!'); // 실패

assert.notStrictEqual('10', 10, '문자열 10은 숫자 10과 같으면 않됨!!!'); // 실패

var obj = { b: 1, a: [1, 2, 3, 4] };
assert.deepEqual(obj, { a: [1, 2, 3, 4], b: 1 }); // 성공

var a = new Date(), b = new Date();
assert.deepEqual(a, b);

assert.deepEqual(/a/ig, /a/gi); // 성공

var eventEmitter = require('events').EventEmitter;
var ee = new EventEmitter();
assert.deepEqual(ee, {}); // 실패

assert.strictEqual(Object.keys(ee).length, 0); // 성공






