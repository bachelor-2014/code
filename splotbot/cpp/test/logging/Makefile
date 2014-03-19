COMPILER = g++
CPPFLAGS = -ggdb -std=c++0x
LIBS = -lm -pthread `pkg-config --libs --cflags opencv sqlite3`
CPPFILES = ../../logging/logger.cpp ../../logging/filelogger.cpp logger_test.cpp ../../logging/videologger.cpp ../../logging/dblogger.cpp
HFILES = ../../logging/logger.h ../../logging/filelogger.h ../../logging/videologger.h ../../logging/dblogger.h

all: logger_test.out

logger_test.out: $(HFILES) $(CPPFILES)
	$(COMPILER) $(CPPFLAGS) $(HFILES) $(CPPFILES) -o logger_test.out $(LIBS)
