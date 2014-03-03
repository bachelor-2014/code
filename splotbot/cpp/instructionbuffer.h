#ifndef INSTRUCTIONBUFFER_H
#define INSTRUCTIONBUFFER_H

#include <queue>
#include <semaphore.h>
#include <mutex>

using namespace std;

/**
 * InstructionBuffer, threadsafe buffer used to hold instructions
 * pushInsturctions: push a set of instructions onto the buffer
 *      numberOfInstructions: number of instructions to push onto the buffer
 *      instructions: array containing instructions
 * popInstructions: pop a set of instructions from the buffer
 *      numberOfInstructions: number of instructions to pop from the buffer
 *      instructions: array to pop the instructions into
 */
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
