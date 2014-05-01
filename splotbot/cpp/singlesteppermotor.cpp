#include <iostream>
#include <sstream>

#include "singlesteppermotor.h"

using namespace std;

/**
 * SingleStepperMotor constructor
 */
SingleStepperMotor::SingleStepperMotor(string name, string gpioMode1, string gpioMode2, string gpioStep, string gpioSleep): gpioMode1(gpioMode1), gpioMode2(gpioMode2), gpioStep(gpioStep), gpioSleep(gpioSleep) {
    this->name = name;

    this->fileLogger = new FileLogger("SingleStepperMotor",name);
}

/**
 * registerActions register the actions of the single stepper motor
 */
void SingleStepperMotor::registerActions(vector<function<void(InstructionBuffer *)>> *actions) {
    cout << "SingleStepperMotor (" << name << ") registering actions" << endl;

    // 'Move' <number of steps>
    function<void(InstructionBuffer *)> move = [&](InstructionBuffer *buffer) -> void {
        int instr[1];
        (*buffer).popInstructions(1, instr);
        int steps = instr[0];

        stringstream ss;
        ss << "SingleStepperMotor (" << name << ") moving " << steps << " steps" << endl;
        string s = ss.str();
        (*fileLogger).Info(s);
    };

    (*actions).push_back(move);
}
