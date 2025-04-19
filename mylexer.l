%top{
  	#include <stdio.h>
  	#include <string.h>  
	
	int lineNum = 1;

	#define MAX_MACROS 1024

	typedef struct {
    	char name[64];
    	char replacement[256];
	} Macro;

	Macro macros[MAX_MACROS];
	int macro_count = 0;

	void add_macro(const char* name, const char* replacement) {
    	for (int i = macro_count - 1; i >= 0; --i) {
        	if (strcmp(macros[i].name, name) == 0) {
            	strcpy(macros[i].replacement, replacement);
            	return;
        	}
    	}
    	// New macro
    	if (macro_count < MAX_MACROS) {
        	strcpy(macros[macro_count].name, name);
        	strcpy(macros[macro_count].replacement, replacement);
        	macro_count++;
    	}
	}
	
	const char* get_macro_replacement(const char* name) {
    for (int i = macro_count - 1; i >= 0; --i) {
        if (strcmp(macros[i].name, name) == 0) {
            return macros[i].replacement;
        }
    }
    return NULL;
}
}

/* definitions */

LOGICAL_OP ("and"|"or"|"not")
BOOL_CONST ("True"|"False")
KEYWORD ("integer"|"scalar"|"str"|"bool"|"True"|"False"|"const"|"if"|"else"|"endif"|"for"|"in"|"endfor"|"while"|"endwhile"|"break"|"continue"|"not"|"and"|"or"|"def"|"enddef"|"main"|"return"|"comp"|"endcomp"|"of")
IDENTIFIER [A-Za-z][A-Za-z0-9_]*
DIGIT [0-9]
INTEGER [0-9][0-9]*
FLOAT {INTEGER}("."{DIGIT}+)?([eE][+-]?{INTEGER})?
ARITHMETIC_OP ("+"|"-"|"*"|"/"|"%"|"**")
SIGNED_INT [-+]{INTEGER} 
SIGNED_FLOAT [-+]{FLOAT}
RELATIONAL_OP ("=="|"!="|"<"|"<="|">"|">=")
ASSIGNMENT_OP ("="|"+="|"-="|"*="|"/="|"%="|":=")
DELIMETER (";"|"("|")"|","|"["|"]"|":"|".")
ESC_CHAR (\\[ntr\\"])
CONST_STRING (\"([ .,a-zA-Z0-9\-+*/:_$%!#@&~^\(\)]|{ESC_CHAR})*\")


/* rules */

%%
{LOGICAL_OP} 		{ printf("token LOGICAL_OP %s\n", yytext);}
{BOOL_CONST}		{ printf("token BOOL_CONST %s\n", yytext);}
{KEYWORD}		    { printf("token KEYWORD %s\n", yytext);}
@defmacro[ \t]+([a-zA-Z_][a-zA-Z0-9_]*)[ \t]+([^ \t\n][^\n]*)[ \t]*\n {
    char macro_name[64], replacement[256];
    sscanf(yytext, "@defmacro %63s %255[^\n]", macro_name, replacement);
    add_macro(macro_name, replacement);
}
{IDENTIFIER} 		{ const char* repl = get_macro_replacement(yytext);
    				if (repl) {
        			// Replace macro inline by pushing replacement to the input stream
        			YY_BUFFER_STATE old_buf = YY_CURRENT_BUFFER;
        			yy_scan_string(repl);
        			yylex();  // Process the replacement immediately
        			yy_delete_buffer(YY_CURRENT_BUFFER);
        			yy_switch_to_buffer(old_buf);
    			} else {
					printf("token IDENTIFIER %s\n", yytext);
    			}
}
{DIGIT}				{ printf("token DIGIT %s\n", yytext);}
{INTEGER} 			{ printf("token INTEGER %s\n", yytext);}
{SIGNED_INT}		{ printf("token SIGNED_INT %s\n", yytext);}
{FLOAT}				{ printf("token FLOAT %s\n", yytext);}
{SIGNED_FLOAT} 		{ printf("token SIGNED_FLOAT %s\n", yytext);}
{ARITHMETIC_OP} 	{ printf("token ARITHMETIC_OP %s\n", yytext);}
{RELATIONAL_OP} 	{ printf("token RELATIONAL_OP %s\n", yytext);}
{ASSIGNMENT_OP} 	{ printf("token ASSIGNMENT_OP %s\n", yytext);}
{DELIMETER} 		{ printf("token DELIMETER %s\n", yytext);}
{CONST_STRING} 		{ printf("token CONST_STRING %s\n", yytext);}

[ \r\t]+			/* skip whitespace */
"//"[^\n]*  		/* skip line comments */
\n 					{ lineNum++;}
.           		{ printf("Line %d Lexical Error: Unrecognized literal %s\n", lineNum, yytext); return 0; }

%%
/* user code */
int main() {
yylex();
}
