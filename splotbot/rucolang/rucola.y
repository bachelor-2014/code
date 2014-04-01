%{
#include <cstdio>
#include <iostream>
#include <vector>
#include "Absyn.h"
#include "rucola.tab.h"
#include "lex.yy.h"
using namespace std;
using namespace Rucola;

//The global program block, used to store the resulting AST
Block *programBlock;

void yyerror(const char *s);
%}

//Possible types returned from Flex or Parsed into
%union {
    Rucola::Statement *stmt;
    Rucola::Block *block;
    Rucola::ComponentCall *ccall;
    int ival;
    float fval;
    string *sval;
    vector<int> *veci;
}

// Constant-string tokens
%token LPAR RPAR DOT COMMA

//Terminal symbols
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING

//Types
%type <block> program stmts
%type <stmt> stmt
%type <veci> args

%%

//Program
program : stmts { programBlock = $1; }
;

//Statements
stmt:
    //Call to a component
    STRING DOT STRING LPAR args RPAR{$$ = new ComponentCall($1, $3, $5);}
;

//A block (multiple statements)
stmts : stmt { $$ = new Block(); $$->AddStatement($1); }
      | stmts stmt  { $1->AddStatement($2);}
;

//Interger list of comma seperated arguments
args :     { $$ = new vector<int>();}  
     | INT { $$ = new vector<int>(); $$->push_back($1);} 
     | args COMMA INT { $1->push_back($3);}
;

%%

/**
 * Print parsing error
 */
void yyerror(const char *s) {
    cout << "Parse error!  Message: " << s << endl;
    // might as well halt now:
    exit(-1);
}
