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
%token <token> TCEQ TCNE TCLT TCLE TCGT TCGE TEQUAL
%token <token> TLPAREN TRPAREN TLBRACE TRBRACE TCOMMA TSEMICOLON 
%token <token> TPLUS TMINUS
%token <token> TVAR TPRE
%token <token> TAT

/* Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above. Ex: when
   we call an ident (defined by union type ident) we are really
   calling an (NIdentifier*). It makes the compiler happy.
 */
%type <ident> ident
%type <expr> numeric expr
%type <exprvec> call_args
%type <block> program stmts 
%type <stmt> stmt var_decl block
%type <token> binary_op

/* Operator precedence for mathematical operators */
%left TPLUS TMINUS

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
     ;

block : TLBRACE stmts TRBRACE { $$ = $2; }
      | TLBRACE TRBRACE { $$ = new NBlock(); }
      ;

var_decl : decl ident { $$ = new NVariableDeclaration(*$2); }
         | decl ident TEQUAL expr { $$ = new NVariableDeclaration(*$2, $4); }
         ;
decl : TVAR | TPRE

ident : TIDENTIFIER { $$ = new NIdentifier(*$1); delete $1; }
      ;

numeric : TINTEGER { $$ = new NInteger(atol($1->c_str())); delete $1; }
        ;

expr : ident TEQUAL expr { $$ = new NAssignment(*$1, *$3); }
     | ident TLPAREN call_args TRPAREN { $$ = new NMethodCall(*$1, *$3); delete $3; }
     | ident { $$ = $1; }
     | numeric
     | expr binary_op expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
     | TLPAREN expr TRPAREN { $$ = $2; }
     ;

call_args : /*blank*/  { $$ = new ExpressionList(); }
          | expr { $$ = new ExpressionList(); $$->push_back($1); }
          | call_args TCOMMA expr  { $1->push_back($3); }
          ;

binary_op : TCEQ | TCNE | TCLT | TCLE | TCGT | TCGE
           | TPLUS | TMINUS
           ;

%%