#include <iostream>
#include <sstream>
#include <unistd.h>

#include "xyaxes.h"
#include "mendel.h"

using namespace std;

/**
 * SingleStepperMotor constructor
 */
XYAxes::XYAxes(string name, string xPort, string yPort, string xLimitSwitchPort, string yLimitSwitchPort, int xStepLimit, int yStepLimit): 
    xPort(xPort), yPort(yPort),
    xLimitSwitchPort(xLimitSwitchPort),
    yLimitSwitchPort(yLimitSwitchPort), xStepLimit(xStepLimit),
    yStepLimit(yStepLimit){

    this->name = name;

    // Initialize the current position
    currentPositionX = 0;
    currentPositionY = 0;

    cout << "xLimit" << xStepLimit << endl;
    cout << "yLimit" << yStepLimit << endl;
    runGCode("G91");
}

/*
 * Checks whether the limit switch at the given port (J9-14) is pressed
 */
bool isLimitSwitchPressed(string switchPort) {
    int gpio;
    
    if (switchPort == "J9") {
        gpio = 69;
    } else if (switchPort.compare("J10") == 0) {
        gpio = 67;
    } else if (switchPort.compare("J11") == 0) {
        gpio = 26;
    } else if (switchPort.compare("J12") == 0) {
        gpio = 68;
    } else if (switchPort.compare("J13") == 0) {
        gpio = 33;
    } else if (switchPort.compare("J14") == 0) {
        gpio = 27;
    } else {
        throw runtime_error("Unknown switch connector: Can not read the switch value.");
    }

    stringstream pathStream;
    pathStream << "/sys/class/gpio/gpio" << gpio << "/value";

    int result;

    ifstream gpioFile(pathStream.str());
    gpioFile >> result;
    gpioFile.close();

    return result == 1;
}

/**
 * registerActions register the actions of the single stepper motor
 */
void XYAxes::registerActions(vector<function<void(InstructionBuffer *)>> 
        *actions) {
    cout << "XYAxes (" << name << ") registering actions" << endl;

    // 'Home'
    function<void(InstructionBuffer *)> home = [&](InstructionBuffer *buffer) -> void {
        // Log the action
        stringstream ss;
        ss << "XYAxes (" << name << ") homing" << endl;
        string s = ss.str();
        (*file_logger).Info(s);

        // Do the homing
        bool xHomed = false;
        bool yHomed = false;

        bool xPressed, yPressed;
        int xMove, yMove;

        // Send the move command
        runGCode("G91");
        while (true) {
            // Get whether or not the limit switches / end stops are pressed
            xPressed = isLimitSwitchPressed(xLimitSwitchPort);
            yPressed = isLimitSwitchPressed(yLimitSwitchPort);
            
            // If not pressed and not homed already, move a single step
            xMove = !xPressed && !xHomed ? -1 : 0;
            yMove = !yPressed && !yHomed ? -1 : 0;
            
            // Else if an axis is not homed, but the limit switch is pressed,
            // move a step back and consider the axis homed
            if (xPressed && !xHomed) {
                xMove = 1;
                xHomed = true;
                
            }
            if (yPressed && !yHomed) {
                yMove = 1;
                yHomed = true;
            }

            stringstream command;
            command << "G1 " << xPort << xMove << " " << yPort << yMove << endl;
            string c = command.str();
            runGCode(c);
            
            // If both axes are homed, stop the loop
            if (xHomed && yHomed) {
                break;
            }

            // Wait before continuing
            //TODO shorter wait time
            sleep(1);
        }

        // Reset the current position
        currentPositionX = 0;
        currentPositionY = 0;
    };

    // 'Move' <x position> <y position>
    function<void(InstructionBuffer *)> move = [&](InstructionBuffer *buffer) -> void {
        int instr[2];
        (*buffer).popInstructions(2, instr);
        int xPosition = instr[0];
        int yPosition = instr[1];

        xPosition = xPosition < 0 ? 0 : xPosition;
        yPosition = yPosition < 0 ? 0 : yPosition;

        xPosition = xPosition > xStepLimit ? xStepLimit : xPosition;
        yPosition = yPosition > yStepLimit ? yStepLimit : yPosition;

        int xSteps = xPosition - currentPositionX;
        int ySteps = yPosition - currentPositionY;

        currentPositionX = xPosition;
        currentPositionY = yPosition;

        stringstream ss;
        ss << "XYAxes (" << name << ") moving (x,y)=(" << xSteps << "," << ySteps << ")" << endl;
        string s = ss.str();
        (*file_logger).Info(s);

        stringstream command;
        command << "G1 " << xPort << xSteps << " " << yPort << ySteps << endl;
        string c = command.str();
        runGCode(c);
    };

    (*actions).push_back(home);
    (*actions).push_back(move);
}
