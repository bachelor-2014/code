COMPILER = g++
CPPFLAGS = -ggdb -std=c++0x
LIBS = -lm -pthread
CPPFILES = libraries/cJSON/cJSON.c component.cpp instructionbuffer.cpp camera.cpp singlesteppermotor.cpp componentinitializer.cpp splotbot.cpp test.cpp
HFILES = libraries/cJSON/cJSON.h component.h instructionbuffer.h camera.h singlesteppermotor.h componentinitializer.h splotbot.h

all: test.out

test.out: $(HFILES) $(CPPFILES)
	$(COMPILER) $(CPPFLAGS) $(CPPFILES) -o test.out $(LIBS)
