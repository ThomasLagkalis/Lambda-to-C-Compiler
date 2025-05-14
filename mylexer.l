%top{
  	#include <stdio.h>
  	#include <string.h>  
  	#include "myanalyzer.tab.h"	
  	#include "cgen.h"
	
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
not		   	{ yylval.str = strdup(yytext); return KW_NOT;}
and 	   	{ yylval.str = strdup(yytext); return KW_AND;}
or		   	{ yylval.str = strdup(yytext); return KW_OR;}
def 	  	{ yylval.str = strdup(yytext); return KW_DEF;}
enddef   	{ yylval.str = strdup(yytext); return KW_ENDDEF;}
main	   	{ yylval.str = strdup(yytext); return KW_MAIN;}
return    	{ yylval.str = strdup(yytext); return KW_RETURN;}
comp	   	{ yylval.str = strdup(yytext); return KW_COMP;}
endcomp   	{ yylval.str = strdup(yytext); return KW_ENDCOMP;}
of		   	{ yylval.str = strdup(yytext); return KW_OF;}

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
					yylval.str = strdup(yytext); return ID;
    			}
}

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
"//"[^\n]*  		/* skip line comments */
\n 					{ line_num++;}
.           		{ printf("Line %d Lexical Error: Unrecognized literal %s\n", line_num, yytext); return 0; }

%%

