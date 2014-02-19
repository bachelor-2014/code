#include <thread>
#include "splotbot.h"

using namespace std;

Splotbot::Splotbot(void) {
    sem_init(&bufferCount, 0, 0);
}

void Splotbot::executeInstructions(int numberOfInstructions, int instructions[]) {
    // Add the instructions to the buffer
    lock.lock();
    for (int i = 0; i < numberOfInstructions; i++) {
        buffer.push(instructions[i]);
        sem_post(&bufferCount);
    }
    lock.unlock();
}

void Splotbot::run() {
    thread( [&] () {
        while (true) {
            sem_wait(&bufferCount);
            lock.lock();
            int instr = buffer.top();
            buffer.pop();
            lock.unlock();
            printf("Instr: %d\n", instr);
        }
    }).detach();
}
