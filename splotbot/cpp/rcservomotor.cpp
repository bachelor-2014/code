#include <iostream>
#include <sstream>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <math.h>

#include "rcservomotor.h"
#include "utils/errors.h"
#include "rucolang/compileargs.h"

using namespace std;

/**
 * RCServoMotor constructor
 */
RCServoMotor::RCServoMotor(string name, string device, unsigned char channel): device(device), channel(channel) {
    this->name = name;

    this->fileLogger = new FileLogger("RCServoMotor",name);
}

/**
 * registerActions register the actions of the single stepper motor
 */
void RCServoMotor::registerActions(vector<function<void(InstructionBuffer *)>> *actions) {
    stringstream ss;
    ss << "Registering actions" << endl;
    string s = ss.str();
    (*fileLogger).Info(s);

    // 'SetTarget' <target in degrees>
    function<void(InstructionBuffer *)> setTarget = [&](InstructionBuffer *buffer) -> void {
        int instr[1];
        (*buffer).popInstructions(1, instr);
        int target = instr[0];

        stringstream ss;
        ss << "Setting target to " << target << endl;
        string s = ss.str();
        (*fileLogger).Info(s);

        setPosition((unsigned short) target);
    };

    (*actions).push_back(setTarget);
}

void RCServoMotor::registerCalls(map<string, map<string,Rucola::CompileArgs>> *componentCalls, int start){
    stringstream ss;
    ss << "Registering calls" << endl;
    string s = ss.str();
    (*fileLogger).Info(s);

    Rucola::CompileArgs setPos;
    setPos.Action = start+1;
    setPos.NumberofArguments = 1;

    (*componentCalls)[name]["setPosition"] = setPos; 
}

// Gets the position of the RC servo motor
int RCServoMotor::getPosition() {
    int fd = openDeviceFile();

    unsigned char command[] = {0x90, channel};
    if(write(fd, command, sizeof(command)) == -1) {
        stringstream ss;
        ss << "Failed to write to device " << device << endl;
        string s = ss.str();
        throw ComponentException(this,s.c_str());
    }
   
    unsigned char response[2];
    if(read(fd,response,2) != 2) {
        stringstream ss;
        ss << "Failed to read from device " << device << endl;
        string s = ss.str();
        throw ComponentException(this,s.c_str());
    }

    close(fd);

    int result = response[0] + 256*response[1];
    return (int) round((((double) (result - 4000)) / 44.4444));
}
 
// Sets the target of the RC servo motor
int RCServoMotor::setPosition(unsigned short target) {
    int fd = openDeviceFile();

    // Convert the target to quarter-of-microseconds
    target = (unsigned short) round(4000 + ((double) target) * 44.4444);

    // Send the command
    unsigned char command[] = {0x84, channel, (unsigned char) (target & 0x7F), (unsigned char) (target >> 7 & 0x7F)};
    if (write(fd, command, sizeof(command)) == -1) {
        stringstream ss;
        ss << "Failed to write to device " << device << endl;
        string s = ss.str();
        throw ComponentException(this,s.c_str());
    }

    close(fd);

    //TODO find better solution for this sleep
    //Currently it is there to allow the motor to finish its rotation before
    //continuing executing more commands
    //sleep(1);

    return 0;
}

// Opens the device file and returns the file descriptor
int RCServoMotor::openDeviceFile() {
    int fd = open(device.c_str(), O_RDWR | O_NOCTTY);

    // Handles error if file opening was not successful
    if (fd == -1) {
        stringstream ss;
        ss << "Failed to open device " << device << endl;
        string s = ss.str();
        throw ComponentException(this,s.c_str());
    }

    return fd;
}
