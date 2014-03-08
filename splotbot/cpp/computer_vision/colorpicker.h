#ifndef COLORPICKER_H 
#define COLORPICKER_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "datastructs.h"

using namespace std;

class ColorPicker {
    public:
        ColorPicker(cv::Mat image, int tolerance);
        ColorInterval computeColorIntervalFromSelection(int x, int y);

    private:
        cv::Mat image;
        int tolerance;
        void getColors(cv::Mat image, int x, int y, bool up, bool down, bool left, bool right, vector<int> *hVector, vector<int> *sVector, vector<int> *vVector);
        bool withinTolerance(cv::Vec3b pixel, cv::Vec3b otherPixel);
};

#endif
