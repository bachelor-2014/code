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
        VideoLogger(string);
        ~VideoLogger();

        template<class T>
        bool Write(T t){
            if(typeid(T) == typeid(string)){
                return writeVideoData(t);
            }
        }

        template<class T>
        T Read(){
            if(typeid(T) == typeid(string)){
                return readVideoData();
            }
        }

    private:
        VideoWriter videoWriter;
        VideoCapture cap;
        string readVideoData();
        bool writeVideoData(string);
};

#endif
