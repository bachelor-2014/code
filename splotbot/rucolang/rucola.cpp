#include "util.h"
#include "Absyn.h"
#include "lexer.h"
#include "rucola.h"
#include <string>
using namespace std;
using namespace Rucola;

extern Block *programBlock;

Block *Rucola::ParseString(string s){
    lex_from_string(s);
    yyparse(); 
    return programBlock; 
}
