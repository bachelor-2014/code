#ifndef SPLOTBOT_H
#define SPLOTBOT_H

#include <stack>
#include <semaphore.h>
#include <mutex>
#include <vector>
#include <string>

#include "instructionbuffer.h"
#include "component.h"
#include "componentinitializer.h"

using namespace std;

class Splotbot {
    public:
        Splotbot();
        void executeInstructions(int numberOfInstructions, int instructions[]);
        void registerCallback(function<void(string,string)> callback);
        void run();

    private:
        InstructionBuffer buffer;
        vector<Component *> components;
        vector<function<void(InstructionBuffer *)>> actions;
        function<void(string,string)> eventCallback;
};

#endif
