#include <iostream>

#include "logger.h"
#include <ctime>

string getTimeStamp(){
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    
    strftime(buffer,80,"%F_%T",timeinfo);

    return string(buffer);
}
