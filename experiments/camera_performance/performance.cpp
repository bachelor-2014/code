#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int numberOfFrames(string videoFile){
        cv::VideoCapture *cap = new cv::VideoCapture(videoFile);

        cv::Mat image;
        int frames = 0;
        bool success = true;
        while(success){
                success = cap->read(image);
                frames++;
        }

        cap->release();
        free(cap);

        return frames;
}

int main() {
    cout << "Running performance experiments" << endl;

    int with_tracking = numberOfFrames("with_tracking.avi");
    int without_tracking = numberOfFrames("without_tracking.avi");

    cout << "With tracking " << with_tracking << endl;
    cout << "Without tracking " << without_tracking << endl;
    return 1;
}
