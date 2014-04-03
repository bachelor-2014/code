#include <iostream>
#include <sstream>

#include "xyaxis.h"
#include "mendel.h"

using namespace std;

/**
 * SingleStepperMotor constructor
 */
XYAxis::XYAxis(string name, char axis): name(name), axis(axis) {
    //Empty constructor
}

/**
 * registerActions register the actions of the single stepper motor
 */
void XYAxis::registerActions(vector<function<void(InstructionBuffer *)>> 
        *actions) {
    cout << "XYAxis (" << name << ") registering actions" << endl;

    // 'Move' <number of steps>
    function<void(InstructionBuffer *)> move = [&](InstructionBuffer *buffer) -> void {
        int instr[1];
        (*buffer).popInstructions(1, instr);
        int steps = instr[0];

        stringstream ss;
        ss << "axis (" << axis << ") moving " << steps << "steps" << endl;
        string s = ss.str();
        (*file_logger).Info(s);

        stringstream command;
        command << axis << steps << endl;
        string s = ss.str();
        runGCode(s);
    };

    (*actions).push_back(move);
}
