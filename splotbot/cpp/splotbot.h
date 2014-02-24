#ifndef SPLOTBOT_H
#define SPLOTBOT_H

#include <stack>
#include <semaphore.h>
#include <mutex>

#include "instructionbuffer.h"

using namespace std;

class Splotbot {
    public:
        Splotbot();
        void executeInstructions(int numberOfInstructions, int instructions[]);
        void run();

    private:
        InstructionBuffer buffer;
};

#endif
