%{
  #include <stdio.h>
  #include "cgen.h"
  
  extern int yylex(void);
  extern int line_num;
%}

%union
{
  char* str;
  int num;
}


%token  ID
%token  <str> INTEGER 
%token  <str> FLOAT 
%token  CONST_STRING

%token ASSIGN

%token KW_IF
%token KW_ENDIF
%token KW_THEN
%token KW_ELSE
%token KW_FOR
%token KW_ENDFOR

%token KW_TRUE
%token KW_FALSE
%token KW_INTEGER
%token KW_SCALAR
%token KW_STR
%token KW_BOOL
%token KW_CONST
%token KW_IN
%token KW_WHILE
%token KW_ENDWHILE
%token KW_BREAK
%token KW_CONTINUE
%token KW_NOT
%token KW_AND
%token KW_OR
%token KW_DEF
%token KW_ENDDEF
%token KW_MAIN
%token KW_RETURN
%token KW_COMP
%token KW_ENDCOMP
%token KW_OF
%token OP_POWER
%token OP_ASSIGN
%token OP_LESSEQUAL
%token OP_GREATEREQUAL
%token OP_EQUAL
%token OP_INEQUAL

%start input

%type <str> expr

%left '-' '+'
%left '*' '/'

%%

input:  
  %empty 
| input expr ';' 
{ 
  if (yyerror_count == 0) {
    puts(c_prologue);
    printf("Expression evaluates to: %s\n", $2); 
  }  
}
;

expr:
  INTEGER { $$ = $1; }
| FLOAT
| '(' expr ')' { $$ = template("(%s)", $2); }
| '[' expr ']' { $$ = template("[%s]", $2); }
| expr '+' expr { $$ = template("%s + %s", $1, $3); }
| expr '-' expr { $$ = template("%s - %s", $1, $3); }
| expr '*' expr { $$ = template("%s * %s", $1, $3); }
| expr '/' expr { $$ = template("%s / %s", $1, $3); }
;

%%
int main () {
  if ( yyparse() == 0 )
    printf("Accepted!\n");
  else
    printf("Rejected!\n");
}
