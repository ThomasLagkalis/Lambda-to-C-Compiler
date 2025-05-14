/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "myanalyzer.y"

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

#line 103 "myanalyzer.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "myanalyzer.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_INTEGER = 4,                    /* INTEGER  */
  YYSYMBOL_FLOAT = 5,                      /* FLOAT  */
  YYSYMBOL_CONST_STRING = 6,               /* CONST_STRING  */
  YYSYMBOL_KW_IF = 7,                      /* KW_IF  */
  YYSYMBOL_KW_ENDIF = 8,                   /* KW_ENDIF  */
  YYSYMBOL_KW_THEN = 9,                    /* KW_THEN  */
  YYSYMBOL_KW_ELSE = 10,                   /* KW_ELSE  */
  YYSYMBOL_KW_FOR = 11,                    /* KW_FOR  */
  YYSYMBOL_KW_ENDFOR = 12,                 /* KW_ENDFOR  */
  YYSYMBOL_KW_TRUE = 13,                   /* KW_TRUE  */
  YYSYMBOL_KW_FALSE = 14,                  /* KW_FALSE  */
  YYSYMBOL_KW_INTEGER = 15,                /* KW_INTEGER  */
  YYSYMBOL_KW_SCALAR = 16,                 /* KW_SCALAR  */
  YYSYMBOL_KW_STR = 17,                    /* KW_STR  */
  YYSYMBOL_KW_BOOL = 18,                   /* KW_BOOL  */
  YYSYMBOL_KW_CONST = 19,                  /* KW_CONST  */
  YYSYMBOL_KW_IN = 20,                     /* KW_IN  */
  YYSYMBOL_KW_WHILE = 21,                  /* KW_WHILE  */
  YYSYMBOL_KW_ENDWHILE = 22,               /* KW_ENDWHILE  */
  YYSYMBOL_KW_BREAK = 23,                  /* KW_BREAK  */
  YYSYMBOL_KW_CONTINUE = 24,               /* KW_CONTINUE  */
  YYSYMBOL_KW_NOT = 25,                    /* KW_NOT  */
  YYSYMBOL_KW_AND = 26,                    /* KW_AND  */
  YYSYMBOL_KW_OR = 27,                     /* KW_OR  */
  YYSYMBOL_KW_DEF = 28,                    /* KW_DEF  */
  YYSYMBOL_KW_ENDDEF = 29,                 /* KW_ENDDEF  */
  YYSYMBOL_KW_MAIN = 30,                   /* KW_MAIN  */
  YYSYMBOL_KW_RETURN = 31,                 /* KW_RETURN  */
  YYSYMBOL_KW_COMP = 32,                   /* KW_COMP  */
  YYSYMBOL_KW_ENDCOMP = 33,                /* KW_ENDCOMP  */
  YYSYMBOL_KW_OF = 34,                     /* KW_OF  */
  YYSYMBOL_DOT = 35,                       /* DOT  */
  YYSYMBOL_OP_POWER = 36,                  /* OP_POWER  */
  YYSYMBOL_OP_LESSEQUAL = 37,              /* OP_LESSEQUAL  */
  YYSYMBOL_OP_GREATEREQUAL = 38,           /* OP_GREATEREQUAL  */
  YYSYMBOL_OP_EQUAL = 39,                  /* OP_EQUAL  */
  YYSYMBOL_OP_INEQUAL = 40,                /* OP_INEQUAL  */
  YYSYMBOL_ASSIGN = 41,                    /* ASSIGN  */
  YYSYMBOL_ASSIGN_PLUS = 42,               /* ASSIGN_PLUS  */
  YYSYMBOL_ASSIGN_MINUS = 43,              /* ASSIGN_MINUS  */
  YYSYMBOL_ASSIGN_PRODUCT = 44,            /* ASSIGN_PRODUCT  */
  YYSYMBOL_ASSIGN_DIV = 45,                /* ASSIGN_DIV  */
  YYSYMBOL_ASSIGN_MOD = 46,                /* ASSIGN_MOD  */
  YYSYMBOL_ASSIGN_DOTS = 47,               /* ASSIGN_DOTS  */
  YYSYMBOL_48_ = 48,                       /* '>'  */
  YYSYMBOL_49_ = 49,                       /* '<'  */
  YYSYMBOL_50_ = 50,                       /* '-'  */
  YYSYMBOL_51_ = 51,                       /* '+'  */
  YYSYMBOL_52_ = 52,                       /* '*'  */
  YYSYMBOL_53_ = 53,                       /* '/'  */
  YYSYMBOL_54_ = 54,                       /* '%'  */
  YYSYMBOL_55_ = 55,                       /* '('  */
  YYSYMBOL_56_ = 56,                       /* ')'  */
  YYSYMBOL_57_ = 57,                       /* '['  */
  YYSYMBOL_58_ = 58,                       /* ']'  */
  YYSYMBOL_59_ = 59,                       /* '.'  */
  YYSYMBOL_60_ = 60,                       /* ';'  */
  YYSYMBOL_61_ = 61,                       /* ':'  */
  YYSYMBOL_62_ = 62,                       /* ','  */
  YYSYMBOL_YYACCEPT = 63,                  /* $accept  */
  YYSYMBOL_start = 64,                     /* start  */
  YYSYMBOL_declarations = 65,              /* declarations  */
  YYSYMBOL_data_type = 66,                 /* data_type  */
  YYSYMBOL_var_decl = 67,                  /* var_decl  */
  YYSYMBOL_id_recursion = 68,              /* id_recursion  */
  YYSYMBOL_array_decl = 69,                /* array_decl  */
  YYSYMBOL_expr = 70,                      /* expr  */
  YYSYMBOL_boolean_expr = 71,              /* boolean_expr  */
  YYSYMBOL_id_expr = 72,                   /* id_expr  */
  YYSYMBOL_relation_expr = 73,             /* relation_expr  */
  YYSYMBOL_assign_expr = 74,               /* assign_expr  */
  YYSYMBOL_arrays = 75,                    /* arrays  */
  YYSYMBOL_arithmetic_expr = 76            /* arithmetic_expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   326

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  56
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  110

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   302


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    54,     2,     2,
      55,    56,    52,    51,    62,    50,    59,    53,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    61,    60,
      49,     2,    48,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    57,     2,    58,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   127,   127,   128,   138,   139,   142,   143,   144,   145,
     149,   153,   154,   158,   159,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   175,   176,   177,   178,   179,   183,
     184,   185,   189,   190,   191,   192,   193,   194,   198,   199,
     200,   201,   202,   203,   204,   209,   213,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "INTEGER",
  "FLOAT", "CONST_STRING", "KW_IF", "KW_ENDIF", "KW_THEN", "KW_ELSE",
  "KW_FOR", "KW_ENDFOR", "KW_TRUE", "KW_FALSE", "KW_INTEGER", "KW_SCALAR",
  "KW_STR", "KW_BOOL", "KW_CONST", "KW_IN", "KW_WHILE", "KW_ENDWHILE",
  "KW_BREAK", "KW_CONTINUE", "KW_NOT", "KW_AND", "KW_OR", "KW_DEF",
  "KW_ENDDEF", "KW_MAIN", "KW_RETURN", "KW_COMP", "KW_ENDCOMP", "KW_OF",
  "DOT", "OP_POWER", "OP_LESSEQUAL", "OP_GREATEREQUAL", "OP_EQUAL",
  "OP_INEQUAL", "ASSIGN", "ASSIGN_PLUS", "ASSIGN_MINUS", "ASSIGN_PRODUCT",
  "ASSIGN_DIV", "ASSIGN_MOD", "ASSIGN_DOTS", "'>'", "'<'", "'-'", "'+'",
  "'*'", "'/'", "'%'", "'('", "')'", "'['", "']'", "'.'", "';'", "':'",
  "','", "$accept", "start", "declarations", "data_type", "var_decl",
  "id_recursion", "array_decl", "expr", "boolean_expr", "id_expr",
  "relation_expr", "assign_expr", "arrays", "arithmetic_expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-61)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-12)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -61,     0,   -61,    28,   -61,   -61,   -61,   -61,   106,   -61,
     106,   106,   106,     3,   -61,   -61,   -60,   -61,   148,   -61,
     -61,   -61,   -61,   -61,   -61,   106,   106,   106,   106,   106,
     106,   -55,   109,     6,   201,   -26,   -26,   177,   -50,   208,
     112,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   -61,   239,   239,   239,   239,
     239,   239,   106,   -46,    -6,   -47,   -61,   -61,   112,   -61,
     -61,   -61,   -61,   -61,   -61,   201,   246,   -26,    97,   170,
     265,   272,   119,   119,   -26,   -26,   -26,   -26,   -26,   141,
     -61,   -43,   -61,    16,   112,   -39,   -61,   121,   -35,     4,
     -34,    23,   112,    -5,   -61,    32,   -21,   -22,   112,   -61
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,    29,    47,    48,    27,    28,     0,    23,
       0,     0,     0,     0,    16,     4,     0,     5,     0,    18,
      15,    19,    17,    44,    20,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    24,    55,    54,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     3,    43,    38,    39,    40,
      41,    42,     0,    47,     0,    11,    12,    22,     0,    21,
       6,     8,     9,     7,    10,    26,    25,    56,    36,    37,
      32,    33,    35,    34,    50,    49,    51,    52,    53,     0,
      31,    30,    13,     0,     0,     0,    14,     0,     0,     0,
       0,     0,     0,     0,    45,     0,     0,     0,     0,    46
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -61,   -61,   -61,    24,   -61,     7,   -61,    54,   -61,   -61,
     -61,   -61,   -61,   -61
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,    14,    74,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
       2,    40,    62,     3,     4,     5,     3,     4,     5,    65,
      43,    68,    90,     6,     7,    33,     6,     7,    94,    95,
      41,    42,    97,   100,   101,     8,   103,   102,     8,   105,
      43,    44,    45,    46,    47,     9,   106,   107,     9,   108,
      66,     0,    48,    49,    50,    51,    52,    53,    54,     0,
      10,    11,    91,    10,    11,    12,     0,    13,    12,     0,
      13,    38,    34,     0,    35,    36,    37,    39,     0,    25,
      26,    27,    28,    29,    30,    31,     0,     0,     0,    56,
      57,    58,    59,    60,    61,    32,    64,     0,     0,   -11,
      33,     0,    92,     0,     0,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,     3,
       4,     5,     3,    63,     5,     0,    89,     0,    96,     6,
       7,    99,     6,     7,     0,    98,   104,    70,    71,    72,
      73,     8,   109,    43,     8,    45,    70,    71,    72,    73,
       0,     9,     0,     0,     9,    48,    49,    50,    51,    52,
      53,    54,    93,     0,     0,    43,    10,    11,     0,    10,
      11,    12,     0,    13,    12,     0,    13,    41,    42,    50,
      51,    52,    53,    54,    41,    42,     0,    43,    44,    45,
      46,    47,     0,     0,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    48,    49,    50,    51,
      52,    53,    54,    41,    42,     0,    43,     0,    55,     0,
       0,     0,     0,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    48,    49,    50,    51,    52,
      53,    54,     0,    67,    41,    42,     0,    43,    44,    45,
      46,    47,     0,     0,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    48,    49,    50,    51,
      52,    53,    54,     0,    69,    41,    42,     0,     0,     0,
       0,     0,    41,     0,     0,    43,    44,    45,    46,    47,
       0,     0,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    48,    49,    50,    51,    52,    53,
      54,    43,    44,    45,     0,    47,     0,     0,    43,    44,
      45,     0,     0,    48,    49,    50,    51,    52,    53,    54,
      48,    49,    50,    51,    52,    53,    54
};

static const yytype_int8 yycheck[] =
{
       0,    61,    57,     3,     4,     5,     3,     4,     5,     3,
      36,    61,    58,    13,    14,    62,    13,    14,    61,     3,
      26,    27,    61,    58,    20,    25,     3,    61,    25,    34,
      36,    37,    38,    39,    40,    35,     4,    58,    35,    61,
      33,    -1,    48,    49,    50,    51,    52,    53,    54,    -1,
      50,    51,    58,    50,    51,    55,    -1,    57,    55,    -1,
      57,    58,     8,    -1,    10,    11,    12,    13,    -1,    41,
      42,    43,    44,    45,    46,    47,    -1,    -1,    -1,    25,
      26,    27,    28,    29,    30,    57,    32,    -1,    -1,    61,
      62,    -1,    68,    -1,    -1,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,     3,
       4,     5,     3,     4,     5,    -1,    62,    -1,    94,    13,
      14,    97,    13,    14,    -1,     4,   102,    15,    16,    17,
      18,    25,   108,    36,    25,    38,    15,    16,    17,    18,
      -1,    35,    -1,    -1,    35,    48,    49,    50,    51,    52,
      53,    54,    11,    -1,    -1,    36,    50,    51,    -1,    50,
      51,    55,    -1,    57,    55,    -1,    57,    26,    27,    50,
      51,    52,    53,    54,    26,    27,    -1,    36,    37,    38,
      39,    40,    -1,    -1,    36,    37,    38,    39,    40,    48,
      49,    50,    51,    52,    53,    54,    48,    49,    50,    51,
      52,    53,    54,    26,    27,    -1,    36,    -1,    60,    -1,
      -1,    -1,    -1,    36,    37,    38,    39,    40,    48,    49,
      50,    51,    52,    53,    54,    48,    49,    50,    51,    52,
      53,    54,    -1,    56,    26,    27,    -1,    36,    37,    38,
      39,    40,    -1,    -1,    36,    37,    38,    39,    40,    48,
      49,    50,    51,    52,    53,    54,    48,    49,    50,    51,
      52,    53,    54,    -1,    56,    26,    27,    -1,    -1,    -1,
      -1,    -1,    26,    -1,    -1,    36,    37,    38,    39,    40,
      -1,    -1,    36,    37,    38,    39,    40,    48,    49,    50,
      51,    52,    53,    54,    48,    49,    50,    51,    52,    53,
      54,    36,    37,    38,    -1,    40,    -1,    -1,    36,    37,
      38,    -1,    -1,    48,    49,    50,    51,    52,    53,    54,
      48,    49,    50,    51,    52,    53,    54
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    64,     0,     3,     4,     5,    13,    14,    25,    35,
      50,    51,    55,    57,    65,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    41,    42,    43,    44,    45,
      46,    47,    57,    62,    70,    70,    70,    70,    58,    70,
      61,    26,    27,    36,    37,    38,    39,    40,    48,    49,
      50,    51,    52,    53,    54,    60,    70,    70,    70,    70,
      70,    70,    57,     4,    70,     3,    68,    56,    61,    56,
      15,    16,    17,    18,    66,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      58,    58,    66,    11,    61,     3,    66,    61,     4,    66,
      58,    20,    61,     3,    66,    34,     4,    58,    61,    66
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    63,    64,    64,    65,    65,    66,    66,    66,    66,
      67,    68,    68,    69,    69,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    71,    71,    71,    71,    71,    72,
      72,    72,    73,    73,    73,    73,    73,    73,    74,    74,
      74,    74,    74,    74,    74,    75,    75,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     1,     1,     1,     1,     1,     1,
       3,     1,     3,     4,     6,     1,     1,     1,     1,     1,
       1,     3,     3,     1,     2,     3,     3,     1,     1,     1,
       4,     4,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,    11,    15,     1,     1,     3,
       3,     3,     3,     3,     2,     2,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3: /* start: start expr ';'  */
