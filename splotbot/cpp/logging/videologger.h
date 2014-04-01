#ifndef VIDEOLOGGER_H
#define VIDEOLOGGER_H

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <opencv2/opencv.hpp>
#include "logger.h"

using namespace std;
using namespace cv;

class VideoLogger : public Logger<Mat*>{

    public:
        VideoLogger(string,VideoCapture*);
        ~VideoLogger();

        bool Write(Mat*);
    private:
        string filename;
        VideoWriter *videoWriter;
        VideoCapture cap;
};

#endif
