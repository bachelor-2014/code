%{
#include <cstdio>
#include <iostream>
#include <vector>
#include "util.h"
#include "Absyn.h"
using namespace std;

%}

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  But tokens could be of any
// arbitrary data type!  So we deal with that in Bison by defining a C union
// holding each of the types of tokens that Flex could return, and have Bison
// use that union instead of "int" for the definition of "yystype":
%union {
    int ival;
    float fval;
    char *sval;
}

// define the constant-string tokens:
%token LPAR RPAR DOT

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING

%%

//A module call
Main:
   Tops 
;

Tops:
    /* empty */ 
    | Top Tops  
;

Top:
    ComponentCall
;

ComponentCall:
    STRING DOT STRING LPAR RPAR{auto cc = ComponentCall($1, $3, vector<int>()); cout << cc.toString();}
;
%%

