#include <iostream>
#include <opencv2/opencv.hpp>
#include "../../computer_vision/dropletdetector.h"

using namespace std;

void mouseEventCallBack(int event, int x, int y, int flags, void* userdata)
{
    if  ( event == cv::EVENT_LBUTTONDOWN )
    {
        cout << "Mouse event: (" << x << ", " << y << ")" << endl;
    }
}

int main() {
    cv::Mat image = cv::imread("droplet.png");

    int minArea = 0;
    int maxArea = 999999;
    cv::Scalar minColor(0, 200, 110);
    cv::Scalar maxColor(180, 255, 155);
    int structuringElementSize = 3;

    DropletDetector detector(minArea, maxArea, minColor, maxColor, structuringElementSize);
    Droplet droplet = detector.detectDroplet(image);

    cout << "area: " << droplet.area << endl;
    cout << "minX: " << droplet.minX << endl;
    cout << "minY: " << droplet.minY << endl;
    cout << "maxX: " << droplet.maxX << endl;
    cout << "maxY: " << droplet.maxY << endl;
    cout << "centroidX: " << droplet.centroidX << endl;
    cout << "centroidY: " << droplet.centroidY << endl;

    cv::rectangle(image, cv::Point(droplet.minX, droplet.minY), cv::Point(droplet.maxX, droplet.maxY), cv::Scalar(0, 255, 0));
    
    cv::namedWindow("Result", cv::WINDOW_AUTOSIZE);
    cv::setMouseCallback("Result", mouseEventCallBack, NULL);
    cv::imshow("Result", image);

    cv::waitKey(0);

    return 0;
}
