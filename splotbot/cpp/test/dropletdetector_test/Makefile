COMPILER = g++
CPPFLAGS = -ggdb -std=c++0x
LIBS = -lm -pthread `pkg-config --libs --cflags opencv cvblob` 
CPPFILES = ../../computer_vision/dropletdetector.cpp ../../computer_vision/computervisionutils.cpp dropletdetector_test.cpp
HFILES = ../../computer_vision/dropletdetector.h ../../computer_vision/computervisionutils.h ../../computer_vision/datastructs.h

all: dropletdetector_test.out

dropletdetector_test.out: $(HFILES) $(CPPFILES)
	$(COMPILER) $(CPPFLAGS) $(CPPFILES) -o test.out $(LIBS)

HEADLESSCPPFILES = ../../computer_vision/dropletdetector.cpp ../../computer_vision/computervisionutils.cpp headlessdropletdetector_test.cpp
HEADLESSHFILES = ../../computer_vision/dropletdetector.h ../../computer_vision/computervisionutils.h ../../computer_vision/datastructs.h
headless.out: $(HEADLESSHFILES) $(HEADLESSCPPFILES) droplet_video.mp4
	$(COMPILER) $(CPPFLAGS) $(HEADLESSCPPFILES) -o headless.out $(LIBS)
