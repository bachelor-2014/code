#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

#include "logger.h"
#include "imagelogger.h"

using namespace std;

ImageLogger::ImageLogger(string componentType,string componentName)
: Logger<cv::Mat*>(){

    this->componentType = componentType;
    this->componentName = componentName;

}

ImageLogger::~ImageLogger(){
}

vector<Entry<cv::Mat*>> ImageLogger::Read(){};

bool ImageLogger::Info(cv::Mat*){};

bool ImageLogger::Error(cv::Mat*){};

bool ImageLogger::Data(cv::Mat* data){

	Entry<cv::Mat*> e = this->entry();
	e.ActivityType = "data";
	e.Data = data;

	this->Write(e);
};

bool ImageLogger::Init(string componentType, string componentName){};
bool ImageLogger::Clear(){};

string ImageLogger::identifier(Entry<cv::Mat*> entry){
	return entry.Timestamp+"_"+entry.ComponentType+"_"+entry.ComponentName+"_"+entry.ActivityType;
}

Entry<cv::Mat*> ImageLogger::entry(){
	Entry<cv::Mat*> entry(getTimeStamp(),this->componentType,
		this->componentName,"",NULL);

	return entry;
}

bool ImageLogger::Write(Entry<cv::Mat*> entry){
	string filename = this->directory + this->identifier(entry) + ".png";

	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	cv::imwrite(filename, *entry.Data, compression_params);

	return true;
}
