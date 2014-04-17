#ifndef CAMERACALIBRATOR_H
#define CAMERACALIBRATOR_H 

#include <string>
#include "instructionbuffer.h"
#include "component.h"
#include "camera.h"
#include "xyaxes.h"

using namespace std;

/**
 */
class CameraCalibrator: public Component {
    public:
        CameraCalibrator(string name,Camera *camera,XYAxes *xyaxes);
        void registerActions(vector<function<void(InstructionBuffer *)>> *actions);
};

#endif
