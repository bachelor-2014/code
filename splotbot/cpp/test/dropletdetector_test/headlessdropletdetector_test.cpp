#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>
#include "../../computer_vision/dropletdetector.h"
#include "../../computer_vision/computervisionutils.h"

using namespace std;

int selectedX = 296;
int selectedY = 118;

// Good coords: (296, 118)

void mouseEventCallBack(int event, int x, int y, int flags, void* userdata)
{
    if  ( event == cv::EVENT_LBUTTONDOWN )
    {
        cout << "Mouse event: (" << x << ", " << y << ")" << endl;
        selectedX = x;
        selectedY = y;
    }
}

int main() {
    cv::Mat image;
    DropletLog firstDropletLog;
    DropletLog secondDropletLog;
    int timestamp;

    cv::VideoCapture cap("droplet_video.mp4");

    if (!cap.isOpened()) {
        cout << "No video data" << endl;
        return -1;
    }

    bool success = cap.read(image);

    //cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);
    //cv::setMouseCallback("Input", mouseEventCallBack, NULL);
    //cv::imshow("Input", image);
    //int key = cv::waitKey(0);
    //cv::destroyWindow("Input");

    int minArea = 0;
    int maxArea = 99999;
    int structuringElementSize = 3;

    ColorInterval colorInterval;
    colorInterval = computeColorIntervalFromSelection(image, 20, selectedX, selectedY);

    //cv::namedWindow("Result", cv::WINDOW_AUTOSIZE);
    //cv::setMouseCallback("Result", mouseEventCallBack, NULL);

    DropletDetector detector(minArea, maxArea, colorInterval, structuringElementSize);

    while (success) {
        Droplet droplet = detector.detectDroplet(image);
        cv::rectangle(image, cv::Point(droplet.minX, droplet.minY), cv::Point(droplet.maxX, droplet.maxY), cv::Scalar(0, 255, 0));
        //cv::imshow("Result", image);

        cv::waitKey(1);

        success = cap.read(image);
        timestamp = (int)time(NULL);

        firstDropletLog = secondDropletLog;

        secondDropletLog.timestamp = timestamp;
        secondDropletLog.droplet = droplet;

        if (firstDropletLog.timestamp != 0) {
            double movementSpeed = computeMovementSpeed(firstDropletLog, secondDropletLog);
            cout << "Movement speed of droplet: " << movementSpeed << " px/s" << endl;
        }

        //cout << "area: " << droplet.area << endl;
        //cout << "minX: " << droplet.minX << endl;
        //cout << "minY: " << droplet.minY << endl;
        //cout << "maxX: " << droplet.maxX << endl;
        //cout << "maxY: " << droplet.maxY << endl;
        //cout << "centroidX: " << droplet.centroidX << endl;
        //cout << "centroidY: " << droplet.centroidY << endl;
    }

    return 0;
}
