#ifndef XYAxes_H
#define XYAxes_H 

#include <string>
#include "instructionbuffer.h"
#include "component.h"
#include "mendel.h"

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
        XYAxes(string name, string xPort, string yPort, string xLimitSwitchPort, string yLimitSwitchPort, int xStepLimit, int yStepLimit, string mendelSocket);
        void registerActions(vector<function<void(InstructionBuffer *)>> *actions);
        void registerCalls(map<string,map<string,Rucola::CompileArgs>>
                *componentCalls, int start);
        void home();
        void move(int xPosition, int yPosition);

        // Current position
        int positionX();
        int positionY();

    private:
        string xPort;
        string yPort;
        string xLimitSwitchPort;
        string yLimitSwitchPort;

        int xStepLimit;
        int yStepLimit;

        int currentPositionX;
        int currentPositionY;

        Mendel *mendel;

        bool isLimitSwitchPressed(string switchPort);
};

#endif
