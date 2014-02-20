#!/usr/bin/env node

var addon = require('./build/Release/addon');
var obj = new addon.SplotbotWrapper();

console.log( obj.runCode([1,2,3]) );
