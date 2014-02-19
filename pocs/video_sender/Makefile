libs = `pkg-config --libs --cflags opencv` -lcurl

command = g++ -std=c++0x -ggdb

VideoSender.out: VideoSender.o base64.o
	$(command) -o $@ $^ $(libs)

VideoSender.o: VideoSender.cpp
	$(command) -c $^

base64.o: base64.cpp
	$(command) -c $^

clean:
	#find -name "*.out" | xargs rm
