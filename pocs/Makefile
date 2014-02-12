libs = `pkg-config --libs --cflags opencv`

command = g++ -std=c++0x -ggdb

%.out: %.cpp
	$(command) -o $@ $^ $(libs)

clean:
	#find -name "*.out" | xargs rm
