#include <stdio.h>
#include <opencv2/opencv.hpp>

typedef struct detection {
    int x;
    int y;
    int width;
    int height;
} Detection;

std::vector<Detection> detectBlobs(cv::Mat image);
