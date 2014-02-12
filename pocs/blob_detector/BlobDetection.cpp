#include <stdio.h>
#include <opencv2/opencv.hpp>

//Variables for trackbar
int h1=104;
int s1=123;
int v1=0;

int h2=124;
int s2=255;
int v2=255;

int structuringElementSize = 3;
int structuringElementType= 2;

int scale=1;

cv::Mat detectBlobs(cv::Mat image) {
    cv::Mat hsvImage;
    cv::Mat binaryImage;

    // Convert to HSV color space
    cv::cvtColor(image, hsvImage, CV_BGR2HSV);

    // Threshold the image
    cv::inRange(hsvImage, cv::Scalar(h1,s1,v1), cv::Scalar(h2,s2,v2), binaryImage);

    // Do opening and closing
    int seType;

    if( structuringElementType == 0 ){ seType = cv::MORPH_RECT; }
    else if( structuringElementType == 1 ){ seType = cv::MORPH_CROSS; }
    else if( structuringElementType == 2) { seType = cv::MORPH_ELLIPSE; }

    cv::Mat element = getStructuringElement(
        seType,
        cv::Size( 2*structuringElementSize + 1, 2*structuringElementSize+1 ),
        cv::Point( structuringElementSize, structuringElementSize )
    );
    
    erode(binaryImage, binaryImage, element);
    dilate(binaryImage, binaryImage, element);

    dilate(binaryImage, binaryImage, element);
    erode(binaryImage, binaryImage, element);

    // Do blob detection
    cv::SimpleBlobDetector::Params params; 

    params.thresholdStep = 5;
    params.minThreshold = 40;
    params.maxThreshold = 60;
    params.minDistBetweenBlobs = 10.0; 

    params.filterByColor = true;
    params.blobColor = 255;

    //params.filterByArea = false;        
    params.minArea = 100.0;              
    params.maxArea = 8000.0;             

    params.filterByCircularity = false;
    params.minCircularity = 0;
    params.maxCircularity = 99999;

    params.filterByInertia = false;
    params.minInertiaRatio = 0;
    params.maxInertiaRatio = 99999;

    params.filterByConvexity = false;
    params.minConvexity = 0;
    params.maxConvexity = 99999;

    cv::SimpleBlobDetector blobDetector(params);
    std::vector<cv::KeyPoint> blobs;
    blobDetector.detect(binaryImage, blobs);

    cv::Mat blobImage;
    cv::drawKeypoints(binaryImage, blobs, blobImage, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    return blobImage;
    //return image;
}

int main( int argc, char** argv )
{
    if (argc != 2) {
        printf("Invalid number of arguments (1 needed)\n");
        return -1;
    }

    cv::VideoCapture cap(std::stoi(argv[1]));//"../captures/1.avi");//

    if (!cap.isOpened())
    {
        printf("No video data\n");
        return -1;
    }

    //Windows
    cvNamedWindow("Original image", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Result image", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Controls", CV_WINDOW_AUTOSIZE);

    //Creating the trackbars
    cvCreateTrackbar("H1","Controls",&h1,255,0);
    cvCreateTrackbar("H2","Controls",&h2,255,0);
    cvCreateTrackbar("S1","Controls",&s1,255,0);
    cvCreateTrackbar("S2","Controls",&s2,255,0);
    cvCreateTrackbar("V1","Controls",&v1,255,0);
    cvCreateTrackbar("V2","Controls",&v2,255,0);
    cvCreateTrackbar("Structuring element size","Controls",&structuringElementSize,30,0);
    cvCreateTrackbar("Structuring element type","Controls",&structuringElementType,2,0);
    cvCreateTrackbar("Scale","Controls",&scale,19,0);

    cv::setTrackbarPos("H1", "Controls", h1);
    cv::setTrackbarPos("H2", "Controls", h2);
    cv::setTrackbarPos("S1", "Controls", s1);
    cv::setTrackbarPos("S2", "Controls", s2);
    cv::setTrackbarPos("V1", "Controls", v1);
    cv::setTrackbarPos("V2", "Controls", v2);
    cv::setTrackbarPos("Structuring element size", "Controls", structuringElementSize);
    cv::setTrackbarPos("Structuring element type", "Controls", structuringElementType);
    cv::setTrackbarPos("Scale", "Controls", scale);

    cv::Mat image;
    cv::Mat resultImage;

    cap >> image;

    while(true) {
        double scaleFactor = (double)(scale+1) / 10;
        cv::resize(image, image, cv::Size(), scaleFactor, scaleFactor);
        resultImage = detectBlobs(image);
        cv::imshow("Original image", image);
        cv::imshow("Result image", resultImage);

        //printf("(%d, %d, %d) to (%d, %d, %d), SE = %d\n", h1, s1, v1, h2, s2, v2, structuringElementSize);

        cap >> image;
        cv::waitKey(1);
    }

    return 0;
}
