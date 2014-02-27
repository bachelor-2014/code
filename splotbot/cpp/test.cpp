#include <iostream>
#include <chrono>
#include <thread>
#include <string>

#include "splotbot.h"
#include "singlesteppermotor.h"

using namespace std;

int main() {
    Splotbot splotbot;
    splotbot.run();

    splotbot.registerCallback([] (string name, string data) -> void {
        cout << "Callback '" << name << "': " << data << endl;
    });

    // Execute some instructions
    int numberOfInstructions;
    int instruction;

    scanf("%d", &numberOfInstructions);

    int instructions[numberOfInstructions];
    for (int i = 0; i < numberOfInstructions; i++) {
        scanf("%d", &instruction);
        instructions[i] = instruction;
    }

    splotbot.executeInstructions(numberOfInstructions, instructions);

    this_thread::sleep_for(chrono::milliseconds(2000));

    return 0;
}
