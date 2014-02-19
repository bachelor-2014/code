#include <thread>
#include "splotbot.h"

using namespace std;

Splotbot::Splotbot(void) {
    sem_init(&bufferCount, 0, 0);
}

void Splotbot::executeInstructions(int numberOfInstructions, int instructions[]) {
    // Add the instructions to the buffer
    printf("Exec: Waiting for lock ...\n");
    lock.lock();
    printf("Exec: Got lock ...\n");
    for (int i = 0; i < numberOfInstructions; i++) {
        buffer.push(instructions[i]);
        sem_post(&bufferCount);
    }
    lock.unlock();
    printf("Exec: Released lock ...\n");
}

void Splotbot::run() {
    this_thread::sleep_for(chrono::milliseconds(1000));
    thread( [&] () {
        while (true) {
            printf("Waiting for buffer ...\n");
            sem_wait(&bufferCount);
            printf("Got buffer ...\n");
            printf("Waiting for lock ...\n");
            lock.lock();
            printf("Got lock ...\n");
            int instr = buffer.top();
            buffer.pop();
            lock.unlock();
            printf("Released lock ...\n");
            printf("Instr: %d\n", instr);
        }
    }).detach();
}
