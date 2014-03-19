#ifndef CAMERA_H
#define CAMERA_H 

#include <string>
#include "instructionbuffer.h"
#include "component.h"
#include "logging/videologger.h"

using namespace std;

/**
 * Camera Component class handles a system camera
 * Is constructed with the following variables:
 * name: Name of the camera
 * videoDevice: The video device id (eg. 0, 1 etc.)
 * eventName: Name of the event used by the camera to send images
 *
 * Use the registerActions(*actions) to register the actions performed by the camera:
 * Mode [1]: Sets the mode of the camera
 *
 * The Camera will automatically pull images on construction 
 */
class Camera: public Component {
    public:
        Camera(string name, int videoDevice, string eventName);
        void registerActions(vector<function<void(InstructionBuffer *)>> *actions);

    private:
        VideoLogger *video_logger;
        string name;
        int videoDevice;
        string eventName;
        void run();
};

#endif
