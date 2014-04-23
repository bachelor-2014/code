#include <iostream>
#include <unistd.h>

#include "cameracalibrator.h"
#include "computer_vision/computervisionutils.h"
#include "utils/errors.h"

using namespace std;
using namespace cv;

/**
 * Camera constructor
 */
CameraCalibrator::CameraCalibrator(string name,Camera *camera,XYAxes *xyaxes): camera(camera), xyaxes(xyaxes) {
    cout    << "Instantiating calibrator " << name << " With camera "
            << camera->name << " and xyaxes " << xyaxes->name << endl;

    this->name = name;
    calibrator = new Calibrator("data/calibration.xml");
}

/**
 * registerActions registeres the actions of the Camera unto an actions buffer
 */
void CameraCalibrator::registerActions(vector<function<void(InstructionBuffer *)>> *actions) {

    // 'Calibrate'
    function<void(InstructionBuffer *)> calibrate = [&](InstructionBuffer *buffer) -> void {
        this->calibrate();
    };

    // 'Recalibrate'
    function<void(InstructionBuffer *)> recalibrate = [&](InstructionBuffer *buffer) -> void {
        this->recalibrate();
    };

    (*actions).push_back(calibrate);
    (*actions).push_back(recalibrate);
}

void CameraCalibrator::calibrate(){
    vector<cv::Mat> images;

    cv::Mat coefs;
    cv::Mat matrix;

    if (calibrator->isCalibrated()) {
        cout << "CameraCalibrator: Camera already calibrated" << endl;
        calibrator->getCalibrationFromFile(&coefs,&matrix,&(camera->xStep), &(camera->yStep));
        camera->calibrate(coefs, matrix);
        (*eventCallback)(name, "success");
        return;
    }

    cout << "CameraCalibrator: Camera not already calibrated" << endl;
        
    int centerX = xyaxes->positionX();
    int centerY = xyaxes->positionY();

    vector<cv::Mat> calibrationImages;
    cv::Mat image;

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            cout << "Moving to (x,y)=(" << centerX+x << "," << centerY+y << ")" << endl;
            // Move to the position
            xyaxes->move(centerX+x, centerY+y);

            // Sleep before grabbing the image, allowing the camera to settle
            sleep(1);

            image = camera->grabImage();

            stringstream fs;
            fs << "data/images/grab" << centerX+x << "_" << centerY+y << ".jpg";
            cv::imwrite(fs.str(), image);

            calibrationImages.push_back(image);
        }
    }

    //cap.release();
    bool success = calibrator->calibrate(calibrationImages,&coefs,&matrix);
    if(!success){
        throw ComponentException(this,"Could not calibrate");
    }
    camera->calibrate(coefs, matrix);

    cout << "Calibrated" << endl;


    //Step calibration

    cout << "Initiate Step calibration" << endl;
    vector<cv::Mat> stepImages;

    xyaxes->move(centerX,centerY);
    sleep(1);
    stepImages.push_back(camera->grabImage());

    xyaxes->move(centerX+1,centerY);
    sleep(1);
    stepImages.push_back(camera->grabImage());

    xyaxes->move(centerX,centerY+1);
    sleep(1);
    stepImages.push_back(camera->grabImage());

    calibrator->stepCalibrate(stepImages, &(camera->xStep), &(camera->yStep));
    cout << "Step calibration done" << endl;

    (*eventCallback)(name, "success");
}

void CameraCalibrator::recalibrate(){
    calibrator->unCalibrate(camera);
    this->calibrate();
}
