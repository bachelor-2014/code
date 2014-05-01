%{
#include <iostream>
#include <string.h>
#include "Absyn.h"
#include "rucola.tab.h"
using namespace std;
using namespace Rucola;
%}
%%
[ \t] ;
\(              { return LPAR; }
\)              { return RPAR; }
\.              { return DOT; }
,               { return COMMA; }
->              { return ARROW; }
\{               { return LBRACE; }
\}               { return RBRACE; }
[0-9]+\.[0-9]+  { yylval.fval = atof(yytext); return FLOAT; }
[-]*[0-9]+          { yylval.ival = atoi(yytext); return INT; }
[a-zA-Z0-9]+    {
    yylval.sval = new std::string(yytext, yyleng);
    return STRING;
}
.              ;
%%
