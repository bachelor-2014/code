%{
#include <cstdio>
#include <iostream>
#include <vector>
#include "util.h"
#include "Absyn.h"
using namespace std;

Block *programBlock;
%}

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  But tokens could be of any
// arbitrary data type!  So we deal with that in Bison by defining a C union
// holding each of the types of tokens that Flex could return, and have Bison
// use that union instead of "int" for the definition of "yystype":
%union {
    Statement *stmt;
    Block *block;
    ComponentCall *ccall;
    int ival;
    float fval;
    string *sval;
    vector<int> *veci;
}

// define the constant-string tokens:
%token LPAR RPAR DOT COMMA

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING

%type <block> program stmts
%type <stmt> stmt
%type <veci> args

%%

//A module call
program : stmts { programBlock = $1; }
;

stmt:
    STRING DOT STRING LPAR args RPAR{$$ = new ComponentCall($1, $3, $5);}
;

stmts : stmt { $$ = new Block(); $$->AddStatement($<stmt>1); }
      | stmts stmt  { $1->AddStatement($<stmt>2);}
;

args :     { $$ = new vector<int>();}  
     | INT { $$ = new vector<int>(); $$->push_back($1);} 
     | args COMMA INT { $1->push_back($3);}
;

%%

