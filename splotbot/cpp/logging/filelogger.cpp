#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#include "filelogger.h"
#include "logger.h"

using namespace std;

FileLogger::FileLogger(string componentType, string componentName) : Logger<string> (){
    this->componentType = componentType;
    this->componentName = componentName;

    filename = this->directory + "data.csv";

    dataOut = new ofstream();
    dataOut->open(filename,ios::out | ios::app);
}

FileLogger::~FileLogger(){
    dataOut->close();
}

vector<Entry<string>> FileLogger::Read(){};

bool FileLogger::Write(Entry<string> entry){

    if(!dataOut->is_open()){
        dataOut->open(filename,ios::out | ios::app);
    }

    string l = this->identifier(entry);
    (*dataOut) << l << endl;


    return true;
};

bool FileLogger::Info(string data){

	Entry<string> e = this->entry();
	e.ActivityType = "info";
	e.Data = data;

	this->Write(e);
};
bool FileLogger::Error(string data){

	Entry<string> e = this->entry();
	e.ActivityType = "error";
	e.Data = data;

	this->Write(e);
};
bool FileLogger::Data(string data){

	Entry<string> e = this->entry();
	e.ActivityType = "data";
	e.Data = data;

	this->Write(e);
};

string FileLogger::identifier(Entry<string> entry){
	return to_string(entry.Timestamp)+","+entry.ComponentType+","+entry.ComponentName+","+entry.ActivityType+","+entry.Data;
}

Entry<string> FileLogger::entry(){

	const double timestamp = double(clock()) / CLOCKS_PER_SEC;

	Entry<string> entry(timestamp,this->componentType,
			this->componentName,"","");

	return entry;
}

bool FileLogger::Clear(){
    dataOut->close();
    dataOut->open(filename,ios::trunc);
    dataOut->close();
}

//bool FileLogger::Write(string filename,string data){
//    if(!dataOut.is_open()){
//        dataOut.open(filename,ios::out | ios::app);
//    }
//
//    dataOut << data << endl;
//    dataOut.close();
//    return true;
//}
//
//vector<string> FileLogger::Read(){
//
//    vector<string> *data = new vector<string>();
//
//    ifstream dataIn(filename);
//
//    string auxstring;
//    while (std::getline(dataIn,auxstring)) {
//        (*data).push_back(auxstring);
//    }
//
//    dataIn.close();
//
//    return (*data);
//}
//
//bool FileLogger::Info(string data){
//    string s = "Info: "+data;
//    FileLogger::Write(s);
//}
//
//bool FileLogger::Error(string data){
//    string s = "Error: "+data;
//    FileLogger::Write(s);
//}
//
