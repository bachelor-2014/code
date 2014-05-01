COMPILER = g++
CPPFLAGS = -ggdb -std=c++0x
LIBS = -lm -pthread `pkg-config --libs --cflags opencv` 
CPPFILES = ../../computer_vision/imagestitcher.cpp ../../computer_vision/featuresandpositionimagestitcher.cpp featuresandpositionimagestitcher_test.cpp ../../camera.cpp ../../utils/threading.cpp ../../utils/base64.cpp
HFILES = ../../computer_vision/imagestitcher.h ../../computer_vision/featuresandpositionimagestitcher.h ../../camera.cpp

all: featuresandpositionimagestitcher_test.out

featuresandpositionimagestitcher_test.out: $(HFILES) $(CPPFILES)
	$(COMPILER) $(CPPFLAGS) $(CPPFILES) -o featuresandpositionimagestitcher_test.out $(LIBS)
