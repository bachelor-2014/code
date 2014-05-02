#include "Absyn.h"
#include "lex.yy.h"
#include "rucola.tab.h"
#include "rucola.h"
#include "compileargs.h"
#include "../utils/errors.h"
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
    ast->Compile(componentCalls, &env, &events, &result);
    return result;
}

vector<int> Rucola::Rucolang::Event(string event, vector<int> args){
    vector<int> result;
    if(events.count(event)){
        Statement *s = events[event];
        if(Rucola::Event *e = dynamic_cast<Rucola::Event*>(s)){
            e->Call(args, componentCalls, &env, &events, &result);
        } else {
            string err = "Error in compiler: event " + event + " not an Event";
            throw RucolaException(err.c_str());
        }
    }
    return result;
}

string Rucola::Rucolang::CodeToString(string code){
    Block *ast = ParseString(code);
    return ast->toString();
}
