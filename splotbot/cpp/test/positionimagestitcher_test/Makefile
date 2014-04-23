COMPILER = g++
CPPFLAGS = -ggdb -std=c++0x
LIBS = -lm -pthread `pkg-config --libs --cflags opencv` 
CPPFILES = ../../computer_vision/imagestitcher.cpp ../../computer_vision/positionimagestitcher.cpp positionimagestitcher_test.cpp ../../camera.cpp ../../utils/threading.cpp ../../utils/base64.cpp
HFILES = ../../computer_vision/imagestitcher.h ../../computer_vision/positionimagestitcher.h ../../camera.cpp

all: positionimagestitcher_test.out

positionimagestitcher_test.out: $(HFILES) $(CPPFILES)
	$(COMPILER) $(CPPFLAGS) $(CPPFILES) -o positionimagestitcher_test.out $(LIBS)
