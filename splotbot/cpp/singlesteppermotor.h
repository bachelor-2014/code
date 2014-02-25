#ifndef SINGLESTEPPERMOTOR_H
#define SINGLESTEPPERMOTOR_H 

#include <string>
#include "instructionbuffer.h"
#include "component.h"

using namespace std;

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
