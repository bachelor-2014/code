#ifndef SINGLESTEPPERMOTOR_H
#define SINGLESTEPPERMOTOR_H 

#include <string>
#include "instructionbuffer.h"
#include "component.h"

using namespace std;

/**
 * SingleStepperMotor Component class handles a system single stepper motor
 * Is constructed with the following variables:
 * name: Name of the motor
 * axis: the axis that is controlled (x,y,z,e)
 *
 * Use the registerActions(*actions) to register the actions performed
 * Move [1]: Moves the axis (Takes negative and positive values 
 * for each direction)
 */
class XYAxis: public Component {
    public:
        XYAxis(string name, char axis);
        void registerActions(vector<function<void(InstructionBuffer *)>> *actions);

    private:
        string name;
        string axis;
};

#endif
