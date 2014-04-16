#include <stdexcept>
#include <iostream>

#include "featuresimagestitcher.h"

using namespace std;

/**
 * Constructs a new FeaturesImageStitcher
 */
FeaturesImageStitcher::FeaturesImageStitcher(Camera *camera): ImageStitcher(camera) {
    // Empty constructor
    // The initialization is done in the base class
}

/*
 * Stitch together the images grabbed by the FeaturesImageStitcher
 */
cv::Mat FeaturesImageStitcher::stitch() {
    // This image stitcher does not make use of the positions of the images
    // Obtain a vector of only the images for stitching
    cout << "FeaturesImageStitcher: Entering method 'stitch()'" << endl;
    cout << "FeaturesImageStitcher: Creating new (empty) vector of images" << endl;
    vector<cv::Mat> images;
    cout << "FeaturesImageStitcher: Transforming grabbed images" << endl;
    transform(grabbedImages.begin(), grabbedImages.end(), back_inserter(images), [](GrabbedImage grabbedImage) {
           return grabbedImage.image;
   });

    // Do the stitching;
    cout << "FeaturesImageStitcher: Creating new image for storing the result" << endl;
    cv::Mat resultImage;
    cout << "FeaturesImageStitcher: Create an instance of the OpenCV 'Stitcher' class" << endl;
    cv::Stitcher stitcher = cv::Stitcher::createDefault();
    cout << "FeaturesImageStitcher: Do the stitching" << endl;
    cv::Stitcher::Status status = stitcher.stitch(images, resultImage);

    // Error handling
    if (status != cv::Stitcher::Status::OK) {
        throw runtime_error("FeaturesImageStitcher failed to stitch images");
    }

    cout << "FeaturesImageStitcher: Return the resulting image" << endl;
    return resultImage;
}
