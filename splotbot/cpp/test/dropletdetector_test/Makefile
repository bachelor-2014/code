COMPILER = g++
CPPFLAGS = -ggdb -std=c++0x
LIBS = -lm -pthread `pkg-config --libs --cflags opencv cvblob` 
CPPFILES = ../../computer_vision/dropletdetector.cpp dropletdetector_test.cpp
HFILES = ../../computer_vision/dropletdetector.h

all: dropletdetector_test.out

dropletdetector_test.out: $(HFILES) $(CPPFILES)
	$(COMPILER) $(CPPFLAGS) $(CPPFILES) -o test.out $(LIBS)
