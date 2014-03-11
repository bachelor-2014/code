#ifndef LOGGER_H
#define LOGGER_H

#include <string>

using namespace std;

class Logger {
    public:
        Logger(string identifier);
        ~Logger();
        int Write(void*);
        int Read(void*);
    protected:
        string identifier;
    private:
        void Start();
        void End();
};

#endif
