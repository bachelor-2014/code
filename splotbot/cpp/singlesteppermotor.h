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
 * gpioMode1:
 * gpioMode2:
 * gpioStep:
 * gpioSleep:
 *
 * Use the registerActions(*actions) to register the actions performed by the stepper motor:
 * Move [1]: Moves the motor (Takes negative and positive values for each dirrection)
 */
class SingleStepperMotor: public Component {
    public:
        SingleStepperMotor(string name, string gpioMode1, string gpioMode2, string gpioStep, string gpioSleep);
        void registerActions(vector<function<void(InstructionBuffer *)>> *actions);

    private:
        string name;
        string gpioMode1;
        string gpioMode2;
        string gpioStep;
        string gpioSleep;
};

#endif
