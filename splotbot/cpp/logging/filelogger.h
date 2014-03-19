#ifndef FILELOGGER_H
#define FILELOGGER_H

#include <iostream>
#include <fstream>
#include <typeinfo>
#include "logger.h"

using namespace std;

class FileLogger : public Logger<string> {

    public:
        FileLogger(string);
        ~FileLogger();

        bool Write(string);

        vector<string> Read();

        bool Info(string);

        bool Error(string);

        bool Clear();

    private:
        string filename;
        ofstream dataOut;
};

#endif
