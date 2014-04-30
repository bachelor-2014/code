#include <stdexcept>
#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

#include "featuresandpositionimagestitcher.h"

using namespace std;

/**
 * Constructs a new FeaturesAndPositionImageStitcher
 */
FeaturesAndPositionImageStitcher::FeaturesAndPositionImageStitcher(Camera *camera, int stepSize): ImageStitcher(camera, stepSize) {
    // Empty constructor
    // The initialization is done in the base class
}

FeaturesAndPositionImageStitcher::FeaturesAndPositionImageStitcher(vector<GrabbedImage> grabbedImages, Camera *camera, int stepSize): ImageStitcher(camera, stepSize){
    this->grabbedImages = grabbedImages;
}

/*
 * Stitch together the images grabbed by the FeaturesAndPositionImageStitcher
 */
cv::Mat FeaturesAndPositionImageStitcher::stitch() {
    //Get step values
    vector<double> xStep = camera->xStep;
    vector<double> yStep = camera->yStep;

    double left = xStep[0] + (-1.0)*xStep[1];
    double down = yStep[0] + (-1.0)*yStep[1];

    x_shift = -left;
    y_shift = down;

    cout << "xStep" << cv::Mat(xStep) << endl;
    cout << "yStep" << cv::Mat(yStep) << endl;

    //Find the max values
    findMaxValues();
    //Finally warp the images
    cv::Mat warped = warp();
    return warped;
}

cv::Mat FeaturesAndPositionImageStitcher::warp() {
    //Result image to warp to
    cv::Mat result = grabbedImages[0].image;
    double width = result.size().width;
    double height = result.size().height;

    // values for the regions of interest
    double rect_x, rect_y, rect_w, rect_h;
    vector<vector<cv::Rect>> roi(2);
    vector<cv::Mat> images(2);

    //Warp images
    for (auto grabbed : grabbedImages){

        // Position of the image for convenience
        int x = grabbed.positionX;
        int y = grabbed.positionY;

        // Skip the first image
        if (x == min_x && y == min_y) {
            continue;
        }

        // Containers for the regions of interest
        vector<cv::Rect> new_roi;
        vector<cv::Rect> result_roi;

        // Compute the regions of interest
        // Add ROI in the x direction
        if (x != min_x) {

            // Positive shift
            if (x_shift >= 0) {
                // Add ROI for the new image
                rect_x = 0.0;
                rect_y = 0.0;
                rect_w = width - x_shift * stepSize;
                rect_h = height;

                new_roi.push_back(cv::Rect(rect_x, rect_y, rect_w, rect_h));

                // Add ROI for the result image
                rect_x = x_shift * stepSize;
                if (y_shift >= 0) {
                    rect_y = (y - min_y) * y_shift;
                } else {
                    rect_y = (max_y - y) * abs(y_shift);
                }
                // Use same width and height as above

                result_roi.push_back(cv::Rect(rect_x, rect_y, rect_w, rect_h));

            // Negative shift
            } else {
                // Add ROI for the new image
                rect_x = abs(x_shift) * stepSize;
                rect_y = 0.0;
                rect_w = width - abs(x_shift) * stepSize;
                rect_h = height;

                new_roi.push_back(cv::Rect(rect_x, rect_y, rect_w, rect_h));

                // Add ROI for the result image
                rect_x = 0.0;
                rect_w = width;
                if (y_shift >= 0) {
                    rect_y = result.size().height - height; //(y - min_y) * y_shift;
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
                rect_h = height - (y_shift * stepSize);

                new_roi.push_back(cv::Rect(rect_x, rect_y, rect_w, rect_h));

                // Add ROI for the result image
                rect_y = y_shift * stepSize;
                if (x_shift >= 0) {
                    rect_x = (x - min_x) * abs(x_shift);
                } else {
                    rect_x = 0.0;
                }
                // Use same width and height as above

                result_roi.push_back(cv::Rect(rect_x, rect_y, rect_w, rect_h));

            // Negative shift
            } else {
                // Add ROI for the new image
                rect_x = 0.0;
                rect_y = height - abs(y_shift);
                rect_w = width;
                rect_h = height - (abs(y_shift) * stepSize);

                new_roi.push_back(cv::Rect(rect_x, rect_y, rect_w, rect_h));

                // Add ROI for the result image
                rect_y = 0;
                if (x_shift >= 0) {
                    rect_x = (x - min_x) * x_shift;
                } else {
                    rect_x = (max_x - x) * abs(x_shift);
                }
                // Use same width and height as above

                result_roi.push_back(cv::Rect(rect_x, rect_y, rect_w, rect_h));
            }
        }

        //DEBUG show the images with ROI //TODO remove this part
        //cout << "result_roi:" << endl;
        //for (auto r : result_roi) {
        //    cout << "-> [" << r.x << ", " << r.y << ", " << r.width << ", " << r.height << "]" << endl;
        //}

        //cout << "new_roi:" << endl;
        //for (auto r : new_roi) {
        //    cout << "-> [" << r.x << ", " << r.y << ", " << r.width << ", " << r.height << "]" << endl;
        //}

        //cv::namedWindow("result", WINDOW_AUTOSIZE);
        //cv::namedWindow("new", WINDOW_AUTOSIZE);

        //cv::Mat debugResult = result.clone();
        //cv::Mat debugNew = grabbed.image.clone();

        //for (auto r : result_roi) {
        //    cv::rectangle(debugResult, r, cv::Scalar(0, 255, 0), 5);
        //}

        //for (auto r : new_roi) {
        //    cv::rectangle(debugNew, r, cv::Scalar(0, 255, 0), 5);
        //}

        //cv::imshow("result", debugResult);
        //cv::imshow("new", debugNew);

        //cv::waitKey(0);
        //DEBUG

        // Stitch the images together
        roi[0] = result_roi;
        roi[1] = new_roi;

        images[0] = result.clone();
        images[1] = grabbed.image;

        cv::Stitcher stitcher = cv::Stitcher::createDefault();
        cv::Stitcher::Status status = stitcher.stitch(images, roi, result);

        // Error handling
        if (status != cv::Stitcher::Status::OK) {
            throw runtime_error("Failed to stitch images");
        }
    }

    return result;
}

void FeaturesAndPositionImageStitcher::findMaxValues(){
    min_x = INT_MAX;
    min_y = INT_MAX;
    max_x = 0;
    max_y = 0;

    for(auto grabbed : grabbedImages){
        if(grabbed.positionX < min_x ){
            min_x = grabbed.positionX;
        }
        if(grabbed.positionY < min_y){
            min_y = grabbed.positionY;
        }
        if(grabbed.positionX > max_x){
            max_x = grabbed.positionX;
        }

        if(grabbed.positionY > max_y){
            max_y = grabbed.positionY;
        }
    }
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
        rect_w = x_shift * stepSize;
        rect_h = height;

        new_roi.push_back(cv::Rect(rect_x, rect_y, rect_w, rect_h));

        // Add ROI for the result image
        rect_x = result.size().width - x_shift * stepSize;
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
        rect_w = abs(x_shift) * stepSize;
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
        rect_h = y_shift * stepSize;

        new_roi.push_back(cv::Rect(rect_x, rect_y, rect_w, rect_h));

        // Add ROI for the result image
        rect_y = result.size().height - y_shift * stepSize;
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
        rect_h = abs(y_shift) * stepSize;

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
