#ifndef IMAGELOGGER_H
#define IMAGELOGGER_H

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <opencv2/opencv.hpp>

#include "logger.h"

using namespace std;

class ImageLogger : public Logger<cv::Mat> {

    public:
        ImageLogger(string componentType, string componentName);
        ~ImageLogger();

        vector<Entry<string>> Read();

		bool Data(cv::Mat);

	protected:
        bool Write(Entry<cv::Mat>);
		string identifier(Entry<cv::Mat>);
		Entry<cv::Mat> entry();
		bool Clear();
};

#endif
