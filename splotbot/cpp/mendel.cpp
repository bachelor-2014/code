#include <iostream>
#include <fstream>

using namespace std;

void runGCode(string s){
    ofstream out;
    out.open("/tmp/mendel.sock",std::ofstream::out | std::ofstream::app);

    out << s << endl;

    out.close();
}
