%top{
  #include <stdio.h>
  #include <string.h>  
  
  int lineNum = 1;
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
{IDENTIFIER} 		{ printf("token IDENTIFIER %s\n", yytext);}
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
