#include "Absyn.h"
#include "lex.yy.h"
#include "rucola.tab.h"
#include "rucola.h"
#include <string>
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
