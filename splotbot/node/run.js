#!/usr/bin/env node

var addon = require('./build/Debug/addon');
var express = require('express'),
    app = express(), 
    http = require('http'), 
    server = http.createServer(app), 
    io = require('socket.io').listen(server);

function getdata(req, res, next) {
    var data='';
    req.setEncoding('utf8');
    req.on('data', function(chunk) { 
       data += chunk;
    });

    req.on('end', function() {
        req.data = data;
        next();
    });
}

/**
 * Unused
 */
function eventCallback(name, data){
    io.sockets.emit(name, { data: data });
}

var splotbot = new addon.SplotbotWrapper();


io.sockets.on('connection', function (socket) {
    /**
     * Socket request for running code on splotbot
     */
    socket.on('runcode', function(code){
        splotbot.runCode(code);
    }); 
});

/**
 * Post request for running code on splotbot
 */
app.post('/runcode', function(req, res){
    var code = req.body;
    splotbot.runCode(code);
    res.send();
});

/**
 * Event callback endpoint
 */
app.post('/event/:name', getdata, function(req, res){
    eventCallback(req.params.name, req.data);
    res.send();
});

server.listen(8080);
