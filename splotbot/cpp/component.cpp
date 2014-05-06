#include <sstream>

#include "component.h"

using namespace std;

Component::Component(){

}

/**
 * registerCallback registeres the event callback
 */
void Component::registerCallback(function<void(string,string,vector<int>)> *callback) {
    eventCallback = callback;
}

/**
 * Raise an error all the way to the client. ALL the way
 */
void Component::raiseError(string message){
    // Log the event
    stringstream ss;
    ss << "A ComponentException was encountered in component (" << name << "): " << message << endl;
    string s = ss.str();

    // Throw the error to the client
    vector<int> args;
    (*eventCallback) ("error", this->name + ": " + message, args);
}
