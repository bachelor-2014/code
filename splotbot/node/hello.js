#!/usr/bin/env node
var addon = require('./build/Release/hello');

console.log(addon.mCallbacks("ok",function(msg) {
    console.log("Callback message: " + msg);
}));

console.log(addon.mReturns());

var objectaddon = require('./build/Release/addon');
var obj = new objectaddon.SplotbotWrapper();

console.log( obj.runCode([1,2,3]) );
