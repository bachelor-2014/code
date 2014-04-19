#include <iostream>
#include <unistd.h>

#include "cameracalibrator.h"

using namespace std;
using namespace cv;

/**
 * Camera constructor
 */
CameraCalibrator::CameraCalibrator(string name,Camera *camera,XYAxes *xyaxes):camera(camera),xyaxes(xyaxes) {
    cout    << "Instantiating calibrator " << name << " With camera "
            << camera->name << " and xyaxes " << xyaxes->name << endl;

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

    camera->stop();

    cv::Mat coefs;
    cv::Mat matrix;

    if (calibrator->isCalibrated()) {
        calibrator->getCalibrationFromFile(&coefs,&matrix);
        return;
    }
        
    int centerX = xyaxes->positionX();
    int centerY = xyaxes->positionY();

    vector<cv::Mat> calibrationImages;
    cv::VideoCapture cap(camera->videoDevice);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
    cv::Mat image;

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            cout << "Moving to (x,y)=(" << centerX+x << "," << centerY+y << ")" << endl;
            // Move to the position
            xyaxes->move(centerX+x, centerY+y);

            // Sleep before grabbing the image, allowing the camera to settle
            sleep(1);

            // Grab image
            bool success = cap.read(image);
            if (!success) {
                stringstream ss;
                ss << "CameraCalibrator failed to grab image from device " << camera->videoDevice;
                throw runtime_error(ss.str());
            }

stringstream fs;
fs << "data/images/grab" << centerX+x << "_" << centerY+y << ".jpg";
cv::imwrite(fs.str(), image);
            calibrationImages.push_back(image);
        }
    }

    cap.release();
    calibrator->calibrate(calibrationImages,&coefs,&matrix);
    cout << "Calibrated" << endl;

    camera->calibrate(coefs, matrix);
}

void CameraCalibrator::recalibrate(){
    calibrator->unCalibrate();
    this->calibrate();
}
