#include <functional>

#include <iostream>

#include "../../logging/logger.h"
#include "../../logging/filelogger.h"

#define SH_FG_RED            "\033[0;31m"
#define SH_FG_GREEN          "\033[0;32m"
#define SH_DEFAULT           "\033[0m"

using namespace std;

bool status = true;

bool test_logger_instantiation(){
    clog << __func__ << endl;

    Logger l = Logger("loller");
    FileLogger fl = FileLogger("file");

    return true;
}

bool test_read_write(){
    clog << __func__ << endl;

    Logger l = Logger("loller");
    l.Write((void*)"aaa");

    const char* towrite = "JohnJohn";

    FileLogger fl = FileLogger("file");
    fl.Write((void*)towrite);

    string s = fl.Read<string>();

    if(s != towrite){
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
    test(test_logger_instantiation,"test_instantiation failed!");
    test(test_read_write,"test write failed");

    if(status){
        return 0;
    }else{
        return 1;
    }
}
