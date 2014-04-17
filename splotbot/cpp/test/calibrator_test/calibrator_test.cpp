#include <opencv2/opencv.hpp>

#include "../../computer_vision/calibrator.h"

using namespace std;

int main() {
    vector<cv::Mat> images;
    images.push_back(cv::imread("data/grab0_0.jpg"));
    images.push_back(cv::imread("data/grab0_1.jpg"));
    images.push_back(cv::imread("data/grab0_2.jpg"));
    images.push_back(cv::imread("data/grab1_0.jpg"));
    images.push_back(cv::imread("data/grab1_1.jpg"));
    images.push_back(cv::imread("data/grab1_2.jpg"));
    images.push_back(cv::imread("data/grab2_0.jpg"));
    images.push_back(cv::imread("data/grab2_1.jpg"));
    images.push_back(cv::imread("data/grab2_2.jpg"));

//    images.push_back(cv::imread("data/cheeses/webcam-capture-1397735145.jpeg"));
//    images.push_back(cv::imread("data/cheeses/webcam-capture-1397735146.jpeg"));
//    images.push_back(cv::imread("data/cheeses/webcam-capture-1397735147.jpeg"));
//    images.push_back(cv::imread("data/cheeses/webcam-capture-1397735148.jpeg"));
//    images.push_back(cv::imread("data/cheeses/webcam-capture-1397735149.jpeg"));
//    images.push_back(cv::imread("data/cheeses/webcam-capture-1397735150.jpeg"));
//    images.push_back(cv::imread("data/cheeses/webcam-capture-1397735151.jpeg"));

    Calibrator *calibrator = new Calibrator("data/config.xml");

    cv::Mat coeffs;
    cv::Mat intrinsicMatrix;
    calibrator->calibrate(images,&coeffs,&intrinsicMatrix);

    cv::Mat srcImage = cv::imread("data/grab0_0.jpg");
    cv::Mat destImage;
    cv::undistort(srcImage,destImage,intrinsicMatrix,coeffs);

    cv::namedWindow("result");
    cv::namedWindow("original");

    cv::imshow("result",destImage);
    cv::imshow("original",srcImage);

    cv::waitKey(0);
}
