#ifndef SCANNER_H
#define SCANNER_H 

#include <string>
#include "instructionbuffer.h"
#include "component.h"
#include "camera.h"
#include "xyaxes.h"

using namespace std;

/**
 * Scanner component handles scanning by using image stitching techniques, using
 * and XYAxes and a Camera component
 * Is constructed with the following variables:
 * name: Name of the scanner
 * camera: A pointer to the Camera component the scanner uses for scanning
 * xyaxes: A pointer to the XYAxes component the scanner uses for scanning
 *
 * Use the registerActions(*actions) to register the actions performed by the scanner:
 * Scan [5]: Does a scan
 */
class Scanner: public Component {
    public:
        Scanner(string name, Camera *camera, XYAxes *xyaxes);
        void registerActions(vector<function<void(InstructionBuffer *)>> *actions);
        void scan(int stepsBetweenImages, int sleepBetweenImages, int fromX, int fromY, int toX, int toY, int stitchingAlgorithm);

    private:
        Camera *camera;
        XYAxes *xyaxes;
};

#endif
