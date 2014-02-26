#ifndef CAMERA_H
#define CAMERA_H 

#include <string>
#include "instructionbuffer.h"
#include "component.h"

using namespace std;

class Camera: public Component {
    public:
        Camera(string name, int videoDevice, string eventName);
        void registerActions(vector<function<void(InstructionBuffer *)>> *actions);

    private:
        string name;
        int videoDevice;
        string eventName;
};

#endif
