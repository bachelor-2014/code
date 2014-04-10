#include <iostream>
#include <sstream>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <math.h>

#include "rcservomotor.h"

using namespace std;

/**
 * RCServoMotor constructor
 */
RCServoMotor::RCServoMotor(string name, string device, unsigned char channel): device(device), channel(channel) {
    this->name = name;
}

/**
 * registerActions register the actions of the single stepper motor
 */
void RCServoMotor::registerActions(vector<function<void(InstructionBuffer *)>> *actions) {
    cout << "RCServoMotor (" << name << ") registering actions" << endl;

    // 'SetTarget' <target in degrees>
    function<void(InstructionBuffer *)> setTarget = [&](InstructionBuffer *buffer) -> void {
        int instr[1];
        (*buffer).popInstructions(1, instr);
        int target = instr[0];

        setPosition((unsigned short) target);

        stringstream ss;
        ss << "RCServoMotor (" << name << ") setting target to " << target << endl;
        string s = ss.str();
        (*file_logger).Info(s);
    };

    (*actions).push_back(setTarget);
}

// Gets the position of the RC servo motor
int RCServoMotor::getPosition() {
    int fd = openDeviceFile();

    unsigned char command[] = {0x90, channel};
    if(write(fd, command, sizeof(command)) == -1) {
        stringstream ss;
        ss << "RCServoMotor (" << name << ") failed to write to device " << device << endl;
        string s = ss.str();
        throw std::runtime_error(s.c_str());
    }
   
    unsigned char response[2];
    if(read(fd,response,2) != 2) {
        stringstream ss;
        ss << "RCServoMotor (" << name << ") failed to read from device " << device << endl;
        string s = ss.str();
        throw std::runtime_error(s.c_str());
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
        ss << "RCServoMotor (" << name << ") failed to write to device " << device << endl;
        string s = ss.str();
        throw std::runtime_error(s.c_str());
    }

    close(fd);

    //TODO find better solution for this sleep
    //Currently it is there to allow the motor to finish its rotation before
    //continuing executing more commands
    sleep(1);

    return 0;
}

// Opens the device file and returns the file descriptor
int RCServoMotor::openDeviceFile() {
    int fd = open(device.c_str(), O_RDWR | O_NOCTTY);

    // Handles error if file opening was not successful
    if (fd == -1) {
        stringstream ss;
        ss << "RCServoMotor (" << name << ") failed to open device " << device << endl;
        string s = ss.str();
        throw std::runtime_error(s.c_str());
    }

    return fd;
}
