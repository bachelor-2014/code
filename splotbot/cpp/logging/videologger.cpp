#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

#include "videologger.h"

using namespace std;
using namespace cv;

Size frameSize;
VideoLogger::VideoLogger(string componentType, string componentName,
		VideoCapture *cap) : Logger<Mat*>(){

    this->componentType = componentType;
    this->componentName = componentName;

    filename = "data/logs/"+this->identifier(this->entry())+".avi";

    double dWidth = (*cap).get(CV_CAP_PROP_FRAME_WIDTH);
    double dHeight = (*cap).get(CV_CAP_PROP_FRAME_HEIGHT);

    frameSize = Size(static_cast<int>(dWidth), static_cast<int>(dHeight));

    videoWriter = new VideoWriter(  filename,
                                    CV_FOURCC('M','P','E','G'),
                                    20,frameSize);

}

VideoLogger::~VideoLogger(){
}

bool VideoLogger::Data(cv::Mat* data){

	Entry<cv::Mat*> e = this->entry();
	e.ActivityType = "data";
	e.Data = data;

	this->Write(e);
};

bool VideoLogger::Clear(){};

string VideoLogger::identifier(Entry<cv::Mat*> entry){
	return entry.Timestamp+"_"+entry.ComponentType+"_"+entry.ComponentName+"_"+entry.ActivityType;
}

Entry<cv::Mat*> VideoLogger::entry(){
	Entry<cv::Mat*> entry(getTimeStamp(),this->componentType,
		this->componentName,"",NULL);

	return entry;
}

bool VideoLogger::Write(Entry<cv::Mat*> entry){

    (*videoWriter).write(*(entry.Data));

    return true;
}
