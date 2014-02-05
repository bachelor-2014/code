libs = `pkg-config --libs --cflags opencv`

command = g++ -std=c++0x

all: BlobDetection.out

BlobDetection.out: BlobDetection.cpp BlobDetection.hpp
	$(command) -o BlobDetection.out BlobDetection.cpp $(libs)

clean:
	rm BlobDetection.out