#line 129 "myanalyzer.y"
{ 
  if (yyerror_count == 0) {
    puts(c_prologue);
    printf("Expression evaluates to: %s;\n", (yyvsp[-1].str)); 
  }  
}
#line 1284 "myanalyzer.tab.c"
    break;

  case 4: /* declarations: var_decl  */
#line 138 "myanalyzer.y"
                            { (yyval.str) = (yyvsp[0].str); }
#line 1290 "myanalyzer.tab.c"
    break;

  case 5: /* declarations: array_decl  */
#line 139 "myanalyzer.y"
                            { (yyval.str) = (yyvsp[0].str); }
#line 1296 "myanalyzer.tab.c"
    break;

  case 6: /* data_type: KW_INTEGER  */
#line 142 "myanalyzer.y"
                            {(yyval.str) = template("int");}
#line 1302 "myanalyzer.tab.c"
    break;

  case 7: /* data_type: KW_BOOL  */
#line 143 "myanalyzer.y"
                            {(yyval.str) = template("int");}
#line 1308 "myanalyzer.tab.c"
    break;

  case 8: /* data_type: KW_SCALAR  */
#line 144 "myanalyzer.y"
                            {(yyval.str) = template("double");}
#line 1314 "myanalyzer.tab.c"
    break;

  case 9: /* data_type: KW_STR  */
