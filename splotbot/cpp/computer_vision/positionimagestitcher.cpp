#include <stdexcept>
#include <iostream>
#include <vector>

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

    //Finally warp the images
    cv::Mat warped = warp();
    return warped;
}

cv::Mat PositionImageStitcher::warp() {
    //Find min and max values
    min_x = 0;
    min_y = 0;
    max_x = 1;
    max_y = 0;

    xStep = {100,0};
    yStep = {0,100};

    //Construct translation matrix
    cv::Mat transmat = translationMatrix(max_x, max_y);
    cout << transmat << endl;
    
    //Find the min and max pixel values in image with max steps
    vector<float> mip = { 100.0, 100.0, 1.0 };
    cv::Mat maximgpixels = cv::Mat(mip);
    cout << maximgpixels << endl;

    //Find total size of image 
    cv::Mat size = transmat * maximgpixels;
    cout << size << endl;

    //Result image to warp to
    int size_x = (int) size.at<float>(0);
    int size_y = (int) size.at<float>(1);
    cv::Mat result = cv::Mat::zeros(size_y,size_x,CV_8UC3);

    //Warp images
    for (auto grabbed : grabbedImages){
        cv::Mat t = translationMatrix(grabbed.positionX, grabbed.positionY);
        cv::Mat temp = cv::Mat::zeros(size_y,size_x,CV_8UC3);
        cout << t << endl;
        cv::warpPerspective(grabbed.image, temp, t, temp.size());
        cv::addWeighted(result,1.0,temp,1.0,0,result);
    }

    return result;
}

cv::Mat PositionImageStitcher::translationMatrix(int x, int y){
    vector<int> transvec = {
        ((xStep[0] * (x-min_x)) + (yStep[0] * (y-min_y))),
        ((xStep[1] * (x-min_x)) + (yStep[1] * (y-min_y)))
    };

    cv::Mat tmat = cv::Mat::eye(3, 3, CV_32FC1);
    tmat.at<float>(0,2) = (float)transvec[0];
    tmat.at<float>(1,2) = (float)transvec[1];

    return tmat;
}
