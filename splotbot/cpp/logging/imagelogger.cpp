#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

#include "videologger.h"

using namespace std;

ImageLogger::ImageLogger(string componentType,string componentName)
	: Logger<cv::Mat*>(){

}

VideoLogger::~VideoLogger(){
}

bool VideoLogger::Write(Mat *image){
    string filename = "data/"+identifier+".avi";

    (*videoWriter).write(*image);

    return true;
}
