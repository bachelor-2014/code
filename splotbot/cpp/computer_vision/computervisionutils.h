#ifndef COMPUTERVISIONUTILS_H 
#define COMPUTERVISIONUTILS_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "datastructs.h"

using namespace std;

/**
 * Compute a suitable color interval from the given image, tolerance and pixel selectedn
 */
ColorInterval computeColorIntervalFromSelection(cv::Mat image, int tolerance, int x, int y);

/**
 * Computer movement speed from droplet logs based on the timestamps and centroids
 *
 * The movement speed is in pixels per second
 */
double computeMovementSpeed(DropletLog first, DropletLog second);

#endif
