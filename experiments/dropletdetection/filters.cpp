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

    cv::Mat in, out;

    cv::imwrite( "results/tracking_experiment_original.png", src );

    in = src.clone();
    out = src.clone();

    t1 = getCurrentTimeMs();
    cv::GaussianBlur(in, out, cv::Size(kernel_size,kernel_size), 0,0);
    t2 = getCurrentTimeMs();

    cv::imwrite( "results/tracking_experiment_gaussian.png", out );
    cout << "Gaussian: " << (t2 - t1) << "ms" << endl;

    in = src.clone();
    out = src.clone();

    t1 = getCurrentTimeMs();
    cv::bilateralFilter(in, out, 31, 100, 100);
    t2 = getCurrentTimeMs();

    cv::imwrite( "results/tracking_experiment_bilateral.png", out );
    cout << "Bilateral: " << (t2 - t1) << "ms" << endl;


    in = src.clone();
    out = src.clone();

    t1 = getCurrentTimeMs();
    cv::medianBlur(in, out, kernel_size);
    t2 = getCurrentTimeMs();

    cv::imwrite( "results/tracking_experiment_median.png", out );
    cout << "Median: " << (t2 - t1) << "ms" << endl;

    cv::waitKey ( 0 );

    return 1;
}
