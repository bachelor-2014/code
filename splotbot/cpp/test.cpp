#include <iostream>
#include <chrono>
#include <thread>
#include <string>

#include "splotbot.h"
#include "singlesteppermotor.h"

using namespace std;

/**
 * Test Program
 * Used to test the splotbot implementation
 */
int main() {
    //Start splotbot
    Splotbot splotbot;
    splotbot.run();

    //Register a test callback to print
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
