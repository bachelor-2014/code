#!/usr/bin/env node

var addon = require('./build/Release/addon');
var express = require('express'),
    app = express(), 
    http = require('http'), 
    server = http.createServer(app), 
    io = require('socket.io').listen(server);

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
 * Bind the even of images being send from the splotbot
 * Splotbot gets a callback function where:
 * camera: The identifier for the camera (string)
 * image: The image data (base64 string)
 */
//splotbot.sendImage(function(camera, image){
//    io.sockets.emit(camera, { image_data: image });
//});

server.listen(8080);
