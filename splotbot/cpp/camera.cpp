#include <iostream>

#include "camera.h"
#include "utils/base64.h"
#include <opencv2/opencv.hpp>
#include <thread>

using namespace std;
using namespace cv;

Camera::Camera(string name, int videoDevice, string eventName): name(name), videoDevice(videoDevice), eventName(eventName) {
    run();
}

void Camera::registerActions(vector<function<void(InstructionBuffer *)>> *actions) {
    cout << "Camera (" << name << ") registering actions" << endl;

    // 'Set camera mode' <mode>
    function<void(InstructionBuffer *)> setMode = [&](InstructionBuffer *buffer) -> void {
        int instr[1];
        (*buffer).popInstructions(1, instr);
        int mode = instr[0];
        cout << "Camera (" << name << ") mode set to " << mode << endl;
        (*eventCallback)("Test name", "Test data");
    };

    (*actions).push_back(setMode);
}


void Camera::run() {
    this_thread::sleep_for(chrono::milliseconds(1000));
    thread( [&] () {
        VideoCapture cap(videoDevice);
        Mat image;
        while (true) {
            bool success = cap.read(image);

            if (!success)
            {
                 cout << "ERROR: Cannot read a frame from video device: " << videoDevice << endl;
                 break;
            }
            vector<uchar> buff;//buffer for coding
            vector<int> param = vector<int>(0);
            //param[0]=CV_IMWRITE_JPEG_QUALITY;
            //param[1]=95;//default(95) 0-100

            imencode(".png", image, buff, param);

            string base64 = base64_encode(&buff[0],buff.size());

            (*eventCallback)("callback_" + name, base64);
        }
    }).detach();
}
