#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

#include "videologger.h"

using namespace std;
using namespace cv;

VideoLogger::VideoLogger(string identifier) : Logger(identifier){
    string filename = "data/"+identifier+".avi";

    Mat image;
    VideoCapture cap(0);

    double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

    Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));

    VideoWriter videoWriter (filename,
            CV_FOURCC('M','P','E','G'),
            20,
            frameSize
            );
            //CV_FOURCC('P','I','M','1'), 20, frameSize, true);

    namedWindow("john",CV_WINDOW_AUTOSIZE);

    if (!cap.isOpened())
    {
        cerr << "No video data\n" << endl;
    }

    if (!videoWriter.isOpened())
    {
        cerr << "can't write video!\n" << endl;
    }

    while(true) {
        bool success = cap.read(image);

        if (!success)
        {
             cerr << "ERROR: Cannot read a frame from video file" << endl;
             break;
        }

        videoWriter.write(image);

        imshow("john",image);

    }
}

VideoLogger::~VideoLogger(){
}

bool VideoLogger::writeVideoData(string data){
    return 0;
}

string VideoLogger::readVideoData(){
}
