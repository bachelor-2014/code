#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <typeinfo>

using namespace std;

class Logger {
    public:
        Logger(string identifier);
        ~Logger();

        template<class T>
        bool Write(T t);

        template<class T>
        T Read();

        bool Clear();

    protected:
        string identifier;
};

#endif
