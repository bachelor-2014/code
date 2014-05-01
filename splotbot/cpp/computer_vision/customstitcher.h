#ifndef CUSTOMSTITCHER_H
#define CUSTOMSTITCHER_H

#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;

/**
 * Stitcher capable of stitching a vector of images
 *
 * An alternative to the implementation in OpenCV
 */
class CustomStitcher {
    public:
        CustomStitcher();
        cv::Mat stitch(vector<cv::Mat> images);

    private:
        cv::Mat stitchTwo(cv::Mat image1, cv::Mat image2);
};

#endif
