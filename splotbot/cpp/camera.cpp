#include <iostream>

#include "camera.h"

using namespace std;

Camera::Camera(string name, int videoDevice, string eventName): name(name), videoDevice(videoDevice), eventName(eventName) {
    // Empty constructor
}

void Camera::registerActions(vector<function<void(InstructionBuffer *)>> *actions) {
    cout << "Camera (" << name << ") registering actions" << endl;

    // 'Set camera mode' <mode>
    function<void(InstructionBuffer *)> setMode = [&](InstructionBuffer *buffer) -> void {
        int instr[1];
        (*buffer).popInstructions(1, instr);
        int mode = instr[0];
        cout << "Camera (" << name << ") mode set to " << mode << endl;
        (*eventCallback)("Test name", "Test data");
    };

    (*actions).push_back(setMode);
}