#line 145 "myanalyzer.y"
                            {(yyval.str) = template("char*");}
#line 1320 "myanalyzer.tab.c"
    break;

  case 10: /* var_decl: id_recursion ':' data_type  */
#line 149 "myanalyzer.y"
                                          { (yyval.str) = template("%s %s", (yyvsp[0].str), (yyvsp[-2].str)); }
#line 1326 "myanalyzer.tab.c"
    break;

  case 11: /* id_recursion: ID  */
#line 153 "myanalyzer.y"
        { (yyval.str) = (yyvsp[0].str); }
#line 1332 "myanalyzer.tab.c"
    break;

  case 12: /* id_recursion: ID ',' id_recursion  */
#line 154 "myanalyzer.y"
                      { (yyval.str) = template("%s, %s", (yyvsp[-2].str), (yyvsp[0].str)); }
#line 1338 "myanalyzer.tab.c"
    break;

  case 13: /* array_decl: '[' ']' ':' data_type  */
#line 158 "myanalyzer.y"
                                        { (yyval.str) = template("%s*", (yyvsp[0].str)); }
#line 1344 "myanalyzer.tab.c"
    break;

  case 14: /* array_decl: ID '[' expr ']' ':' data_type  */
#line 159 "myanalyzer.y"
                                        { (yyval.str) = template("%s %s[%s]", (yyvsp[0].str), (yyvsp[-5].str), (yyvsp[-3].str)); }
