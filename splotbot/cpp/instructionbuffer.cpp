#include <thread>
#include "splotbot.h"

using namespace std;

InstructionBuffer::InstructionBuffer(void) {
    sem_init(&bufferCount, 0, 0);
}

void InstructionBuffer::pushInstructions(int numberOfInstructions, int instructions[]) {
    lock.lock();
    for (int i = 0; i < numberOfInstructions; i++) {
        buffer.push(instructions[i]);
        sem_post(&bufferCount);
    }
    lock.unlock();
}

void InstructionBuffer::popInstructions(int numberOfInstructions, int instructions[]) {
    for (int i = 0; i < numberOfInstructions; i++) {
        sem_wait(&bufferCount);
        lock.lock();
        instructions[i] = buffer.front();
        buffer.pop();
        lock.unlock();
    }
}
