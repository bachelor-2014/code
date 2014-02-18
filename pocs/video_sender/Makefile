libs = `pkg-config --libs --cflags opencv` -lcurl

command = g++

VideoSender.out: VideoSender.cpp
	$(command) -o $@ $^ $(libs)

clean:
	#find -name "*.out" | xargs rm
