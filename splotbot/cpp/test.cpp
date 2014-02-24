#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include "libraries/cJSON/cJSON.h"

#include "splotbot.h"
//#include "singlesteppermotor.h"

using namespace std;

cJSON* getConfigDocument() {
    ifstream in("../basic_config.json");
    string contents(
            (istreambuf_iterator<char>(in)), 
            istreambuf_iterator<char>()
    );
    return cJSON_Parse(contents.c_str());
}

int main() {
    Splotbot splotbot;
    splotbot.run();

    // Create a SingleStepperMotor for testing JSON parsing
    cJSON *document = getConfigDocument();
    //SingleStepperMotor motor(document);

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
