#include <stdexcept>
#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

#include "positionimagestitcher.h"

using namespace std;

/**
 * Constructs a new PositionImageStitcher
 */
PositionImageStitcher::PositionImageStitcher(Camera *camera): ImageStitcher(camera) {
    // Empty constructor
    // The initialization is done in the base class
}

PositionImageStitcher::PositionImageStitcher(vector<GrabbedImage> grabbedImages, Camera *camera): ImageStitcher(camera){
    this->grabbedImages = grabbedImages;
}

/*
 * Stitch together the images grabbed by the PositionImageStitcher
 */
cv::Mat PositionImageStitcher::stitch() {
    //Get step values
    xStep = camera->xStep;
    yStep = camera->yStep;

    double left = xStep[0] + (-1.0)*xStep[1];
    double down = yStep[0] + (-1.0)*yStep[1];
    xStep[0] = -left;
    xStep[1] = 0;

    yStep[1] = down;
    yStep[0] = 0;

    minvector = {0.0, 0.0};
    minpixelvector = {0.0, 0.0};
    cout << "xStep" << cv::Mat(xStep) << endl;
    cout << "yStep" << cv::Mat(yStep) << endl;

    //Find the max values
    findMaxValues();
    //Finally warp the images
    cv::Mat warped = warp();
    return warped;
}

cv::Mat PositionImageStitcher::warp() {
    //Result image to warp to
    int size_x = (int) size.at<float>(0);
    int size_y = (int) size.at<float>(1);
    cv::Mat result = cv::Mat::zeros(size_y,size_x,CV_8UC3);

    //Warp images
    for (auto grabbed : grabbedImages){

        cv::Mat t = translationMatrix(grabbed.positionX, grabbed.positionY);
        cv::Mat temp = cv::Mat::zeros(size_y,size_x,CV_8UC3);
        cv::warpPerspective(grabbed.image, temp, t, temp.size());


        cv::Mat mask;
        cv::threshold(temp,mask,1.0,255.0,THRESH_BINARY_INV);

        bitwise_and(result,mask,result);

        result = result + temp;

    }

    return result;
}

cv::Mat PositionImageStitcher::translationMatrix(int x, int y){
    vector<double> transvec = {
        ((xStep[0] * (x-min_x)) + (yStep[0] * (y-min_y))) + minvector[0] - minpixelvector[0],
        ((xStep[1] * (x-min_x)) + (yStep[1] * (y-min_y))) + minvector[1] - minpixelvector[1]
    };

    cv::Mat tmat = cv::Mat::eye(3, 3, CV_32FC1);
    tmat.at<float>(0,2) = (float)transvec[0];
    tmat.at<float>(1,2) = (float)transvec[1];
    cout << "tmat: " << tmat << endl;

    return tmat;
}

void PositionImageStitcher::findMaxValues(){
    min_x = INT_MAX;
    min_y = INT_MAX;
    max_x = 0;
    max_y = 0;
    vector<float> max_pixel_values(3);
    max_pixel_values[2] = 1.0;

    for(auto grabbed : grabbedImages){
            cout << to_string(min_x) << "," << to_string(min_y) << endl;
            cout << to_string(grabbed.positionX) << "," << to_string(grabbed.positionY) << endl;
        if(grabbed.positionX <= min_x ){
            min_x = grabbed.positionX;
        }
        if(grabbed.positionY <= min_y){
            min_y = grabbed.positionY;
        }
        if(grabbed.positionX >= max_x){
            max_x = grabbed.positionX;
            max_pixel_values[0] = (float) grabbed.image.cols;
        }

        if(grabbed.positionY >= max_y){
            max_y = grabbed.positionY;
            max_pixel_values[1] = (float) grabbed.image.rows;
        }
    }

    for(auto grabbed : grabbedImages){
        cv::Mat t = translationMatrix(grabbed.positionX, grabbed.positionY); 
        cout << "Possibly min vector" << t << endl;
        if(t.at<float>(0,2) < minvector[0]){
            minvector[0] = t.at<float>(0,2);
        }

        if(t.at<float>(1,2) < minvector[1]){
            minvector[1] = t.at<float>(1,2);
        }
    }

    minvector[0] = abs(minvector[0]);
    minvector[1] = abs(minvector[1]);
    cout << "Min vector" << cv::Mat(minvector) << endl;
    

    //Find the min and max pixel values in image with max steps
    cv::Mat max_pixel_values_matrix = cv::Mat(max_pixel_values);

    //Find total size of image 
    cv::Mat transmat = translationMatrix(max_x, max_y);
    cout << "Transmat for size" << transmat << endl;
    size = transmat * max_pixel_values_matrix;
    cout << "Max pixel values matrix: " << max_pixel_values_matrix << endl;
    cout << "Size: " << size << endl;
}

