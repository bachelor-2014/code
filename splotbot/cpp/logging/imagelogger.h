#ifndef IMAGELOGGER_H
#define IMAGELOGGER_H

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <opencv2/opencv.hpp>

#include "logger.h"

using namespace std;

class ImageLogger : public Logger<cv::Mat*> {

    public:
        ImageLogger(string componentType, string componentName);
        ~ImageLogger();

        vector<Entry<cv::Mat*>> Read();

	bool Info(cv::Mat*);
	bool Error(cv::Mat*);
	bool Data(cv::Mat*);

	bool Init(string componentType, string componentName);
	string identifier(Entry<cv::Mat*>);
	bool Clear();

	protected:
        bool Write(Entry<cv::Mat*>);
	Entry<cv::Mat*> entry();
};

#endif
