#ifndef IMAGESTITCHER_H
#define IMAGESTITCHER_H

#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;

typedef struct {
    int positionX;
    int positionY;
    cv::Mat image;
} GrabbedImage;

/**
 * ImageStitcher class defines an interface for containers of
 * various image stitching algorithm implementations.
 *
 * Image stitching is achieved through the following methods:
 * 
 */
class ImageStitcher {
    public:
        ImageStitcher(int videoDevice);
        void grabImage(int positionX, int positionY);
        virtual cv::Mat stitch() {};

    protected:
        int videoDevice;
        vector<GrabbedImage> grabbedImages;
};

#endif
