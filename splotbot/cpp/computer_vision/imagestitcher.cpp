#include <stdexcept>
#include <opencv2/opencv.hpp>

#include "imagestitcher.h"

using namespace std;

/**
 * Constructs a new image stitcher
 */
ImageStitcher::ImageStitcher(Camera *camera): camera(camera) {
    // Empty constructor
    // All fields are initialized at this point
}

/**
 * Grabs a single image and stores it together with the given
 * position so it can be stitched at a later point
 */
void ImageStitcher::grabImage(int positionX, int positionY) {
    GrabbedImage grabbedImage;
    grabbedImage.positionX = positionX;
    grabbedImage.positionY = positionY;

    cv::Mat image = camera->grabImage();
    grabbedImage.image = image;

    //TODO DEBUG remove this when done
    stringstream fs;
    fs << "data/images/grab" << positionX << "_" << positionY << ".jpg";
    cv::imwrite(fs.str(), image);
    //TODO remove the above when done

    grabbedImages.push_back(grabbedImage);
}
