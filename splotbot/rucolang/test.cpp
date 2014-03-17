#include <iostream>
#include <cstdio>
#include "rucola.h"
using namespace std;
using namespace Rucola;

main() {
    string s = 
        "module1.do(1,2)"
        "module2.do(1,2)";
    Block *program = Rucola::ParseString(s);

    cout << program->toString();
}

