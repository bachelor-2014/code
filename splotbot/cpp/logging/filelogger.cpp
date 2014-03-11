#include <iostream>
#include <fstream>

#include "filelogger.h"

using namespace std;

ofstream dataIn;
ofStream dataOut;

FileLogger::FileLogger(string identifier) : Logger(identifier){
}

int FileLogger::Write(void *data){
    char *d;
    d = (char*)data;
    
    return 0;
}
