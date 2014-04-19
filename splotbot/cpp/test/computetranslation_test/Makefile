COMPILER = g++
CPPFLAGS = -ggdb -std=c++0x
LIBS = -lm -pthread `pkg-config --libs --cflags opencv` 
CPPFILES = ../../computer_vision/computervisionutils.cpp test.cpp
HFILES = ../../computer_vision/computervisionutils.h

all: test.out

test.out: $(HFILES) $(CPPFILES)
	$(COMPILER) $(CPPFLAGS) $(CPPFILES) -o test.out $(LIBS)
