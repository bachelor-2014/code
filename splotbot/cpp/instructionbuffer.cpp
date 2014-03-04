#include <thread>
#include "splotbot.h"

using namespace std;

/**
 * Constructor for the buffer
 */
InstructionBuffer::InstructionBuffer(void) {
    sem_init(&bufferCount, 0, 0);
}

/**
 * pushInstructions: push instructions onto the buffer
 */
void InstructionBuffer::pushInstructions(int numberOfInstructions, int instructions[]) {
    lock.lock();
    //Push instructions
    for (int i = 0; i < numberOfInstructions; i++) {
        buffer.push(instructions[i]);
        sem_post(&bufferCount);
    }
    lock.unlock();
}

/**
 * popInstructions: pop instructions from the buffer
 */
void InstructionBuffer::popInstructions(int numberOfInstructions, int instructions[]) {
    for (int i = 0; i < numberOfInstructions; i++) {
        sem_wait(&bufferCount);
        lock.lock();

        //Pop instruction
        instructions[i] = buffer.front();
        buffer.pop();

        lock.unlock();
    }
}
