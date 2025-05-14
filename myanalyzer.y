/*----------------------------------------------------- Prologue ----------------------------------------------------- */
%{
  #include <stdio.h>
  #include <string.h>
  #include <ctype.h>
  #include "cgen.h"
  
  extern int yylex(void);
  extern int line_num;
  
  
  void replace_identifier(const char* input, const char* var, const char* replacement, char* output) {
	/*Helper function thet repcaces an input's string (input) identifier (var) with a new str (replacement) 
	in output. This function is originally made for array comprehension usiong another array.*/
    const char* p = input;
    char* out = output;
    size_t var_len = strlen(var);

    while (*p) {
        if (strncmp(p, var, var_len) == 0 && 
            (p == input || !isalnum(*(p-1))) && 
            !isalnum(*(p+var_len))) {
            strcpy(out, replacement);
            out += strlen(replacement);
            p += var_len;
        } else {
            *out++ = *p++;
        }
    }
    *out = '\0';
}
%}

/*----------------------------------------------------- Bison Declerations ----------------------------------------------------- */
%union
{
  char* str;
  int num;
}


%token  <str> ID
%token  <str> INTEGER 
%token  <str> FLOAT 
%token  CONST_STRING

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
%token <str> DOT
%token OP_POWER
%token OP_LESSEQUAL
%token OP_GREATEREQUAL
%token OP_EQUAL
%token OP_INEQUAL
%token ASSIGN
%token ASSIGN_PLUS
%token ASSIGN_MINUS
%token ASSIGN_PRODUCT
%token ASSIGN_DIV
%token ASSIGN_MOD
%token ASSIGN_DOTS

%type <str> expr
%type <str> boolean_expr
%type <str> relation_expr
%type <str> assign_expr
%type <str> arithmetic_expr
%type <str> id_expr
%type <str> data_type
%type <str> arrays
%type <str> array_decl
%type <str> id_recursion
%type <str> var_decl
%type <str> declarations

%right INTEGER
%right ASSIGN_PLUS
%right ASSIGN_MINUS
%right ASSIGN_PRODUCT
%right ASSIGN_DIV
%right ASSIGN_MOD
%right ASSIGN_DOTS
%right ASSIGN
%left KW_OR
%left KW_AND
%right KW_NOT
%left OP_EQUAL
%left OP_INEQUAL
%left OP_LESSEQUAL
%left OP_GREATEREQUAL
%left '>' '<'
%left '-' '+' '*' '/' '%'
%right OP_POWER 
%left '(' ')'  '[' ']' '.'

%start start
/*----------------------------------------------------- Grammar Rules ----------------------------------------------------- */
%%

start:  
%empty
| start expr ';' 
{ 
  if (yyerror_count == 0) {
    puts(c_prologue);
    printf("Expression evaluates to: %s;\n", $2); 
  }  
}
;
/* --------------------------------------------------- Declarations ------------------------------------------------------------*/
declarations:
var_decl		    { $$ = $1; }
| array_decl		    { $$ = $1; }

data_type:
KW_INTEGER	            {$$ = template("int");}
  | KW_BOOL	            {$$ = template("int");}
  | KW_SCALAR               {$$ = template("double");}
  | KW_STR                  {$$ = template("char*");}
 ;
 
var_decl:
id_recursion ':' data_type	  	  { $$ = template("%s %s", $3, $1); }
;

id_recursion:
ID 	{ $$ = $1; }
| ID ',' id_recursion { $$ = template("%s, %s", $1, $3); }
;
 
 array_decl:
'[' ']' ':' data_type			{ $$ = template("%s*", $4); } 
| ID '[' expr ']' ':' data_type		{ $$ = template("%s %s[%s]", $6, $1, $3); }	 
/* --------------------------------------------------- Expression Rules --------------------------------------------------------*/

expr:
id_expr			{ $$ = $1; }
| declarations		{ $$ = $1; }// Make sure to change that, declarations are not expressions.
| assign_expr 		{ $$ = $1; }
| boolean_expr 		{ $$ = $1; }
| relation_expr		{ $$ = $1; }
| arithmetic_expr	{ $$ = $1; }
| '[' expr ')'		{ $$ = template("[ %s ]", $2); }
| '(' expr ')'		{ $$ = template("( %s )", $2); }
| DOT			{ $$ = template("( %s )", $1); }
;

