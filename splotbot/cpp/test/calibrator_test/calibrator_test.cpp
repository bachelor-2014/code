#include <opencv2/opencv.hpp>

#include "../../computer_vision/calibrator.h"

using namespace std;

int main() {
    vector<cv::Mat> images;
    images.push_back(cv::imread("test/calibrator_test/data/grab0_0.jpg"));
    images.push_back(cv::imread("test/calibrator_test/data/grab0_1.jpg"));
    images.push_back(cv::imread("test/calibrator_test/data/grab0_2.jpg"));
    images.push_back(cv::imread("test/calibrator_test/data/grab1_0.jpg"));
    images.push_back(cv::imread("test/calibrator_test/data/grab1_1.jpg"));
    images.push_back(cv::imread("test/calibrator_test/data/grab1_2.jpg"));
    images.push_back(cv::imread("test/calibrator_test/data/grab2_0.jpg"));
    images.push_back(cv::imread("test/calibrator_test/data/grab2_1.jpg"));
    images.push_back(cv::imread("test/calibrator_test/data/grab2_2.jpg"));

    Calibrator *calibrator = new Calibrator("data/config.xml");

    cv::Mat coeffs;
    cv::Mat intrinsicMatrix;
    calibrator->calibrate(images,&coeffs,&intrinsicMatrix);

    cv::Mat srcImage = cv::imread("test/calibrator_test/data/grab0_0.jpg");
    cv::Mat destImage;
    cout << "Coeffs" << coeffs << endl;
    cv::undistort(srcImage,destImage,intrinsicMatrix,coeffs);

    cv::namedWindow("result");
    cv::namedWindow("original");

    cv::imshow("result",destImage);
    cv::imshow("original",srcImage);

    cv::waitKey(0);
}
