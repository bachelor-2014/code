libs = `pkg-config --libs --cflags opencv`

command = g++ -std=c++0x

all: SurfDetection.out

SurfDetection.out: SurfDetection.cpp
	$(command) -o SurfDetection.out SurfDetection.cpp $(libs)

clean:
	rm SurfDetection.out
