%{
#include <cstdio>
#include <iostream>
#include <vector>
#include "Absyn.h"
#include "rucola.tab.h"
#include "lex.yy.h"
#include "../utils/errors.h"
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
    Rucola::Event *event;
    Rucola::Expr *expr;
    Rucola::IExpr *iexpr;
    Rucola::VExpr *vexpr;
    int ival;
    float fval;
    string *sval;
    vector<Rucola::Expr*> *vece;
}

// Constant-string tokens
%token LPAR RPAR DOT COMMA ARROW LBRACE RBRACE

//Terminal symbols
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING

//Types
%type <block> program stmts
%type <stmt> stmt
%type <vece> args
%type <expr> expr

%%

//Program
program : stmts { programBlock = $1; }
;

//Statements
stmt:
    //Call to a component
    STRING DOT STRING LPAR args RPAR{$$ = new ComponentCall($1, $3, $5);}
    | LPAR STRING RPAR ARROW LBRACE stmts RBRACE {$$ = new Event($2, $6);}
;

//A block (multiple statements)
stmts : stmt { $$ = new Block(); $$->AddStatement($1); }
      | stmts stmt  { $1->AddStatement($2);}
;

//Interger list of comma seperated arguments
args :     { $$ = new vector<Expr*>();}  
     | expr { $$ = new vector<Expr*>(); $$->push_back($1);} 
     | args COMMA expr { $1->push_back($3);}
;

//An expression, either a constant int or a variable
expr : INT { $$ = new IExpr($1); }  
     | STRING { $$ = new VExpr($1); } 
;

%%

/**
 * Print parsing error
 */
void yyerror(const char *s) {
    string error = "Could not parse, is this valid Rucolang code?";
    throw RucolaException(error.c_str());
}
