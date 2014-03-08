#include <iostream>
#include <opencv2/opencv.hpp>
#include "../../computer_vision/dropletdetector.h"

using namespace std;

int main() {
    cv::Mat image = cv::imread("droplet.png");

    int minArea = 0;
    int maxArea = 999999;
    cv::Scalar minColor(0, 200, 110);
    cv::Scalar maxColor(180, 255, 155);
    int structuringElementSize = 3;

    DropletDetector detector(minArea, maxArea, minColor, maxColor, structuringElementSize);
    detector.detectDroplet(image);

    cv::waitKey(0);

    return 0;
}
