#include <functional>
#include <iostream>
#include <string>

#include "../../logging/logger.h"
#include "../../logging/filelogger.h"
#include "../../logging/videologger.h"

#define SH_FG_RED            "\033[0;31m"
#define SH_FG_GREEN          "\033[0;32m"
#define SH_DEFAULT           "\033[0m"

using namespace std;

bool status = true;

bool test_logger_instantiation(){
    clog << __func__ << endl;

    Logger fl = FileLogger("file");

    return true;
}

bool test_file_read_write(){
    clog << __func__ << endl;

    string towrite = "JohnJohn";

    FileLogger fl = FileLogger("file");
    fl.Write<string>(towrite);

    string s = fl.Read<string>();

    if(s != towrite){
        cout << s << endl;
        return false;
    }

    return true;
}

bool test_video_read_write(){
    clog << __func__ << endl;

    VideoCapture cap(0);

    VideoLogger *video_logger = new VideoLogger("exp",&cap);
    if(!cap.isOpened()){
        cerr << "No video data!" << endl;
    }

    Mat image;
    while (true) {
        //Pull image
        bool success = cap.read(image);

        if (!success)
        {
                cout << "ERROR: Cannot read a frame from video device: " << endl;
                break;
        }

        namedWindow("test",CV_WINDOW_AUTOSIZE);
        imshow("test",image);

        // Log the image
        (*video_logger).Write(&image);

        waitKey(1);
    }
}

bool test(function<bool()> f, string message){
    if(!f()){
        status = false;
        cerr << SH_FG_RED << " Fail: " << message << SH_DEFAULT << endl;
    } else {
        clog << SH_FG_GREEN << " Ran" << SH_DEFAULT << endl;
    }
}

int main() {
    test(test_file_read_write,"test write failed");
    test(test_logger_instantiation,"test_instantiation failed!");
    test(test_video_read_write,"test video failed");

    if(status){
        return 0;
    }else{
        return 1;
    }
}
