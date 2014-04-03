#include <iostream>
#include <fstream>

using namespace std;

void runGCode(string s){
    ofstream out;
    out.open("data/mendel.sock",std::ofstream::out | std::ofstream::app);

    out << s << endl;

    out.close();
}

int main(int argc, char** argv){
    runGCode(string(argv[1]));
}
