#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include <cmath>

#include "colorpicker.h"

using namespace std;

// Computes the color interval from the pixel chosen on the image using the tolerance
ColorInterval computeColorIntervalFromSelection(cv::Mat image, int tolerance, int x, int y) {
    ColorInterval colorInterval;

    cv::Mat blurredImage;
    cv::Mat hsvImage;

    // Apply a blur to the image
    //cv::GaussianBlur(image, blurredImage, cv::Size(3,3), 1.0);
    //cv::bilateralFilter(image, blurredImage, 30, 100, 100);
    cv::medianBlur(image, blurredImage, 31);

    // Convert the image to HSV
    cv::cvtColor(blurredImage, hsvImage, CV_BGR2HSV);

    // Compute the color interval
    cv::Vec3b pixel = hsvImage.at<cv::Vec3b>(y, x);
    int minH = ((int)pixel[0]) - tolerance;
    int minS = ((int)pixel[1]) - tolerance;
    int minV = ((int)pixel[2]) - tolerance;

    int maxH = ((int)pixel[0]) + tolerance;
    int maxS = ((int)pixel[1]) + tolerance;
    int maxV = ((int)pixel[2]) + tolerance;

    //// DEBUG: Print values
    //cout << "ColorPicker interval computed:" << endl;
    //cout << "H: " << minH << " - " << maxH << endl;
    //cout << "S: " << minS << " - " << maxS << endl;
    //cout << "V: " << minV << " - " << maxV << endl;
    //cout << endl;

    colorInterval.minColor = cv::Scalar(minH, minS, minV);
    colorInterval.maxColor = cv::Scalar(maxH, maxS, maxV);
    
    return colorInterval;
}
