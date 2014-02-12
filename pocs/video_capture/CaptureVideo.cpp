#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

bool react_to_key (int i);

bool capturing; // Global value, indicating if were writing

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

    cout << "Frame Size = " << dWidth << "x" << dHeight << endl;
    cout << "Supported commands:" << endl;
    cout << "c \t : \t capture to result.avi" << endl;

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

        // Write frame
        if(capturing){
            videoWriter.write(image);
        }

        imshow("john",image);

        bool stop = react_to_key(waitKey(10));
        if(stop)
            break;
    }

    return 0;
}

bool react_to_key(int keyPress){
        if (keyPress == 27) //esc
        {
            cout << "esc key is pressed by user" << endl;
            return true;
        }

        if (keyPress == 99) //c
        {
            cout << "Capturing" << endl;
            capturing = !capturing;
        }

        return false;
}
