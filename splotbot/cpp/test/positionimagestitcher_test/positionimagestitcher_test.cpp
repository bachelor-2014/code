#include <iostream>
#include <chrono>
#include <unistd.h>
#include <opencv2/opencv.hpp>

#include "../../computer_vision/imagestitcher.h"
#include "../../computer_vision/positionimagestitcher.h"

using namespace std;

int main() {
    cout << "Constructing Image Stitcher" << endl;
    //Load test data
    cv::Mat image = imread("100px.png", CV_LOAD_IMAGE_COLOR);

    vector<GrabbedImage> gv;
    GrabbedImage gi;
    gi.positionX = 0;
    gi.positionY = 0;
    gi.image = image;
    GrabbedImage gi2;
    gi2.positionX = 1;
    gi2.positionY = 0;
    gi2.image = image;

    gv.push_back(gi);
    gv.push_back(gi2);

    PositionImageStitcher pis(gv, NULL);
    cout << "Testing stitching" << endl;
    cv::Mat stitched_image = pis.stitch();
    cv::namedWindow( "stitched", WINDOW_AUTOSIZE );
    cv::imshow( "stitched",  stitched_image);
    cv::waitKey(0);
}
