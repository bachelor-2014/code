#ifndef SPLOTBOT_H
#define SPLOTBOT_H

#include <stack>
#include <semaphore.h>
#include <mutex>

using namespace std;

class Splotbot {
    public:
        Splotbot();
        void executeInstructions(int numberOfInstructions, int instructions[]);
        void run();

    private:
        stack<int> buffer;
        sem_t bufferCount;
        mutex lock;
};

#endif
