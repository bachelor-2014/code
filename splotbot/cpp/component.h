#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>

#include "instructionbuffer.h"

using namespace std;

/**
 * Component class, represents a component in the system
 * Used as an interface
 *
 * Use the registerActions(*actions) to register the actions performed by the component
 * Use the registerCallback to register the event callback
 */
class Component {
    public:
        virtual void registerActions(vector<function<void(InstructionBuffer *)>> *actions) {};
        void registerCallback(function<void(string,string)> *callback);

    protected:
        function<void(string,string)> *eventCallback;
};

#endif
