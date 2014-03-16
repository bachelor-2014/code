#include <iostream>
#include <fstream>

#include "filelogger.h"

using namespace std;

ofstream dataOut;
string filename;

FileLogger::FileLogger(string identifier) : Logger(identifier){
    filename = "data/"+identifier;

    dataOut.open(filename,ios::out | ios::trunc);
    dataOut.close();
}

FileLogger::~FileLogger(){
}

bool FileLogger::writeStringData(string data){
    if(!dataOut.is_open()){
        dataOut.open(filename,ios::out | ios::app);
    }

    dataOut << data << endl;
    dataOut.close();
    return 0;
}

string FileLogger::readStringData(){
    string* outstr = new string;

    ifstream dataIn(filename);

    string auxstring;
    while (std::getline(dataIn,auxstring)) {
        (*outstr).append(auxstring);
    }

    dataIn.close();
    return *outstr;
}

bool FileLogger::infoStringData(string data){
    string s = "Info: "+data;
    writeStringData(s);
}

bool FileLogger::errorStringData(string data){
    string s = "Error: "+data;
    writeStringData(s);
}
