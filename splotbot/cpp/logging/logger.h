#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <typeinfo>
#include <vector>

using namespace std;

template <typename T>
class Logger {
    public:
        Logger(string identifier){};
        ~Logger(){};

        virtual bool Write(T t){
            cout << "hat" << endl;
        };

        virtual vector<T> Read(){};

        virtual bool Info(T t){};

        virtual bool Error(T t){};

        virtual bool Clear(){};

    protected:
        string identifier;
};

#endif
