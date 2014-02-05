#include "BlobDetection.hpp"

using namespace cv;

cv::Mat threshold(cv::Mat image) {
    return image;
}

int main( int argc, char** argv )
{
    if (argc != 2) {
        printf("Invalid number of arguments (1 needed)\n");
        return -1;
    }

    VideoCapture cap(std::stoi(argv[1]));

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
        waitKey(1);
    }

    return 0;
}
