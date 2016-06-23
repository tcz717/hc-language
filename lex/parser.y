%{
    #include "node.h"
    #include <cstdio>
    #include <cstdlib>
    NBlock *programBlock; /* the top level root node of our final AST */

    extern int yylex();
    void yyerror(const char *s) { printf("ERROR: %s\n", s); std::exit(1); }
%}

%defines

/* Represents the many different ways we can access our data */
%union {
    Node *node;
    NBlock *block;
    NExpression *expr;
    NStatement *stmt;
    NIdentifier *ident;
    NVariableDeclaration *var_decl;
    std::vector<NVariableDeclaration*> *varvec;
    std::vector<NExpression*> *exprvec;
    std::string *string;
    int token;
}

/* Define our terminal symbols (tokens). This should
   match our tokens.l lex file. We also define the node type
   they represent.
 */
%token <string> TIDENTIFIER TINTEGER TREGISTER
%left <token> TCOMMA
%right <token> TEQUAL
%nonassoc <token> TCEQ TCNE TCLT TCLE TCGT TCGE
%left <token> TPLUS TMINUS
%token <token> TLPAREN TRPAREN TLBRACE TRBRACE TSEMICOLON TCOLON TAT
%token <token> TVAR TPRE TLOOP

/* Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above. Ex: when
   we call an ident (defined by union type ident) we are really
   calling an (NIdentifier*). It makes the compiler happy.
 */
%type <ident> ident
%type <expr> numeric expr atom term
%type <exprvec> call_args
%type <block> program stmts 
%type <stmt> stmt var_decl block loop
%type <token> campare_op math2_op

%start program

%%

program : stmts { programBlock = $1; }
        ;

stmts : stmt { $$ = new NBlock(); $$->statements.push_back($1); }
      | stmts stmt { $1->statements.push_back($2); }
      ;

stmt : var_decl TSEMICOLON
     | expr TSEMICOLON { $$ = new NExpressionStatement(*$1); }
     | block
     | loop
     ;

block : TLBRACE stmts TRBRACE { $$ = $2; }
      | TLBRACE TRBRACE { $$ = new NBlock(); }
      ;

var_decl : TVAR ident { $$ = new NVariableDeclaration(*$2); }
         | TVAR ident TAT numeric { $$ = new NVariableDeclaration(*$2, ((NInteger*)$4)->value); }
         | TVAR ident TEQUAL expr { $$ = new NVariableDeclaration(*$2, $4); }
         | TVAR ident TAT numeric TEQUAL expr { $$ = new NVariableDeclaration(*$2, ((NInteger*)$4)->value, $6); }
         ;

loop : TLOOP stmt { $$ = $2; }
     | TLOOP TCOLON ident stmt { $$ = $4; }

ident : TIDENTIFIER { $$ = new NIdentifier(*$1); delete $1; }
      ;

numeric : TINTEGER { $$ = new NInteger(atol($1->c_str())); delete $1; }
        ;

expr : ident TEQUAL expr { $$ = new NAssignment(*$1, *$3); }
     | term { $$ = $1; }
     | expr campare_op term { $$ = new NBinaryOperator(*$1, $2, *$3); }
     ;

term : atom { $$ = $1; }
     | term math2_op atom { $$ = new NBinaryOperator(*$1, $2, *$3); }

atom : ident { $$ = $1; }
     | numeric
     | TLPAREN expr TRPAREN { $$ = $2; }
     | ident TLPAREN call_args TRPAREN { $$ = new NMethodCall(*$1, *$3); delete $3; }

call_args : /*blank*/  { $$ = new ExpressionList(); }
          | expr { $$ = new ExpressionList(); $$->push_back($1); }
          | call_args TCOMMA expr  { $1->push_back($3); }
          ;

campare_op : TCEQ | TCNE | TCLT | TCLE | TCGT | TCGE
           ;

math2_op :   TPLUS | TMINUS
           ;

%%