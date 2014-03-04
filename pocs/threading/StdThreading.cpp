#include <iostream>
#include <thread>

using namespace std;

int main(int argc, char** argv) {
    for (int i = 0; i < 5; i++) {
        thread( [&] () {
            for (int j = 0; j < 5; j++) {
                cout << "Thread " << i << ": " << j << endl;
            }
        });
    }

    return 0;
}
