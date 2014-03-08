#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include <cmath>
#include <math.h>

#include "computervisionutils.h"

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

/**
 * Computer movement speed from droplet logs based on the timestamps and centroids
 *
 * The movement speed is in pixels per second
 */
double computeMovementSpeed(DropletLog first, DropletLog second) {
    double x1 = (double)first.droplet.centroidX;
    double y1 = (double)first.droplet.centroidY;

    double x2 = (double)second.droplet.centroidX;
    double y2 = (double)second.droplet.centroidY;

    double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    double timeDifference = (double) (second.timestamp - first.timestamp);

    return distance / ((double) timeDifference);
}
