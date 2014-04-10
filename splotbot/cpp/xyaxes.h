#ifndef XYAxes_H
#define XYAxes_H 

#include <string>
#include "instructionbuffer.h"
#include "component.h"

using namespace std;

/**
 * Is constructed with the following variables:
 * name: Name of the motor
 * axis: the axis that is controlled (x,y,z,e)
 *
 * Use the registerActions(*actions) to register the actions performed
 * Move [1]: Moves the axis (Takes negative and positive values 
 * for each direction)
 */
class XYAxes: public Component {
    public:
        XYAxes(string name, string xPort, string yPort, string xLimitSwitchPort, string yLimitSwitchPort, int xStepLimit, int yStepLimit);
        void registerActions(vector<function<void(InstructionBuffer *)>> *actions);
        void home();
        void move(int xPosition, int yPosition);

    private:
        string xPort;
        string yPort;
        string xLimitSwitchPort;
        string yLimitSwitchPort;

        int xStepLimit;
        int yStepLimit;

        int currentPositionX;
        int currentPositionY;
};

#endif
