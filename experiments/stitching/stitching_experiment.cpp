#include <iostream>
#include <chrono>
#include <unistd.h>
#include <opencv2/opencv.hpp>

#include "../../splotbot/cpp/computer_vision/imagestitcher.h"

using namespace std;

typedef struct {
    string dir;
    string name;
    vector<GrabbedImage> images;
    int stepSize;
} Experiment;

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
            gi.image = cv::imread(ss.str());
        }
    }

    return exp;
}

void runExperiment(Experiment exp) {
    //TODO
}

int main() {
    int numberOfExperiments;
    cin >> numberOfExperiments;
    cout << "Number of experiments: " << numberOfExperiments << endl;

    Experiment exp;

    for (int i = 0; i < numberOfExperiments; i++) {
        exp = readExperiment();
        runExperiment(exp);
    }

    return 1;
}
