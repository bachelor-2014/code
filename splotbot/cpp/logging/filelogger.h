#ifndef FILELOGGER_H
#define FILELOGGER_H

#include "logger.h"

using namespace std;

class FileLogger : private Logger{
    public:
        FileLogger(string);
        int Write(void*);
};

#endif
