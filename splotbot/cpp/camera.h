#ifndef CAMERA_H
#define CAMERA_H 

#include <string>
#include <mutex>
#include <opencv2/opencv.hpp>
#include "instructionbuffer.h"
#include "component.h"
#include "logging/videologger.h"
#include "computer_vision/dropletdetector.h"

using namespace std;
using namespace cv;

/**
 * Camera Component class handles a system camera
 * Is constructed with the following variables:
 * name: Name of the camera
 * videoDevice: The video device id (eg. 0, 1 etc.)
 * eventName: Name of the event used by the camera to send images
 *
 * Use the registerActions(*actions) to register the actions performed by the camera:
 * Mode [1]: Sets the mode of the camera
 * DropletSelector [2]: Selected the droplet using the given x,y coordinates
 * SetDropletVariables [4]: Sets the droplet variables with minSets the droplet
 *      variables with min area, max area, structuring element size and tolerance
 *
 * The Camera will automatically pull images on construction 
 */
class Camera: public Component {
    public:
        Camera(string name, int videoDevice, string eventName);
        int videoDevice;
        void registerActions(vector<function<void(InstructionBuffer *)>> *actions);
        void setMode(int m);
        void stop();
        void start();
        void dropletDetection();
        Mat grabImage();
        void calibrate(cv::Mat coefs, cv::Mat matrix);

    private:
        VideoLogger *video_logger;
        //VideoCapture *cap;
        mutex imagelock;
        int mode;
        string eventName;
        Mat image;

        /**
         * Droplet detection variables
         */
        DropletDetector dropletdetector;
        int tolerance;

        /**
         * Internal Methods
         */
        void run();
        void updateDropletDetector();

        /**
         * Calibration
         */
        bool isCalibrated = false;
        cv::Mat coefs;
        cv::Mat matrix;
};

#endif
