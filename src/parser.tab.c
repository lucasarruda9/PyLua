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
#line 1 "parser/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include "../ast/ast.h"
#include "../tabela/tabela.h"
#include <string.h>

int yylex();  // Declaração da função yylex que será chamada pelo parser
void yyerror(const char *s);  // Função de erro para lidar com erros sintáticos
extern FILE *yyin;  // Arquivo de entrada (pode ser stdin ou um arquivo)
extern int line_num;  // Linha atual (definida no scanner)
extern int col_num;   // Coluna atual (definida no scanner)
extern void inicializa_pilha();  // Declaração da função de inicialização da pilha de indentação

void yyerror(const char *s) {
    fprintf(stderr, "[ERRO SINTATICO] %s na linha %d, coluna %d\n", s, line_num, col_num);
}

#line 90 "src/parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INTEGER = 3,                    /* INTEGER  */
  YYSYMBOL_PLUS = 4,                       /* PLUS  */
  YYSYMBOL_MINUS = 5,                      /* MINUS  */
  YYSYMBOL_MULTIPLY = 6,                   /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 7,                     /* DIVIDE  */
  YYSYMBOL_MODULO = 8,                     /* MODULO  */
  YYSYMBOL_POWER = 9,                      /* POWER  */
  YYSYMBOL_FLOOR_DIV = 10,                 /* FLOOR_DIV  */
  YYSYMBOL_LT = 11,                        /* LT  */
  YYSYMBOL_GT = 12,                        /* GT  */
  YYSYMBOL_LE = 13,                        /* LE  */
  YYSYMBOL_GE = 14,                        /* GE  */
  YYSYMBOL_EQ = 15,                        /* EQ  */
  YYSYMBOL_NE = 16,                        /* NE  */
  YYSYMBOL_NE2 = 17,                       /* NE2  */
  YYSYMBOL_LPAREN = 18,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 19,                    /* RPAREN  */
  YYSYMBOL_IDENTIFIER = 20,                /* IDENTIFIER  */
  YYSYMBOL_ASSIGN = 21,                    /* ASSIGN  */
  YYSYMBOL_PLUS_EQ = 22,                   /* PLUS_EQ  */
  YYSYMBOL_MINUS_EQ = 23,                  /* MINUS_EQ  */
  YYSYMBOL_MULT_EQ = 24,                   /* MULT_EQ  */
  YYSYMBOL_DIV_EQ = 25,                    /* DIV_EQ  */
  YYSYMBOL_FLOOR_EQ = 26,                  /* FLOOR_EQ  */
  YYSYMBOL_POW_EQ = 27,                    /* POW_EQ  */
  YYSYMBOL_MOD_EQ = 28,                    /* MOD_EQ  */
  YYSYMBOL_BITAND = 29,                    /* BITAND  */
  YYSYMBOL_BITOR = 30,                     /* BITOR  */
  YYSYMBOL_BITXOR = 31,                    /* BITXOR  */
  YYSYMBOL_BITNOT = 32,                    /* BITNOT  */
  YYSYMBOL_SHIFTL = 33,                    /* SHIFTL  */
  YYSYMBOL_SHIFTR = 34,                    /* SHIFTR  */
  YYSYMBOL_AND_EQ = 35,                    /* AND_EQ  */
  YYSYMBOL_OR_EQ = 36,                     /* OR_EQ  */
  YYSYMBOL_XOR_EQ = 37,                    /* XOR_EQ  */
  YYSYMBOL_SHIFTR_EQ = 38,                 /* SHIFTR_EQ  */
  YYSYMBOL_SHIFTL_EQ = 39,                 /* SHIFTL_EQ  */
  YYSYMBOL_ERROR = 40,                     /* ERROR  */
  YYSYMBOL_NEWLINE = 41,                   /* NEWLINE  */
  YYSYMBOL_KEYWORD = 42,                   /* KEYWORD  */
  YYSYMBOL_IF = 43,                        /* IF  */
  YYSYMBOL_ELIF = 44,                      /* ELIF  */
  YYSYMBOL_ELSE = 45,                      /* ELSE  */
  YYSYMBOL_MATCH = 46,                     /* MATCH  */
  YYSYMBOL_CASE = 47,                      /* CASE  */
  YYSYMBOL_FOR = 48,                       /* FOR  */
  YYSYMBOL_WHILE = 49,                     /* WHILE  */
  YYSYMBOL_LBRACKET = 50,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 51,                  /* RBRACKET  */
  YYSYMBOL_LBRACE = 52,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 53,                    /* RBRACE  */
  YYSYMBOL_COMMA = 54,                     /* COMMA  */
  YYSYMBOL_COLON = 55,                     /* COLON  */
  YYSYMBOL_DOT = 56,                       /* DOT  */
  YYSYMBOL_DECORATOR = 57,                 /* DECORATOR  */
  YYSYMBOL_ARROW = 58,                     /* ARROW  */
  YYSYMBOL_FLOAT = 59,                     /* FLOAT  */
  YYSYMBOL_HEX = 60,                       /* HEX  */
  YYSYMBOL_OCT = 61,                       /* OCT  */
  YYSYMBOL_BIN = 62,                       /* BIN  */
  YYSYMBOL_STRING_DQ = 63,                 /* STRING_DQ  */
  YYSYMBOL_STRING_SQ = 64,                 /* STRING_SQ  */
  YYSYMBOL_TRIPLE_DQ = 65,                 /* TRIPLE_DQ  */
  YYSYMBOL_TRIPLE_SQ = 66,                 /* TRIPLE_SQ  */
  YYSYMBOL_COMMENT = 67,                   /* COMMENT  */
  YYSYMBOL_INDENT = 68,                    /* INDENT  */
  YYSYMBOL_DEDENT = 69,                    /* DEDENT  */
  YYSYMBOL_NEG = 70,                       /* NEG  */
  YYSYMBOL_YYACCEPT = 71,                  /* $accept  */
  YYSYMBOL_input = 72,                     /* input  */
  YYSYMBOL_line = 73,                      /* line  */
  YYSYMBOL_expr = 74,                      /* expr  */
  YYSYMBOL_declaracao = 75,                /* declaracao  */
  YYSYMBOL_bloco = 76,                     /* bloco  */
  YYSYMBOL_linhas = 77,                    /* linhas  */
  YYSYMBOL_condicional = 78                /* condicional  */
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
#define YYLAST   335

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  8
/* YYNRULES -- Number of rules.  */
#define YYNRULES  48
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  91

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   325


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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    74,    74,    75,    78,    86,    98,   106,   118,   119,
     120,   121,   128,   129,   137,   138,   139,   140,   141,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   168,   171,   174,   177,
     180,   183,   186,   189,   194,   199,   200,   204,   207
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
  "\"end of file\"", "error", "\"invalid token\"", "INTEGER", "PLUS",
  "MINUS", "MULTIPLY", "DIVIDE", "MODULO", "POWER", "FLOOR_DIV", "LT",
  "GT", "LE", "GE", "EQ", "NE", "NE2", "LPAREN", "RPAREN", "IDENTIFIER",
  "ASSIGN", "PLUS_EQ", "MINUS_EQ", "MULT_EQ", "DIV_EQ", "FLOOR_EQ",
  "POW_EQ", "MOD_EQ", "BITAND", "BITOR", "BITXOR", "BITNOT", "SHIFTL",
  "SHIFTR", "AND_EQ", "OR_EQ", "XOR_EQ", "SHIFTR_EQ", "SHIFTL_EQ", "ERROR",
  "NEWLINE", "KEYWORD", "IF", "ELIF", "ELSE", "MATCH", "CASE", "FOR",
  "WHILE", "LBRACKET", "RBRACKET", "LBRACE", "RBRACE", "COMMA", "COLON",
  "DOT", "DECORATOR", "ARROW", "FLOAT", "HEX", "OCT", "BIN", "STRING_DQ",
  "STRING_SQ", "TRIPLE_DQ", "TRIPLE_SQ", "COMMENT", "INDENT", "DEDENT",
  "NEG", "$accept", "input", "line", "expr", "declaracao", "bloco",
  "linhas", "condicional", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-71)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -71,     5,   -71,   -28,   -71,    -2,    -2,    38,    -2,   -71,
      -4,   -71,    94,   -21,   -20,   -71,   -71,   -71,   132,    -2,
      -2,    -2,    -2,    -2,    -2,    -2,    -2,   -71,    -2,    -2,
      -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,
      -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,   -71,   -71,
     -71,   -71,   194,   194,   194,   194,   194,   194,   194,   194,
     163,    26,    26,    13,    13,    13,    13,    13,   150,   150,
     150,   150,   301,   301,   301,   287,   225,   256,   108,   108,
     -27,   -41,     6,   -16,   -71,    -1,   -14,   -71,   -71,   -41,
     -71
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,    12,     0,     0,    13,     0,    10,
       0,     3,     6,     7,     9,    11,    13,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    35,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     4,     5,
       8,    14,    36,    37,    38,    39,    40,    42,    43,    41,
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
       0,     0,     0,    47,    46,     0,     0,    44,    45,     0,
      48
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -71,   -71,   -70,    50,   -71,   -50,   -71,   -71
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,    11,    12,    13,    83,    85,    14
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
       3,     4,     4,     5,     5,     2,     3,     3,     4,     4,
       5,     5,    84,    15,    28,    88,     6,     6,    16,     7,
      49,    50,    34,     6,     6,     7,     7,    82,    81,    86,
       8,     8,    31,    32,    33,    34,    35,     8,     8,    90,
       9,    89,    10,     0,     0,     0,     9,     9,    10,    10,
       0,     0,     0,     0,     0,    17,    18,     0,    27,    19,
      20,    21,    22,    23,    24,    25,    26,     0,    87,    52,
      53,    54,    55,    56,    57,    58,    59,     0,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    29,    30,    31,    32,    33,    34,    35,     0,
       0,     0,     0,    43,    44,    45,     0,    46,    47,     0,
       0,     0,     0,     0,     0,    48,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
       0,    51,     0,     0,    29,    30,    31,    32,    33,    34,
      35,    43,    44,    45,     0,    46,    47,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,     0,    80,    46,    47,     0,     0,     0,     0,     0,
       0,     0,    43,    44,    45,     0,    46,    47,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    43,    44,    45,     0,    46,    47,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    43,     0,    45,     0,    46,    47,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    43,     0,     0,     0,    46,
      47,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,     0,     0,     0,     0,
      46,    47,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    46,    47
};

