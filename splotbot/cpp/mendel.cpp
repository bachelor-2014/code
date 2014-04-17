#include <iostream>
#include <fstream>
#include "mendel.h"

Mendel::Mendel(string socketPath):socketPath(socketPath){}

void Mendel::runGCode(string s){
    ofstream out;
    out.open(socketPath,std::ofstream::out | std::ofstream::app);

    out << s << endl;

    out.close();
}
