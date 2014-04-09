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
Camera::Camera(string name, int videoDevice, string eventName): name(name), videoDevice(videoDevice), eventName(eventName) {
    mode = 1;
    tolerance = 20;
    run();
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
    function<void(InstructionBuffer *)> setMode = [&](InstructionBuffer *buffer) -> void {
        //Get mode
        int instr[1];
        (*buffer).popInstructions(1, instr);
        mode = instr[0];
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

        dropletdetector.colorInterval =
            computeColorIntervalFromSelection(image, tolerance,x,y);

        //Stop the droplet selection
    };

    (*actions).push_back(setMode);
    (*actions).push_back(dropletSelector);
    (*actions).push_back(setDropletVariables);
}


/**
 * The run functions
 * Starts the video capture device and pulls images
 */
void Camera::run() {
    runAsThread( [&] () {
        //VideoCapture
        VideoCapture cap(videoDevice);
        cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
        cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

        video_logger = new VideoLogger("exp",&cap);


        while (true) {
            if(mode > 0){
                //Pull image
                bool success = cap.read(image);

                if (!success)
                {
                     cout << "ERROR: Cannot read a frame from video device: " << videoDevice << endl;
                     break;
                }

                if(mode > 1){
                    //Droplet detection
                    Droplet droplet = dropletdetector.detectDroplet(image);
                cv::rectangle(image, cv::Point(droplet.minX, droplet.minY),
                        cv::Point(droplet.maxX, droplet.maxY), cv::Scalar(0,
                            255, 0));

                }

                // Log the image
                (*video_logger).Write(&image);

                //Convert image to base64
                vector<uchar> buff;//buffer for coding
                vector<int> param = vector<int>(0);

                //param[0]=CV_IMWRITE_JPEG_QUALITY;
                //param[1]=95;//default(95) 0-100

                imencode(".png", image, buff, param);

                string base64 = base64_encode(&buff[0],buff.size());

                //Send the images to the event
                (*eventCallback)(eventName, base64);
            }
        }
    });
}
