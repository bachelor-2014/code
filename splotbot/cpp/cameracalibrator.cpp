#include <iostream>
#include <unistd.h>

#include "cameracalibrator.h"
#include "computer_vision/computervisionutils.h"
#include "utils/errors.h"
#include "rucolang/compileargs.h"

using namespace std;
using namespace cv;

/**
 * Camera constructor
 */
CameraCalibrator::CameraCalibrator(string name,Camera *camera,XYAxes *xyaxes): camera(camera), xyaxes(xyaxes) {
    this->name = name;
    calibrator = new Calibrator("data/calibration.xml");
}

/**
 * registerActions registeres the actions of the Camera unto an actions buffer
 */
void CameraCalibrator::registerActions(vector<function<void(InstructionBuffer *)>> *actions) {
    stringstream ss;
    ss << "Registering actions" << endl;
    string s = ss.str();
    (*file_logger).Info(s);

    // 'Calibrate'
    function<void(InstructionBuffer *)> calibrate = [&](InstructionBuffer *buffer) -> void {
        stringstream ss;
        ss << "Calibrating" << endl;
        string s = ss.str();
        (*file_logger).Info(s);

        this->calibrate();
    };

    // 'Recalibrate'
    function<void(InstructionBuffer *)> recalibrate = [&](InstructionBuffer *buffer) -> void {
        stringstream ss;
        ss << "Recalibrating" << endl;
        string s = ss.str();
        (*file_logger).Info(s);

        this->recalibrate();
    };

    (*actions).push_back(calibrate);
    (*actions).push_back(recalibrate);
}

void CameraCalibrator::registerEvents(map<string,int> *eventArgs){
    (*eventArgs)[name] = 0; 
}

void CameraCalibrator::calibrate(){
    vector<cv::Mat> images;

    cv::Mat coefs;
    cv::Mat matrix;

    vector<int> args;

    if (calibrator->isCalibrated()) {
        calibrator->getCalibrationFromFile(&coefs,&matrix,&(camera->xStep), &(camera->yStep));
        camera->calibrate(coefs, matrix);
        (*eventCallback)(name, "success", args);
        return;
    }

    int centerX = xyaxes->positionX();
    int centerY = xyaxes->positionY();

    vector<cv::Mat> calibrationImages;
    cv::Mat image;

    // Stop the camera
    int cameraMode = camera->getMode();
    if (cameraMode > 0) {
        camera->stop();
    }

    // Make the camera open the video device as a resource
    // of this thread
    camera->openVideoDevice();

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
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

    bool success = calibrator->calibrate(calibrationImages,&coefs,&matrix);
    if(!success){
        throw ComponentException(this, "Failed to calibrate");
    }
    camera->calibrate(coefs, matrix);

    //Step calibration
    vector<vector<cv::Mat>> allStepImages;
    int stepTimes = 3;
    for(int i = 0; i < stepTimes; i++){
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

        xyaxes->move(centerX,centerY);
        sleep(1);

        allStepImages.push_back(stepImages);
    }


    try {
        calibrator->stepCalibrate(allStepImages, &(camera->xStep), &(camera->yStep));
    } catch(ComponentException& e){
        // Reset the position
        xyaxes->move(centerX, centerY);

        // Close the video device in this thread
        camera->closeVideoDevice();

        // Restart the camera
        if (cameraMode > 0) {
            camera->start();
        }

        throw;
    } catch(exception& e){
        // Reset the position
        xyaxes->move(centerX, centerY);

        // Close the video device in this thread
        camera->closeVideoDevice();

        // Restart the camera
        if (cameraMode > 0) {
            camera->start();
        }

        throw;
    }

    (*eventCallback)(name, "success", args);

    // Reset the position
    xyaxes->move(centerX, centerY);

    // Close the video device in this thread
    camera->closeVideoDevice();

    // Restart the camera
    if (cameraMode > 0) {
        camera->start();
    }
}

void CameraCalibrator::registerCalls(map<string, map<string,Rucola::CompileArgs>> *componentCalls, int start){
    stringstream ss;
    ss << "Registering calls" << endl;
    string s = ss.str();
    (*file_logger).Info(s);

    Rucola::CompileArgs calibrateCall;
    calibrateCall.Action = start+1;
    calibrateCall.NumberofArguments = 0;

    Rucola::CompileArgs recalibrateCall;
    recalibrateCall.Action = start+2;
    recalibrateCall.NumberofArguments = 0;

    (*componentCalls)[name]["calibrate"] = calibrateCall; 
    (*componentCalls)[name]["recalibrate"] = recalibrateCall; 
}

void CameraCalibrator::recalibrate(){
    calibrator->unCalibrate(camera);
    this->calibrate();
}
