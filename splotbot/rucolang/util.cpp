#include <iostream>
#include "util.h"

using namespace std;

/**
 * Print parsing error
 */
void yyerror(const char *s) {
    cout << "Parse error!  Message: " << s << endl;
    // might as well halt now:
    exit(-1);
}
