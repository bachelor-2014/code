#ifndef VIDEOLOGGER_H
#define VIDEOLOGGER_H

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <opencv2/opencv.hpp>
#include "logger.h"

using namespace std;
using namespace cv;

class VideoLogger : public Logger{

    public:
        VideoLogger(string,VideoCapture*);
        ~VideoLogger();

        template<class T>
        bool Write(T t){
            if(typeid(T) == typeid(Mat*)){
                return writeVideoData(t);
            }
        }

    private:
        string filename;
        VideoWriter *videoWriter;
        VideoCapture cap;
        bool writeVideoData(Mat*);
};

#endif
