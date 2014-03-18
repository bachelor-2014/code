#ifndef UTIL_H
#define UTIL_H
#include <cstdio>
#include <vector>

using namespace std;

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

void yyerror(const char *s);

#endif
