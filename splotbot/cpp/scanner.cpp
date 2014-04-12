#include <iostream>
#include <sstream>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#include "utils/base64.h"
#include "computer_vision/imagestitcher.h"
#include "computer_vision/featuresimagestitcher.h"

#include "scanner.h"

using namespace std;

/**
 * Scanner constructor
 */
Scanner::Scanner(string name, Camera *camera, XYAxes *xyaxes): camera(camera), xyaxes(xyaxes) {
    this->name = name;
}

/*
 * Scans the given area by use of image stitching techniques.
 * 
 * Takes the following parameters:
 * stepsBetweenImages:  The number of steppers to move the stepper motors between
 *                      grabbing each of the images (same step amount is used for
 *                      both axes)
 * sleepBetweenImages:  The number of milisecons to sleep after moving the camera
 * fromX:               The start x position of the scan
 * fromY:               The start y position of the scan
 * toX:                 The end x position of the scan
 * toY:                 The end y position of the scan
 * stitchingAlgorithm:  Which image stitching algorithm to use. Currently not in use,
 *                      as only a single algorithm is implemented
 */
void Scanner::scan(int stepsBetweenImages, int sleepBetweenImages, int fromX, int fromY, int toX, int toY, int stitchingAlgorithm) {
    // Create the image stitcher
    ImageStitcher *stitcher;
    switch (stitchingAlgorithm) {
        default: {
            FeaturesImageStitcher fst(camera->videoDevice);
            stitcher = &fst;
        }
        break;
    }

    // Go to each camera position between the given from and to coordinates
    // and grab an image in each place
    // TODO currently the camera might move a bit further than the to-destination. Should this be changed?
    for (int x = fromX; x < (toX + stepsBetweenImages); x += stepsBetweenImages) {
        for (int y = fromY; y < (toY + stepsBetweenImages); y += stepsBetweenImages) {
            // Move to the position
            xyaxes->move(x, y);

            // Sleep before grabbing the image, allowing the camera to settle
            usleep(sleepBetweenImages);

            // Grab the image
            stitcher->grabImage(x, y);
        }
    }
    
    // Stitch the images together
    cv::Mat stitchedImage;
    stitchedImage = stitcher->stitch();

    // Convert the image to base64
    vector<uchar> buff;
    vector<int> param = vector<int>(0);
    imencode(".png", stitchedImage, buff, param);
    string base64 = base64_encode(&buff[0],buff.size());

    // Send the image as an event
    (*eventCallback)(name, base64);
}

/**
 * registerActions register the actions of the scanner
 */
void Scanner::registerActions(vector<function<void(InstructionBuffer *)>> *actions) {
    cout << "Scanner (" << name << ") registering actions" << endl;

    // 'Scan' <steps between each image> <sleep time between each image> <from x> <from y> <to x> <to y> <stitching algorithm>
    function<void(InstructionBuffer *)> scanAction = [&](InstructionBuffer *buffer) -> void {
        int instr[7];
        (*buffer).popInstructions(7, instr);

        int stepsBetweenImages = instr[0];
        int sleepBetweenImages = instr[1];
        int fromX = instr[2];
        int fromY = instr[3];
        int toX = instr[4];
        int toY = instr[5];
        int stitchingAlgorithm = instr[6];

        scan(stepsBetweenImages, sleepBetweenImages, fromX, fromY, toX, toY, stitchingAlgorithm);

        stringstream ss;
        ss << "Scanner (" << name << ") scanning area (" << fromX << ", " << fromY << ") -> (" << toX << ", " << toY << ") with " << stepsBetweenImages << " steps and " << sleepBetweenImages << " miliseconds of sleep time between each image, stitching with algorithm " << stitchingAlgorithm << endl;
        string s = ss.str();
        (*file_logger).Info(s);
    };

    (*actions).push_back(scanAction);
}
