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

#ifndef YY_YY_SRC_PARSER_TAB_H_INCLUDED
# define YY_YY_SRC_PARSER_TAB_H_INCLUDED
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
    INTEGER = 258,                 /* INTEGER  */
    PLUS = 259,                    /* PLUS  */
    MINUS = 260,                   /* MINUS  */
    MULTIPLY = 261,                /* MULTIPLY  */
    DIVIDE = 262,                  /* DIVIDE  */
    MODULO = 263,                  /* MODULO  */
    POWER = 264,                   /* POWER  */
    FLOOR_DIV = 265,               /* FLOOR_DIV  */
    LT = 266,                      /* LT  */
    GT = 267,                      /* GT  */
    LE = 268,                      /* LE  */
    GE = 269,                      /* GE  */
    EQ = 270,                      /* EQ  */
    NE = 271,                      /* NE  */
    NE2 = 272,                     /* NE2  */
    LPAREN = 273,                  /* LPAREN  */
    RPAREN = 274,                  /* RPAREN  */
    IDENTIFIER = 275,              /* IDENTIFIER  */
    ASSIGN = 276,                  /* ASSIGN  */
    PLUS_EQ = 277,                 /* PLUS_EQ  */
    MINUS_EQ = 278,                /* MINUS_EQ  */
    MULT_EQ = 279,                 /* MULT_EQ  */
    DIV_EQ = 280,                  /* DIV_EQ  */
    FLOOR_EQ = 281,                /* FLOOR_EQ  */
    POW_EQ = 282,                  /* POW_EQ  */
    MOD_EQ = 283,                  /* MOD_EQ  */
    BITAND = 284,                  /* BITAND  */
    BITOR = 285,                   /* BITOR  */
    BITXOR = 286,                  /* BITXOR  */
    BITNOT = 287,                  /* BITNOT  */
    SHIFTL = 288,                  /* SHIFTL  */
    SHIFTR = 289,                  /* SHIFTR  */
    AND_EQ = 290,                  /* AND_EQ  */
    OR_EQ = 291,                   /* OR_EQ  */
    XOR_EQ = 292,                  /* XOR_EQ  */
    SHIFTR_EQ = 293,               /* SHIFTR_EQ  */
    SHIFTL_EQ = 294,               /* SHIFTL_EQ  */
    ERROR = 295,                   /* ERROR  */
    NEWLINE = 296,                 /* NEWLINE  */
    KEYWORD = 297,                 /* KEYWORD  */
    IF = 298,                      /* IF  */
    ELIF = 299,                    /* ELIF  */
    ELSE = 300,                    /* ELSE  */
    MATCH = 301,                   /* MATCH  */
    CASE = 302,                    /* CASE  */
    FOR = 303,                     /* FOR  */
    WHILE = 304,                   /* WHILE  */
    LBRACKET = 305,                /* LBRACKET  */
    RBRACKET = 306,                /* RBRACKET  */
    LBRACE = 307,                  /* LBRACE  */
    RBRACE = 308,                  /* RBRACE  */
    COMMA = 309,                   /* COMMA  */
    COLON = 310,                   /* COLON  */
    DOT = 311,                     /* DOT  */
    DECORATOR = 312,               /* DECORATOR  */
    ARROW = 313,                   /* ARROW  */
    FLOAT = 314,                   /* FLOAT  */
    HEX = 315,                     /* HEX  */
    OCT = 316,                     /* OCT  */
    BIN = 317,                     /* BIN  */
    STRING_DQ = 318,               /* STRING_DQ  */
    STRING_SQ = 319,               /* STRING_SQ  */
    TRIPLE_DQ = 320,               /* TRIPLE_DQ  */
    TRIPLE_SQ = 321,               /* TRIPLE_SQ  */
    COMMENT = 322,                 /* COMMENT  */
    INDENT = 323,                  /* INDENT  */
    DEDENT = 324,                  /* DEDENT  */
    NEG = 325                      /* NEG  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 21 "parser/parser.y"

    int intval;
    struct Arvore *no;
    char *string;
    struct ListaNo *lista;

#line 141 "src/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SRC_PARSER_TAB_H_INCLUDED  */
