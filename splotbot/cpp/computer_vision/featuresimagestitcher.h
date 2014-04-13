#ifndef FEATURESIMAGESTITCHER_H
#define FEATURESIMAGESTITCHER_H 

#include <opencv2/opencv.hpp>
#include <opencv2/stitching/stitcher.hpp>

#include "imagestitcher.h"

using namespace std;

/**
 *
 */
class FeaturesImageStitcher: public ImageStitcher {
    public:
        FeaturesImageStitcher(int videoDevice);
        cv::Mat stitch();
};

#endif
