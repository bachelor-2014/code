#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <curl/curl.h>
#include <fstream>
#include <iterator>
#include "base64.h"

using namespace cv;
using namespace std;

bool react_to_key (int i);
void send_image (Mat image);

bool capturing; // Global value, indicating if were writing

int main( int argc, char** argv )
{
    if (argc != 2) {
        printf("Invalid number of arguments (1 needed)\n");
        return -1;
    }

    VideoCapture cap(std::atoi(argv[1]));

    Mat image;

    namedWindow("john",CV_WINDOW_AUTOSIZE);


    if (!cap.isOpened())
    {
        printf("No video data\n");
        return -1;
    }

    while(true) {
        bool success = cap.read(image);

        if (!success)
        {
             cout << "ERROR: Cannot read a frame from video file" << endl;
             break;
        }

        send_image(image);

        imshow("john",image);

        bool stop = react_to_key(waitKey(10));
        if(stop)
            break;
    }

    return 0;
}

bool react_to_key(int keyPress){
        if (keyPress == 27) //esc
        {
            cout << "esc key is pressed by user" << endl;
            return true;
        }

        if (keyPress == 99) //c
        {
            cout << "Capturing" << endl;
            capturing = !capturing;
        }

        return false;
}

void send_image(Mat image){
    vector<uchar> buff;//buffer for coding
    vector<int> param = vector<int>(0);
    //param[0]=CV_IMWRITE_JPEG_QUALITY;
    //param[1]=95;//default(95) 0-100

    imencode(".png", image, buff, param);

    string base64 = base64_encode(&buff[0],buff.size());
    int b64len = base64.length() + 1;
    char *b64 = new char[base64.length() + 1];
    strcpy(b64, base64.c_str());

    CURL *curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8000/image");
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, b64);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, b64len);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    delete [] b64;
}
