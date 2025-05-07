/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_MYANALYZER_TAB_H_INCLUDED
# define YY_YY_MYANALYZER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID = 258,                      /* ID  */
    INTEGER = 259,                 /* INTEGER  */
    FLOAT = 260,                   /* FLOAT  */
    CONST_STRING = 261,            /* CONST_STRING  */
    ASSIGN = 262,                  /* ASSIGN  */
    KW_IF = 263,                   /* KW_IF  */
    KW_ENDIF = 264,                /* KW_ENDIF  */
    KW_THEN = 265,                 /* KW_THEN  */
    KW_ELSE = 266,                 /* KW_ELSE  */
    KW_FOR = 267,                  /* KW_FOR  */
    KW_ENDFOR = 268,               /* KW_ENDFOR  */
    KW_TRUE = 269,                 /* KW_TRUE  */
    KW_FALSE = 270,                /* KW_FALSE  */
    KW_INTEGER = 271,              /* KW_INTEGER  */
    KW_SCALAR = 272,               /* KW_SCALAR  */
    KW_STR = 273,                  /* KW_STR  */
    KW_BOOL = 274,                 /* KW_BOOL  */
    KW_CONST = 275,                /* KW_CONST  */
    KW_IN = 276,                   /* KW_IN  */
    KW_WHILE = 277,                /* KW_WHILE  */
    KW_ENDWHILE = 278,             /* KW_ENDWHILE  */
    KW_BREAK = 279,                /* KW_BREAK  */
    KW_CONTINUE = 280,             /* KW_CONTINUE  */
    KW_NOT = 281,                  /* KW_NOT  */
    KW_AND = 282,                  /* KW_AND  */
    KW_OR = 283,                   /* KW_OR  */
    KW_DEF = 284,                  /* KW_DEF  */
    KW_ENDDEF = 285,               /* KW_ENDDEF  */
    KW_MAIN = 286,                 /* KW_MAIN  */
    KW_RETURN = 287,               /* KW_RETURN  */
    KW_COMP = 288,                 /* KW_COMP  */
    KW_ENDCOMP = 289,              /* KW_ENDCOMP  */
    KW_OF = 290,                   /* KW_OF  */
    OP_POWER = 291,                /* OP_POWER  */
    OP_ASSIGN = 292,               /* OP_ASSIGN  */
    OP_LESSEQUAL = 293,            /* OP_LESSEQUAL  */
    OP_GREATEREQUAL = 294,         /* OP_GREATEREQUAL  */
    OP_EQUAL = 295,                /* OP_EQUAL  */
    OP_INEQUAL = 296               /* OP_INEQUAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 10 "myanalyzer.y"

  char* str;
  int num;

#line 110 "myanalyzer.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_MYANALYZER_TAB_H_INCLUDED  */
