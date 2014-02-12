#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if (argc != 2) {
        printf("Invalid number of arguments (1 needed)\n");
        return -1;
    }

    VideoCapture cap(std::stoi(argv[1]));

    Mat image;

    namedWindow("john",CV_WINDOW_AUTOSIZE);

    double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

    Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));

    VideoWriter videoWriter ("result.avi", 
            CV_FOURCC('P','I','M','1'), 20, frameSize, true);

    if (!cap.isOpened())
    {
        printf("No video data\n");
        return -1;
    }

    if (!videoWriter.isOpened())
    {
        printf("can't write video!\n");
        return -1;
    }

    while(true) {
        bool success = cap.read(image);

        if (!success)
        {
             cout << "ERROR: Cannot read a frame from video file" << endl;
             break;
        }

        videoWriter.write(image);

        imshow("john",image);

        waitKey(10);
    }

    return 0;
}
