COMPILER = g++
CPPFLAGS = -ggdb -std=c++0x
LIBS = -lm -pthread `pkg-config --libs --cflags opencv`
CPPFILES = logger.cpp filelogger.cpp run.cpp videologger.cpp
HFILES = logger.h filelogger.h videologger.h

all: logger_test.out

logger_test.out: $(HFILES) $(CPPFILES)
	$(COMPILER) $(CPPFLAGS) $(HFILES) $(CPPFILES) -o logger_test.out $(LIBS)
