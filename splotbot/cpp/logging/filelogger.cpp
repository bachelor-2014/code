#include <iostream>
#include <fstream>

#include "filelogger.h"

using namespace std;

ofstream dataOut;
string filename;

FileLogger::FileLogger(string identifier) : Logger(identifier){
    filename = "data/"+identifier;
}

FileLogger::~FileLogger(){
}

bool FileLogger::Write(void *data){
    char *d;
    d = (char*)data;
    if(!dataOut.is_open()){
        dataOut.open(filename,ios::out | ios::trunc);
    }

    dataOut << d << endl;
    dataOut.close();
    return 0;
}

