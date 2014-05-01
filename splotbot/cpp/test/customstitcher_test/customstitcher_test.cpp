#include <iostream>
#include <chrono>
#include <unistd.h>
#include <opencv2/opencv.hpp>

#include "../../computer_vision/customstitcher.h"

using namespace std;

int main() {
    vector<cv::Mat> images(4);
    images[0] = cv::imread("grab40_30.jpg");
    images[1] = cv::imread("grab40_35.jpg");
    images[2] = cv::imread("grab45_30.jpg");
    images[3] = cv::imread("grab45_35.jpg");

    CustomStitcher stitcher;
    cv::Mat result = stitcher.stitch(images);

    cv::namedWindow("result", cv::WINDOW_AUTOSIZE);
    cv::imshow("result", result);
    cv::waitKey(0);

    return 0;
}
