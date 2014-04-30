#ifndef RUCOLA_H
#define RUCOLA_H
#include "Absyn.h"
#include "rucola.h"
#include <map>
using namespace std;

namespace Rucola{
    Block *ParseString(string s);
    class Rucolang {
        public:
            Rucolang();
            void RegisterComponentCalls(map<string,map<string,int>> componentCalls);
            vector<int> Compile(string code);
        private:
            map<string,map<string,int>> componentCalls;
    };
}
#endif