boolean_expr:
KW_NOT expr		{ $$ = template("! %s", $2); }
| expr KW_OR expr 	{ $$ = template("%s || %s", $1, $3); }
| expr KW_AND expr 	{ $$ = template("%s && %s", $1, $3); }
| KW_TRUE 		{ $$ = template("1"); }
| KW_FALSE		{ $$ = template("0"); }
;

id_expr:
ID 			{ $$ = $1; }
| ID '[' expr ']'	{ $$ = template("%s[%s]", $1, $3); }
| ID '[' INTEGER ']'	{ $$ = template("%s[%s]", $1, $3); }
;

relation_expr: 
 expr OP_EQUAL expr 		{ $$ = template("%s == %s", $1, $3); }
| expr OP_INEQUAL expr 		{ $$ = template("%s != %s", $1, $3); }
| expr '<' expr 		{ $$ = template("%s < %s", $1, $3); }
| expr '>' expr			{ $$ = template("%s > %s", $1, $3); }
| expr OP_LESSEQUAL expr	{ $$ = template("%s <= %s", $1, $3); }
| expr OP_GREATEREQUAL expr	{ $$ = template("%s >= %s", $1, $3); }
;

assign_expr:
ID ASSIGN_PLUS expr		{ $$ = template("%s =+ %s", $1, $3); }
| ID ASSIGN_MINUS expr		{ $$ = template("%s =- %s", $1, $3); }
| ID ASSIGN_PRODUCT expr	{ $$ = template("%s =* %s", $1, $3); }
| ID ASSIGN_DIV expr		{ $$ = template("%s =/ %s", $1, $3); }
| ID ASSIGN_MOD expr		{ $$ = template("%s =% %s", $1, $3); }
| ID ASSIGN expr		{ $$ = template("%s = %s", $1, $3); }
| arrays 			{ $$ = $1; }
;

// Arrays Comprehensions
arrays:
ID ASSIGN_DOTS '[' expr KW_FOR ID ':' INTEGER ']' ':' data_type
{
	$$ = template("%s* %s = (%s*)malloc(%s * sizeof(%s));\n for (int %s = 0; %s < %s; ++%s)\n\t %s[%s] = %s", $11, $1, $11, $8, $11, $6, $6, $8, $6, $1, $6, $4 );
}
| ID ASSIGN_DOTS '[' expr KW_FOR ID ':' data_type KW_IN ID KW_OF INTEGER ']' ':' data_type
{
	char indexed_access[512];
	sprintf(indexed_access, "%s[%s_i]", $10, $10);  // array[array_i]
	char transformed_expr[512];
	replace_identifier($4, $6, indexed_access, transformed_expr);  // replace identidier with array[array_i]

	$$ = template("%s* %s = (%s*)malloc(%s * sizeof(%s));\n for (int %s_i = 0; %s_i < %s; ++%s_i)\n\t %s[%s] = %s", $15, $1, $15, $12, $15, $10, $10, $12, $10, $1, $10, transformed_expr);
}
;

arithmetic_expr:
INTEGER 		{ $$ = $1; }
| FLOAT   		{ $$ = $1; }
| expr '+' expr 	{ $$ = template("%s + %s", $1, $3); }
| expr '-' expr 	{ $$ = template("%s - %s", $1, $3); }
| expr '*' expr 	{ $$ = template("%s * %s", $1, $3); }
| expr '/' expr 	{ $$ = template("%s / %s", $1, $3); }
| expr '%' expr 	{ $$ = template("%s % %s", $1, $3); }
| '+' expr	        { $$ = template("+%s", $2);}
| '-' expr	        { $$ = template("-%s", $2);}
| expr OP_POWER expr 	{ $$ = template("pow(%s, %s)", $1, $3);}
;


/*----------------------------------------------------- Epilogue ----------------------------------------------------- */
%%
int main () {
  if ( yyparse() == 0 )
    printf("Accepted!\n");
  else
    printf("Rejected!\n");
}
