#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include <map>
#include <tuple>

#include "instructionbuffer.h"

#include "logging/filelogger.h"
#include "logging/imagelogger.h"
#include "logging/videologger.h"

#include "rucolang/compileargs.h"

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
        Component();
        virtual void registerActions(vector<function<void(InstructionBuffer *)>> *actions) {};
        virtual void registerCalls(map<string,map<string,Rucola::CompileArgs>> *componentCalls, int start) {};
        void registerCallback(function<void(string,string,vector<int>)> *callback);
        string name;
        void raiseError(string message);

    protected:
<<<<<<< HEAD
        function<void(string,string)> *eventCallback;
        FileLogger *fileLogger;
        ImageLogger *imageLogger;
        VideoLogger *videoLogger;
=======
        function<void(string,string,vector<int>)> *eventCallback;
        FileLogger *file_logger;
>>>>>>> 66b842a402c7c46daab824baa2e813f060424cb6

};

#endif
