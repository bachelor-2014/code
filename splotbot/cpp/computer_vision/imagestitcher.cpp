#include <opencv2/opencv.hpp>

#include "imagestitcher.h"

using namespace std;

/**
 * Constructs a new image stitcher
 */
ImageStitcher::ImageStitcher(int videoDevice): videoDevice(videoDevice) {
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

    cv::VideoCapture cap(videoDevice);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

    cv::Mat image;
    bool success = cap.read(image);

    if (!success) {
        stringstream ss;
        ss << "ImageStitcher failed to grab image from device " << videoDevice;
        throw runtime_error(ss.str());
    }

    cap.release();

    grabbedImage.image = image;

    //TODO DEBUG remove this when done
    stringstream fs;
    fs << "data/images/grab" << positionX << "_" << positionY << ".jpg";
    cv::imwrite(fs.str(), image);
    //TODO remove the above when done

    grabbedImages.push_back(grabbedImage);
}
