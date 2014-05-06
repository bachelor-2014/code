#include <iostream>
#include <thread>

#include "splotbot.h"
#include "utils/threading.h"
#include "utils/errors.h"
#include "rucolang/rucola.h"
#include "rucolang/compileargs.h"

using namespace std;

/**
 * Splotbot constructor
 */
Splotbot::Splotbot(string configFile, string mendelSocket) {

    cout << "Splotbot starting with " << endl << "config: " << configFile << endl << "Mendel socket: " << mendelSocket << endl;

    // Register empty callback
    registerCallback([] (string name, string data) -> void {
        cout << "Default callback. You need to provide a better one." << endl;
    });

    cout << "EvoBot intializing components ..." << endl;
    components = initializeComponents(&eventCallback,configFile,mendelSocket);

    cout << "Number of components in Splotbot: " << components.size() << endl;

    for (auto it = components.begin(); it != components.end(); ++it) {
        Component *c = *it;
        (*c).registerCalls(&componentCalls, (actions.size()-1));
        (*c).registerActions(&actions);
    }

    cout << "Number of actions registered: " << actions.size() << endl;

    cout << "Registerings Component Calls with Rucolang" << endl;
    rucolang.RegisterComponentCalls(componentCalls);
    rucolang.RegisterEventCallback(&eventCallback);
}

/**
 * executeInstructions exectures a list of instructions
 */
void Splotbot::executeInstructions(int numberOfInstructions, int instructions[]) {
    buffer.pushInstructions(numberOfInstructions, instructions);
}

void Splotbot::executeRucolaCode(string code){
        try{
            if(code != ""){
                vector<int> instrs = rucolang.Compile(code);
                executeInstructions(instrs.size(), &instrs[0]);
            }else{
                cout << "Clearing" << endl;
                rucolang.Clear();
            }
        } catch(RucolaException& e){
            runAsThread( [=] () {
                vector<int> args;
                eventCallback("error", e.what(), args);
            });
        }
}

/**
 * registerCallback registeres an event callback
 */
void Splotbot::registerCallback(function<void(string,string)> callback) {
    eventCallback = [=](string event, string data, vector<int> args){
        vector<int> instrs = rucolang.Event(event, args);
        executeInstructions(instrs.size(), &instrs[0]);
        callback(event, data);
    };
}

/**
 * run starts the Splotbot
 */
void Splotbot::run() {
    runAsThread( [&] () {
        while (true) {
            int popped[1];
            buffer.popInstructions(1, popped);
            int action = popped[0];

            try {
                actions[action](&buffer);
            } catch(ComponentException& e){
                e.component->raiseError(e.what());
            } catch(exception& e) {
                cout << "TOO GENERAL AN EXCEPTION." << endl;
            }
        }
    });
}
