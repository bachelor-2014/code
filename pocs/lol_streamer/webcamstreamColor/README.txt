
----------------------------Kindly let me know if you change this code. Please mail me at anirudh2059@gmail.com------------------------------------ 

Before using this code please install all the Open CV libraries. Its simple in Ubuntu. I have used Synaptic manager to install all Opencv libraries. 

 


Compile your code using this commands once all the dependencies are installed. 

1. gcc -I /usr/include/opencv -lcxcore -lhighgui -lm -lcv -lpthread stream_server.c -o stream_server

2. gcc -I /usr/include/opencv -lcxcore -lhighgui -lm -lcv -lpthread stream_client.c -o stream_client


Execute your code using this command

./stream_client 127.0.0.1  8888  640 480     
 
 
 
 Enjoy !!
