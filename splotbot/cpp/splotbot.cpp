#include <iostream>
#include <thread>
#include "splotbot.h"
#include "utils/threading.h"

using namespace std;

/**
 * Splotbot constructor
 */
Splotbot::Splotbot(string configFile, string mendelSocket) {
    cout << "Splotbot starting with " << endl << "config: " << configFile << endl << "Mendel socket: " << mendelSocket << endl;
    // Register empty callback
    registerCallback([] (string name, string data) -> void {
        cout << "Default callback. You need to provide a better one." << endl;
    });

    components = initializeComponents(&eventCallback);

    cout << "Number of components in Splotbot: " << components.size() << endl;

    for (auto it = components.begin(); it != components.end(); ++it) {
        Component *c = *it;
        (*c).registerActions(&actions);
    }

    cout << "Number of actions registered: " << actions.size() << endl;
}

/**
 * executeInstructions exectures a list of instructions
 */
void Splotbot::executeInstructions(int numberOfInstructions, int instructions[]) {
    buffer.pushInstructions(numberOfInstructions, instructions);
}

/**
 * registerCallback registeres an event callback
 */
void Splotbot::registerCallback(function<void(string,string)> callback) {
    eventCallback = callback;
}

/**
 * run starts the Splotbot
 */
void Splotbot::run() {
    runAsThread( [&] () {
        while (true) {
            int popped[1];
            buffer.popInstructions(1, popped);
            int action = popped[0];

            actions[action](&buffer);
        }
    });
}
