#include <iostream>

#include "logger.h"

using namespace std;

string identifier;

Logger::Logger(string id){
    identifier = id;
    Start();
}

Logger::~Logger(){
    End();
}

int Logger::Write(void *data){
    char *d;
    d = (char*)data;
    cout << "Writing" << d << endl;
    return 0;
}

void Logger::Start() {
    cout << "Starting " << identifier << endl;
}

void Logger::End() {
    cout << "Ending" << endl;
}
