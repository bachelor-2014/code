#include <iostream>
#include <unistd.h>
#include <stdexcept>

#include "camera.h"
#include "utils/errors.h"
#include "utils/base64.h"
#include <opencv2/opencv.hpp>
#include <thread>
#include "utils/threading.h"
#include "computer_vision/dropletdetector.h"
#include "computer_vision/computervisionutils.h"
#include <ctime>

using namespace std;
using namespace cv;

/**
 * Camera constructor
 */
Camera::Camera(string name, int videoDevice, string eventName): videoDevice(videoDevice), eventName(eventName) {
    this->name = name;
    setMode(0);
    tolerance = 20;
    isCalibrated = false;

    this->fileLogger = new FileLogger("Camera",name);

}

/**
 * registerActions registeres the actions of the Camera unto an actions buffer
 */
void Camera::registerActions(vector<function<void(InstructionBuffer *)>> *actions) {
    stringstream ss;
    ss << "Registering actions" << endl;
    string s = ss.str();
    (*fileLogger).Info(s);

    // 'Set camera mode' <mode>
    // Modes:
    // 0 - Camera Off
    // 1 - Camera On
    // 2 - Droplet detection
    function<void(InstructionBuffer *)> setCameraMode = [&](InstructionBuffer *buffer) -> void {
        // Get args 
        int instr[1];
        (*buffer).popInstructions(1, instr);

        // Log
        stringstream ss;
        ss << "Setting mode to " << instr[0] << endl;
        string s = ss.str();
        (*fileLogger).Info(s);

        cout << s << endl;

        // Do the action
        setMode(instr[0]);

        cout << "Camera mode successfully set" << endl;
    };

    // 'Set droplet variables' 
    // <min area> <max area> <structuring element size> <tolerance>
    function<void(InstructionBuffer *)> setDropletVariables = [&](InstructionBuffer *buffer) -> void {
        // Get args 
        int instr[4];
        (*buffer).popInstructions(4, instr);

        // Log
        stringstream ss;
        ss << "Setting droplet variables: minArea = " << instr[0] << ", maxArea = " << instr[1] << ", structuringElementSize = " << instr[2] << ", tolerance = " << instr[3] << endl;
        string s = ss.str();
        (*fileLogger).Info(s);

        // Do the action
        dropletdetector.minArea = instr[0];
        dropletdetector.maxArea = instr[1];
        dropletdetector.structuringElementSize = instr[2];
        tolerance = instr[3];

    };

    // 'End color selector' <x> <y>
    function<void(InstructionBuffer *)> dropletSelector = [&](InstructionBuffer *buffer) -> void {
        // Get args 
        int instr[2];
        (*buffer).popInstructions(2, instr);
        int x = instr[0];
        int y = instr[1];

        // Log
        stringstream ss;
        ss << "Setting droplet detection color interval based on image position (x, y) = (" << x << ", " << y << ")" << endl;
        string s = ss.str();
        (*fileLogger).Info(s);

        // Do the action
        Mat image = grabImage();
        dropletdetector.colorInterval =
            computeColorIntervalFromSelection(image, tolerance,x,y);
    };

    (*actions).push_back(setCameraMode);
    (*actions).push_back(dropletSelector);
    (*actions).push_back(setDropletVariables);
}

void Camera::registerCalls(map<string, map<string,Rucola::CompileArgs>> *componentCalls, int start){
    stringstream ss;
    ss << "Registering calls" << endl;
    string s = ss.str();
    (*fileLogger).Info(s);

    Rucola::CompileArgs mode;
    mode.Action = start+1;
    mode.NumberofArguments = 1;

    Rucola::CompileArgs dropletselect;
    dropletselect.Action = start+2;
    dropletselect.NumberofArguments = 2;

    Rucola::CompileArgs dropletvariables;
    dropletvariables.Action = start+3;
    dropletvariables.NumberofArguments = 4;

    (*componentCalls)[name]["mode"] = mode; 
    (*componentCalls)[name]["dropletselect"] = dropletselect; 
    (*componentCalls)[name]["dropletvariables"] = dropletvariables; 
}

/**
 * Sets the current camera mode
 */
void Camera::setMode(int m){
    if (mode == 0 && m > 0) {
        openVideoDevice();
        run();
    }
    mode = m;
}

/**
 * Gets the current camera mode
 */
int Camera::getMode() {
    return mode;
}

/**
 * Stops the camera, making it no longer grabbing new images
 */
void Camera::stop(){
    imagelock.lock();
    setMode(0);
    closeVideoDevice();
    //sleep(3);
}

