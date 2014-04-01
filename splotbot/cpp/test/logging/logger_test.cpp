#include <functional>
#include <iostream>
#include <vector>
#include <string>

#include "../../logging/logger.h"
#include "../../logging/filelogger.h"
#include "../../logging/videologger.h"
#include "../../logging/dblogger.h"

#define SH_FG_RED            "\033[0;31m"
#define SH_FG_GREEN          "\033[0;32m"
#define SH_DEFAULT           "\033[0m"

using namespace std;

bool status = true;

bool test_logger_instantiation(){
    clog << __func__ << endl;

    Logger<string> fl = FileLogger("file");

    return true;
}

bool test_file_read_write(){
    clog << __func__ << endl;

    string towrite = "JohnJohn";

    for(int i=0; i++; i < 2){

        FileLogger fl("file");
        fl.Clear();
        fl.Write(towrite);

        vector<string> res = fl.Read();

        //for(string s : res){
        //    cout << s << endl;
        //}
        if(res.size() != 1)
            return false;

        if(res[0] != towrite){
            cerr << res[0] << endl;
            return false;
        }
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

bool test_db_read_write(){
    clog << __func__ << endl;

    DBLogger *dblogger = new DBLogger("john");

    (*dblogger).Clear();

    bool w =    (*dblogger).Write(string("data1")) &&
                (*dblogger).Write(string("data2")) &&
                (*dblogger).Write(string("data3"));
    if(!w){
        return false;
    }

    vector<string> res = (*dblogger).Read();
    if(res.size() != 3){
        clog << "Write didn't work. Size: " << res.size() << endl;
        return false;
    }

    (*dblogger).Clear();
    res = (*dblogger).Read();
    if(res.size() != 0){
        clog << "Clear didn't work. Remaining: " << res.size() << endl;
        return false;
    }

    return true;
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
    //test(test_video_read_write,"test video failed");
    test(test_db_read_write,"test read write db failed");

    if(status){
        return 0;
    }else{
        return 1;
    }
}
