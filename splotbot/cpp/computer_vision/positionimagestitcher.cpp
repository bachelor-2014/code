#include <stdexcept>
#include <iostream>
#include <vector>
#include <climits>

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

        cv::namedWindow("temp");
        cv::namedWindow("mask");
        cv::namedWindow("result1");
        cv::namedWindow("result2");
        cv::namedWindow("result3");


        cv::Mat mask;
        cv::threshold(temp,mask,1.0,255.0,THRESH_BINARY_INV);

        cv::imshow("temp",temp);
        cv::imshow("mask",mask);
        cv::imshow("result1",result);

        bitwise_and(result,mask,result);

        cv::imshow("result3",result);
        result = result + temp;

        cv::imshow("result2",result);
        cv::waitKey(0);

    }

    return result;
}

cv::Mat PositionImageStitcher::translationMatrix(double x, double y){
    vector<double> transvec = {
        ((xStep[0] * (x-min_x)) + (yStep[0] * (y-min_y))),
        ((xStep[1] * (x-min_x)) + (yStep[1] * (y-min_y)))
    };

    cv::Mat tmat = cv::Mat::eye(3, 3, CV_32FC1);
    tmat.at<float>(0,2) = (float)transvec[0];
    tmat.at<float>(1,2) = (float)transvec[1];

    return tmat;
}

void PositionImageStitcher::findMaxValues(){
    min_x = INT_MAX;
    min_y = INT_MAX;
    max_x = 0;
    max_y = 0;
    vector<float> mip;

    for(auto grabbed : grabbedImages){
            cout << to_string(min_x) << "," << to_string(min_y) << endl;
            cout << to_string(grabbed.positionX) << "," << to_string(grabbed.positionY) << endl;
        if(grabbed.positionX <= min_x && grabbed.positionY <= min_y){
            min_x = grabbed.positionX;
            min_y = grabbed.positionY;
        }
        if(grabbed.positionX >= max_x && grabbed.positionY >= max_y){
            max_x = grabbed.positionX;
            max_y = grabbed.positionY;
            mip = { ((float)grabbed.image.rows), ((float)grabbed.image.cols), 1.0 };
        }
    }
    cout << to_string(max_x) << to_string(max_y) << endl;
    //Construct translation matrix
    cv::Mat transmat = translationMatrix(max_x, max_y);

    //Find the min and max pixel values in image with max steps
    cv::Mat maximgpixels = cv::Mat(mip);

    //Find total size of image 
    size = transmat * maximgpixels;
}

