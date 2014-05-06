#include "Absyn.h"
#include "lex.yy.h"
#include "rucola.tab.h"
#include "rucola.h"
#include "compileargs.h"
#include "../utils/errors.h"
#include <string>
#include "../libraries/cJSON/cJSON.h"
using namespace std;
using namespace Rucola;

extern Block *programBlock;

/**
 * Parse Rucola Abstract Syntax from a string
 */
Block *Rucola::ParseString(string s){
    yy_scan_string(s.c_str());
    yyparse(); 
    return programBlock; 
}

/**
 * Rucolang
 */
Rucola::Rucolang::Rucolang(){
    //Empty constructor
}

void Rucola::Rucolang::Clear(){
    events = map<string,Statement*>();
    env = map<string,int>();
}

string Rucola::Rucolang::Documentation(){
    cJSON *root = cJSON_CreateObject();
    for(auto comp : componentCalls){
        cJSON *component = cJSON_CreateObject();
        string componentName = comp.first;
        //ComponentCalls
        cJSON *componentActions = cJSON_CreateObject();
        for(auto call : comp.second){
            string callName = call.first;
            CompileArgs args = call.second;
            int numberOfArguments = args.NumberofArguments;
            cJSON_AddNumberToObject(componentActions, callName.c_str(), numberOfArguments);
        }
        cJSON_AddItemToObject(component, "actions", componentActions);

        //ComponentEvents
        cJSON *componentEvents = cJSON_CreateObject();
        for(auto event : eventArgs[componentName]){
           cJSON_AddNumberToObject(componentEvents, event.first.c_str(),
                   event.second); 
        }

        cJSON_AddItemToObject(component, "events", componentEvents);

        cJSON_AddItemToObject(root, componentName.c_str(), component);
    }

    string s = string(cJSON_Print(root));
    cJSON_Delete(root);

    return s;
}

void Rucola::Rucolang::RegisterComponentCalls(map<string,map<string,CompileArgs>> componentCalls){
    this->componentCalls = componentCalls;
}

void Rucola::Rucolang::RegisterEvents(map<string,map<string,int>> eventArgs){
    this->eventArgs = eventArgs;
}

void Rucola::Rucolang::RegisterEventCallback(function<void(string,string,vector<int>)> *eventCallback){
    this->eventCallback = eventCallback;
}

vector<int> Rucola::Rucolang::Compile(string code){
    vector<int> result;
    Block *ast = ParseString(code);
    ast->Compile(componentCalls, &env, &events, &result, (*eventCallback));
    return result;
}

vector<int> Rucola::Rucolang::Event(string event, vector<int> args){
    vector<int> result;
    if(events.count(event)){
        Statement *s = events[event];
        if(Rucola::Event *e = dynamic_cast<Rucola::Event*>(s)){
            e->Call(args, componentCalls, &env, &events, &result, (*eventCallback));
        } else {
            string err = "Error in compiler: event " + event + " not an Event";
            throw RucolaException(err.c_str());
        }
    }
    return result;
}

string Rucola::Rucolang::CodeToString(string code){
    Block *ast = ParseString(code);
    return ast->toString();
}
