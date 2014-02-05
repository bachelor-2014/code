command = g++ `pkg-config --cflags --libs opencv`

all: CaptureVideo.out

CaptureVideo.out: CaptureVideo.cpp
	$(command) CaptureVideo.cpp -o CaptureVideo.out
