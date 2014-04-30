#include <iostream>
#include <chrono>
#include <unistd.h>
#include <opencv2/opencv.hpp>

#include "../../computer_vision/imagestitcher.h"
#include "../../computer_vision/featuresandpositionimagestitcher.h"

using namespace std;

int main() {
    cout << "Constructing Image Stitcher" << endl;
    //Load test data
    cv::Mat image1 = imread("grab40_30.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat image2 = imread("grab40_35.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat image3 = imread("grab45_30.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat image4 = imread("grab45_35.jpg", CV_LOAD_IMAGE_COLOR);

    vector<GrabbedImage> gv;
    GrabbedImage gi;
    gi.positionX = 40;
    gi.positionY = 30;
    gi.image = image1;
    GrabbedImage gi2;
    gi2.positionX = 40;
    gi2.positionY = 35;
    gi2.image = image2;
    GrabbedImage gi3;
    gi3.positionX = 45;
    gi3.positionY = 30;
    gi3.image = image3;
    GrabbedImage gi4;
    gi4.positionX = 45;
    gi4.positionY = 35;
    gi4.image = image4;

    gv.push_back(gi);
    gv.push_back(gi2);
    gv.push_back(gi3);
    gv.push_back(gi4);

    Camera camera("Cam", 0, "event");
    camera.xStep = {24.915325033641395, 5.7030984481543534};
    camera.yStep = {15.704089269213707, -2.6978784794984407};

    //camera.yStep = {-0.4,18.6};
    //camera.xStep = {-18.2, 0.0};

    FeaturesAndPositionImageStitcher pis(gv, &camera, 5);
    cout << "Testing stitching" << endl;
    cv::Mat stitched_image = pis.stitch();
    cv::namedWindow( "stitched", WINDOW_AUTOSIZE );
    cv::imshow( "stitched",  stitched_image);

    cv::waitKey(0);
}
