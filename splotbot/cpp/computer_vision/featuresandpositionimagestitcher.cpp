#include <stdexcept>
#include <iostream>

#include "featuresandpositionimagestitcher.h"

using namespace std;

/**
 * Constructs a new FeaturesandPositionImageStitcher
 */
FeaturesandPositionImageStitcher::FeaturesandPositionImageStitcher(Camera *camera): ImageStitcher(camera) {
    // Empty constructor
    // The initialization is done in the base class
}

/*
 * Stitch together the images grabbed by the FeaturesandPositionImageStitcher
 */
cv::Mat FeaturesandPositionImageStitcher::stitch() {
    // This image stitcher does not make use of the positions of the images
    // Obtain a vector of only the images for stitching
    cout << "FeaturesandPositionImageStitcher: Entering method 'stitch()'" << endl;

    // Do the stitching;
    cout << "FeaturesandPositionImageStitcher: Creating new image for storing the result" << endl;
    cv::Mat resultImage = grabbedImages[0].image;
    cout << "FeaturesandPositionImageStitcher: Create an instance of the OpenCV 'Stitcher' class" << endl;
    cout << "FeaturesandPositionImageStitcher: Do the stitching" << endl;
    for(int i = 1; i< grabbedImages.size(); i++){
        GrabbedImage grabbed = grabbedImages[i];
        cout << "Now stitching image with position: (" <<
            to_string(grabbed.positionX) << "," << to_string(grabbed.positionY)
            << ")" << endl;
        resultImage = stitchImg(&grabbed.image, &resultImage);
    }


    cout << "FeaturesandPositionImageStitcher: Return the resulting image" << endl;
    return resultImage;
}

cv::Mat FeaturesandPositionImageStitcher::stitchImg(cv::Mat *image1, cv::Mat *image2){
    cv::Mat resultImage;
    cout << "Vector" << endl;
    vector<cv::Mat> images;
    images.push_back(*image1);
    images.push_back(*image2);
    cout << "Stitching images" << endl;
    cv::Stitcher stitcher = cv::Stitcher::createDefault();
    cv::Stitcher::Status status = stitcher.stitch(images, resultImage);

    // Error handling
    if (status != cv::Stitcher::Status::OK) {
        throw runtime_error("FeaturesandPositionImageStitcher failed to stitch images");
    }
    cout << "Returning result image" << endl;
    return resultImage;

   
}
