#ifndef SPLOTBOT_H
#define SPLOTBOT_H

#include <stack>
#include <semaphore.h>
#include <mutex>
#include <vector>

#include "instructionbuffer.h"
#include "component.h"
#include "componentinitializer.h"

using namespace std;

class Splotbot {
    public:
        Splotbot();
        void executeInstructions(int numberOfInstructions, int instructions[]);
        void run();

    private:
        InstructionBuffer buffer;
        vector<Component *> components;
        vector<function<void(InstructionBuffer *)>> actions;
};

#endif