#line 1350 "myanalyzer.tab.c"
    break;

  case 15: /* expr: id_expr  */
#line 163 "myanalyzer.y"
                        { (yyval.str) = (yyvsp[0].str); }
#line 1356 "myanalyzer.tab.c"
    break;

  case 16: /* expr: declarations  */
#line 164 "myanalyzer.y"
                        { (yyval.str) = (yyvsp[0].str); }
#line 1362 "myanalyzer.tab.c"
    break;

  case 17: /* expr: assign_expr  */
#line 165 "myanalyzer.y"
                        { (yyval.str) = (yyvsp[0].str); }
#line 1368 "myanalyzer.tab.c"
    break;

  case 18: /* expr: boolean_expr  */
#line 166 "myanalyzer.y"
                        { (yyval.str) = (yyvsp[0].str); }
#line 1374 "myanalyzer.tab.c"
    break;

  case 19: /* expr: relation_expr  */
#line 167 "myanalyzer.y"
                        { (yyval.str) = (yyvsp[0].str); }
#line 1380 "myanalyzer.tab.c"
    break;

  case 20: /* expr: arithmetic_expr  */
#line 168 "myanalyzer.y"
                        { (yyval.str) = (yyvsp[0].str); }
#line 1386 "myanalyzer.tab.c"
    break;

  case 21: /* expr: '[' expr ')'  */
