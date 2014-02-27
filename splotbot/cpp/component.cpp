#include "component.h"

using namespace std;

void Component::registerCallback(function<void(string,string)> *callback) {
    eventCallback = callback;
}
