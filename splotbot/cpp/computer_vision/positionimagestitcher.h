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
        PositionImageStitcher(Camera *camera, int stepSize);
        PositionImageStitcher(vector<GrabbedImage> grabbedImages, Camera *camera, int stepSize);
        cv::Mat stitch();
    private:
        cv::Mat warp();
        cv::Mat translationMatrix(int x, int y);
        void fixmin(cv::Mat minTranslation);
        void findMaxValues();
        int min_x;
        int min_y;
        int max_x;
        int max_y;

        double x_shift;
        double y_shift;

        double total_width;
        double total_height;

};

#endif
