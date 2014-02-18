libs = `pkg-config --libs --cflags opencv` -lcurl

command = g++ -std=c++0x

VideoSender.out: VideoSender.cpp
	$(command) -o $@ $^ $(libs)

clean:
	#find -name "*.out" | xargs rm
