#include <iostream>
#include <opencv2/opencv.hpp>
#include "../../computer_vision/dropletdetector.h"
#include "../../computer_vision/colorpicker.h"

using namespace std;

int selectedX;
int selectedY;

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
    cv::Mat image = cv::imread("droplet.png");

    cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);
    cv::setMouseCallback("Input", mouseEventCallBack, NULL);
    cv::imshow("Input", image);
    int key = cv::waitKey(0);

    int minArea = 0;
    int maxArea = 999999;
    ColorInterval colorInterval;
    
    ColorPicker colorPicker(image, 20);
    colorInterval = colorPicker.computeColorIntervalFromSelection(selectedX, selectedY);

    //cv::Scalar minColor(0, 200, 110);
    //cv::Scalar maxColor(180, 255, 155);
    //colorInterval.minColor = minColor;
    //colorInterval.maxColor = maxColor;

    int structuringElementSize = 3;

    DropletDetector detector(minArea, maxArea, colorInterval, structuringElementSize);
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
