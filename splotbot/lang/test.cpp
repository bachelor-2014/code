#include <iostream>
#include <cstdio>
#include "util.h"
#include "Absyn.h"
using namespace std;

extern Block *programBlock;


main() {
    // open a file handle to a particular file:
    FILE *myfile = fopen("code.spl", "r");
    // make sure it's valid:
    if (!myfile) {
        cout << "I can't open a.snazzle.file!" << endl;
        return -1;
    }
    // set flex to read from it instead of defaulting to STDIN:
    yyin = myfile;

    // parse through the input until there is no more:
    yyparse();

    cout << programBlock->toString();
}

