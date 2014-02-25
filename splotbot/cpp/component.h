#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>

#include "instructionbuffer.h"

using namespace std;

class Component {
    public:
        virtual void registerActions(vector<function<void(InstructionBuffer *)>> *actions) {};
};

#endif
