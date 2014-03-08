#ifndef BLOBDETECTOR_H 
#define BLOBDETECTOR_H 

#include <iostream>
#include <opencv2/opencv.hpp>
#include <cvblob.h>

using namespace std;

/**
 *  Represents a detected droplet
 */
typedef struct {
    int minX;
    int minY;
    int maxX;
    int maxY;
    double centroidX;
    double centroidY;
    int area;
} Droplet;

/**
 * DropletDetector is capable of detecting droplets through use
 * of BLOB detection and BLOB feature extration.
 * It is constructed with the followed arguments:
 * 
 * minArea: The minimum area of the droplet to detect
 * minArea: The maximum area of the droplet to detect
 * minColor: The minimum color of the droplet to detect
 * maxColor: The maximum color of the droplet to detect
 * structuringElementSize: The size of the structuring element used when
 *      applying morphology
 *
 * Use the detectDroplet(image) method to detect a droplet on the given image.
 */
class DropletDetector {
    public:
        DropletDetector(int minArea, int maxArea, cv::Scalar minColor, cv::Scalar maxColor, int structuringElementSize);
        Droplet detectDroplet(cv::Mat image);

    private:
        int minArea;
        int maxArea;
        cv::Scalar minColor;
        cv::Scalar maxColor;
        int structuringElementSize;
};

#endif
