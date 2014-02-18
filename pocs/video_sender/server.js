var express = require('express');
var app = express.createServer();
var fs = require('fs');

app.use(express.bodyParser());

app.post('/', function(req, res){
    //console.log(req.body);
    fs.writeFile("image.jpg", JSON.stringify(req.body));
}); 

app.listen(1337);
