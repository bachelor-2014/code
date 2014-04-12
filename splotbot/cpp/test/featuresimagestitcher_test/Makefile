COMPILER = g++
CPPFLAGS = -ggdb -std=c++0x
LIBS = -lm -pthread `pkg-config --libs --cflags opencv` 
CPPFILES = ../../computer_vision/imagestitcher.cpp ../../computer_vision/featuresimagestitcher.cpp featuresimagestitcher_test.cpp
HFILES = ../../computer_vision/imagestitcher.h ../../computer_vision/featuresimagestitcher.h

all: featuresimagestitcher_test.out

featuresimagestitcher_test.out: $(HFILES) $(CPPFILES)
	$(COMPILER) $(CPPFLAGS) $(CPPFILES) -o featuresimagestitcher_test.out $(LIBS)
