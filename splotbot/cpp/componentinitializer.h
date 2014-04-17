#ifndef COMPONENTINITIALIZER_H
#define COMPONENTINITIALIZER_H

#include <vector>
#include "component.h"
#include "libraries/cJSON/cJSON.h"

using namespace std;

/**
 * initilizeComponents initilizes the components from the config file
 * callback: is used for callback event
 * Can be used with Lambda or function:
 *      initilizeComponents([](string eventName, string data){...});
 */
vector<Component *> initializeComponents(function<void(string,string)> *callback, string configFilename, string mendelSocket);

string getStringParam(cJSON *parameters, string key);

#endif
