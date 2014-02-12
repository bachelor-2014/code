libs = `pkg-config --libs --cflags opencv gstreamer-1.0`

command = g++ -std=c++0x -ggdb

all: Streamer.out

Streamer.out: Streamer.cpp
	$(command) -o $@ $^ $(libs)

clean:
	#find -name "*.out" | xargs rm
