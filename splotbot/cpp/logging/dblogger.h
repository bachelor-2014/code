#ifndef DBLOGGER_H
#define DBLOGGER_H

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <vector>
#include "logger.h"

using namespace std;

class DBLogger : public Logger{

    public:
        DBLogger(string);
        ~DBLogger();

        template<class T>
        bool Write(T t){
            if(typeid(T) == typeid(string)){
                return writeStringData(t);
            }
        }

        template<class T>
        vector<T> Read(){
            if(typeid(T) == typeid(string)){
                return readStringData();
            }
        }

    private:
        bool writeStringData(string);
        vector<string> readStringData();
};

#endif
