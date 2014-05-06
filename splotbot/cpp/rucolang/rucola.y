%{
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
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
    Rucola::Assignment *assignment;
    Rucola::Conditional *conditional;
    Rucola::Event *event;
    Rucola::Expr *expr;
    Rucola::IExpr *iexpr;
    Rucola::VExpr *vexpr;
    int ival;
    float fval;
    string *sval;
    vector<Rucola::Expr*> *vece;
    vector<string*> *strings;
}

// Constant-string tokens
%token LPAR RPAR DOT COMMA ASSIGN ARROW LBRACE RBRACE COLON SEMI
%token PLUS MINUS TIMES DIV MOD EQ NEQ LT LTEQ GT GTEQ AND OR
%token IF ELSE PRINT

// Precedence
%right ASSIGN
%nonassoc PRINT
%left OR
%left AND
%left EQ NEQ
%nonassoc LT LTEQ GT GTEQ
%left PLUS MINUS
%left TIMES DIV MOD
%nonassoc LBRACE


//Terminal symbols
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING
%token <sval> STRINGLIT

//Types
%type <block> program stmts
%type <stmt> stmt
%type <vece> args
%type <expr> expr
%type <strings> argnames

%%

//Program
program : stmts { programBlock = $1; }
;

//Statements
stmt:
      //Call to a component
      STRING DOT STRING LPAR args RPAR{$$ = new ComponentCall($1, $3, $5);}
      //Variable assignment
    | STRING ASSIGN expr { $$ = new Assignment($1, $3); }

      //Event binding
    | LPAR STRING argnames RPAR ARROW LBRACE stmts RBRACE {$$ = new Event($2, $3, $7);}

      //Conditional statement
    | IF LPAR expr RPAR LBRACE stmts RBRACE ELSE LBRACE stmts RBRACE { $$ = new Conditional($3, $6, $10); }
      //Print
    | PRINT STRINGLIT LPAR args RPAR { $$ = new Print($2, $4);}
;

//A block (multiple statements)
stmts :
       stmt { $$ = new Block(); $$->AddStatement($1); }
      | stmts stmt  { $1->AddStatement($2);}
;

//Interger list of comma seperated arguments
args :     { $$ = new vector<Expr*>();}  
     | expr { $$ = new vector<Expr*>(); $$->push_back($1);} 
     | args COMMA expr { $1->push_back($3);}
;

//String list of comma seperated argument names
argnames : { $$ = new vector<string*>(); }
         | COLON STRING { $$ = new vector<string*>(); $$->push_back($2);}
         | argnames COMMA STRING { $1->push_back($3);}

//An expression, either a constant int or a variable
expr : LPAR expr RPAR { $$ = $2; }
     | INT { $$ = new IExpr($1); }  
     | STRING { $$ = new VExpr($1); } 
     | expr PLUS expr { $$ = new AExpr(new string("+"), $1, $3); }
     | expr MINUS expr { $$ = new AExpr(new string("-"), $1, $3); }
     | expr TIMES expr { $$ = new AExpr(new string("*"), $1, $3); }
     | expr DIV expr { $$ = new AExpr(new string("/"), $1, $3); }
     | expr MOD expr { $$ = new AExpr(new string("%"), $1, $3); }
     | expr EQ expr { $$ = new AExpr(new string("=="), $1, $3); }
     | expr NEQ expr { $$ = new AExpr(new string("!="), $1, $3); }
     | expr LT expr { $$ = new AExpr(new string("<"), $1, $3); }
     | expr LTEQ expr { $$ = new AExpr(new string("<="), $1, $3); }
     | expr GT expr { $$ = new AExpr(new string(">"), $1, $3); }
     | expr GTEQ expr { $$ = new AExpr(new string(">="), $1, $3); }
     | expr AND expr { $$ = new AExpr(new string("&&"), $1, $3); }
     | expr OR expr { $$ = new AExpr(new string("||"), $1, $3); }
;

%%

/**
 * Print parsing error
 */
void yyerror(const char *s) {
    string error = "Could not parse, is this valid Rucolang code?";
    throw RucolaException(error.c_str());
}
