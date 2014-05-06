#include <iostream>
#include <sstream>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <ctime>
#include <semaphore.h>

#include "utils/base64.h"
#include "utils/errors.h"
#include "utils/threading.h"

#include "rucolang/compileargs.h"

#include "computer_vision/imagestitcher.h"
#include "computer_vision/positionimagestitcher.h"
#include "computer_vision/featuresimagestitcher.h"
#include "computer_vision/featuresandpositionimagestitcher.h"

#include "scanner.h"

using namespace std;

/**
 * Scanner constructor
 */
Scanner::Scanner(string name, Camera *camera, XYAxes *xyaxes): camera(camera), xyaxes(xyaxes) {
    this->name = name;
    this->fileLogger = new FileLogger("Scanner",name);
    this->imageLogger = new ImageLogger("Scanner",name);
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
        case 0:
            stitcher = new FeaturesImageStitcher(camera, stepsBetweenImages);
            break;
        case 1: 
            stitcher = new FeaturesAndPositionImageStitcher(camera, stepsBetweenImages);
            break;
        case 2:
            stitcher = new PositionImageStitcher(camera, stepsBetweenImages);
            break;
        default: 
            stitcher = new FeaturesImageStitcher(camera, stepsBetweenImages);
            break;
    }

    // Save the start position, so it can later be reset
    int resetX = xyaxes->positionX();
    int resetY = xyaxes->positionY();

    // Stop the camera
    int cameraMode = camera->getMode();
    if (cameraMode > 0) {
        camera->stop();
    }

    // Make the camera open the video device as a resource
    // of this thread
    camera->openVideoDevice();

    // Go to each camera position between the given from and to coordinates
    // and grab an image in each place
    // TODO currently the camera might move a bit further than the to-destination. Should this be changed?
    for (int x = fromX; x < (toX + stepsBetweenImages); x += stepsBetweenImages) {
        for (int y = fromY; y < (toY + stepsBetweenImages); y += stepsBetweenImages) {
            // Move to the position
            xyaxes->move(x, y);

            // Sleep before grabbing the image, allowing the camera to settle
            usleep(sleepBetweenImages * 1000);

            // Grab the image
            stitcher->grabImage(x, y);
        }
    }

    // Move back to the previous position
    xyaxes->move(resetX, resetY);

    // Close the video device in this thread
    camera->closeVideoDevice();

    // Restart the camera
    if (cameraMode > 0) {
        camera->start();
    }

    // Run stitching in a separate thread
    // In order to aboid the image stitcher local variable
    // going out of scope, us a sempahore to make sure it is
    // copied in the thread before continuing afterwards
    sem_t stitcherSemaphore;
    sem_init(&stitcherSemaphore, 0, 0);
    
    runAsThread( [&] () {
        // Stitch the images together
        cv::Mat stitchedImage;
        
        // Timing variable
        clock_t timestamp;

        // Get time for timing
        timestamp = clock();
        const double startTime = double(timestamp) / CLOCKS_PER_SEC;

        if (FeaturesImageStitcher *i = dynamic_cast<FeaturesImageStitcher*>(stitcher)) {
            FeaturesImageStitcher ii = *i;
            sem_post(&stitcherSemaphore);
            stitchedImage = ii.stitch();
        } else if (FeaturesAndPositionImageStitcher *i = dynamic_cast<FeaturesAndPositionImageStitcher*>(stitcher)) {
            FeaturesAndPositionImageStitcher ii = *i;
            sem_post(&stitcherSemaphore);
            stitchedImage = ii.stitch();
        } else if (PositionImageStitcher *i = dynamic_cast<PositionImageStitcher*>(stitcher)) {
            PositionImageStitcher ii = *i;
            sem_post(&stitcherSemaphore);
            stitchedImage = ii.stitch();
        } else {
           throw ComponentException(this, "Unknown image stitcher type detected");
        }

        // Get time for timing
        timestamp = clock();
        const double endTime = double(timestamp) / CLOCKS_PER_SEC;

        // Send the stitching time as an event
        double runTime = endTime - startTime;

        vector<int> args = { ((int)runTime) * 1000 };
        (*eventCallback)(name + "_time", to_string(runTime), args);

        // Convert the image to base64
        vector<uchar> buff;
        vector<int> param = vector<int>(0);
        imencode(".png", stitchedImage, buff, param);
	imageLogger->Data(&stitchedImage);

        string base64 = base64_encode(&buff[0],buff.size());

        // Send the image as an event
        vector<int> args2;
        (*eventCallback)(name, base64, args2);
            
            });

    // Wait for the stitching thread to get started
    sem_wait(&stitcherSemaphore);
}

/**
 * registerActions register the actions of the scanner
 */
void Scanner::registerActions(vector<function<void(InstructionBuffer *)>> *actions) {
    stringstream ss;
    ss << "Registering actions" << endl;
    string s = ss.str();
    (*fileLogger).Info(s);

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
        ss << "Scanning area (" << fromX << ", " << fromY << ") -> (" << toX << ", " << toY << ") with " << stepsBetweenImages << " steps and " << sleepBetweenImages << " milliseconds of sleep time between each image, stitching with algorithm " << stitchingAlgorithm << endl;
        string s = ss.str();
        (*fileLogger).Info(s);
    };

    (*actions).push_back(scanAction);
}

void Scanner::registerCalls(map<string, map<string,Rucola::CompileArgs>> *componentCalls, int start){
    stringstream ss;
    ss << "Registering calls" << endl;
    string s = ss.str();
    (*fileLogger).Info(s);

    Rucola::CompileArgs scanCall;
    scanCall.Action = start+1;
    scanCall.NumberofArguments = 7;

    (*componentCalls)[name]["scan"] = scanCall; 
}
