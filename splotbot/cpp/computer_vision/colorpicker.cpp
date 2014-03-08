#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include <cmath>

#include "colorpicker.h"

using namespace std;

// Constructor. Initializes the ColorPicker
ColorPicker::ColorPicker(cv::Mat image, int tolerance): image(image), tolerance(tolerance) {
    // Empty constructor
}

// Computes the color interval from the pixel chosen on the image using the tolerance
ColorInterval ColorPicker::computeColorIntervalFromSelection(int x, int y) {
    ColorInterval colorInterval;

    cv::Mat blurredImage;
    cv::Mat hsvImage;

    // Apply a slight gaussian blur to the image
    cv::GaussianBlur(image, blurredImage, cv::Size(3,3), 1.0);

    // Convert the image to HSV
    cv::cvtColor(blurredImage, hsvImage, CV_BGR2HSV);

    // Compute the color interval
    vector<int> hVector;
    vector<int> sVector;
    vector<int> vVector;
    cout << "Image size: (W, H) = (" << image.size().width << ", " << image.size().height << ")" << endl; 
    getColors(hsvImage, x, y, true, true, true, true, &hVector, &sVector, &vVector);
    cout << "Got color" << endl;

    int minH = *min_element(begin(hVector), end(hVector));
    int minS = *min_element(begin(sVector), end(sVector));
    int minV = *min_element(begin(vVector), end(vVector));

    int maxH = *max_element(begin(hVector), end(hVector));
    int maxS = *max_element(begin(sVector), end(sVector));
    int maxV = *max_element(begin(vVector), end(vVector));

    cout << "ColorPicker interval computed:" << endl;
    cout << "H: " << minH << " - " << maxH << endl;
    cout << "S: " << minS << " - " << maxS << endl;
    cout << "V: " << minV << " - " << maxV << endl;
    cout << endl;
    
    return colorInterval;
}
// Recursive function for computing the color interval
void ColorPicker::getColors(cv::Mat image, int x, int y, bool up, bool down, bool left, bool right, vector<int> *hVector, vector<int> *sVector, vector<int> *vVector) {
    //hVector->push_back(0);
    //hVector->push_back(180);

    //sVector->push_back(200);
    //sVector->push_back(255);

    //vVector->push_back(110);
    //vVector->push_back(155);

    cout << "Getting first pixel" << endl;
    cv::Vec3b pixel = image.at<cv::Vec3b>(x, y);
    cout << "Got first pixel" << endl;

    cout << "Adding pixel values to vectors" << endl;
    hVector->push_back(pixel[0]);
    sVector->push_back(pixel[1]);
    vVector->push_back(pixel[2]);
    cout << "Added pixel values to vectors" << endl;

    // Call the function recursivelse if the values are withing the tolerance
    cout << "Initializing other values" << endl;
    cv::Vec3b otherPixel;
    int otherX;
    int otherY;
    cout << "Initialized other values" << endl;

    // Go up
    if (up && (y > 0)) {
        otherX = x;
        otherY = y-1;
        cout << "Going up (" << otherX << ", " << otherY << ")" << endl;
        otherPixel = image.at<cv::Vec3b>(otherX, otherY);
        cout << "Got pixel" << endl;

        if (withinTolerance(pixel, otherPixel)) {
            cout << "Within tolerance" << endl;
            getColors(image, otherX, otherY, true, false, true, true, hVector, sVector, vVector);
        }
    }

    // Go down
    if (down && (y < (image.size().height - 1))) {
        otherX = x;
        otherY = y+1;
        cout << "Going down (" << otherX << ", " << otherY << ")" << endl;
        otherPixel = image.at<cv::Vec3b>(otherX, otherY);
        cout << "Got pixel" << endl;

        if (withinTolerance(pixel, otherPixel)) {
            cout << "Within tolerance" << endl;
            getColors(image, otherX, otherY, false, true, true, true, hVector, sVector, vVector);
        }
    }

    // Go left
    if (left && (x > 0)) {
        otherX = x-1;
        otherY = y;
        cout << "Going left (" << otherX << ", " << otherY << ")" << endl;
        otherPixel = image.at<cv::Vec3b>(otherX, otherY);
        cout << "Got pixel" << endl;

        if (withinTolerance(pixel, otherPixel)) {
            cout << "Within tolerance" << endl;
            getColors(image, otherX, otherY, true, true, true, false, hVector, sVector, vVector);
        }
    }

    // Go right
    if (right && (x < (image.size().width - 1))) {
        otherX = x+1;
        otherY = y;
        cout << "Going right (" << otherX << ", " << otherY << ")" << endl;
        otherPixel = image.at<cv::Vec3b>(otherX, otherY);
        cout << "Got pixel" << endl;

        if (withinTolerance(pixel, otherPixel)) {
            cout << "Within tolerance" << endl;
            getColors(image, otherX, otherY, true, true, false, true, hVector, sVector, vVector);
        }
    }
}

// Checker whether the given pixels are withing the tolerance of each other
bool ColorPicker::withinTolerance(cv::Vec3b pixel, cv::Vec3b otherPixel) {
    return  (abs(pixel[0] - otherPixel[0]) <= tolerance) &&
            (abs(pixel[1] - otherPixel[1]) <= tolerance) &&
            (abs(pixel[2] - otherPixel[2]) <= tolerance);
}
