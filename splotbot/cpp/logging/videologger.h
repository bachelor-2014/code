#ifndef VIDEOLOGGER_H
#define VIDEOLOGGER_H

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <opencv2/opencv.hpp>
#include "logger.h"

using namespace std;

class VideoLogger : public Logger<cv::Mat*>{

	public:
		VideoLogger(string,string,cv::VideoCapture*);
		~VideoLogger();

		bool Data(cv::Mat* data);

		bool Init(string componentType, string componentName){};
		string identifier(Entry<cv::Mat*> entry);
		bool Clear();
	
	protected:
		Entry<cv::Mat*> entry(); 
		bool Write(Entry<cv::Mat*>);


	private:
		string filename;
		cv::VideoWriter *videoWriter;
		cv::VideoCapture cap;

};

#endif