#line 169 "myanalyzer.y"
                        { (yyval.str) = template("[ %s ]", (yyvsp[-1].str)); }
#line 1392 "myanalyzer.tab.c"
    break;

  case 22: /* expr: '(' expr ')'  */
#line 170 "myanalyzer.y"
                        { (yyval.str) = template("( %s )", (yyvsp[-1].str)); }
#line 1398 "myanalyzer.tab.c"
    break;

  case 23: /* expr: DOT  */
#line 171 "myanalyzer.y"
                        { (yyval.str) = template("( %s )", (yyvsp[0].str)); }
#line 1404 "myanalyzer.tab.c"
    break;

  case 24: /* boolean_expr: KW_NOT expr  */
#line 175 "myanalyzer.y"
                        { (yyval.str) = template("! %s", (yyvsp[0].str)); }
#line 1410 "myanalyzer.tab.c"
    break;

  case 25: /* boolean_expr: expr KW_OR expr  */
#line 176 "myanalyzer.y"
                        { (yyval.str) = template("%s || %s", (yyvsp[-2].str), (yyvsp[0].str)); }
#line 1416 "myanalyzer.tab.c"
    break;

  case 26: /* boolean_expr: expr KW_AND expr  */
#line 177 "myanalyzer.y"
                        { (yyval.str) = template("%s && %s", (yyvsp[-2].str), (yyvsp[0].str)); }
