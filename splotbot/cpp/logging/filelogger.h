#ifndef FILELOGGER_H
#define FILELOGGER_H

#include <iostream>
#include <fstream>
#include "logger.h"

using namespace std;

class FileLogger : private Logger{

    public:
        FileLogger(string);
        ~FileLogger();
        bool Write(void*);

        template<class T>
        T Read(){

            string* outstr = new string;

            ifstream dataIn(filename);

            string auxstring;
            while (std::getline(dataIn,auxstring)) {
                (*outstr).append(auxstring);
            }

            cout << *outstr << endl;
            dataIn.close();
            //*outstr = "JOHN";
            //static_cast<void*>(outstr);
            //char* output = (char*)outstr.c_str();
            //static_cast<void*>(outstr);
            return *outstr; //"strrrring beijiinG";
        }
        //typedef bool Read (void*);
    private:
        string filename;
};

#endif
