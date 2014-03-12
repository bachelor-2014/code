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
        bool Write(void*);

        /**
        * Oh c++. Header file and implementation cant be seperate when 
        * using templates. Gotta love that low-level
        */
        template<class T>
        T Read(){
            if(typeid(T) == typeid(string)){
                return readDataFromFile();
            }
        }
    private:
        string filename;
        string readDataFromFile();
};

#endif
