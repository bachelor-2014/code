COMPILER = g++
CPPFLAGS = -ggdb -std=c++0x
LIBS = -lm -pthread `pkg-config --libs --cflags opencv cvblob` -lopencv_stitching
CPPFILES = libraries/cJSON/cJSON.cpp utils/base64.cpp utils/threading.cpp \
	computer_vision/imagestitcher.cpp \
	computer_vision/featuresimagestitcher.cpp component.cpp \
	computer_vision/positionimagestitcher.cpp \
	instructionbuffer.cpp camera.cpp singlesteppermotor.cpp \
	rcservomotor.cpp scanner.cpp  mendel.cpp xyaxes.cpp \
	cameracalibrator.cpp \
	componentinitializer.cpp splotbot.cpp test.cpp logging/logger.cpp \
	logging/filelogger.cpp logging/videologger.cpp \
	computer_vision/dropletdetector.cpp \
	computer_vision/computervisionutils.cpp computer_vision/calibrator.cpp \
	computer_vision/featuresandpositionimagestitcher.cpp \
	utils/errors.cpp

OBJFILES = $(CPPFILES:.cpp=.o)
PROGRAM = test.out

default: depend all

depend: .depend

all: $(CPPFILES) $(PROGRAM)

tests: test/calibrator_test/calibrator_test.out

.depend: $(CPPFILES)
	rm -f ./.depend
	$(COMPILER) $(CPPFLAGS) -MM $^>>./.depend;

include .depend

data/experiments.db:
	-@mkdir data 2>/dev/null || true
	sqlite3 data/experiments.db < logging/data/table.sql

data/images:
	mkdir -p data/images

$(PROGRAM): $(OBJFILES) data/experiments.db data/images
	$(COMPILER) $(CPPFLAGS) $(OBJFILES) -o $@ $(LIBS)

.cpp.o:
	$(COMPILER) -c $(CPPFLAGS) $< -o $@

test/calibrator_test/calibrator_test.out: $(OBJFILES)
	$(COMPILER) -c $(CPPFLAGS) $*.cpp -o $@

clean:
	rm $(OBJFILES) $(PROGRAM)
