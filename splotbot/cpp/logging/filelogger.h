#ifndef FILELOGGER_H
#define FILELOGGER_H

#include <iostream>
#include <fstream>
#include <typeinfo>
#include "logger.h"

using namespace std;

class FileLogger : public Logger{

    public:
        FileLogger(string);
        ~FileLogger();

        template<class T>
        bool Write(T t){
            if(typeid(T) == typeid(string)){
                return writeStringData(t);
            }
        }

        template<class T>
        T Read(){
            if(typeid(T) == typeid(string)){
                return readStringData();
            }
        }

        template<class T>
        bool Info(T t){
            if(typeid(T) == typeid(string)){
                return infoStringData(t);
            }
        }

        template<class T>
        bool Error(T t){
            if(typeid(T) == typeid(string)){
                return errorStringData(t);
            }
        }

    private:
        string filename;
        string readStringData();
        bool writeStringData(string);
        bool infoStringData(string);
        bool errorStringData(string);
};

#endif
