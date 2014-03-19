#ifndef DBLOGGER_H
#define DBLOGGER_H

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <vector>
#include "logger.h"

using namespace std;

class DBLogger : public Logger<string>{

    public:
        DBLogger(string);
        ~DBLogger();

        bool Write(string);

        vector<string> Read();

        bool Info(string);

        bool Error(string);

        bool Clear();

    private:
        bool write(string,string);
};

#endif
