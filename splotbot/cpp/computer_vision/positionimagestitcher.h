#ifndef POSITIONIMAGESTITCHER_H
#define POSITIONIMAGESTITCHER_H 

#include <opencv2/opencv.hpp>
#include <opencv2/stitching/stitcher.hpp>

#include "../camera.h"

#include "imagestitcher.h"

using namespace std;

/**
 *
 */
class PositionImageStitcher: public ImageStitcher {
    public:
        PositionImageStitcher(Camera *camera);
        PositionImageStitcher(vector<GrabbedImage> grabbedImages, Camera *camera);
        cv::Mat stitch();
    private:
        cv::Mat warp();
        cv::Mat translationMatrix(int x, int y);
        int min_x;
        int min_y;
        int max_x;
        int max_y;

        vector<int> xStep;
        vector<int> yStep;
};

#endif
