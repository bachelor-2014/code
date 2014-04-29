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

/*

double rect_x, rect_y, rect_w, rect_h;
vector<cv::Rect> new_roi;
vector<cv::Rect> result_roi;

// Add ROI in the x direction
if (x != min_x) {

    // Positive shift
    if (x_shift >= 0) {
        // Add ROI for the new image
        rect_x = 0.0;
        rect_y = 0.0;
        rect_w = x_shift * step_size;
        rect_h = height;

        new_roi.push_back(cv::Rect(rect_x, rect_y, rect_w, rect_h));

        // Add ROI for the result image
        rect_x = result.size().width - x_shift * step_size;
        if (y_shift >= 0) (
            rect_y = (y - min_y) * y_shift;
        } else {
            rect_y = (max_y - y) * abs(y_shift);
        }
        // Use same width and height as above

        result_roi.push_back(cv::Rect(rect_x, rect_y, rect_w, rect_h));

    // Negative shift
    } else {
        // Add ROI for the new image
        rect_x = width - abs(x_shift);
        rect_y = 0.0;
        rect_w = abs(x_shift) * step_size;
        rect_h = height;

        new_roi.push_back(cv::Rect(rect_x, rect_y, rect_w, rect_h));

        // Add ROI for the result image
        rect_x = 0;
        if (y_shift >= 0) (
            rect_y = (y - min_y) * y_shift;
        } else {
            rect_y = (max_y - y) * abs(y_shift);
        }
        // Use same width and height as above

        result_roi.push_back(cv::Rect(rect_x, rect_y, rect_w, rect_h));
    }
}

// Add ROI in the y direction
if (y != min_y) {

    // Positive shift
    if (y_shift >= 0) {
        // Add ROI for the new image
        rect_x = 0.0;
        rect_y = 0.0;
        rect_w = width;
        rect_h = y_shift * step_size;

        new_roi.push_back(cv::Rect(rect_x, rect_y, rect_w, rect_h));

        // Add ROI for the result image
        rect_y = result.size().height - y_shift * step_size;
        if (x_shift >= 0) (
            rect_x = (x - min_x) * x_shift;
        } else {
            rect_x = (max_x - x) * abs(x_shift);
        }
        // Use same width and height as above

        result_roi.push_back(cv::Rect(rect_x, rect_y, rect_w, rect_h));

    // Negative shift
    } else {
        // Add ROI for the new image
        rect_x = 0.0;
        rect_y = height - abs(y_shift);
        rect_w = width;
        rect_h = abs(y_shift) * step_size;

        new_roi.push_back(cv::Rect(rect_x, rect_y, rect_w, rect_h));

        // Add ROI for the result image
        rect_y = 0;
        if (x_shift >= 0) (
            rect_x = (x - min_x) * x_shift;
        } else {
            rect_x = (max_x - x) * abs(x_shift);
        }
        // Use same width and height as above

        result_roi.push_back(cv::Rect(rect_x, rect_y, rect_w, rect_h));
    }
}
*/
