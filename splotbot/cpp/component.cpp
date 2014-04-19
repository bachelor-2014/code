#include "component.h"

using namespace std;

Component::Component(){
    file_logger = new FileLogger("exp");
}

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
    (*eventCallback) ("error",this->name + ": " + message);
}
