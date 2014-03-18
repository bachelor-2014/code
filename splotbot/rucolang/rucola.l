%{
#include <iostream>
#include <string.h>
#include "Absyn.h"
#include "rucola.tab.h"
#include "lexer.h"
using namespace std;
using namespace Rucola;
#define YY_DECL extern "C" int yylex()
%}
%%
[ \t] ;
\(              { return LPAR; }
\)              { return RPAR; }
\.              { return DOT; }
,               { return COMMA; }
[0-9]+\.[0-9]+  { yylval.fval = atof(yytext); return FLOAT; }
[0-9]+          { yylval.ival = atoi(yytext); return INT; }
[a-zA-Z0-9]+    {
    // we have to copy because we can't rely on yytext not changing underneath us:
    yylval.sval = new std::string(yytext, yyleng);
    return STRING;
}
.              ;
%%

/**
 * Set the string to be lexed from
 */
void lex_from_string(string s){
    yy_scan_string(s.c_str());
}
