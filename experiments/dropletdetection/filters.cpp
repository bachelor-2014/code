#include <iostream>
#include <sys/time.h>
#include <opencv2/opencv.hpp>
#include <unistd.h>

using namespace std;

typedef struct{
    cv::Mat image;
    double time;
} Result;

const int kernel_size = 31;
unsigned long t1,t2; // used for timing

cv::Mat gaussianBlur(cv::Mat in){

    cv::Mat out = in.clone();
    cv::GaussianBlur(in, out, cv::Size(kernel_size,kernel_size), 0,0);

    return out;
}

cv::Mat bilateralBlur(cv::Mat in){

    cv::Mat out = in.clone();
    cv::bilateralFilter(in, out, 31, 100, 100);
    return out;
}

cv::Mat medianBlur(cv::Mat in){

    cv::Mat out = in.clone();
    cv::medianBlur(in, out, kernel_size);

    return out;
}

unsigned long getCurrentTimeMs() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (unsigned long)((tv.tv_sec * 1000ul) + (tv.tv_usec / 1000ul));
}

int main() {
    t1 = getCurrentTimeMs();
    sleep(1);
    t2 = getCurrentTimeMs();
    cout << "Weird: " << (t2-t1) << "ms" << endl;
    cout << "Running filters experiments" << endl;

    cv::Mat src = cv::imread( "noiced.png", 1 );
    cv::Mat dst = src.clone();

    cv::imwrite( "results/tracking_experiment_original.png", dst );

    t1 = getCurrentTimeMs();
    dst = gaussianBlur(src);
    t2 = getCurrentTimeMs();
    cv::imwrite( "results/tracking_experiment_gaussian.png", dst );
    cout << "Gaussian: " << (t2 - t1) << "ms" << endl;

    t1 = getCurrentTimeMs();
    dst = bilateralBlur(src);
    t2 = getCurrentTimeMs();
    cv::imwrite( "results/tracking_experiment_bilateral.png", dst );
    cout << "Bilateral: " << (t2 - t1) << "ms" << endl;

    t1 = getCurrentTimeMs();
    dst = medianBlur(src);
    t2 = getCurrentTimeMs();
    cv::imwrite( "results/tracking_experiment_median.png", dst );
    cout << "Median: " << (t2 - t1) << "ms" << endl;

    cv::waitKey ( 0 );

    return 1;
}
