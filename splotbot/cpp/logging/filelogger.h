#ifndef FILELOGGER_H
#define FILELOGGER_H

#include <iostream>
#include <fstream>
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

            string* outstr = new string;

            ifstream dataIn(filename);

            string auxstring;
            while (std::getline(dataIn,auxstring)) {
                (*outstr).append(auxstring);
            }

            dataIn.close();
            return *outstr;
        }
        //typedef bool Read (void*);
    private:
        string filename;
};

#endif
