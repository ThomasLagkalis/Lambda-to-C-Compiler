%top{
  #include <stdio.h>
  #include <string.h>  
  
  int lineNum = 1;
}

/* definitions */

LOGICAL_OP ("and"|"or"|"not")
IDENTIFIER [A-Za-z][A-Za-z0-9_]*
INTEGER [0-9][0-9]*
ARITHMETIC_OP ("+"|"-"|"*"|"/"|"%"|"**")
RELATIONAL_OP ("=="|"!="|"<"|"<="|">"|">=")
ASSIGNMENT_OP ("="|"+="|"-="|"*="|"/="|"%="|":=")
DELIMETER (";"|"("|")"|","|"["|"]"|":"|".")

/* rules */

%%
{LOGICAL_OP} 		{ printf("token LOGICAL_OP %s\n", yytext);}
{IDENTIFIER} 		{ printf("token IDENTIFIER %s\n", yytext);}
{INTEGER} 			{ printf("token INTEGER %s\n", yytext);}
{ARITHMETIC_OP} 	{ printf("token ARITHMETIC_OP %s\n", yytext);}
{RELATIONAL_OP} 	{ printf("token RELATIONAL_OP %s\n", yytext);}
{ASSIGNMENT_OP} 	{ printf("token ASSIGNMENT_OP %s\n", yytext);}
{DELIMETER} 		{ printf("token DELIMETER %s\n", yytext);}

[ \r\t]+			/* skip whitespace */
\n 					{ lineNum++;}
.           		{ printf("Line %d Lexical Error: Unrecognized literal %s\n", lineNum, yytext); return 0; }

%%
/* user code */
int main() {
yylex();
}
