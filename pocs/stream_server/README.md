# Poc of node streaming server
#
This shows a simple example of streaming a changing image to a web browser
It works by reading a single image on the machine and sending it over 
socket.io to a client. 

Its currently based on rather stupid timeouts for chaning the image
should eventually be a hook from c++ or something similar

## Howto

Start the server: ./stream_server.js
Run and example that keeps changing the files: ./loop_and_change_files
Open client.html in a browser