#line 1422 "myanalyzer.tab.c"
    break;

  case 27: /* boolean_expr: KW_TRUE  */
#line 178 "myanalyzer.y"
                        { (yyval.str) = template("1"); }
#line 1428 "myanalyzer.tab.c"
    break;

  case 28: /* boolean_expr: KW_FALSE  */
#line 179 "myanalyzer.y"
                        { (yyval.str) = template("0"); }
#line 1434 "myanalyzer.tab.c"
    break;

  case 29: /* id_expr: ID  */
#line 183 "myanalyzer.y"
                        { (yyval.str) = (yyvsp[0].str); }
#line 1440 "myanalyzer.tab.c"
    break;

  case 30: /* id_expr: ID '[' expr ']'  */
#line 184 "myanalyzer.y"
                        { (yyval.str) = template("%s[%s]", (yyvsp[-3].str), (yyvsp[-1].str)); }
#line 1446 "myanalyzer.tab.c"
    break;

  case 31: /* id_expr: ID '[' INTEGER ']'  */
#line 185 "myanalyzer.y"
                        { (yyval.str) = template("%s[%s]", (yyvsp[-3].str), (yyvsp[-1].str)); }
#line 1452 "myanalyzer.tab.c"
    break;

  case 32: /* relation_expr: expr OP_EQUAL expr  */
#line 189 "myanalyzer.y"
                                { (yyval.str) = template("%s == %s", (yyvsp[-2].str), (yyvsp[0].str)); }
#line 1458 "myanalyzer.tab.c"
    break;

  case 33: /* relation_expr: expr OP_INEQUAL expr  */
#line 190 "myanalyzer.y"
                                { (yyval.str) = template("%s != %s", (yyvsp[-2].str), (yyvsp[0].str)); }
#line 1464 "myanalyzer.tab.c"
    break;

  case 34: /* relation_expr: expr '<' expr  */
