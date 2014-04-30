#include "Absyn.h"
#include "lex.yy.h"
#include "rucola.tab.h"
#include "rucola.h"
#include "compileargs.h"
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

/**
 * Rucolang
 */
Rucola::Rucolang::Rucolang(){
    //Empty constructor
}

void Rucola::Rucolang::RegisterComponentCalls(map<string,map<string,CompileArgs>> componentCalls){
    this->componentCalls = componentCalls;
}

vector<int> Rucola::Rucolang::Compile(string code){
    vector<int> result;
    Block *ast = ParseString(code);
    ast->Compile(componentCalls, &result);
    return result;
}
