#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/stitching/stitcher.hpp>

using namespace cv;

int main( int argc, char** argv )
{
    if (argc != 3) {
        printf("Invalid number of arguments (2 needed)\n");
        return -1;
    }

    int frameNumber = std::stoi(argv[2]);
    VideoCapture cap(argv[1]);

    if (!cap.isOpened())
    {
        printf("No video data\n");
        return -1;
    }

    Mat image;
    vector<Mat> imageVector;
    Mat resultImage;

    int frn;

    bool success = cap.read(image);
    printf("Grabbing frame %d", frn);

    while (success) {
        imageVector.push_back(image);

        for (int i = 1; (i < frameNumber) && success; i++) {
            success = cap.grab();
            frn++;
            printf(" %d", frn);
        }

        if (success) success = cap.read(image);
        frn++;
        printf(" %d", frn);
    }

    printf("\nNumber of images: %lu\n", imageVector.size());

    Stitcher stitcher = Stitcher::createDefault();
    Stitcher::Status status = stitcher.stitch(imageVector, resultImage);

    if (status == Stitcher::OK) {
        return imwrite("result.jpg", resultImage);
    } else {
        printf("Error stitching image\n");
    }

    return 0;
}
