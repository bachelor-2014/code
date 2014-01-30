#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/stitching/stitcher.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    vector<Mat> vImg;
    Mat rImg;

    for (int i = 1; i<argc; i++){
        vImg.push_back(imread(argv[i]));
    }

    Stitcher stitcher = Stitcher::createDefault();
    stitcher.stitch(vImg, rImg);

    return imwrite("result.jpg",rImg);
}
