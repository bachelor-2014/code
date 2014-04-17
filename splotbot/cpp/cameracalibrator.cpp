#include <iostream>
#include <unistd.h>

#include "cameracalibrator.h"

using namespace std;
using namespace cv;

/**
 * Camera constructor
 */
CameraCalibrator::CameraCalibrator(string name,Camera *camera,XYAxes *xyaxes) {}

/**
 * registerActions registeres the actions of the Camera unto an actions buffer
 */
void CameraCalibrator::registerActions(vector<function<void(InstructionBuffer *)>> *actions) {

    function<void(InstructionBuffer *)> calibrate = [&](InstructionBuffer *buffer) -> void {
    };

    (*actions).push_back(calibrate);
}
