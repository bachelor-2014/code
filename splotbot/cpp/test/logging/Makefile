COMPILER = g++
CPPFLAGS = -ggdb -std=c++0x
LIBS = -lm -pthread
#`pkg-config --libs --cflags opencv`
CPPFILES = ../../logging/logger.cpp ../../logging/filelogger.cpp logger_test.cpp
HFILES = ../../logging/logger.h ../../logging/filelogger.h

all: logger_test.out

logger_test.out: $(HFILES) $(CPPFILES)
	$(COMPILER) $(CPPFLAGS) $(HFILES) $(CPPFILES) -o logger_test.out $(LIBS)
