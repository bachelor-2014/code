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

    cap >> image;

    cout << "Frame Size = " << dWidth << "x" << dHeight << endl;

    Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));

    VideoWriter videoWriter ("/home/csp/projects/itu/6.semester/bachelor/code/pocs/image_stitcher/result.avi", 
            CV_FOURCC('P','I','M','1'), 20, frameSize, true);

    if (!cap.isOpened())
    {
        printf("No video data\n");
        return -1;
    }

    if (!videoWriter.isOpened())
    {
        printf("couldn't write video!\n");
        return -1;
    }

    while(true) {
        bool success = cap.read(image);

        if (!success)
        {
             cout << "ERROR: Cannot read a frame from video file" << endl;
             break;
        }

        // Write frame
        videoWriter.write(image);

        imshow("john",image);

        if (waitKey(10) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "esc key is pressed by user" << endl;
            break; 
        }
        //cap >> image;
        //waitKey(1);
    }

    return 0;
}
