#include <iostream>
#include <unistd.h>

#include "camera.h"
#include "utils/base64.h"
#include <opencv2/opencv.hpp>
#include <thread>
#include "utils/threading.h"
#include "computer_vision/dropletdetector.h"
#include "computer_vision/computervisionutils.h"

using namespace std;
using namespace cv;

/**
 * Camera constructor
 */
Camera::Camera(string name, int videoDevice, string eventName): videoDevice(videoDevice), eventName(eventName) {
    this->name = name;
    setMode(0);
    tolerance = 20;
    //cap = new VideoCapture(videoDevice);
    //cap->set(CV_CAP_PROP_FRAME_WIDTH, 320);
    //cap->set(CV_CAP_PROP_FRAME_HEIGHT, 240);
    //run();
}

/**
 * registerActions registeres the actions of the Camera unto an actions buffer
 */
void Camera::registerActions(vector<function<void(InstructionBuffer *)>> *actions) {
    cout << "Camera (" << name << ") registering actions" << endl;

    // 'Set camera mode' <mode>
    // Modes:
    // 0 - Camera Off
    // 1 - Camera On
    // 2 - Droplet detection
    function<void(InstructionBuffer *)> setCameraMode = [&](InstructionBuffer *buffer) -> void {
        //Get mode
        int instr[1];
        (*buffer).popInstructions(1, instr);
        setMode(instr[0]);
        cout << "Camera (" << name << ") mode set to " << mode << endl;
    };

    // 'Set droplet variables' 
    // <min area> <max area> <structuring element size> <tolerance>
    function<void(InstructionBuffer *)> setDropletVariables = [&](InstructionBuffer *buffer) -> void {
        int instr[4];
        (*buffer).popInstructions(4, instr);

        dropletdetector.minArea = instr[0];
        dropletdetector.maxArea = instr[1];
        dropletdetector.structuringElementSize = instr[2];
        tolerance = instr[3];

    };

    // 'End color selector' <x> <y>
    function<void(InstructionBuffer *)> dropletSelector = [&](InstructionBuffer *buffer) -> void {

        //Get coordinates
        int instr[2];
        (*buffer).popInstructions(2, instr);
        int x = instr[0];
        int y = instr[0];

        Mat image = grabImage();
        dropletdetector.colorInterval =
            computeColorIntervalFromSelection(image, tolerance,x,y);

        //Stop the droplet selection
    };

    (*actions).push_back(setCameraMode);
    (*actions).push_back(dropletSelector);
    (*actions).push_back(setDropletVariables);
}

/**
 * Sets the current camera mode
 */
void Camera::setMode(int m){
    if (mode == 0 && m > 0) {
        run();
    }
    mode = m;
}

/**
 * Stops the camera, making it no longer grabbing new images
 */
void Camera::stop(){
    setMode(0);
    sleep(3);
}

/**
 * Starts the camera
 */
void Camera::start(){
    //Don't stop the droplet detection
    if(mode == 0){
        setMode(1);
    } else if (mode < 2) {
        setMode(1);
    }
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
    //cout << "Camera: Entering function 'grabImage()'" << endl;
    Mat newimage;
    //cout << "Camera: Acquiring lock ..." << endl;
    imagelock.lock();
    //cout << "Camera: Acquired lock ..." << endl;
    newimage = image.clone();
    //cout << "Camera: Releasing lock ..." << endl;
    imagelock.unlock();
    //cout << "Camera: Released lock ..." << endl;
    return newimage;
}

/**
 * The run functions
 * Starts the video capture device and pulls images
 */
void Camera::run() {
    runAsThread( [&] () {

        cout << "Camera: Thread opening capture device ..." << endl;
        VideoCapture cap(videoDevice);
        cout << "Camera: Thread opened capture device" << endl;
        cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
        cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

        cout << "Camera caps set" << endl;
        //video_logger = new VideoLogger("exp",&cap);


        while (mode > 0) {
            imagelock.lock();
            bool success = cap.read(image); 
            Mat img = image.clone();
            imagelock.unlock();

            if(isCalibrated){
                cout << "Undistorting" << endl;
                Mat imgClone = img.clone();
                cv::undistort(imgClone,img,matrix,coefs);
            }

            if(mode > 1){
                //Droplet detection
                Droplet droplet = dropletdetector.detectDroplet(img);
            cv::rectangle(img, cv::Point(droplet.minX, droplet.minY),
                    cv::Point(droplet.maxX, droplet.maxY), cv::Scalar(0,
                        255, 0));

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
            (*eventCallback)(eventName, base64);
        }

        cout << "Camera: Releasing the capture device ..." << endl;
        cap.release();
        //free(cap);
        cout << "Camera: Released the capture device" << endl;
    });
}

void Camera::calibrate(cv::Mat coefs, cv::Mat matrix) {
    this->coefs = coefs;
    this->matrix = matrix;
    isCalibrated = true;
}