/**
 * Starts the camera
 */
void Camera::start(){
    //Don't stop the droplet detection
    openVideoDevice();
    if(mode == 0){
        setMode(1);
    } else if (mode < 2) {
        setMode(1);
    }
    image.unlock();
}

/**
 * Opens the video device
 */
void Camera::openVideoDevice() {
    cap = new VideoCapture(videoDevice);

    cap->set(CV_CAP_PROP_FRAME_WIDTH, 320);
    cap->set(CV_CAP_PROP_FRAME_HEIGHT, 240);

    this->videoLogger = new VideoLogger("Camera",name,cap);
}

/**
 * Closes the video device
 */
void Camera::closeVideoDevice() {
    cap->release();
}

/**
 * Start the droplet detection
 */
void Camera::dropletDetection(){
    setMode(2);
}

/**
 * Grabs the current camera image
 */
Mat Camera::grabImage() {
    Mat image;

    //imagelock.lock();

    //VideoCapture cap(videoDevice);
    //cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    //cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

    bool success = cap->read(image); 

    //cap.release();

    if (!success) {
        throw ComponentException(this,"Camera: Failed to grab image");
    }

    if(isCalibrated){
        Mat imageClone = image.clone();
        cv::undistort(imageClone, image, matrix, coefs);
    }

    videoLogger->Data(&image);
    //newimage = image.clone();

    //imagelock.unlock();

    return image;
}

/**
 * The run functions
 * Starts the video capture device and pulls images
 */
void Camera::run() {
    runAsThread( [&] () {

        //cout << "Camera: Thread opening capture device ..." << endl;
        //VideoCapture cap(videoDevice);
        //cout << "Camera: Thread opened capture device" << endl;
        //cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
        //cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

        //cout << "Camera caps set" << endl;
        //video_logger = new VideoLogger("exp",&cap);

        DropletLog firstDropletLog;
        DropletLog secondDropletLog;
        clock_t timestamp;

        while (mode > 0) {
            //imagelock.lock();
            //bool success = cap.read(image); 
            //Mat img = image.clone();
            //imagelock.unlock();
            
            imagelock.lock();
            Mat img = grabImage();
            imagelock.unlock();

            //if(isCalibrated){
            //    cout << "Undistorting" << endl;
            //    Mat imgClone = img.clone();
            //    cv::undistort(imgClone,img,matrix,coefs);
            //}

            if(mode > 1){
                //Droplet detection
                Droplet droplet = dropletdetector.detectDroplet(img);
            cv::rectangle(img, cv::Point(droplet.minX, droplet.minY),
                    cv::Point(droplet.maxX, droplet.maxY), cv::Scalar(0,
                        255, 0));
                timestamp = clock();
                firstDropletLog = secondDropletLog;

                secondDropletLog.timestamp = double(timestamp) / CLOCKS_PER_SEC * 1000;
                secondDropletLog.droplet = droplet;

                if (firstDropletLog.timestamp != 0) {
                    double movementSpeed =
                        computeMovementSpeed(firstDropletLog,
                                secondDropletLog);
                    //Send the images to the event
                    vector<int> args = { (int)(movementSpeed * 1000) };
                    (*eventCallback)(name + "_dropletspeed", to_string(1000 * movementSpeed), args);
                }

            }

            // Log the image
            //(*video_logger).Write(&img);

            //Convert image to base64
            vector<uchar> buff;//buffer for coding
            vector<int> param = vector<int>(0);

            //param[0]=CV_IMWRITE_JPEG_QUALITY;
            //param[1]=95;//default(95) 0-100

            imencode(".png", img, buff, param);

            string base64 = base64_encode(&buff[0],buff.size());

            //Send the images to the event
            vector<int> args;
            (*eventCallback)(eventName, base64, args);
        }

        //cout << "Camera: Releasing the capture device ..." << endl;
        //cap.release();
        ////free(cap);
        //cout << "Camera: Released the capture device" << endl;
    });
}

void Camera::calibrate(cv::Mat coefs, cv::Mat matrix) {
    this->coefs = coefs;
    this->matrix = matrix;
    isCalibrated = true;
}

void Camera::uncalibrate(){
    isCalibrated = false;
}

void Camera::translation(double xTranslationX, double yTranslationX, double xTranslationY, double yTranslationY){
    vector<double> x = {xTranslationX, yTranslationX};
    vector<double> y = {xTranslationY, yTranslationY};
    this->xStep = x;
    this->yStep = y;
}
