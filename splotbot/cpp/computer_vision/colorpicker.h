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

#endif
