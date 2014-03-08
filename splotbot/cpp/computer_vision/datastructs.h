#ifndef DATASTRUCTS_H 
#define DATASTRUCTS_H 

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

/**
 *  Represents a detected droplet
 */
typedef struct {
    int minX;
    int minY;
    int maxX;
    int maxY;
    double centroidX;
    double centroidY;
    int area;
} Droplet;

/**
 * Represents a color interval in which to detect objects
 */
typedef struct {
    cv::Scalar minColor;
    cv::Scalar maxColor;
} ColorInterval;

#endif