#line 191 "myanalyzer.y"
                                { (yyval.str) = template("%s < %s", (yyvsp[-2].str), (yyvsp[0].str)); }
#line 1470 "myanalyzer.tab.c"
    break;

  case 35: /* relation_expr: expr '>' expr  */
#line 192 "myanalyzer.y"
                                { (yyval.str) = template("%s > %s", (yyvsp[-2].str), (yyvsp[0].str)); }
#line 1476 "myanalyzer.tab.c"
    break;

  case 36: /* relation_expr: expr OP_LESSEQUAL expr  */
#line 193 "myanalyzer.y"
                                { (yyval.str) = template("%s <= %s", (yyvsp[-2].str), (yyvsp[0].str)); }
#line 1482 "myanalyzer.tab.c"
    break;

  case 37: /* relation_expr: expr OP_GREATEREQUAL expr  */
#line 194 "myanalyzer.y"
                                { (yyval.str) = template("%s >= %s", (yyvsp[-2].str), (yyvsp[0].str)); }
#line 1488 "myanalyzer.tab.c"
    break;

  case 38: /* assign_expr: ID ASSIGN_PLUS expr  */
#line 198 "myanalyzer.y"
                                { (yyval.str) = template("%s =+ %s", (yyvsp[-2].str), (yyvsp[0].str)); }
#line 1494 "myanalyzer.tab.c"
    break;

  case 39: /* assign_expr: ID ASSIGN_MINUS expr  */
#line 199 "myanalyzer.y"
                                { (yyval.str) = template("%s =- %s", (yyvsp[-2].str), (yyvsp[0].str)); }
#line 1500 "myanalyzer.tab.c"
    break;

  case 40: /* assign_expr: ID ASSIGN_PRODUCT expr  */
#line 200 "myanalyzer.y"
                                { (yyval.str) = template("%s =* %s", (yyvsp[-2].str), (yyvsp[0].str)); }
#line 1506 "myanalyzer.tab.c"
    break;

  case 41: /* assign_expr: ID ASSIGN_DIV expr  */
#line 201 "myanalyzer.y"
                                { (yyval.str) = template("%s =/ %s", (yyvsp[-2].str), (yyvsp[0].str)); }
#line 1512 "myanalyzer.tab.c"
    break;

  case 42: /* assign_expr: ID ASSIGN_MOD expr  */
#line 202 "myanalyzer.y"
                                { (yyval.str) = template("%s =% %s", (yyvsp[-2].str), (yyvsp[0].str)); }
#line 1518 "myanalyzer.tab.c"
    break;

  case 43: /* assign_expr: ID ASSIGN expr  */
#line 203 "myanalyzer.y"
                                { (yyval.str) = template("%s = %s", (yyvsp[-2].str), (yyvsp[0].str)); }
#line 1524 "myanalyzer.tab.c"
    break;

  case 44: /* assign_expr: arrays  */
#line 204 "myanalyzer.y"
                                { (yyval.str) = (yyvsp[0].str); }
#line 1530 "myanalyzer.tab.c"
    break;

  case 45: /* arrays: ID ASSIGN_DOTS '[' expr KW_FOR ID ':' INTEGER ']' ':' data_type  */
#line 210 "myanalyzer.y"
{
	(yyval.str) = template("%s* %s = (%s*)malloc(%s * sizeof(%s));\n for (int %s = 0; %s < %s; ++%s)\n\t %s[%s] = %s", (yyvsp[0].str), (yyvsp[-10].str), (yyvsp[0].str), (yyvsp[-3].str), (yyvsp[0].str), (yyvsp[-5].str), (yyvsp[-5].str), (yyvsp[-3].str), (yyvsp[-5].str), (yyvsp[-10].str), (yyvsp[-5].str), (yyvsp[-7].str) );
}
#line 1538 "myanalyzer.tab.c"
    break;

  case 46: /* arrays: ID ASSIGN_DOTS '[' expr KW_FOR ID ':' data_type KW_IN ID KW_OF INTEGER ']' ':' data_type  */
