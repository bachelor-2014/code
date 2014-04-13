#include <iostream>

#include "featuresimagestitcher.h"

using namespace std;

/**
 * Constructs a new FeaturesImageStitcher
 */
FeaturesImageStitcher::FeaturesImageStitcher(int videoDevice): ImageStitcher(videoDevice) {
    // Empty constructor
    // The initialization is done in the base class
}

/*
 * Stitch together the images grabbed by the FeaturesImageStitcher
 */
cv::Mat FeaturesImageStitcher::stitch() {
    // This image stitcher does not make use of the positions of the images
    // Obtain a vector of only the images for stitching
    vector<cv::Mat> images;
    transform(grabbedImages.begin(), grabbedImages.end(), back_inserter(images), [](GrabbedImage grabbedImage) {
           return grabbedImage.image;
   });

    // Do the stitching;
    cv::Mat resultImage;
    cv::Stitcher stitcher = cv::Stitcher::createDefault();
    cv::Stitcher::Status status = stitcher.stitch(images, resultImage);

    // Error handling
    if (status != cv::Stitcher::Status::OK) {
        throw runtime_error("FeaturesImageStitcher failed to stitch images");
    }

    return resultImage;
}
