#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main( int argc, char** argv )
{
    if (argc != 3) {
        printf("Invalid number of arguments (2 needed)\n");
        return -1;
    }

    int frameNumber = std::stoi(argv[2]);
    VideoCapture cap(argv[1]);

    if (!cap.isOpened())
    {
        printf("No video data\n");
        return -1;
    }

    Mat image;

    for (int i = 1; i < frameNumber; i++) {
        cap.grab();
    }

    bool success = cap.read(image);

    if (!success) {
        printf("Failed to grab frame\n");
        return -1;
    }

    namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
    imshow( "Display Image", image );

    waitKey(0);

    return 0;
}
