#!/usr/bin/env node
var fs = require('fs');

var server = require('http').Server(
  function(req,res){

    if(req.url == "/image" && req.method == "POST"){

      base64Data = '';
      req.on('data',function(data){
        base64Data += data // new Buffer(data).toString('base64')
      });

      req.on('end',function(){

        sendResponse({image_data:base64Data},function(){
          base64Data = '';
          bytes = '';
          res.writeHead(200,"ok");
          res.end();
        });

      });

    }

  });

var io = require('socket.io').listen(server, { log: false });

function sendResponse(data,cb){
  io.sockets.emit('image_data', { image_data: base64Data } );
  //io.sockets.on('image_success', cb);
  cb();
}
server.listen(8000);
