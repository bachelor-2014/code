var addon = require('./build/Release/hello');

console.log(addon.hello("Test", function(msg) {
    console.log("Callback message: " + msg);
}));

console.log(addon.other());


var objectaddon = require('./build/Release/addon');
var obj = new objectaddon.MyObject(10);
console.log( obj.plusOne() ); // 11
console.log( obj.plusOne() ); // 12
console.log( obj.plusOne() ); // 13
