#include <stdio.h>
#include <iostream>
 
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

cv::Mat detectBlobs(cv::Mat image) {
    cv::Mat greyImage;
    cv::cvtColor(image, greyImage, CV_BGR2GRAY);

    cv::Mat binaryImage;
    cv::threshold(greyImage, binaryImage, 100.0, 255.0, cv::THRESH_BINARY);

    cv::SimpleBlobDetector::Params params; 

    params.thresholdStep = 5;
    params.minThreshold = 40;
    params.maxThreshold = 60;
    params.minDistBetweenBlobs = 10.0; 

    params.filterByColor = true;
    params.blobColor = 255;

    params.filterByArea = false;        
    params.minArea = 100.0;              
    params.maxArea = 8000.0;             

    params.filterByCircularity = false;
    //params.minCircularity = 0;
    //params.maxCircularity = 99999;

    params.filterByInertia = false;
    //params.minInertiaRatio = 0;
    //params.maxInertiaRatio = 99999;

    params.filterByConvexity = false;
    //params.minConvexity = 0;
    //params.maxConvexity = 99999;

    //cv::SimpleBlobDetector detector(params);
    cv::SurfFeatureDetector detector( 400 );
    std::vector<cv::KeyPoint> blobs;
    detector.detect(binaryImage, blobs);

    cv::Mat blobImage;    
    cv::drawKeypoints(binaryImage, blobs, blobImage, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    return blobImage;
}

int main( int argc, char** argv )
{
    if (argc != 2) {
        printf("Invalid number of arguments (1 needed)\n");
        return -1;
    }

    cv::VideoCapture cap("../captures/1.avi");//std::stoi(argv[1]));

    if (!cap.isOpened())
    {
        printf("No video data\n");
        return -1;
    }

    cv::Mat image;

    //cv::namedWindow("Result",1);

    cap >> image;

    while(true) {
        image = detectBlobs(image);
        //cv::imwrite("Result",image);

        cap >> image;
        //cv::waitKey(1);
    }

    return 0;
}
