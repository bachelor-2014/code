#!/usr/bin/env node
var fs = require('fs');

var server = require('http').Server(
  function(req,res){

    if(req.url == "/image" && req.method == "POST"){
      //var buffer_image = 'john.png'
      //stream = fs.createWriteStream(buffer_image)

      //req.pipe(stream, { end: false });

      //var bytes = ''
      //req.on('data', function(data){
      //  bytes += data.toString()
      //});
      var base64Data = '';
      req.on('data',function(data){
        base64Data += data // new Buffer(data).toString('base64')
      });

      req.on('end',function(){
          res.writeHead(200,"ok");

          io.sockets.emit('image_data', { image_data: base64Data } );

          res.end();
          //sendBase64Image(
          //  new Buffer(bytes).toString('base64'),
          //  function(){ res.end(); });

          //fs.readFile(buffer_image,function(err,data){
          //  handleFile(err,data,function(){ res.end(); });
          //});

      });

    }

  });

var io = require('socket.io').listen(server, { log: false });

function handleFile(err,data,cb){
  sendBase64Image(new Buffer(data).toString('base64'),cb);
}

function sendBase64Image(base64Data,cb){
}

server.listen(8000);
