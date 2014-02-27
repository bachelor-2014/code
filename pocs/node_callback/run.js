#!/usr/bin/env node
var texample = require('./build/Debug/texample');
texample.callback = function(i) {
    console.log('Bang: ' + i);
}
texample.start();

