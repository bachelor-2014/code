#include <iostream>
#include <sstream>

#include "singlesteppermotor.h"

using namespace std;

/**
 * RCServoMotor constructor
 */
RCServoMotor::RCServoMotor(string name, int channel): name(name), channel(channel) {
    //Empty constructor
}

/**
 * registerActions register the actions of the single stepper motor
 */
void RCServoMotor::registerActions(vector<function<void(InstructionBuffer *)>> *actions) {
    cout << "RCServoMotor (" << name << ") registering actions" << endl;

    // 'SetTarget' <target in degrees>
    function<void(InstructionBuffer *)> setTarget = [&](InstructionBuffer *buffer) -> void {
        int instr[1];
        (*buffer).popInstructions(1, instr);
        int target = instr[0];

        stringstream ss;
        ss << "RCServoMotor (" << name << ") setting target to " << target << endl;
        string s = ss.str();
        (*file_logger).Info(s);
    };

    (*actions).push_back(setTarget);
}
