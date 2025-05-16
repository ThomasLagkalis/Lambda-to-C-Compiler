/*----------------------------------------------------- Prologue ----------------------------------------------------- */
%{
  #include <stdio.h>
  #include <string.h>
  #include <ctype.h>
  #include <stdlib.h>
  #include "cgen.h"
  
  extern int yylex(void);
  extern int line_num;
  int inside_comp = 0;
  
  typedef struct comp_type {
    char *name;
    struct comp_type *next;
  } comp_type;

  comp_type *comp_type_list = NULL;

  void add_comp_type(const char *name) {
    comp_type *new_type = (comp_type *)malloc(sizeof(comp_type));
    new_type->name = strdup(name);
    new_type->next = comp_type_list;
    comp_type_list = new_type;
  }

  int is_comp_type(const char *name) {
    comp_type *current = comp_type_list;
    while (current) {
      if (strcmp(current->name, name) == 0) return 1;
      current = current->next;
    }
    return 0;
  }

  void free_comp_types() {
    comp_type *current = comp_type_list;
    while (current) {
      comp_type *next = current->next;
      free(current->name);
      free(current);
      current = next;
    }
    comp_type_list = NULL;
  }
  
typedef struct func {
    char *cname; // complex type name
    char *fname;
    char *fargs;
    char *ftype;
    char *fbody;
} func;

typedef struct func_node {
    func *data;
    struct func_node *next;
} func_node;

func_node *func_list_head = NULL;

void add_func(const char *name, const char *args, const char *type, const char *body) {
    /* Adds a func struct to the linked list */
    func *new_func = (func *)malloc(sizeof(func));
    if (!new_func) return;
    
    new_func->fname = name ? strdup(name) : NULL;
    new_func->fargs = args ? strdup(args) : NULL;
    new_func->ftype = type ? strdup(type) : NULL;
    new_func->fbody = body ? strdup(body) : NULL;

    func_node *new_node = (func_node *)malloc(sizeof(func_node));
    if (!new_node) {
        free(new_func->fname);
        free(new_func->fargs);
        free(new_func->ftype);
        free(new_func->fbody);
        free(new_func);
        return;
    }
    
    new_node->data = new_func;
    new_node->next = func_list_head;
    func_list_head = new_node;
}

void print_func_list() {
/*For debugging purposes*/
    func_node *current = func_list_head;
    while (current != NULL) {
        printf("Function: %s(%s) -> %s\nBody:\n%s\n\n",
            current->data->fname,
            current->data->fargs,
            current->data->ftype,
            current->data->fbody);
        current = current->next;
    }
}

void free_func_list() {
    /*This should be called in the end of the parses for clean up.*/
    func_node *current = func_list_head;
    while (current != NULL) {
        func_node *next = current->next;
        if (current->data) {
            if (current->data->fname) free(current->data->fname);
            if (current->data->fargs) free(current->data->fargs);
            if (current->data->ftype) free(current->data->ftype);
            if (current->data->fbody) free(current->data->fbody);
            free(current->data);
        }
        free(current);
        current = next;
    }
    func_list_head = NULL;
}

char* get_func_signatures(char* cname) {
    // First reverse the list
    func_node *prev = NULL;
    func_node *current = func_list_head;
    func_node *next = NULL;
    
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    func_list_head = prev;

    // Now process the list as before
    size_t bufsize = 1024;
    size_t used = 0;
    char *result = malloc(bufsize);
    if (!result) return NULL;
    result[0] = '\0';

    current = func_list_head;
    while (current != NULL && current->data) {
        const char *fname = current->data->fname ? current->data->fname : "";
        const char *ftype = current->data->ftype ? current->data->ftype : "void";
        const char *fargs = current->data->fargs ? current->data->fargs : "";

        char signature[512];
        int len = snprintf(signature, sizeof(signature),
                 "%s (*%s)(struct %s *self%s%s);\n",
                 ftype, fname, cname,
                 (fargs && strlen(fargs) > 0) ? ", " : "",
                 (fargs && strlen(fargs) > 0) ? fargs : "");

        if (used + len + 1 > bufsize) {
            bufsize *= 2;
            char *new_result = realloc(result, bufsize);
            if (!new_result) {
                free(result);
                return NULL;
            }
            result = new_result;
        }

        strcpy(result + used, signature);
        used += len;
        current = current->next;
    }

    return result;
}

char* get_func_with_body(char* cname) {
    func_node *current = func_list_head;
    size_t bufsize = 4096;  // Start with larger buffer since we're including bodies
    size_t used = 0;
    char *result = malloc(bufsize);
    if (!result) return NULL;
    result[0] = '\0';

    // First pass: generate function implementations
    while (current != NULL && current->data) {
        const char *fname = current->data->fname ? current->data->fname : "";
        const char *ftype = current->data->ftype ? current->data->ftype : "void";
        const char *fargs = current->data->fargs ? current->data->fargs : "";
        const char *fbody = current->data->fbody ? current->data->fbody : "";

        // Generate function implementation
        char func_impl[1024];
        int len = snprintf(func_impl, sizeof(func_impl),
                 "%s %s(struct %s *self%s%s) {\n%s\n}\n\n",
                 ftype, fname, cname,
                 (fargs && strlen(fargs) > 0) ? ", " : "",
                 (fargs && strlen(fargs) > 0) ? fargs : "",
                 fbody);

        // Check buffer space
        if (used + len + 1 > bufsize) {
            bufsize *= 2;
            char *new_result = realloc(result, bufsize);
            if (!new_result) {
                free(result);
                return NULL;
            }
            result = new_result;
        }

        strcpy(result + used, func_impl);
        used += len;
        current = current->next;
    }

    // Second pass: generate constructor
    comp_type *comp_current = comp_type_list;

        // Start building constructor
        char constructor_start[256];
        int len = snprintf(constructor_start, sizeof(constructor_start),
                 "%s ctor_%s = {", cname, cname);
        
        // Check buffer space and append start
        if (used + len + 1 > bufsize) {
            bufsize *= 2;
            char *new_result = realloc(result, bufsize);
            if (!new_result) {
                free(result);
                return NULL;
            }
            result = new_result;
        }
        strcpy(result + used, constructor_start);
        used += len;

        // Add all functions for this component type
        current = func_list_head;
        int first = 1;
        while (current != NULL && current->data) {
                char func_entry[256];
                len = snprintf(func_entry, sizeof(func_entry),
                         "%s.%s = %s",
                         first ? "" : ", ",
                         current->data->fname,
                         current->data->fname);
                
                // Check buffer space and append function entry
                if (used + len + 1 > bufsize) {
                    bufsize *= 2;
                    char *new_result = realloc(result, bufsize);
                    if (!new_result) {
                        free(result);
                        return NULL;
                    }
                    result = new_result;
                }
                strcpy(result + used, func_entry);
                used += len;
                first = 0;
            current = current->next;
        }

        // Close constructor
        char constructor_end[] = "};\n\n";
        len = strlen(constructor_end);
        if (used + len + 1 > bufsize) {
            bufsize *= 2;
            char *new_result = realloc(result, bufsize);
            if (!new_result) {
                free(result);
                return NULL;
            }
            result = new_result;
        }
        strcpy(result + used, constructor_end);
        used += len;

        comp_current = comp_current->next;

    return result;
}

  
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
%token  <str> COMP_ID

%token <str> COMP_TYPE
%token <str> COMMENT
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
%type <str> many_funcs
%type <str> comp_start
%type <str> comp_decl
%type <str> comp_var_decl
%type <str> comp_id_recursion
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
| body single_statement			{ $$ = template("%s\n%s", $1, $2); }
| single_declaration 			{ $$ = $1; }
| single_statement			{ $$ = $1; }
;


/* --------------------------------------------------- Declarations ------------------------------------------------------------*/
// Declarations could be single or many.
declarations:
 declarations single_declaration			{ $$ = template("%s\n%s", $1, $2); } 	
| single_declaration 					{ $$ = $1; }
;

single_declaration:
var_decl		    { $$ = $1; }
| array_decl		    { $$ = $1; }
| const_decl		    { $$ = $1; }
| func_decl		    { $$ = $1; }
| comp_decl		    { $$ = $1; }
;

data_type:
KW_INTEGER	            {$$ = template("int"); }
  | KW_BOOL	            {$$ = template("int");}
  | KW_SCALAR               {$$ = template("double");}
  | KW_STR                  {$$ = template("StringType");}
  | ID                      {if (is_comp_type($1)) { $$ = template("%s", $1); } else { yyerror("Unknown type"); YYERROR; }}
;

comp_start:
KW_COMP ID 			{inside_comp = 1; $$ = $2;}
;

comp_decl:
comp_start':' comp_var_decl KW_ENDCOMP ';'			
{ 
inside_comp = 0;
add_comp_type($1);
$$ = template("typedef struct %s {\n%s\n}%s;", $1, $3, $1 );
 }
| comp_start ':' comp_var_decl many_funcs KW_ENDCOMP ';'		
{
    inside_comp = 0;
    add_comp_type($1);
    char *signatures = get_func_signatures($1);
    char *funcs_with_body = get_func_with_body($1);
    $$ = template("typedef struct %s {\n%s\n%s\n}%s;\n\n%s", $1, $3, signatures ? signatures : "", $1, funcs_with_body ? funcs_with_body : ""); 
    if (signatures) free(signatures);
    if (funcs_with_body) free(funcs_with_body);
    free_func_list();
 }
;

many_funcs:
many_funcs func_decl			{ $$ = template("%s\n%s", $1, $2); }
| func_decl				{ $$ = $1; }
;

comp_var_decl:
 comp_id_recursion ':' data_type ';'			{ $$ = template("%s %s;", $3, $1); }
| comp_id_recursion ':' data_type ';' comp_var_decl	{ $$ = template("%s %s;\n%s", $3, $1, $5); }
;

comp_id_recursion:
COMP_ID 				{ $$ = $1; }
| COMP_ID '[' INTEGER ']'			{ $$ = template("%s[%s]", $1, $3); }
| COMP_ID ',' comp_id_recursion 	{ $$ = template("%s, %s", $1, $3); }
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
{ if (!inside_comp) $$ = template("%s %s(%s){\n%s\n}", $7, $2, $4, $9);
else {
	add_func($2, $4, $7, $9);
}
}
| KW_DEF ID '(' func_args ')' ARROW data_type ':' KW_ENDDEF ';'
{ if (!inside_comp) $$ = template("%s %s(%s){\n\n}", $7, $2, $4);
else {
	add_func($2, $4, $7, NULL);
}
 }
| KW_DEF ID '(' func_args ')' ':' body KW_ENDDEF ';'
{ if (!inside_comp) $$ = template("void %s(%s){\n%s\n}", $2, $4, $7);
else {
	add_func($2, $4, NULL, $7);
}
 }
| KW_DEF ID '(' func_args ')' ':' KW_ENDDEF ';'
{ if(!inside_comp) $$ = template("void %s(%s){\n\n}", $2, $4);
else{
	add_func($2, $4, NULL, NULL);
}
 }
;
/* --------------------------------------------------- Statements Rules --------------------------------------------------------*/
single_statement:
assign_statement ';'				{ $$ = template("%s;",$1); }
| func_statement ';'				{ $$ = template("%s;",$1); }
| return_statement ';'				{ $$ = $1; }
| arrays ';'					{ $$ = $1; }
| if_statement ';'				{ $$ = $1; }
| for_statement	';'				{ $$ = $1; }
| while_statement ';'				{ $$ = $1; }
| id_expr ';'					{ $$ = $1; }
| ';'						{ $$ = ";"; }
;

assign_statement:
//ID ASSIGN func_statement 			{ $$ = template("%s = %s;", $1, $3); }
 assign_expr 					{ $$ = $1; }
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
KW_IF '(' expr ')' ':' body KW_ENDIF 				{ $$ = template("if (%s){\n%s\n}", $3, $6); }
| KW_IF '(' expr ')' ':' body KW_ELSE ':' body KW_ENDIF   	{ $$ = template("if (%s){\n%s\n} else{ \n%s\n}", $3, $6, $9); }
;


for_statement:
KW_FOR ID KW_IN '[' expr ':' expr ':' expr ']' ':' loop_body KW_ENDFOR 
{ $$ = template("for (int %s = %s; %s<=%s; %s+=%s){\n%s\n}", $2, $5, $2, $7, $2, $9, $12); }
| KW_FOR ID KW_IN '[' expr ':' expr ']' ':' loop_body KW_ENDFOR 	
{ $$ = template("for (int %s = %s; %s<=%s; %s++){\n%s\n}", $2, $5, $2, $7, $2, $10); }
;

while_statement:
KW_WHILE '(' expr ')' ':' loop_body KW_ENDWHILE		
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
func_statement		{ $$ = $1; }
| str_expr		{ $$ = $1; }	
| id_expr		{ $$ = $1; }
| assign_expr 		{ $$ = $1; }
| boolean_expr 		{ $$ = $1; }
| relation_expr		{ $$ = $1; }
| arithmetic_expr	{ $$ = $1; }
| '[' expr ')'		{ $$ = template("[ %s ]", $2); }
| '(' expr ')'		{ $$ = template("( %s )", $2); }
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
ID DOT id_expr						{ $$ = template("%s.%s", $1, $3); }
| ID DOT func_statement 	   			{ $$ = template("%s.%s", $1, $3); }
| COMP_ID						{ $$ = template("self->%s", $1); }
| COMP_ID DOT ID '(' func_statement_args ')'    	
{ if (strcmp($5, "") == 0) $$ = template("self->%s.%s(&self->%s %s);", $1, $3, $1, $5); else $$ = template("self->%s.%s(&self->%s, %s);", $1, $3, $1, $5);}
| COMP_ID DOT id_expr					{ $$ = template("self->%s.%s", $1, $3); }
| ID '[' expr ']' 					{ $$ = template("%s[%s]", $1, $3); }
| ID '[' expr ']' DOT func_statement			{ $$ = template("%s[%s].%s;", $1, $3, $6); }
| ID '[' expr ']' DOT id_expr 				{ $$ = template("%s[%s].%s", $1, $3, $6); }
| COMP_ID '[' expr ']'					{ $$ = template("self->%s[%s]", $1, $3); }
| COMP_ID '[' expr ']' DOT ID '(' func_statement_args ')'		
{if (strcmp($8, "") == 0) $$ = template("self->%s[%s].%s(&self->%s[%s] %s);", $1, $3, $6, $1, $3, $8 ); else $$ = template("self->%s[%s].%s(&self->%s[i], %s);"), $1, $3, $6, $1, $3, $8; }
| COMP_ID '[' expr ']' DOT id_expr 			{ $$ = template("self->%s[%s].%s", $1, $3, $6); }
| ID 							{ $$ = $1; }
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
id_expr ASSIGN_PLUS expr			{ $$ = template("%s =+ %s", $1, $3); }
| id_expr ASSIGN_MINUS expr			{ $$ = template("%s =- %s", $1, $3); }
| id_expr ASSIGN_PRODUCT expr			{ $$ = template("%s =* %s", $1, $3); }
| id_expr ASSIGN_DIV expr			{ $$ = template("%s =/ %s", $1, $3); }
| id_expr ASSIGN_MOD expr			{ $$ = template("%s =% %s", $1, $3); }
| id_expr ASSIGN expr				{ $$ = template("%s = %s", $1, $3); }
;


arithmetic_expr:
INTEGER 		{ $$ = $1; }
| FLOAT   		{ $$ = $1; }
| expr '+' expr 	{ $$ = template("%s + %s", $1, $3); }
| expr '-' expr 	{ $$ = template("%s - %s", $1, $3); }
| expr '*' expr 	{ $$ = template("%s * %s", $1, $3); }
| expr '/' expr 	{ $$ = template("%s / %s", $1, $3); }
| expr '%' expr 	{ $$ = template("%s %% %s", $1, $3); }
| '+' expr	        { $$ = template("+%s", $2);}
| '-' expr	        { $$ = template("-%s", $2);}
| expr OP_POWER expr 	{ $$ = template("pow(%s, %s)", $1, $3);}
;


/*----------------------------------------------------- Epilogue ----------------------------------------------------- */
%%
int main () {
  if ( yyparse() == 0 ){
    printf("\n\n/*+++++++++Accepted!++++++++++*/\n");
    free_func_list();
    free_comp_types();
    }
  else{
    printf("\n\n/*---------Rejected!----------*/\n");
    free_func_list();
    free_comp_types();
}
}
