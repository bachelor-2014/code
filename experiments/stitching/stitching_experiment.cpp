#include <iostream>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include <sys/time.h>

#include "../../splotbot/cpp/camera.h"
#include "../../splotbot/cpp/computer_vision/imagestitcher.h"
#include "../../splotbot/cpp/computer_vision/positionimagestitcher.h"
#include "../../splotbot/cpp/computer_vision/featuresimagestitcher.h"

using namespace std;

typedef struct {
    string dir;
    string name;
    vector<GrabbedImage> images;
    int stepSize;
} Experiment;

unsigned long getCurrentTimeMs() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (unsigned long)((tv.tv_sec * 1000ul) + (tv.tv_usec / 1000ul));
}

Experiment readExperiment() {
    string dir, name;
    int startX, startY, endX, endY, stepSize;
    cin >> name >> dir >> startX >> startY >> endX >> endY >> stepSize;

    Experiment exp;
    exp.dir = dir;
    exp.name = name;

    for (int x = startX; x <= endX; x += stepSize) {
        for (int y = startY; y <= endY; y += stepSize) {
            GrabbedImage gi;
            gi.positionX = x;
            gi.positionY = y;

            stringstream ss;
            ss << dir << "/grab" << x << "_" << y << ".jpg";
            gi.image = cv::imread(ss.str(), CV_LOAD_IMAGE_COLOR);

            exp.images.push_back(gi);
        }
    }

    return exp;
}

void runExperiment(Experiment exp, int repetitions) {
    cout << "Running experiment: " << exp.name << endl;

    Camera camera("Cam", 0, "event");
    camera.xStep = {19.879867553710938, 0.072934468587239579};
    camera.yStep = {0.81430053710937500, -19.770927429199219};

    PositionImageStitcher pis(exp.images, &camera, exp.stepSize);
    FeaturesImageStitcher fis(exp.images, &camera, exp.stepSize);

    unsigned long startTime, endTime, positionTime, featuresTime;
    cv::Mat positionResult, featuresResult;

    ofstream os;
    os.open("results/results.txt", ios::out | ios::app);

    cout << "-> Stitching based on position ..." << endl;
    os << exp.name << "_position";
    for (int i = 0; i < repetitions; i++) {
        startTime = getCurrentTimeMs();
        positionResult = pis.stitch();
        endTime = getCurrentTimeMs();
        positionTime = endTime - startTime;

        os << "," << positionTime;
    }
    os << endl;

    cout << "-> Stitching based on features ..." << endl;
    os << exp.name << "_features";
    for (int i = 0; i < repetitions; i++) {
        try {
            startTime = getCurrentTimeMs();
            featuresResult = fis.stitch();
            endTime = getCurrentTimeMs();
            featuresTime = endTime - startTime;

            os << "," << featuresTime;
        } catch (const runtime_error& error) {
            os << ",err";
            break;
        }
    }
    os << endl;

    os.close();

    cv::imwrite("results/" + exp.name + "_position.jpg", positionResult);
    cv::imwrite("results/" + exp.name + "_features.jpg", featuresResult);
}

int main() {
    cout << "Running image stitching experiments" << endl;
    cout << "###################################" << endl;

    ofstream os;
    os.open("results/results.txt", ios::out);
    os.close();

    int numberOfExperiments, repetitions;
    cin >> numberOfExperiments >> repetitions;
    cout << "Number of experiments: " << numberOfExperiments << endl;
    cout << "Number of repetitions per experiment: " << repetitions << endl;

    Experiment exp;

    for (int i = 0; i < numberOfExperiments; i++) {
        exp = readExperiment();
        runExperiment(exp, repetitions);
    }

    cout << "###################################" << endl;

    return 1;
}
