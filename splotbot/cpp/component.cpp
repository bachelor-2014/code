#include "component.h"

using namespace std;

Component::Component(){}

/**
 * registerCallback registeres the event callback
 */
void Component::registerCallback(function<void(string,string)> *callback) {
    eventCallback = callback;
}

/**
 * Raise an error all the way to the client. ALL the way
 */
void Component::raiseError(string message){
    cout << "THROWING UP" << endl;
    (*eventCallback) ("error",this->name + ": " + message);
}
