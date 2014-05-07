#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <stdexcept>

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
    //int minV = 0;

    int maxH = ((int)pixel[0]) + tolerance;
    int maxS = ((int)pixel[1]) + tolerance;
    int maxV = ((int)pixel[2]) + tolerance;
    //int maxV = 255;

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

void computeTranslation(cv::Mat image1, cv::Mat image2, double *xTranslation, double *yTranslation) {
    cv::Size board_size = cv::Size(9, 6);

    vector<cv::Point2f> corners1;
    vector<cv::Point2f> corners2;

    bool found1 = findChessboardCorners(image1, board_size, corners1);
    bool found2 = findChessboardCorners(image2, board_size, corners2);

    if (!found2 || !found2) {
        throw runtime_error("Computer vision utils: Failed to detect chessboard corners when computing translation");
    }

    //Corner sums
    cv::Point2f corners1sum(0,0);
    cv::Point2f corners2sum(0,0);

    cout << "Corner1sum before: " << corners1sum << endl;
    cout << "Corner2sum before: " << corners2sum << endl;

    for(int i = 0; i<corners1.size(); i++){
        corners1sum.x += corners1[i].x;
        corners1sum.y += corners1[i].y;

        corners2sum.x += corners2[i].x;
        corners2sum.y += corners2[i].y;
    }
    cout << "Corner1sum: " << corners1sum << endl;
    cout << "Corner2sum: " << corners2sum << endl;

    //Center points
    cv::Point2f corners1center;
    corners1center.x = corners1sum.x / corners1.size();
    corners1center.y = corners1sum.y / corners1.size();

    cv::Point2f corners2center;
    corners2center.x = corners2sum.x / corners2.size();
    corners2center.y = corners2sum.y / corners2.size();

    cout << "Corner1center: " << corners1center << endl;
    cout << "Corner2center: " << corners2center << endl;

    *xTranslation = corners2center.x - corners1center.x;
    *yTranslation = corners2center.y - corners1center.y;
}
