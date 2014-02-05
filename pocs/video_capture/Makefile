libs = `pkg-config --libs --cflags opencv`

command = g++ 

all: CaptureVideo.out

CaptureVideo.out: CaptureVideo.cpp
	$(command) -o CaptureVideo.out CaptureVideo.cpp $(libs)

clean:
	rm CaptureVideo.out
