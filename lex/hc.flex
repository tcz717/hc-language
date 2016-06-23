%{
#include <string> 
#include "node.h" 
#include "parser.hpp" 

#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
%}

%option noyywrap nounput

%%

[\n\t]

"var"                   return TOKEN(TVAR); 
"pre"                   return TOKEN(TPRE); 

[_a-zA-Z][_a-zA-Z0-9]*  SAVE_TOKEN; return TIDENTIFIER;
#[0-9]+                 SAVE_TOKEN; return TREGISTER;
[1-9][0-9]*|0      SAVE_TOKEN; return TINTEGER;
 "="					return TOKEN(TEQUAL); 
"=="			      	return TOKEN(TCEQ); 
"!="			  		return TOKEN(TCNE); 
"<"				  		return TOKEN(TCLT); 
"<="	        		return TOKEN(TCLE); 
">"				  		return TOKEN(TCGT); 
">="			        return TOKEN(TCGE); 

"("	          			return TOKEN(TLPAREN); 
")"				      	return TOKEN(TRPAREN); 
"{"         			return TOKEN(TLBRACE); 
"}"				      	return TOKEN(TRBRACE); 

","				  		return TOKEN(TCOMMA); 
";"				  		return TOKEN(TSEMICOLON); 

 
"+"				  		return TOKEN(TPLUS); 
"-"		        		return TOKEN(TMINUS); 
"@"		        		return TOKEN(TAT); 
 
.                       printf("Unknown token!\n"); yyterminate(); 


%%