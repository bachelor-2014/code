#ifndef INSTRUCTIONBUFFER_H
#define INSTRUCTIONBUFFER_H

#include <queue>
#include <semaphore.h>
#include <mutex>

using namespace std;

class InstructionBuffer {
    public:
        InstructionBuffer();
        void pushInstructions(int numberOfInstructions, int instructions[]);
        void popInstructions(int numberOfInstructions, int instructions[]);

    private:
        queue<int> buffer;
        sem_t bufferCount;
        mutex lock;
};

#endif
