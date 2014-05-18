#include <iostream>
#include <sys/time.h>
#include <opencv2/opencv.hpp>

using namespace std;

typedef struct{
    cv::Mat image;
    double time;
} Result;

const int kernel_size = 31;
unsigned long t1,t2; // used for timing

unsigned long getCurrentTimeMs() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (unsigned long)((tv.tv_sec * 1000ul) + (tv.tv_usec / 1000ul));
}

cv::Mat gaussianBlur(cv::Mat in, unsigned long *time){

    cv::Mat out;
    unsigned long t1, t2;
    t1 = getCurrentTimeMs();
    cv::GaussianBlur(in, out, cv::Size(kernel_size,kernel_size), 0,0);
    t2 = getCurrentTimeMs();
    *time = t2 - t1;

    return out;
}

cv::Mat bilateralBlur(cv::Mat in, unsigned long *time){

    cv::Mat out;
    unsigned long t1, t2;
    t1 = getCurrentTimeMs();
    cv::bilateralFilter(in, out, 31, 100, 100);
    t2 = getCurrentTimeMs();
    *time = t2 - t1;

    return out;
}

cv::Mat medianBlur(cv::Mat in, unsigned long *time){

    cv::Mat out;
    unsigned long t1, t2;
    t1 = getCurrentTimeMs();
    cv::medianBlur(in, out, kernel_size);
    cv::GaussianBlur(in, out, cv::Size(kernel_size,kernel_size), 0,0);
    t2 = getCurrentTimeMs();
    *time = t2 - t1;

    return out;
}

int main() {
    cout << "Running filters experiments" << endl;

    cv::Mat src = cv::imread( "noiced.png", 1 );
    cv::Mat dst = src.clone();

    cv::imwrite( "results/tracking_experiment_original.png", dst );

    unsigned long t;

    dst = gaussianBlur(src, &t);
    cv::imwrite( "results/tracking_experiment_gaussian.png", dst );
    cout << "Gaussian: " << t << "ms" << endl;

    dst = bilateralBlur(src, &t);
    cv::imwrite( "results/tracking_experiment_bilateral.png", dst );
    cout << "Bilateral: " << t << "ms" << endl;

    dst = medianBlur(src, &t);
    cv::imwrite( "results/tracking_experiment_median.png", dst );
    cout << "Median: " << t << "ms" << endl;

    cv::waitKey ( 0 );

    return 1;
}
