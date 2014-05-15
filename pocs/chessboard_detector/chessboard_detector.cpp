#include <iostream>
#include <stdexcept>
#include <opencv2/opencv.hpp>

using namespace std;

cv::Mat detectAndDraw(cv::Mat image1) {
    cv::Size board_size = cv::Size(9, 6);

    vector<cv::Point2f> corners1;

    bool found1 = findChessboardCorners(image1, board_size, corners1);

    if (!found1) {
        throw runtime_error("Computer vision utils: Failed to detect chessboard corners when computing translation");
    }

    //Corner sums
    cv::Point2f corners1sum(0,0);

    cout << "Corner1sum before: " << corners1sum << endl;

    for(int i = 0; i<corners1.size(); i++){
        corners1sum.x += corners1[i].x;
        corners1sum.y += corners1[i].y;
    }
    cout << "Corner1sum: " << corners1sum << endl;

    //Center points
    cv::Point2f corners1center;
    corners1center.x = corners1sum.x / corners1.size();
    corners1center.y = corners1sum.y / corners1.size();

    cout << "Corner1center: " << corners1center << endl;


    drawChessboardCorners(image1, board_size, corners1, found1);
    cv::circle(image1, cv::Point(corners1center.x, corners1center.y), 5, cv::Scalar(0, 0, 255), 10);

    cv::namedWindow("result", CV_WINDOW_AUTOSIZE);
    cv::imshow("result", image1);
    cv::waitKey(0);
}

int main(int argc, char** argv) {

    for (int i = 1; i < argc; i++) {
        string filename(argv[i]);
        cv::Mat image = cv::imread(filename);
        detectAndDraw(image);
    }

    return 1;
}
