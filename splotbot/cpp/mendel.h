#ifndef MENDEL_H
#define MENDEL_H

#include <iostream>
#include <fstream>

using namespace std;

class Mendel {

    public:
        Mendel(string socketPath);
        void runGCode(string gcode);

    private:
        string socketPath;
};

#endif
