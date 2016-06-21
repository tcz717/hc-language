%{
#include "token.h"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
extern "C" int yywrap() { }
%}

%%

[\n\t]
[_a-zA-Z][_a-zA-Z0-9]*  SAVE_TOKEN; return TIDENTIFIER;
#[0-9]+                 SAVE_TOKEN; return TREGISTER;

%%