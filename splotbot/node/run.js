#!/usr/bin/env node

var addon = require('./build/Debug/addon');
var express = require('express'),
    app = express(), 
    http = require('http'), 
    server = http.createServer(app), 
    io = require('socket.io').listen(server, { log: false });

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

function allowCrossDomain(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'Content-Type');

    next();
}

app.use(allowCrossDomain);


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
app.post('/runcode', getdata, function(req, res){
    var code = JSON.parse(req.data);
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


server.listen(8000);
