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

    cv::Point2f points1[3];
    cv::Point2f points2[3];

    points1[0] = corners1[0];
    points1[1] = corners1[1];
    points1[2] = corners1[2];

    points2[0] = corners2[0];
    points2[1] = corners2[1];
    points2[2] = corners2[2];

    cv::Mat affineTransformation(2, 3, CV_32FC1);
    affineTransformation = getAffineTransform(points1, points2);

    cout << "Affine transformation computed: " << affineTransformation << endl;

    *xTranslation = affineTransformation.at<double>(0, 2);
    *yTranslation = affineTransformation.at<double>(1, 2);

    //TODO DEBUG: save the images
    stringstream fs11;
    fs11 << "data/images/clean_translation_image1_" << (*xTranslation) << ".jpg";
    cv::imwrite(fs11.str(), image1);

    stringstream fs21;
    fs21 << "data/images/clean_translation_image2_" << (*xTranslation) << ".jpg";
    cv::imwrite(fs21.str(), image2);
    
    drawChessboardCorners(image1, board_size, cv::Mat(corners1), found1);
    drawChessboardCorners(image2, board_size, cv::Mat(corners2), found2);

    stringstream fs1;
    fs1 << "data/images/translation_image1_" << (*xTranslation) << ".jpg";
    cv::imwrite(fs1.str(), image1);

    stringstream fs2;
    fs2 << "data/images/translation_image2_" << (*xTranslation) << ".jpg";
    cv::imwrite(fs2.str(), image2);
}
