#!/usr/bin/env node

// Our cc module
var addon = require('./build/Debug/addon');

// Requirements
var express = require('express'), // Web server
    app = express(), // App object to hold the server
    http = require('http'),
    server = http.createServer(app), // Start the server
    // Bind socket.io. Logging is disabled because it's very verbose
    io = require('socket.io').listen(server, { log: false });

args = process.argv
if(args.length < 4){
    console.log("Please provide config file and mendel socket as command line arguments");
    process.exit(1);
}
var splotbot = new addon.SplotbotWrapper(process.argv[2],process.argv[3]);

/**
 * Read incoming request data
 */
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
 * Enable access for all clients from everywhere
 */
function allowCrossDomain(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Headers', 'Content-Type');

    // Propagate the call
    next();
}

// Bind the crossdomain function to all request
app.use(allowCrossDomain);

/**
 * Expose something to the socket stream (out)
 */
function eventCallback(name, data){
    io.sockets.emit(name, { data: data });
}

// Listen for socket connections
io.sockets.on('connection', function (socket) {

    // Socket request for running code on splotbot
    socket.on('runcode', function(code){
        splotbot.runCode(code);
    }); 
});

// Post request for running code on splotbot
app.post('/runcode', getdata, function(req, res){
    var code = JSON.parse(req.data);
    console.log("Code was:",code);
    splotbot.runCode(code);
    res.send();
});

// Event callback endpoint
app.post('/event/:name', getdata, function(req, res){
    eventCallback(req.params.name, req.data);
    res.send();
});

app.get('/',function(req,res){
    res.sendfile("client/app/index.html");
});

//Serving the client folder
app.get('/*', function(req,res){
       res.sendfile("client/app/" + req.params[0]);
});

// Bind server to port
server.listen(8000);
