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
        void calibrate(vector<cv::Mat> images,
                cv::Mat *distortionCoeffs, cv::Mat *intrinsicMatrix);
        void getCalibrationFromFile(cv::Mat *distortionCoeffs,
                cv::Mat *intrinsicMatrix);

    private:
        string configFile;
};

#endif
