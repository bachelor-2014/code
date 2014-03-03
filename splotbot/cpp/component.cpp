#include "component.h"

using namespace std;

/**
 * registerCallback registeres the event callback
 */
void Component::registerCallback(function<void(string,string)> *callback) {
    eventCallback = callback;
}
