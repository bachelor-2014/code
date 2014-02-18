#!/usr/bin/env node

var server = require('http').Server();
var io = require('socket.io').listen(server, { log: false });
var fs = require('fs');

//var ss = require('socket.io-stream');
//var path = require('path');
//var app = require('http').createServer(handler);
//var io = sio.listen(8000);

io.on('connection', function(socket) {
  io.sockets.emit('event', { time: new Date().toJSON() });

  setInterval(function(){

    fs.readFile("active.png",handleFile);

  },1000);

  socket.on('disconnect', function(){ message: "bye" });
  //var filename = path.basename(data.name);
  //stream.pipe(fs.createWriteStream(filename));
});
function handleFile(err,data){

  io.sockets.emit('new_image', {image_data: new Buffer(data).toString('base64')} );
}

server.listen(8000);
