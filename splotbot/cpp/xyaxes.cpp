#include <iostream>
#include <sstream>

#include "xyaxes.h"
#include "mendel.h"

using namespace std;

/**
 * SingleStepperMotor constructor
 */
XYAxes::XYAxes(string name, char xPort, char yPort): name(name), 
    xPort(xPort), yPort(yPort) {
    //Empty constructor
}

/**
 * registerActions register the actions of the single stepper motor
 */
void XYAxes::registerActions(vector<function<void(InstructionBuffer *)>> 
        *actions) {
    cout << "XYAxes (" << name << ") registering actions" << endl;

    // 'Move' <number of steps>
    function<void(InstructionBuffer *)> move = [&](InstructionBuffer *buffer) -> void {
        int instr[2];
        (*buffer).popInstructions(2, instr);
        int xSteps = instr[0];
        int ySteps = instr[1];

        stringstream ss;
        ss << "axis (" << name << ") moving (x,y)=(" << xSteps << "," << ySteps << ")" << endl;
        string s = ss.str();
        (*file_logger).Info(s);

        stringstream command;
        command << "G1 " << xPort << xSteps << " " << yPort << ySteps << endl;
        string c = command.str();
        runGCode(c);
    };

    (*actions).push_back(move);
}
