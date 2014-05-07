var qs = require('querystring');
var http = require('http');

http.createServer(function (req, res) {
  res.writeHead(200, {'Content-Type': 'text/plain'});
console.log(request.method);
if (req.method == 'POST') {
console.log("post")
        var body = '';
        req.on('data', function (data) {
            body += data;
        });

        req.on('end', function () {
		console.log("end");
            var POST = qs.parse(body);
	   console.log(POST)
        });
    }

  res.end('Hello World\n');
}).listen(8000, '127.0.0.1');
