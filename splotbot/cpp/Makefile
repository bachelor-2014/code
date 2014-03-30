COMPILER = g++
CPPFLAGS = -ggdb -std=c++0x
LIBS = -lm -pthread `pkg-config --libs --cflags opencv cvblob` 
CPPFILES = libraries/cJSON/cJSON.cpp utils/base64.cpp utils/threading.cpp component.cpp instructionbuffer.cpp camera.cpp singlesteppermotor.cpp componentinitializer.cpp splotbot.cpp test.cpp logging/logger.cpp logging/filelogger.cpp logging/videologger.cpp computer_vision/dropletdetector.cpp computer_vision/computervisionutils.cpp
HFILES = libraries/cJSON/cJSON.h component.h instructionbuffer.h camera.h singlesteppermotor.h componentinitializer.h splotbot.h utils/base64.h utils/threading.h logging/logger.h logging/filelogger.h logging/videologger.h computer_vision/dropletdetector.h computer_vision/computervisionutils.h
OBJFILES = $(CPPFILES:.cpp=.o)
PROGRAM = test.out

all: $(CPPFILES) $(PROGRAM)

data/experiments.db:
	sqlite3 data/experiments.db < logging/data/table.sql

$(PROGRAM): $(OBJFILES) data/experiments.db
	$(COMPILER) $(CPPFLAGS) $(OBJFILES) -o $@ $(LIBS)

.cpp.o:
		$(COMPILER) -c $(CPPFLAGS) $< -o $@
clean:
	rm $(OBJFILES) $(PROGRAM)