static const yytype_int8 yycheck[] =
{
       1,     3,     3,     5,     5,     0,     1,     1,     3,     3,
       5,     5,    82,    41,    18,    85,    18,    18,    20,    20,
      41,    41,     9,    18,    18,    20,    20,    68,    55,    45,
      32,    32,     6,     7,     8,     9,    10,    32,    32,    89,
      41,    55,    43,    -1,    -1,    -1,    41,    41,    43,    43,
      -1,    -1,    -1,    -1,    -1,     5,     6,    -1,     8,    21,
      22,    23,    24,    25,    26,    27,    28,    -1,    69,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    -1,    -1,    29,    30,    31,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    41,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    19,    -1,    -1,     4,     5,     6,     7,     8,     9,
      10,    29,    30,    31,    -1,    33,    34,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    19,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    30,    31,    -1,    33,    34,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    30,    31,    -1,    33,    34,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    -1,    31,    -1,    33,    34,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    33,
      34,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    72,     0,     1,     3,     5,    18,    20,    32,    41,
      43,    73,    74,    75,    78,    41,    20,    74,    74,    21,
      22,    23,    24,    25,    26,    27,    28,    74,    18,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    29,    30,    31,    33,    34,    41,    41,
      41,    19,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      19,    55,    68,    76,    73,    77,    45,    69,    73,    55,
      76
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    71,    72,    72,    73,    73,    73,    73,    73,    73,
      73,    73,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    75,    75,    75,    75,
      75,    75,    75,    75,    76,    77,    77,    78,    78
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     1,     1,     2,     1,
       1,     2,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     1,     6,     9
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
  case 4: /* line: expr NEWLINE  */
#line 78 "parser/parser.y"
                      { 
        imprimeArvore((yyvsp[-1].no), 0);
        // Avaliação da expressão vai aqui
        int resultado = avaliarArvore((yyvsp[-1].no));
        printf("Resultado: %d\n", resultado);
        DesalocarArvore((yyvsp[-1].no));
        (yyval.no) = NULL;
}
#line 1270 "src/parser.tab.c"
    break;

  case 5: /* line: declaracao NEWLINE  */
#line 86 "parser/parser.y"
                            { 
        imprimeArvore((yyvsp[-1].no), 0);
        // Avalia e executa a atribuição na tabela de símbolos
        if ((yyvsp[-1].no)->tipo == NoAtribuicao) {
            if ((yyvsp[-1].no)->esquerdo->tipo == NoVariavel) {
                int resultado = avaliarArvore((yyvsp[-1].no));
                printf("Resultado da atribuição: %d\n", resultado);
            }
        }
        DesalocarArvore((yyvsp[-1].no));
        (yyval.no) = NULL;
}
#line 1287 "src/parser.tab.c"
    break;

  case 6: /* line: expr  */
#line 98 "parser/parser.y"
                                                 { 
        imprimeArvore((yyvsp[0].no), 0);
        // Avaliação da expressão vai aqui
        int resultado = avaliarArvore((yyvsp[0].no));
        printf("Resultado: %d\n", resultado);
        DesalocarArvore((yyvsp[0].no));
        (yyval.no) = NULL;
}
#line 1300 "src/parser.tab.c"
    break;

  case 7: /* line: declaracao  */
#line 106 "parser/parser.y"
                                                       { 
        imprimeArvore((yyvsp[0].no), 0);
        // Avalia e executa a atribuição na tabela de símbolos
        if ((yyvsp[0].no)->tipo == NoAtribuicao) {
            if ((yyvsp[0].no)->esquerdo->tipo == NoVariavel) {
                int resultado = avaliarArvore((yyvsp[0].no));
                printf("Resultado da atribuição: %d\n", resultado);
            }
        }
        DesalocarArvore((yyvsp[0].no));
        (yyval.no) = NULL;
}
#line 1317 "src/parser.tab.c"
    break;

  case 8: /* line: condicional NEWLINE  */
#line 118 "parser/parser.y"
                              { imprimeArvore((yyvsp[-1].no), 0); DesalocarArvore((yyvsp[-1].no)); (yyval.no) = NULL; }
#line 1323 "src/parser.tab.c"
    break;

  case 9: /* line: condicional  */
#line 119 "parser/parser.y"
                  { imprimeArvore((yyvsp[0].no), 0); DesalocarArvore((yyvsp[0].no)); (yyval.no) = NULL; }
#line 1329 "src/parser.tab.c"
    break;

  case 10: /* line: NEWLINE  */
#line 120 "parser/parser.y"
                 { (yyval.no) = NULL; }
#line 1335 "src/parser.tab.c"
    break;

  case 11: /* line: error NEWLINE  */
#line 121 "parser/parser.y"
                       { 
                    printf("[ERRO SINTATICO] Erro recuperado até o final da linha\n"); 
                    yyerrok;
                    (yyval.no) = NULL;
                }
#line 1345 "src/parser.tab.c"
    break;

  case 12: /* expr: INTEGER  */
#line 128 "parser/parser.y"
                               { (yyval.no) = CriarNoInteiro((yyvsp[0].intval)); }
#line 1351 "src/parser.tab.c"
    break;

  case 13: /* expr: IDENTIFIER  */
#line 129 "parser/parser.y"
                               { 
                               Simbolo *s = buscarSimbolo((yyvsp[0].string));
                               if (s == NULL) {
                                   printf("[AVISO] Variável '%s' não declarada\n", (yyvsp[0].string));
                                   inserirSimbolo((yyvsp[0].string), TIPO_INT);
                               }
                               (yyval.no) = CriarNoVariavel((yyvsp[0].string)); 
                              }
#line 1364 "src/parser.tab.c"
    break;

  case 14: /* expr: LPAREN expr RPAREN  */
#line 137 "parser/parser.y"
                               { (yyval.no) = (yyvsp[-1].no); }
#line 1370 "src/parser.tab.c"
    break;

  case 15: /* expr: expr PLUS expr  */
#line 138 "parser/parser.y"
                               { (yyval.no) = CriarNoOperador((yyvsp[-2].no), (yyvsp[0].no), '+'); }
#line 1376 "src/parser.tab.c"
    break;

  case 16: /* expr: expr MINUS expr  */
#line 139 "parser/parser.y"
                               { (yyval.no) = CriarNoOperador((yyvsp[-2].no), (yyvsp[0].no), '-'); }
#line 1382 "src/parser.tab.c"
    break;

  case 17: /* expr: expr MULTIPLY expr  */
#line 140 "parser/parser.y"
                               { (yyval.no) = CriarNoOperador((yyvsp[-2].no), (yyvsp[0].no), '*'); }
#line 1388 "src/parser.tab.c"
    break;

  case 18: /* expr: expr DIVIDE expr  */
#line 141 "parser/parser.y"
                               {
                                if ((yyvsp[0].no)->valor == 0 && (yyvsp[0].no)->tipo == NoLiteral) {
                                    yyerror("Divisão por zero");
                                    (yyval.no) = CriarNoInteiro(0);
                                } else {
                                    (yyval.no) = CriarNoOperador((yyvsp[-2].no), (yyvsp[0].no), '/');
                                }
                              }
#line 1401 "src/parser.tab.c"
    break;

  case 19: /* expr: expr MODULO expr  */
#line 149 "parser/parser.y"
                               { (yyval.no) = CriarNoOperador((yyvsp[-2].no), (yyvsp[0].no), '%'); }
#line 1407 "src/parser.tab.c"
    break;

  case 20: /* expr: expr POWER expr  */
#line 150 "parser/parser.y"
                               { (yyval.no) = CriarNoOperador((yyvsp[-2].no), (yyvsp[0].no), 'p'); }
#line 1413 "src/parser.tab.c"
    break;

  case 21: /* expr: expr FLOOR_DIV expr  */
#line 151 "parser/parser.y"
                               { (yyval.no) = CriarNoOperador((yyvsp[-2].no), (yyvsp[0].no), 'f'); }
#line 1419 "src/parser.tab.c"
    break;

  case 22: /* expr: expr LT expr  */
#line 152 "parser/parser.y"
                               { (yyval.no) = CriarNoOperador((yyvsp[-2].no), (yyvsp[0].no), '<'); }
#line 1425 "src/parser.tab.c"
    break;

  case 23: /* expr: expr GT expr  */
#line 153 "parser/parser.y"
                               { (yyval.no) = CriarNoOperador((yyvsp[-2].no), (yyvsp[0].no), '>'); }
#line 1431 "src/parser.tab.c"
    break;

  case 24: /* expr: expr LE expr  */
#line 154 "parser/parser.y"
                               { (yyval.no) = CriarNoOperador((yyvsp[-2].no), (yyvsp[0].no), 'l'); }
#line 1437 "src/parser.tab.c"
    break;

  case 25: /* expr: expr GE expr  */
#line 155 "parser/parser.y"
                               { (yyval.no) = CriarNoOperador((yyvsp[-2].no), (yyvsp[0].no), 'g'); }
#line 1443 "src/parser.tab.c"
    break;

  case 26: /* expr: expr EQ expr  */
#line 156 "parser/parser.y"
                               { (yyval.no) = CriarNoOperador((yyvsp[-2].no), (yyvsp[0].no), '='); }
#line 1449 "src/parser.tab.c"
    break;

  case 27: /* expr: expr NE expr  */
#line 157 "parser/parser.y"
                               { (yyval.no) = CriarNoOperador((yyvsp[-2].no), (yyvsp[0].no), 'n'); }
#line 1455 "src/parser.tab.c"
    break;

  case 28: /* expr: expr NE2 expr  */
#line 158 "parser/parser.y"
                               { (yyval.no) = CriarNoOperador((yyvsp[-2].no), (yyvsp[0].no), 'n'); }
#line 1461 "src/parser.tab.c"
    break;

  case 29: /* expr: expr BITAND expr  */
#line 159 "parser/parser.y"
                               { (yyval.no) = CriarNoOperador((yyvsp[-2].no), (yyvsp[0].no), '&'); }
#line 1467 "src/parser.tab.c"
    break;

  case 30: /* expr: expr BITOR expr  */
#line 160 "parser/parser.y"
                               { (yyval.no) = CriarNoOperador((yyvsp[-2].no), (yyvsp[0].no), '|'); }
#line 1473 "src/parser.tab.c"
    break;

  case 31: /* expr: expr BITXOR expr  */
#line 161 "parser/parser.y"
                               { (yyval.no) = CriarNoOperador((yyvsp[-2].no), (yyvsp[0].no), '^'); }
#line 1479 "src/parser.tab.c"
    break;

  case 32: /* expr: expr SHIFTL expr  */
#line 162 "parser/parser.y"
                               { (yyval.no) = CriarNoOperador((yyvsp[-2].no), (yyvsp[0].no), 's'); }
#line 1485 "src/parser.tab.c"
    break;

  case 33: /* expr: expr SHIFTR expr  */
#line 163 "parser/parser.y"
                               { (yyval.no) = CriarNoOperador((yyvsp[-2].no), (yyvsp[0].no), 'r'); }
#line 1491 "src/parser.tab.c"
    break;

  case 34: /* expr: MINUS expr  */
#line 164 "parser/parser.y"
                               { (yyval.no) = CriarNoOperador((yyvsp[0].no), NULL, '-'); }
#line 1497 "src/parser.tab.c"
    break;

  case 35: /* expr: BITNOT expr  */
#line 165 "parser/parser.y"
                                  { (yyval.no) = CriarNoOperador((yyvsp[0].no), NULL, '~'); }
#line 1503 "src/parser.tab.c"
    break;

  case 36: /* declaracao: IDENTIFIER ASSIGN expr  */
#line 168 "parser/parser.y"
                                    { 
            (yyval.no) = CriaNoAtribuicao(CriarNoVariavel((yyvsp[-2].string)), (yyvsp[0].no));
}
#line 1511 "src/parser.tab.c"
    break;

  case 37: /* declaracao: IDENTIFIER PLUS_EQ expr  */
#line 171 "parser/parser.y"
                                 { 
            (yyval.no) = CriaNoAtribuicao(CriarNoVariavel((yyvsp[-2].string)), CriarNoOperador(CriarNoVariavel((yyvsp[-2].string)), (yyvsp[0].no), '+'));
}
#line 1519 "src/parser.tab.c"
    break;

  case 38: /* declaracao: IDENTIFIER MINUS_EQ expr  */
#line 174 "parser/parser.y"
                                  { 
            (yyval.no) = CriaNoAtribuicao(CriarNoVariavel((yyvsp[-2].string)), CriarNoOperador(CriarNoVariavel((yyvsp[-2].string)), (yyvsp[0].no), '-'));
}
#line 1527 "src/parser.tab.c"
    break;

  case 39: /* declaracao: IDENTIFIER MULT_EQ expr  */
#line 177 "parser/parser.y"
                                 { 
            (yyval.no) = CriaNoAtribuicao(CriarNoVariavel((yyvsp[-2].string)), CriarNoOperador(CriarNoVariavel((yyvsp[-2].string)), (yyvsp[0].no), '*'));
}
#line 1535 "src/parser.tab.c"
    break;

  case 40: /* declaracao: IDENTIFIER DIV_EQ expr  */
#line 180 "parser/parser.y"
                                { 
            (yyval.no) = CriaNoAtribuicao(CriarNoVariavel((yyvsp[-2].string)), CriarNoOperador(CriarNoVariavel((yyvsp[-2].string)), (yyvsp[0].no), '/'));
}
#line 1543 "src/parser.tab.c"
    break;

  case 41: /* declaracao: IDENTIFIER MOD_EQ expr  */
#line 183 "parser/parser.y"
                                { 
            (yyval.no) = CriaNoAtribuicao(CriarNoVariavel((yyvsp[-2].string)), CriarNoOperador(CriarNoVariavel((yyvsp[-2].string)), (yyvsp[0].no), '%'));
}
#line 1551 "src/parser.tab.c"
    break;

  case 42: /* declaracao: IDENTIFIER FLOOR_EQ expr  */
#line 186 "parser/parser.y"
                                  { 
            (yyval.no) = CriaNoAtribuicao(CriarNoVariavel((yyvsp[-2].string)), CriarNoOperador(CriarNoVariavel((yyvsp[-2].string)), (yyvsp[0].no), 'b'));
}
#line 1559 "src/parser.tab.c"
    break;

  case 43: /* declaracao: IDENTIFIER POW_EQ expr  */
#line 189 "parser/parser.y"
                                { 
            (yyval.no) = CriaNoAtribuicao(CriarNoVariavel((yyvsp[-2].string)), CriarNoOperador(CriarNoVariavel((yyvsp[-2].string)), (yyvsp[0].no), 'a'));
}
#line 1567 "src/parser.tab.c"
    break;

  case 44: /* bloco: INDENT linhas DEDENT  */
#line 194 "parser/parser.y"
                           { (yyval.lista) = (yyvsp[-1].lista); }
#line 1573 "src/parser.tab.c"
    break;

  case 45: /* linhas: linhas line  */
#line 199 "parser/parser.y"
                  { (yyval.lista) = AdicionarNoLista((yyvsp[-1].lista), (yyvsp[0].no)); }
#line 1579 "src/parser.tab.c"
    break;

  case 46: /* linhas: line  */
#line 200 "parser/parser.y"
           { (yyval.lista) = AdicionarNoLista(NULL, (yyvsp[0].no));}
#line 1585 "src/parser.tab.c"
    break;

  case 47: /* condicional: IF LPAREN expr RPAREN COLON bloco  */
#line 204 "parser/parser.y"
                                        {
          (yyval.no) = CriarNoIf((yyvsp[-3].no), CriarNoBloco((yyvsp[0].lista)), NULL);
      }
#line 1593 "src/parser.tab.c"
    break;

  case 48: /* condicional: IF LPAREN expr RPAREN COLON bloco ELSE COLON bloco  */
#line 207 "parser/parser.y"
                                                         {
          (yyval.no) = CriarNoIf((yyvsp[-6].no), CriarNoBloco((yyvsp[-3].lista)), CriarNoBloco((yyvsp[0].lista)));
      }
#line 1601 "src/parser.tab.c"
    break;


#line 1605 "src/parser.tab.c"

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

#line 211 "parser/parser.y"


/* Função principal para executar o parser */
int main(int argc, char **argv) {
    /* Inicializa a tabela de símbolos */
    inicializarTabela();
    
    /* Inicializa a pilha de indentação */
    inicializa_pilha();
    
    /* Configura o arquivo de entrada ou usa stdin */
    if (argc > 1) {
        yyin = fopen(argv[1], "r");  // Abre o arquivo de entrada
        if (yyin == NULL) {
            printf("Erro ao abrir arquivo %s\n", argv[1]);
            return 1;
        }
    } else {
        yyin = stdin;  // Se não passar argumento, usa a entrada padrão
        printf("Digite expressões em Python. Pressione Ctrl+D (Linux/Mac) ou Ctrl+Z seguido de Enter (Windows) para encerrar.\n");
    }
    
    /* Executa o parser */
    yyparse();  // Chama o parser para começar a análise
    
    /* Imprime a tabela de símbolos */
    imprimirTabela();
    
    /* Libera a tabela de símbolos */
    liberarTabela();
    
    /* Fecha o arquivo se necessário */
    if (argc > 1) {
        fclose(yyin);
    }
    
    return 0;
}
