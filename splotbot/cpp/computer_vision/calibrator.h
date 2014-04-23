#ifndef CALIBRATOR_H
#define CALIBRATOR_H

#include <vector>
#include <opencv2/opencv.hpp>

#include "../camera.h"
#include "../xyaxes.h"

using namespace std;

/**
 */
class Calibrator {
    public:
        Calibrator(string configFile);
        bool calibrate(vector<cv::Mat> images,
                cv::Mat *distortionCoeffs, cv::Mat *intrinsicMatrix);
        void getCalibrationFromFile(cv::Mat *distortionCoeffs,
                cv::Mat *intrinsicMatrix, vector<double> *xStep, vector<double> *yStep);

        bool isCalibrated();
        bool unCalibrate(Camera *camera);
        void writeToConfig(string key, cv::Mat data);
        cv::Mat readFromConfig(string key);
        void stepCalibrate(vector<cv::Mat> images, vector<double> *xStep, vector<double> *yStep);

    private:
        string configFile;
};

#endif
