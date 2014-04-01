#include <iostream>
#include <unistd.h>

#include "camera.h"
#include "utils/base64.h"
#include <opencv2/opencv.hpp>
#include <thread>
#include "utils/threading.h"

using namespace std;
using namespace cv;

/**
 * Camera constructor
 */
Camera::Camera(string name, int videoDevice, string eventName): name(name), videoDevice(videoDevice), eventName(eventName) {
    run();
}

/**
 * registerActions registeres the actions of the Camera unto an actions buffer
 */
void Camera::registerActions(vector<function<void(InstructionBuffer *)>> *actions) {
    cout << "Camera (" << name << ") registering actions" << endl;

    // 'Set camera mode' <mode>
    function<void(InstructionBuffer *)> setMode = [&](InstructionBuffer *buffer) -> void {
        //Get mode
        int instr[1];
        (*buffer).popInstructions(1, instr);
        int mode = instr[0];
        cout << "Camera (" << name << ") mode set to " << mode << endl;

        //Send event
        (*eventCallback)("Test name", "Test data");
    };

    (*actions).push_back(setMode);
}


/**
 * The run functions
 * Starts the video capture device and pulls images
 */
void Camera::run() {
    runAsThread( [&] () {
        //VideoCapture
        VideoCapture cap(videoDevice);

        video_logger = new VideoLogger("exp",&cap);

        Mat image;
        while (true) {
            //Pull image
            bool success = cap.read(image);

            if (!success)
            {
                 cout << "ERROR: Cannot read a frame from video device: " << videoDevice << endl;
                 break;
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
            sleep(1);
        }
    });
}
