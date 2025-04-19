%{
#include <stdio.h>
%}

%option noyywrap

/* Definição de tokens */

/* Palavras-chave do Python */
KEYWORD     and|as|assert|break|class|continue|def|del|elif|else|except|False|finally|for|from|global|if|import|in|is|lambda|None|nonlocal|not|or|pass|raise|return|True|try|while|with|yield

/* Operadores */
PLUS        "+"
MINUS       "-"
MULTIPLY    "*"
DIVIDE      "/"
MODULO      "%"
POWER       "**"
FLOOR_DIV   "//"
LT          "<"
GT          ">"
LE          "<="
GE          ">="
EQ          "=="
NE          "!="
NE2         "<>"
ASSIGN      "="
PLUS_EQ     "+="
MINUS_EQ    "-="
MULT_EQ     "*="
DIV_EQ      "/="
MOD_EQ      "%="
FLOOR_EQ    "//="
POW_EQ      "**="
BITAND      "&"
BITOR       "|"
BITXOR      "^"
BITNOT      "~"
SHIFTL      "<<"
SHIFTR      ">>"
AND_EQ      "&="
OR_EQ       "|="
XOR_EQ      "^="
SHIFTR_EQ   ">>="
SHIFTL_EQ   "<<="

/* Delimitadores */
LPAREN      "("
RPAREN      ")"
LBRACKET    "["
RBRACKET    "]"
LBRACE      "{"
RBRACE      "}"
COMMA       ","
COLON       ":"
DOT         "."
SEMICOLON   ";"
AT          "@"
ARROW       "->"

/* Identificadores */
IDENTIFIER  [a-zA-Z_][a-zA-Z0-9_]*

/* Números */
INTEGER     [0-9]+
FLOAT       [0-9]*\.[0-9]+([eE][-+]?[0-9]+)?
HEX         0[xX][0-9a-fA-F]+
OCT         0[oO][0-7]+
BIN         0[bB][01]+

/* Strings */
STRING_DQ   \"([^\"\n\\]|\\(.|\n))*\"
STRING_SQ   \'([^\'\n\\]|\\(.|\n))*\'
TRIPLE_DQ   \"\"\"[^\"]*\"\"\"
TRIPLE_SQ   \'\'\'[^\']*\'\'\'

/* Comentários */
COMMENT     #.*
INDENT      ^[ \t]+

/* Regras */
%%

{KEYWORD}   { printf("KEYWORD: %s\n", yytext); }

{PLUS}      { printf("PLUS: %s\n", yytext); }
{MINUS}     { printf("MINUS: %s\n", yytext); }
{MULTIPLY}  { printf("MULTIPLY: %s\n", yytext); }
{DIVIDE}    { printf("DIVIDE: %s\n", yytext); }
{MODULO}    { printf("MODULO: %s\n", yytext); }
{POWER}     { printf("POWER: %s\n", yytext); }
{FLOOR_DIV} { printf("FLOOR_DIV: %s\n", yytext); }
{LT}        { printf("LT: %s\n", yytext); }
{GT}        { printf("GT: %s\n", yytext); }
{LE}        { printf("LE: %s\n", yytext); }
{GE}        { printf("GE: %s\n", yytext); }
{EQ}        { printf("EQ: %s\n", yytext); }
{NE}        { printf("NE: %s\n", yytext); }
{NE2}       { printf("NE2: %s\n", yytext); }
{ASSIGN}    { printf("ASSIGN: %s\n", yytext); }
{PLUS_EQ}   { printf("PLUS_EQ: %s\n", yytext); }
{MINUS_EQ}  { printf("MINUS_EQ: %s\n", yytext); }
{MULT_EQ}   { printf("MULT_EQ: %s\n", yytext); }
{DIV_EQ}    { printf("DIV_EQ: %s\n", yytext); }
{MOD_EQ}    { printf("MOD_EQ: %s\n", yytext); }
{FLOOR_EQ}  { printf("FLOOR_EQ: %s\n", yytext); }
{POW_EQ}    { printf("POW_EQ: %s\n", yytext); }
{BITAND}    { printf("BITAND: %s\n", yytext); }
{BITOR}     { printf("BITOR: %s\n", yytext); }
{BITXOR}    { printf("BITXOR: %s\n", yytext); }
{BITNOT}    { printf("BITNOT: %s\n", yytext); }
{SHIFTL}    { printf("SHIFTL: %s\n", yytext); }
{SHIFTR}    { printf("SHIFTR: %s\n", yytext); }
{AND_EQ}    { printf("AND_EQ: %s\n", yytext); }
{OR_EQ}     { printf("OR_EQ: %s\n", yytext); }
{XOR_EQ}    { printf("XOR_EQ: %s\n", yytext); }
{SHIFTR_EQ} { printf("SHIFTR_EQ: %s\n", yytext); }
{SHIFTL_EQ} { printf("SHIFTL_EQ: %s\n", yytext); }

{LPAREN}    { printf("LPAREN: %s\n", yytext); }
{RPAREN}    { printf("RPAREN: %s\n", yytext); }
{LBRACKET}  { printf("LBRACKET: %s\n", yytext); }
{RBRACKET}  { printf("RBRACKET: %s\n", yytext); }
{LBRACE}    { printf("LBRACE: %s\n", yytext); }
{RBRACE}    { printf("RBRACE: %s\n", yytext); }
{COMMA}     { printf("COMMA: %s\n", yytext); }
{COLON}     { printf("COLON: %s\n", yytext); }
{DOT}       { printf("DOT: %s\n", yytext); }
{SEMICOLON} { printf("SEMICOLON: %s\n", yytext); }
{AT}        { printf("AT: %s\n", yytext); }
{ARROW}     { printf("ARROW: %s\n", yytext); }

{IDENTIFIER} { printf("IDENTIFIER: %s\n", yytext); }

{INTEGER}   { printf("INTEGER: %s\n", yytext); }
{FLOAT}     { printf("FLOAT: %s\n", yytext); }
{HEX}       { printf("HEX: %s\n", yytext); }
{OCT}       { printf("OCT: %s\n", yytext); }
{BIN}       { printf("BIN: %s\n", yytext); }

{STRING_DQ} { printf("STRING_DQ: %s\n", yytext); }
{STRING_SQ} { printf("STRING_SQ: %s\n", yytext); }
{TRIPLE_DQ} { printf("TRIPLE_DQ: %s\n", yytext); }
{TRIPLE_SQ} { printf("TRIPLE_SQ: %s\n", yytext); }

{COMMENT}   { printf("COMMENT: %s\n", yytext); }
{INDENT}    { printf("INDENT: %s\n", yytext); }

[ \t\r\n]+  { /* ignore whitespace */ }
.           { printf("UNKNOWN: %s\n", yytext); }

%%

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            printf("Erro ao abrir arquivo %s\n", argv[1]);
            return 1;
        }
    } else {
        yyin = stdin;
    }
    
    yylex();
    
    if (argc > 1) {
        fclose(yyin);
    }
    
    return 0;
}

