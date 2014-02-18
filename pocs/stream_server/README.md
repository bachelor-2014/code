# Poc of node streaming server

This shows a simple example of streaming a changing image to a web browser
It works by reading a single image on the machine and sending it over 
socket.io to a client. 

Its currently based on rather stupid timeouts for chaning the image
should eventually be a hook from c++ or something similar

## Howto

Install node and npm
Install the dependencies: npm install
Open client.html in a browser
Start the server: ./stream_server.js
POST an image to the server, like: 
    curl -XPOST --data-binary @file_path localhost:8000/image
