#!/usr/bin/env node
var fs = require('fs');

var server = require('http').Server(
  function(req,res){

    if(req.url == "/image" && req.method == "POST"){
      var buffer_image = 'john.png'

      stream = fs.createWriteStream(buffer_image)
      req.pipe(stream);

      req.on('end',function(){
        res.writeHead(200,"ok")
        fs.readFile(buffer_image,function(err,data){
          handleFile(err,data,function(){ res.end(); });
        });
      });

    }

  });

var io = require('socket.io').listen(server, { log: false });

io.on('connection', function(socket) {
  io.sockets.emit('event', { time: new Date().toJSON() });

  socket.on('disconnect', function(){ message: "bye" });
});

function handleFile(err,data,cb){
  sendBase64Image(new Buffer(data).toString('base64'),cb);
}

function sendBase64Image(base64Data,cb){
  console.log(base64Data);
  io.sockets.emit('new_image', {image_data: base64Data} );
  cb()
}

server.listen(8000);
