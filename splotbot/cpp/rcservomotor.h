#ifndef RCSERVO_H
#define RCSERVO_H 

#include <string>
#include "instructionbuffer.h"
#include "component.h"

using namespace std;

/**
 * RCServo Component class handles a single RC servo motor 
 * Is constructed with the following variables:
 * name: Name of the motor
 * device: The USB device of the servo controller
 * channel: The channel on the servo controller on which the motor is attached
 *
 * Use the registerActions(*actions) to register the actions performed by the RC servo motor:
 * SetTarget [1]: Moves the RC servo motor to the given target in degrees (0 to 90)
 */
class RCServoMotor: public Component {
    public:
        RCServoMotor(string name, string device, unsigned char channel);
        void registerActions(vector<function<void(InstructionBuffer *)>> *actions);
        int getPosition();
        int setPosition(unsigned short target);

    private:
        string name;
        string device;
        unsigned char channel;
        int openDeviceFile();
};

#endif
