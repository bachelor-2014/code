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
};

#endif
