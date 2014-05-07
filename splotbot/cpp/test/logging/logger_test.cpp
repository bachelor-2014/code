#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

#include "../../logging/logger.h"
#include "../../logging/filelogger.h"
#include "../../logging/videologger.h"
#include "../../logging/imagelogger.h"

#define SH_FG_RED            "\033[0;31m"
#define SH_FG_GREEN          "\033[0;32m"
#define SH_DEFAULT           "\033[0m"

using namespace std;

bool status = true;

bool test_logger_instantiation(){
    clog << __func__ << endl;

    Logger<string> fl = FileLogger("type","name");

    return true;
}

bool test_file_read_write(){
    clog << __func__ << endl;

    string towrite = "JohnJohn";

    FileLogger fl("type","name");
    fl.Clear();
    fl.Data(towrite);

    return true;
}

bool test_image_read_write(){
	clog << __func__ << endl;

	string image = "data/grab0_0.jpg";
	cv::Mat mat = cv::imread(image);

	ImageLogger il("type","name");
	il.Data(&mat);

	return true;
}

bool test_video_read_write(){
	clog << __func__ << endl;

        cv::VideoCapture *cap = new cv::VideoCapture(0);

        cap->set(CV_CAP_PROP_FRAME_WIDTH, 320);
        cap->set(CV_CAP_PROP_FRAME_HEIGHT, 240);

	string image = "data/grab0_0.jpg";
	cv::Mat mat = cv::imread(image);

        VideoLogger *videoLogger = new VideoLogger("Camera","johnny stash",cap);
        videoLogger->Data(&mat);


	ImageLogger il("type","name");
	il.Data(&mat);

	return true;
}

bool test(function<bool()> f, string message){
    if(!f()){
        status = false;
        cerr << SH_FG_RED << " Fail: " << message << SH_DEFAULT << endl;
    } else {
        clog << SH_FG_GREEN << " Ran" << SH_DEFAULT << endl;
    }
}

int main() {
    test(test_file_read_write,"test write file failed");
    test(test_image_read_write,"test write image failed");
    //test(test_video_read_write,"test write video failed");
    test(test_logger_instantiation,"test_instantiation failed!");

    clog << "TIMESTAMP:" << getTimeStamp() << endl;
    if(status){
	return 0;
    }else{
	return 1;
    }
}
