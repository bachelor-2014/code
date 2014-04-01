#include <iostream>
#include <fstream>
#include <vector>

#include "filelogger.h"
#include "logger.h"

using namespace std;

FileLogger::FileLogger(string identifier) : Logger<string>(identifier){
    filename = "data/"+identifier;

    dataOut.open(filename,ios::out | ios::app);
}

FileLogger::~FileLogger(){
    dataOut.close();
}
bool FileLogger::Write(string data){
    if(!dataOut.is_open()){
        dataOut.open(filename,ios::out | ios::app);
    }

    dataOut << data << endl;
    dataOut.close();
    return true;
}

vector<string> FileLogger::Read(){

    vector<string> *data = new vector<string>();

    ifstream dataIn(filename);

    string auxstring;
    while (std::getline(dataIn,auxstring)) {
        (*data).push_back(auxstring);
    }

    dataIn.close();

    return (*data);
}

bool FileLogger::Info(string data){
    string s = "Info: "+data;
    FileLogger::Write(s);
}

bool FileLogger::Error(string data){
    string s = "Error: "+data;
    FileLogger::Write(s);
}

bool FileLogger::Clear(){
    dataOut.close();
    dataOut.open(filename,ios::trunc);
    dataOut.close();
}
