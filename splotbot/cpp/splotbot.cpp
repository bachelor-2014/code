#include <iostream>
#include <thread>
#include "splotbot.h"

using namespace std;

Splotbot::Splotbot(void) {
    components = initializeComponents();

    cout << "Number of components in Splotbot: " << components.size() << endl;

    for (vector<Component *>::iterator it = components.begin(); it != components.end(); ++it) {
        Component *c = *it;
        (*c).registerActions(&actions);
    }

    cout << "Number of actions registered: " << actions.size() << endl;
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
            int action = popped[0];

            actions[action](&buffer);
        }
    }).detach();
}
