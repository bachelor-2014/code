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

string FileLogger::readDataFromFile(){
    string* outstr = new string;

    ifstream dataIn(filename);

    string auxstring;
    while (std::getline(dataIn,auxstring)) {
        (*outstr).append(auxstring);
    }

    dataIn.close();
    return *outstr;
}
