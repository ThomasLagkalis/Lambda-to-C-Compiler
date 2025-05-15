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

%define parse.error verbose

%token  <str> ID
%token  <str> INTEGER 
%token  <str> FLOAT 
%token  <str> CONST_STRING

%token ARROW
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
%type <str> str_expr
%type <str> arithmetic_expr
%type <str> id_expr
%type <str> data_type
%type <str> arrays
%type <str> array_decl
%type <str> id_recursion
%type <str> var_decl
%type <str> declarations
%type <str> single_declaration
%type <str> number_or_str
%type <str> const_decl
%type <str> body
%type <str> func_args
%type <str> func_decl
%type <str> main_func
%type <str> prog
%type <str> func_statement
%type <str> func_statement_args
%type <str> single_statement
%type <str> assign_statement
%type <str> return_statement
%type <str> if_statement
%type <str> for_statement
%type <str> while_statement
%type <str> loop_body
%type <str> if_helper

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
%left '(' 
%left ')'  
%left '[' 
%left ']' 
%left '.'

%start start
/*----------------------------------------------------- Grammar Rules ----------------------------------------------------- */
%%

start:  
prog 
{ 
  if (yyerror_count == 0) {
    puts(c_prologue);
    printf("%s", $1); 
  }  
}
;

//The programm starts either with declarations and then the main or just the main.
prog:
declarations main_func 		{ $$ = template("%s\n%s", $1, $2); }
| main_func			{ $$ = $1; }
;

// main function with or without body.
main_func:
KW_DEF KW_MAIN '(' ')' ':' body KW_ENDDEF ';'	{ $$ = template("int main(){\n%s\n}", $6); }
| KW_DEF KW_MAIN '(' ')' ':' KW_ENDDEF ';'	{ $$ = template("int main(){\n\n}" ); }   
;

// This is the body used in functions, loops etc...
body:
body single_declaration 		{ $$ = template("%s\n%s", $1, $2); }
|body single_statement			{ $$ = template("%s\n%s", $1, $2); }
| single_declaration 			{ $$ = $1; }
| single_statement			{ $$ = $1; }
;
/* --------------------------------------------------- Declarations ------------------------------------------------------------*/
// Declarations could be single or many.
declarations:
declarations single_declaration			{ $$ = template("%s\n%s", $1, $2); } 	
| single_declaration 				{ $$ = $1; }
;

single_declaration:
var_decl		    { $$ = $1; }
| array_decl		    { $$ = $1; }
| const_decl		    { $$ = $1; }
| func_decl		    { $$ = $1; }
;

data_type:
KW_INTEGER	            {$$ = template("int");}
  | KW_BOOL	            {$$ = template("int");}
  | KW_SCALAR               {$$ = template("double");}
  | KW_STR                  {$$ = template("char*");}
;

var_decl:
id_recursion ':' data_type ';'	  	  { $$ = template("%s %s;", $3, $1); }
;

id_recursion:
ID 			{ $$ = $1; }
| ID ',' id_recursion 	{ $$ = template("%s, %s", $1, $3); }
;
 
 array_decl:
'[' ']' ':' data_type ';'		{ $$ = template("%s*", $4); } 
| ID '[' expr ']' ':' data_type	';'	{ $$ = template("%s %s[%s]", $6, $1, $3); }	 
;

number_or_str:
INTEGER 		    { $$ = $1; }
| FLOAT			    { $$ = $1; }
| CONST_STRING		    { $$ = $1; }
;

const_decl:
KW_CONST ID ASSIGN number_or_str ':' data_type ';'		{ $$ = template("const %s %s = %s", $6, $2, $4); }	
;

// Maybe should add later arrays as arguments
func_args:
%empty						{ $$ = "" ; }
| ID ':' data_type				{ $$ = template("%s %s", $3, $1); }
| ID ':' data_type ',' func_args		{ $$ = template("%s %s, %s", $3, $1, $5); }
| ID '[' ']' ':' data_type			{ $$ = template("%s* %s", $5, $1); }
| ID '[' ']' ':' data_type ',' func_args		{ $$ = template("%s* %s, %s", $5, $1, $5); }
;

