#include <iostream>
#include <chrono>
#include <unistd.h>
#include <opencv2/opencv.hpp>

#include "../../computer_vision/imagestitcher.h"
#include "../../computer_vision/featuresimagestitcher.h"

using namespace std;

int main() {
    cout << "Constructing image stitcher ..." << endl;
    ImageStitcher *st;
    FeaturesImageStitcher fst(0);
    st = &fst;
    cout << "Constructed image stitcher" << endl;

    cout << "Grabbing images ..." << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Grabbing image " << i << " ..." << endl;

        sleep(1);
        cout << 3 << endl;
        sleep(1);
        cout << 2 << endl;
        sleep(1);
        cout << 1 << endl;
        sleep(1);

        st->grabImage(i, i);
        cout << "Grabbed image " << i << endl;

        sleep(3);
    }
    cout << "Grabbed images" << endl;

    cout << "Stitching images ..." << endl;
    cv::Mat resultImage;
    resultImage = st->stitch();
    cout << "Stitched images" << endl;

    cout << "Writing image ..." << endl;
    cv::imwrite("images/result.jpg", resultImage);
    cout << "Wrote image" << endl;
}
