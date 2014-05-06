#ifndef RUCOLA_H
#define RUCOLA_H
#include "Absyn.h"
#include "compileargs.h"
#include <map>
#include <functional>
#include <string>
using namespace std;

namespace Rucola{
    Block *ParseString(string s);
    class Rucolang {
        public:
            Rucolang();
            void Clear();
            string Documentation();
            void RegisterComponentCalls(map<string,map<string, CompileArgs>> componentCalls);
            void RegisterEvents(map<string,map<string,int>> eventArgs);
            void RegisterEventCallback(function<void(string,string,vector<int>)> *eventCallback);
            vector<int> Compile(string code);
            string CodeToString(string code);
            vector<int> Event(string event, vector<int> args);
        private:
            map<string,map<string,CompileArgs>> componentCalls;
            map<string,map<string,int>> eventArgs;
            map<string, Statement*> events;
            map<string, int> env;
            function<void(string,string,vector<int>)> *eventCallback;
    };

}
#endif