// Fucntion with or without body
func_decl:
KW_DEF ID '(' func_args ')' ARROW data_type ':' body KW_ENDDEF ';'
{ $$ = template("%s %s(%s){\n%s\n}", $7, $2, $4, $9); }
| KW_DEF ID '(' func_args ')' ARROW data_type ':' KW_ENDDEF ';'
{ $$ = template("%s %s(%s){\n\n}", $7, $2, $4); }
| KW_DEF ID '(' func_args ')' ':' body KW_ENDDEF ';'
{ $$ = template("void %s(%s){\n%s\n}", $2, $4, $7); }
| KW_DEF ID '(' func_args ')' ':' KW_ENDDEF ';'
{ $$ = template("void %s(%s){\n\n}", $2, $4); }
;
/* --------------------------------------------------- Statements Rules --------------------------------------------------------*/
single_statement:
assign_statement ';'				{ $$ = $1; }
| func_statement ';'				{ $$ = template("%s;",$1); }
| return_statement ';'				{ $$ = $1; }
| arrays ';'					{ $$ = $1; }
| if_statement ';'				{ $$ = $1; }
| for_statement	';'				{ $$ = $1; }
| while_statement ';'				{ $$ = $1; }
;

assign_statement:
ID ASSIGN func_statement 			{ $$ = template("%s = %s;", $1, $3); }
| assign_expr 					{ $$ = $1; }
;

func_statement:
ID '(' func_statement_args ')' 			{ $$ = template("%s(%s)", $1, $3); }
;

func_statement_args:
%empty						{ $$ = "" ; }
| expr						{ $$ = $1; }
| expr ',' func_statement_args 			{ $$ = template("%s, %s", $1, $3); }
;

return_statement:
KW_RETURN 					{ $$ = template("return;"); }
| KW_RETURN expr 				{ $$ = template("return %s;", $2); }
;

if_statement:
KW_IF '(' if_helper ')' ':' body KW_ENDIF 				{ $$ = template("if (%s){\n%s\n}", $3, $6); }
| KW_IF '(' if_helper ')' ':' body KW_ELSE ':' body KW_ENDIF   	{ $$ = template("if (%s){\n%s\n} else{ \n%s\n}", $3, $6, $9); }
;

if_helper:
expr						{ $$ = $1; }
| func_statement				{ $$ = $1; }

for_statement:
KW_FOR ID KW_IN '[' arithmetic_expr ':' arithmetic_expr ':' arithmetic_expr ']' ':' loop_body KW_ENDFOR 
{ $$ = template("for (int %s = %s; %s<=%s; %s+=%s){\n%s\n}", $2, $5, $2, $7, $2, $9, $12); }
| KW_FOR ID KW_IN '[' arithmetic_expr ':' arithmetic_expr ']' ':' loop_body KW_ENDFOR 	
{ $$ = template("for (int %s = %s; %s<=%s; %s++){\n%s\n}", $2, $5, $2, $7, $2, $10); }
;

while_statement:
KW_WHILE '(' if_helper ')' ':' loop_body KW_ENDWHILE		
{ $$ = template("while(%s){\n%s\n}",$3, $6); }
;

loop_body:
body				{ $$ = $1; }
| KW_BREAK 			{ $$ = template("break;"); }
| KW_CONTINUE	 		{ $$ = template("continue;"); }
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

/* --------------------------------------------------- Expression Rules --------------------------------------------------------*/

expr:
//func_statement		{ $$ = $1; }
 str_expr		{ $$ = $1; }	
| id_expr		{ $$ = $1; }
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

str_expr:
CONST_STRING		{ $$ = $1; }
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
    printf("\n\n/*+++++++++Accepted!++++++++++*/\n");
  else
    printf("\n\n/*---------Rejected!----------*/\n");
}
