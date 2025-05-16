%top{
  	#include <stdio.h>
  	#include <string.h>  
  	#include <stdlib.h>	
  	#include "myanalyzer.tab.h"	
  	#include "cgen.h"
	
	extern int inside_comp;
	int line_num = 1;


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

IDENTIFIER [A-Za-z][A-Za-z0-9_]*
COMPLEX_IDENTIFIER "#"[A-Za-z][A-Za-z0-9_]*
DIGITS [0-9]
INTEGERS [0-9][0-9]*
FLOATS {INTEGERS}("."{DIGITS}+)?([eE][+-]?{INTEGERS})?
ESC_CHAR (\\[ntr\\"])
CONST_STRING (\"([ .,a-zA-Z0-9\-+*/:_$%!#@&~^\(\)]|{ESC_CHAR})*\")


/* rules */

%%
{CONST_STRING} 		{  yylval.str = strdup(yytext); return CONST_STRING;}

True    	{ yylval.str = strdup(yytext); return KW_TRUE;}
False   	{ yylval.str = strdup(yytext); return KW_FALSE;}
integer 	{ yylval.str = strdup(yytext); return KW_INTEGER;}
scalar  	{ yylval.str = strdup(yytext); return KW_SCALAR;}
str     	{ yylval.str = strdup(yytext); return KW_STR;}
bool    	{ yylval.str = strdup(yytext); return KW_BOOL;}
const   	{ yylval.str = strdup(yytext); return KW_CONST;}
if      	{ yylval.str = strdup(yytext); return KW_IF;}
else    	{ yylval.str = strdup(yytext); return KW_ELSE;}
endif   	{ yylval.str = strdup(yytext); return KW_ENDIF;}
for     	{ yylval.str = strdup(yytext); return KW_FOR;}
in      	{ yylval.str = strdup(yytext); return KW_IN;}
endfor  	{ yylval.str = strdup(yytext); return KW_ENDFOR;}
while   	{ yylval.str = strdup(yytext); return KW_WHILE;}
endwhile	{ yylval.str = strdup(yytext); return KW_ENDWHILE;}
break   	{ yylval.str = strdup(yytext); return KW_BREAK;}
continue   	{ yylval.str = strdup(yytext); return KW_CONTINUE;}
not		{ yylval.str = strdup(yytext); return KW_NOT;}
and 	   	{ yylval.str = strdup(yytext); return KW_AND;}
or		{ yylval.str = strdup(yytext); return KW_OR;}
def 	  	{ yylval.str = strdup(yytext); return KW_DEF;}
enddef   	{ yylval.str = strdup(yytext); return KW_ENDDEF;}
main	   	{ yylval.str = strdup(yytext); return KW_MAIN;}
return    	{ yylval.str = strdup(yytext); return KW_RETURN;}
comp	   	{ yylval.str = strdup(yytext); return KW_COMP;}
endcomp   	{ yylval.str = strdup(yytext); return KW_ENDCOMP;}
of		   	{ yylval.str = strdup(yytext); return KW_OF;}

@defmacro[ \t]+{IDENTIFIER}[ \t]+.+ {
    char macro_name[64], replacement[256];
    sscanf(yytext, "@defmacro %63s %255[^\n]", macro_name, replacement);
    add_macro(macro_name, replacement);
}

{COMPLEX_IDENTIFIER} {
			yylval.str = strdup(yytext + 1); // Drop the "#"
        		return COMP_ID;
}

{IDENTIFIER} 		{ 
			const char* repl = get_macro_replacement(yytext);
    			if (repl) {
    			// unput(ch) puts the character ch back into the input stream.
        		for(int i=strlen(repl); i>0; i--) unput(repl[i-1]);
    			} else {
			yylval.str = strdup(yytext); return ID;
    			}
			}


"->"		{ yylval.str = strdup(yytext); return ARROW; }
"="		{ yylval.str = strdup(yytext); return ASSIGN;}
"**"        	{ yylval.str = strdup(yytext); return OP_POWER;}
">="		{ yylval.str = strdup(yytext); return OP_GREATEREQUAL;}
"<="		{ yylval.str = strdup(yytext); return OP_LESSEQUAL;}
"=="		{ yylval.str = strdup(yytext); return OP_EQUAL;}
"!="		{ yylval.str = strdup(yytext); return OP_INEQUAL;}
"+="		{ yylval.str = strdup(yytext); return ASSIGN_PLUS;}
"-="		{ yylval.str = strdup(yytext); return ASSIGN_MINUS;}
"*="		{ yylval.str = strdup(yytext); return ASSIGN_PRODUCT;}
"/="		{ yylval.str = strdup(yytext); return ASSIGN_DIV;}
"%="		{ yylval.str = strdup(yytext); return ASSIGN_MOD;}
":="		{ yylval.str = strdup(yytext); return ASSIGN_DOTS;}
"<"			return '<';
">"			return '>';
"+"         return '+';
"-"         return '-';
"*"         return '*';
"/"         return '/';
"%"			return '%';
";"	    	return ';';
":"	    	return ':';
"."	    	return DOT;
","	    	return ',';
"("	    	return '(';
")"	    	return ')';
"["	    	return '[';
"]"	    	return ']';


{INTEGERS} 				{ yylval.str = strdup(yytext); return INTEGER;}
{FLOATS}				{ yylval.str = strdup(yytext); return FLOAT;}

[ \r\t]+			/* skip whitespace */
"--"[^\n]*  			/* skip line comments */
\n 					{ line_num++;}
.           		{ printf("Line %d Lexical Error: Unrecognized literal %s\n", line_num, yytext); return 0; }

%%

