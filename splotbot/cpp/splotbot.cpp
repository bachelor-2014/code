#include <thread>
#include "splotbot.h"

using namespace std;

Splotbot::Splotbot(void) {

}

void Splotbot::executeInstructions(int numberOfInstructions, int instructions[]) {
    buffer.pushInstructions(numberOfInstructions, instructions);
}

void Splotbot::run() {
    this_thread::sleep_for(chrono::milliseconds(1000));
    thread( [&] () {
        while (true) {
            int popped[1];
            buffer.popInstructions(1, popped);
            printf("Instr: %d\n", popped[0]);
        }
    }).detach();
}
