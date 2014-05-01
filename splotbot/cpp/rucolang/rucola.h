#ifndef RUCOLA_H
#define RUCOLA_H
#include "Absyn.h"
#include "compileargs.h"
#include <map>
using namespace std;

namespace Rucola{
    Block *ParseString(string s);
    class Rucolang {
        public:
            Rucolang();
            void RegisterComponentCalls(map<string,map<string, CompileArgs>> componentCalls);
            vector<int> Compile(string code);
            string CodeToString(string code);
            vector<int> Event(string event);
        private:
            map<string,map<string,CompileArgs>> componentCalls;
            map<string, Statement*> events;
    };

}
#endif
