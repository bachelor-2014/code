COMPILER = g++
CPPFLAGS = -ggdb -std=c++0x
LIBS = -lm -pthread `pkg-config --libs --cflags opencv` 
CPPFILES = ../../computer_vision/calibrator.cpp calibrator_test.cpp
HFILES = ../../computer_vision/calibrator.h

all: calibrator_test.out

data:
	mkdir data

calibrator_test.out: $(HFILES) $(CPPFILES) data
	$(COMPILER) $(CPPFLAGS) $(CPPFILES) -o calibrator_test.out $(LIBS)

goodjohn.out: goodjohn.cpp
	$(COMPILER) $(CPPFLAGS) goodjohn.cpp -o goodjohn.out $(LIBS)
