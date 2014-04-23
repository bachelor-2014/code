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
HFILES = libraries/cJSON/cJSON.h computer_vision/imagestitcher.h \
	computer_vision/featuresimagestitcher.h component.h \
	computer_vision/positionimagestitcher.h \
	instructionbuffer.h camera.h singlesteppermotor.h \
	rcservomotor.h scanner.h cameracalibrator.h mendel.h xyaxes.h \
	componentinitializer.h splotbot.h utils/base64.h utils/threading.h \
	logging/logger.h logging/filelogger.h logging/videologger.h \
	computer_vision/dropletdetector.h \
	computer_vision/computervisionutils.h computer_vision/calibrator.h \
	computer_vision/featuresandpositionimagestitcher.h \
	utils/errors.h

OBJFILES = $(CPPFILES:.cpp=.o)
PROGRAM = test.out

all: $(CPPFILES) $(PROGRAM)

data/experiments.db:
	-@mkdir data 2>/dev/null || true
	sqlite3 data/experiments.db < logging/data/table.sql

data/images:
	mkdir -p data/images

$(PROGRAM): $(OBJFILES) data/experiments.db data/images
	$(COMPILER) $(CPPFLAGS) $(OBJFILES) -o $@ $(LIBS)

.cpp.o:
	$(COMPILER) -c $(CPPFLAGS) $< -o $@
clean:
	rm $(OBJFILES) $(PROGRAM)
