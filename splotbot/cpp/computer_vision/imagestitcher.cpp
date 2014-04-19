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

    cout << "ImageStitcher: Grapping image from camera '" << camera->name << "'" << endl;
    //cout << "ImageStitcher: Opening capture device " << camera->videoDevice << " ..." << endl;
    //cv::VideoCapture cap(camera->videoDevice);
    //cout << "ImageStitcher: Opened capture device" << endl;
    //cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    //cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

    //cv::Mat image;
    //bool success = cap.read(image);

    //if (!success) {
    //    stringstream ss;
    //    ss << "ImageStitcher failed to grab image from device " << camera->videoDevice;
    //    throw runtime_error(ss.str());
    //}

    //cap.release();

    //grabbedImage.image = image;
    cv::Mat image = camera->grabImage();
    grabbedImage.image = image;

    //cout << "ImageStitcher: grabbing image ..." << endl;
    //cv::Mat image = camera->grabImage();
    //cout << "ImageStitcher: grabbed image" << endl;
    //grabbedImage.image = image;

    //TODO DEBUG remove this when done
    stringstream fs;
    fs << "data/images/grab" << positionX << "_" << positionY << ".jpg";
    cv::imwrite(fs.str(), image);
    //TODO remove the above when done

    grabbedImages.push_back(grabbedImage);
}
