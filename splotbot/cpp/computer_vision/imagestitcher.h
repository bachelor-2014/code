#ifndef IMAGESTITCHER_H
#define IMAGESTITCHER_H

#include <vector>
#include <opencv2/opencv.hpp>

#include "../camera.h"

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
 * grabImage:   Grabs an image an stores it
 * stitch:      Stitches the grabbed images and returns the results
 */
class ImageStitcher {
    public:
        ImageStitcher(Camera *camera);
        void grabImage(int positionX, int positionY);
        virtual cv::Mat stitch() {};

    protected:
        Camera *camera;
        vector<GrabbedImage> grabbedImages;
};

#endif
