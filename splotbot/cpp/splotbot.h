#ifndef SPLOTBOT_H
#define SPLOTBOT_H

#include <semaphore.h>
#include <mutex>
#include <vector>
#include <string>
#include <map>

#include "instructionbuffer.h"
#include "component.h"
#include "componentinitializer.h"
#include "rucolang/rucola.h"
#include "rucolang/compileargs.h"

using namespace std;

/**
 * Splotbot class the main class for the splotbot robot
 *
 * executeInstructions used to execute a list of instructions
 *      numberOfInstructions: amount of instructions to execute
 *      instructions: array of instructions to execute
 *
 * registerCallback registers an event callback
 *      callback: is used for callback event
 *      Can be used with Lambda or function:
 *           registerCallback([](string eventName, string data){...});
 *
 * run run the splotbot
 *
 */
class Splotbot {
    public:
        Splotbot(string configFile, string mendelSocket);
        void executeInstructions(int numberOfInstructions, int instructions[]);
        void executeRucolaCode(string code);
        void registerCallback(function<void(string,string)> callback);
        void run();

    private:
        InstructionBuffer buffer;
        vector<Component *> components;
        vector<function<void(InstructionBuffer *)>> actions;
        function<void(string,string)> eventCallback;
        Rucola::Rucolang rucolang;
        map<string,map<string,Rucola::CompileArgs>> componentCalls;
};

#endif
