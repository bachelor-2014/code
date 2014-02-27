#!/usr/bin/env node

var addon = require('./build/Debug/addon');
var express = require('express'),
    app = express(), 
    http = require('http'), 
    server = http.createServer(app), 
    io = require('socket.io').listen(server);

addon.eventCallback = function (name,data){
    console.log(name + ":" + data);
    io.sockets.emit(name, { image_data: data });
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

server.listen(8080);
