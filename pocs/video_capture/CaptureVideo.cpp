#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main( int argc, char** argv )
{
    if (argc != 2) {
        printf("Invalid number of arguments (1 needed)\n");
        return -1;
    }

    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        printf("No video data\n");
        return -1;
    }

    Mat image;

    namedWindow("john",1);

    cap >> image;

    while(true) {
        imshow("john",image);

        cap >> image;
    }

    return 0;
}
