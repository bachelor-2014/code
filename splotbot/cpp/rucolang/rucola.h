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
            void RegisterComponentCalls(map<string,map<string, CompileArgs>> componentCalls);
            void RegisterEventCallback(function<void(string,string,vector<int>)> *eventCallback);
            vector<int> Compile(string code);
            string CodeToString(string code);
            vector<int> Event(string event, vector<int> args);
        private:
            map<string,map<string,CompileArgs>> componentCalls;
            map<string, Statement*> events;
            map<string, int> env;
            function<void(string,string,vector<int>)> *eventCallback;
    };

}
#endif
