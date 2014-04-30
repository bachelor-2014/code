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
    cv::Mat result = cv::Mat::zeros(total_height,total_width,CV_8UC3);

    //Warp images
    for (auto grabbed : grabbedImages){

        cv::Mat t = translationMatrix(grabbed.positionX, grabbed.positionY);
        cv::Mat temp = cv::Mat::zeros(total_height,total_width,CV_8UC3);
        cv::warpPerspective(grabbed.image, temp, t, temp.size());


        // Create a mask
        cv::Mat mask;
        cv::threshold(temp,mask,1.0,255.0,THRESH_BINARY_INV);

        // Reduce the size of the mask a bit
        int structuringElementSize = 5;
        int elementType = cv::MORPH_RECT;

        cv::Mat element = getStructuringElement(
            elementType,
            cv::Size( 2*structuringElementSize + 1, 2*structuringElementSize+1 ),
            cv::Point( structuringElementSize, structuringElementSize )
        );

        dilate(mask, mask, element);

        // Remove the mask part of the result image
        bitwise_and(result,mask,result);

        // Remove the non-mask part of the temporary image
        bitwise_not(mask, mask);
        bitwise_and(temp, mask, temp);

        result = result + temp;
    }

    return result;
}

cv::Mat FeaturesAndPositionImageStitcher::translationMatrix(int x, int y){
    double x_trans;
    double y_trans;

    if(x_shift >= 0){
        x_trans = (x-min_x)*x_shift;
    }else{
        x_trans = (max_x-x)*abs(x_shift);
    }

    if(y_shift >= 0){
        y_trans = (y-min_y)*y_shift;
    }else{
        y_trans = (max_y-y)*abs(y_shift);
    }

    cv::Mat tmat = cv::Mat::eye(3, 3, CV_32FC1);
    tmat.at<float>(0,2) = (float)x_trans;
    tmat.at<float>(1,2) = (float)y_trans;

    return tmat;
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
    double width = grabbedImages[0].image.size().width;
    double height = grabbedImages[0].image.size().height;

    total_width = width+(max_x-min_x)*abs(x_shift);
    total_height = height+(max_y-min_y)*abs(y_shift);
    cout << "width,height" << to_string(width) << "," << to_string(height) << endl;
    cout << "total width,height" << to_string(total_width) << "," << to_string(total_height) << endl;
    cout << "min_x, max_x" << to_string(min_x) << "," << to_string(max_x) << endl;
    cout << "min_y, max_y" << to_string(min_y) << "," << to_string(max_y) << endl;
}

