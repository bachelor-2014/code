#ifndef FEATURESIMAGESTITCHER_H
#define FEATURESIMAGESTITCHER_H 

#include <opencv2/opencv.hpp>
#include <opencv2/stitching/stitcher.hpp>

#include "../camera.h"

#include "imagestitcher.h"

using namespace std;

/**
 *
 */
class FeaturesImageStitcher: public ImageStitcher {
    public:
        FeaturesImageStitcher(Camera *camera);
        cv::Mat stitch();
};

#endif