#line 214 "myanalyzer.y"
{
	char indexed_access[512];
	sprintf(indexed_access, "%s[%s_i]", (yyvsp[-5].str), (yyvsp[-5].str));  // array[array_i]
	char transformed_expr[512];
	replace_identifier((yyvsp[-11].str), (yyvsp[-9].str), indexed_access, transformed_expr);  // replace identidier with array[array_i]

	(yyval.str) = template("%s* %s = (%s*)malloc(%s * sizeof(%s));\n for (int %s_i = 0; %s_i < %s; ++%s_i)\n\t %s[%s] = %s", (yyvsp[0].str), (yyvsp[-14].str), (yyvsp[0].str), (yyvsp[-3].str), (yyvsp[0].str), (yyvsp[-5].str), (yyvsp[-5].str), (yyvsp[-3].str), (yyvsp[-5].str), (yyvsp[-14].str), (yyvsp[-5].str), transformed_expr);
}
#line 1551 "myanalyzer.tab.c"
    break;

  case 47: /* arithmetic_expr: INTEGER  */
#line 225 "myanalyzer.y"
                        { (yyval.str) = (yyvsp[0].str); }
#line 1557 "myanalyzer.tab.c"
    break;

  case 48: /* arithmetic_expr: FLOAT  */
#line 226 "myanalyzer.y"
                        { (yyval.str) = (yyvsp[0].str); }
#line 1563 "myanalyzer.tab.c"
    break;

  case 49: /* arithmetic_expr: expr '+' expr  */
#line 227 "myanalyzer.y"
                        { (yyval.str) = template("%s + %s", (yyvsp[-2].str), (yyvsp[0].str)); }
#line 1569 "myanalyzer.tab.c"
    break;

  case 50: /* arithmetic_expr: expr '-' expr  */
#line 228 "myanalyzer.y"
                        { (yyval.str) = template("%s - %s", (yyvsp[-2].str), (yyvsp[0].str)); }
#line 1575 "myanalyzer.tab.c"
    break;

  case 51: /* arithmetic_expr: expr '*' expr  */
#line 229 "myanalyzer.y"
                        { (yyval.str) = template("%s * %s", (yyvsp[-2].str), (yyvsp[0].str)); }
#line 1581 "myanalyzer.tab.c"
    break;

  case 52: /* arithmetic_expr: expr '/' expr  */
#line 230 "myanalyzer.y"
                        { (yyval.str) = template("%s / %s", (yyvsp[-2].str), (yyvsp[0].str)); }
#line 1587 "myanalyzer.tab.c"
    break;

  case 53: /* arithmetic_expr: expr '%' expr  */
#line 231 "myanalyzer.y"
                        { (yyval.str) = template("%s % %s", (yyvsp[-2].str), (yyvsp[0].str)); }
#line 1593 "myanalyzer.tab.c"
    break;

  case 54: /* arithmetic_expr: '+' expr  */
#line 232 "myanalyzer.y"
                        { (yyval.str) = template("+%s", (yyvsp[0].str));}
#line 1599 "myanalyzer.tab.c"
    break;

  case 55: /* arithmetic_expr: '-' expr  */
#line 233 "myanalyzer.y"
                        { (yyval.str) = template("-%s", (yyvsp[0].str));}
#line 1605 "myanalyzer.tab.c"
    break;

  case 56: /* arithmetic_expr: expr OP_POWER expr  */
#line 234 "myanalyzer.y"
                        { (yyval.str) = template("pow(%s, %s)", (yyvsp[-2].str), (yyvsp[0].str));}
#line 1611 "myanalyzer.tab.c"
    break;


#line 1615 "myanalyzer.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 239 "myanalyzer.y"

int main () {
  if ( yyparse() == 0 )
    printf("Accepted!\n");
  else
    printf("Rejected!\n");
}
