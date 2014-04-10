#include <iostream>
#include <sstream>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#include "scanner.h"

using namespace std;

/**
 * Scanner constructor
 */
Scanner::Scanner(string name, Camera *camera, XYAxes *xyaxes): camera(camera), xyaxes(xyaxes) {
    this->name = name;
}

void Scanner::scan(int stepsBetweenImages, int fromX, int fromY, int toX, int toY) {
    //TODO
}

/**
 * registerActions register the actions of the single stepper motor
 */
void Scanner::registerActions(vector<function<void(InstructionBuffer *)>> *actions) {
    cout << "Scanner (" << name << ") registering actions" << endl;

    // 'Scan' <steps between each image> <from x> <from y> <to x> <to y>
    function<void(InstructionBuffer *)> setTarget = [&](InstructionBuffer *buffer) -> void {
        int instr[5];
        (*buffer).popInstructions(5, instr);

        int stepsBetweenImages = instr[0];
        int fromX = instr[1];
        int fromY = instr[2];
        int toX = instr[3];
        int toY = instr[4];

        scan(stepsBetweenImages, fromX, fromY, toX, toY);

        stringstream ss;
        ss << "Scanner (" << name << ") scanning area () -> () with ? steps between each image " << endl;
        string s = ss.str();
        (*file_logger).Info(s);
    };

    (*actions).push_back(setTarget);
}
