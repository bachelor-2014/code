#include <iostream>
#include <unistd.h>
#include <opencv2/opencv.hpp>

#include "../../computer_vision/computervisionutils.h"

using namespace std;

int main() {
    cv::Mat image1 = cv::imread("image1.jpg");
    cv::Mat image2 = cv::imread("image2.jpg");

    double xTranslation;
    double yTranslation;

    computeTranslation(image1, image2, &xTranslation, &yTranslation);

    cout << "xTranslation = " << xTranslation << endl;
    cout << "yTranslation = " << yTranslation << endl;

    return 1;
}
