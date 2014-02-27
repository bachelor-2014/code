#ifndef COMPONENTINITIALIZER_H
#define COMPONENTINITIALIZER_H

#include <vector>
#include "component.h"

using namespace std;

vector<Component *> initializeComponents(function<void(string,string)> *callback);

#endif
