COMPILER = g++
CPPFLAGS = -ggdb -std=c++0x
LIBS = -lm -pthread `pkg-config --libs --cflags opencv cvblob` 
CPPFILES = ../../computer_vision/imagestitcher.cpp ../../computer_vision/featuresandpositionimagestitcher.cpp featuresandpositionimagestitcher_test.cpp ../../camera.cpp ../../computer_vision/dropletdetector.cpp ../../instructionbuffer.cpp ../../component.cpp ../../utils/base64.cpp ../../computer_vision/computervisionutils.cpp ../../logging/filelogger.cpp ../../utils/threading.cpp
HFILES = ../../computer_vision/imagestitcher.h ../../computer_vision/featuresandpositionimagestitcher.h ../../camera.h ../../computer_vision/dropletdetector.h

all: featuresandpositionimagestitcher_test.out

featuresandpositionimagestitcher_test.out: $(HFILES) $(CPPFILES)
	$(COMPILER) $(CPPFLAGS) $(CPPFILES) -o featuresandpositionimagestitcher_test.out $(LIBS)
