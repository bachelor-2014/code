#ifndef FEATURESANDPOSITIONIMAGESTITCHER_H
#define FEATURESANDPOSITIONIMAGESTITCHER_H 

#include <opencv2/opencv.hpp>
#include <opencv2/stitching/stitcher.hpp>

#include "../camera.h"

#include "imagestitcher.h"

using namespace std;

/**
 *
 */
class FeaturesandPositionImageStitcher: public ImageStitcher {
    public:
        FeaturesandPositionImageStitcher(Camera *camera);
        cv::Mat stitch();
    private:
        cv::Mat stitchImg(cv::Mat image1, cv::Mat image2);
};

#endif
