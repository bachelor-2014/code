COMPILER = g++
CPPFLAGS = -ggdb -std=c++0x
LIBS = -lm -pthread `pkg-config --libs --cflags opencv cvblob` -lopencv_stitching

SRCFILES = libraries/cJSON/cJSON.cpp utils/base64.cpp utils/threading.cpp \
	computer_vision/imagestitcher.cpp \
	computer_vision/featuresimagestitcher.cpp component.cpp \
	computer_vision/positionimagestitcher.cpp \
	instructionbuffer.cpp camera.cpp singlesteppermotor.cpp \
	rcservomotor.cpp scanner.cpp  mendel.cpp xyaxes.cpp \
	cameracalibrator.cpp \
	componentinitializer.cpp splotbot.cpp logging/logger.cpp \
	logging/filelogger.cpp logging/videologger.cpp \
	computer_vision/dropletdetector.cpp \
	computer_vision/computervisionutils.cpp computer_vision/calibrator.cpp \
	computer_vision/featuresandpositionimagestitcher.cpp \
	utils/errors.cpp
OBJFILES = $(SRCFILES:.cpp=.o)

TESTFILES = $(shell find -name "*test.cpp")
TESTOBJ = $(TESTFILES:.cpp=.out)

PROGRAM = test.out
PROGRAMSRC = test.cpp

default: depend all

depend: .depend

all: $(SRCFILES) $(PROGRAM)

tests: $(TESTOBJ)

.depend: $(SRCFILES)
	rm -f ./.depend
	$(COMPILER) $(CPPFLAGS) -MM $^>>./.depend;

include .depend

data/experiments.db:
	-@mkdir data 2>/dev/null || true
	sqlite3 data/experiments.db < logging/data/table.sql

data/images:
	mkdir -p data/images

$(PROGRAM): $(OBJFILES) data/experiments.db data/images $(PROGRAMSRC)
	$(COMPILER) $(CPPFLAGS) $(OBJFILES) $(PROGRAMSRC) -o $@ $(LIBS)

.cpp.o:
	$(COMPILER) -c $(CPPFLAGS) $< -o $@

.cpp.out: $(SRCFILES) $(OBJFILES) data/experiments.db data/images $*.cpp
	$(COMPILER) $(CPPFLAGS) $(OBJFILES) $*.cpp -o $@ $(LIBS)

clean:
	rm $(OBJFILES) $(PROGRAM)
