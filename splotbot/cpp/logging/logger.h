#ifndef LOGGER_H
#define LOGGER_H

#include <string>

using namespace std;

class Logger {
    public:
        Logger(string identifier);
        ~Logger();
        bool Write(void*);
        template<class T>
        T Read();
        //typedef bool Read (void*);
    protected:
        string identifier;
    private:
        void Start();
        void End();
};

#endif
