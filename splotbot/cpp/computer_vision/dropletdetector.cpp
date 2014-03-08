#include <iostream>
#include <opencv2/opencv.hpp>
#include <cvblob.h>

#include "dropletdetector.h"

using namespace std;

// Constructor. Initializes the state of the DropletDetector
DropletDetector::DropletDetector(int minArea, int maxArea, cv::Scalar minColor, cv::Scalar maxColor, int structuringElementSize): minArea(minArea), maxArea(maxArea), minColor(minColor), maxColor(maxColor), structuringElementSize(structuringElementSize) {
    // Empty constructor
}

// Detect the largest matching droplet on the given image
Droplet DropletDetector::detectDroplet(cv::Mat image) {
    Droplet droplet;

    cv::Mat blurredImage;
    cv::Mat hsvImage;
    cv::Mat thresholdedImage;
    cv::Mat morphologyImage;

    // Apply a slight gaussian blur to the image
    cv::GaussianBlur(image, blurredImage, cv::Size(3,3), 1.0);

    // Convert the image to HSV
    cv::cvtColor(blurredImage, hsvImage, CV_BGR2HSV);

    // Threshold the image based on the min and max colors
    cv::inRange(hsvImage, minColor, maxColor, thresholdedImage);

    // Apply morphology
    morphologyImage = thresholdedImage.clone();

    int elementType = cv::MORPH_CROSS;
    cv::Mat element = getStructuringElement(
        elementType,
        cv::Size( 2*structuringElementSize + 1, 2*structuringElementSize+1 ),
        cv::Point( structuringElementSize, structuringElementSize )
    );
    
    erode(morphologyImage, morphologyImage, element);
    dilate(morphologyImage, morphologyImage, element);

    dilate(morphologyImage, morphologyImage, element);
    erode(morphologyImage, morphologyImage, element);

    // Do BLOB extraction
    cvb::CvBlobs blobs;
    IplImage *labelImg = cvCreateImage( morphologyImage.size(), IPL_DEPTH_LABEL, 1 );
    IplImage morphologyImg = morphologyImage;
    IplImage img = image;
    unsigned int result = cvb::cvLabel(&morphologyImg, labelImg, blobs);

    // Filter the blobs by area
    cvb::cvFilterByArea(blobs, minArea, maxArea);

    // Select the largest BLOB matching the criteria
    double maxArea = 0;
    for (cvb::CvBlobs::const_iterator it = blobs.begin(); it != blobs.end(); ++it)
    {
        double area = it->second->area;

        if (area > maxArea) {
            droplet.area = area;
            droplet.minX = it->second->minx;
            droplet.maxX = it->second->maxx;
            droplet.minY = it->second->miny;
            droplet.maxY = it->second->maxy;
            droplet.centroidX = it->second->centroid.x;
            droplet.centroidY = it->second->centroid.y;
        }

    }

    //// DEBUG: Render the blobs on the image
    //cvb::cvRenderBlobs( labelImg, blobs, &img, &img );

    //// DEBUG: Show the images
    //cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
    //cv::namedWindow("Blurred", cv::WINDOW_AUTOSIZE);
    //cv::namedWindow("Thresholded", cv::WINDOW_AUTOSIZE);
    //cv::namedWindow("Morphology", cv::WINDOW_AUTOSIZE);

    //cv::imshow("Original", image);
    //cv::imshow("Blurred", blurredImage);
    //cv::imshow("Thresholded", thresholdedImage);
    //cv::imshow("Morphology", morphologyImage);

    return droplet;
}
