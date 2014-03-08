#ifndef DROPLETDETECTOR_H 
#define DROPLETDETECTOR_H 

#include <iostream>
#include <opencv2/opencv.hpp>
#include <cvblob.h>
#include "datastructs.h"

using namespace std;

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
        DropletDetector(int minArea, int maxArea, ColorInterval colorInterval, int structuringElementSize);
        Droplet detectDroplet(cv::Mat image);

    private:
        int minArea;
        int maxArea;
        int structuringElementSize;
        ColorInterval colorInterval;
};

#endif
