#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

#include "videologger.h"

using namespace std;
using namespace cv;

Size frameSize;
VideoLogger::VideoLogger(string identifier, VideoCapture *cap) : Logger(identifier){
    filename = "data/"+identifier+".avi";

    double dWidth = (*cap).get(CV_CAP_PROP_FRAME_WIDTH);
    double dHeight = (*cap).get(CV_CAP_PROP_FRAME_HEIGHT);

    frameSize = Size(static_cast<int>(dWidth), static_cast<int>(dHeight));

    videoWriter = new VideoWriter(  filename,
                                    CV_FOURCC('M','P','E','G'),
                                    20,frameSize);
}

VideoLogger::~VideoLogger(){
}

bool VideoLogger::writeVideoData(Mat *image){

    (*videoWriter).write(*image);

    return true;
}
