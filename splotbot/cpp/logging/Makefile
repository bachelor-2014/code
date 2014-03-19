COMPILER = g++
CPPFLAGS = -ggdb -std=c++0x
LIBS = -lm -pthread `pkg-config --libs --cflags opencv sqlite3`
CPPFILES = filelogger.cpp run.cpp videologger.cpp dblogger.cpp
HFILES = logger.h filelogger.h videologger.h dblogger.h

default: logger_test.out

data/experiments.db:
	sqlite3 data/experiments.db < data/table.sql

logger_test.out: $(HFILES) $(CPPFILES) data/experiments.db
	$(COMPILER) $(CPPFLAGS) $(HFILES) $(CPPFILES) -o logger_test.out $(LIBS)

test.out: logger.h filelogger.h filelogger.cpp testlogger.cpp data/experiments.db
	$(COMPILER) $(CPPFLAGS) logger.h filelogger.h filelogger.cpp testlogger.cpp -o test.out $(LIBS)
