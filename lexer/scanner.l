%{
#include <stdio.h>
#include <stdlib.h>
#include "../src/parser.tab.h"  /* Caminho ajustado para o novo local do arquivo gerado */


int convert_to_int(char *text) {
    return atoi(text);
}

int line_num = 1; // linha atual
%}


%option noyywrap noinput nounput nomain

/* Definição de tokens */

/* Palavras-chave do Python */
KEYWORD     and|as|assert|break|class|continue|def|del|except|False|finally|from|global|import|in|is|lambda|None|nonlocal|not|or|pass|raise|return|True|try|with|yield


UNDERLINE   "_"
ASYNC       "async"
AWAIT       "await"

/* Condicionais */

IF         "if"
ELIF       "elif"
ELSE       "else"
MATCH      "match"
CASE       "case"

/* Loop */

FOR        "for"
WHILE      "while"

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
DECORATOR   "@"
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
COMMENT     \#.*

INDENT      ^[ \t]+

%%

\n              { line_num++; }
[ \t\r]+        { /* ignora espaços e tabulações */ }

/* ===== TRATAMENTO DE ERROS LÉXICOS ===== */

/* Identificadores inválidos (ex: 123abc) */
[0-9]+[a-zA-Z_][a-zA-Z0-9_]* {
    fprintf(stderr, "ERRO LÉXICO na linha %d: Identificador não pode começar com número: '%s'\n", line_num, yytext);
    return ERROR;
}

/* Números malformados */
0[xX][^0-9a-fA-F]+ {
    fprintf(stderr, "ERRO LÉXICO na linha %d: Número hexadecimal inválido: '%s'\n", line_num, yytext);
    return ERROR;
}
0[bB][^01]+ {
    fprintf(stderr, "ERRO LÉXICO na linha %d: Número binário inválido: '%s'\n", line_num, yytext);
    return ERROR;
}
0[oO][^0-7]+ {
    fprintf(stderr, "ERRO LÉXICO na linha %d: Número octal inválido: '%s'\n", line_num, yytext);
    return ERROR;
}

/* String mal terminada com escape no final */
\"([^\"\n\\]|\\.)*\\$ {
    fprintf(stderr, "ERRO LÉXICO na linha %d: String dupla com escape malformado no final\n", line_num);
    return ERROR;
}
\'([^\'\n\\]|\\.)*\\$ {
    fprintf(stderr, "ERRO LÉXICO na linha %d: String simples com escape malformado no final\n", line_num);
    return ERROR;
}

/* Caracteres de controle inválidos */
[\x01-\x08\x0B\x0C\x0E-\x1F] {
    fprintf(stderr, "ERRO LÉXICO na linha %d: Caractere de controle não permitido: código 0x%02X\n", line_num, yytext[0]);
    return ERROR;
}

/* ===== TOKENS ===== */

{KEYWORD}       { /* Palavra-chave reconhecida */ }
{UNDERLINE}     { /* UNDERLINE reconhecido */ }
{ASYNC}         { /* ASYNC reconhecido */ }
{AWAIT}         { /* AWAIT reconhecido */ }
{MATCH}         { /* MATCH reconhecido */ }
{CASE}          { /* CASE reconhecido */ }
{IF}            { /* IF reconhecido */ }
{ELIF}          { /* ELIF reconhecido */ }
{ELSE}          { /* ELSE reconhecido */ }

{PLUS}      { return PLUS; }
{MINUS}     { return MINUS; }
{MULTIPLY}  { return MULTIPLY; }
{DIVIDE}    { return DIVIDE; }

{MODULO}    { /* MODULO reconhecido */ }
{POWER}     { /* POWER reconhecido */ }
{FLOOR_DIV} { /* FLOOR_DIV reconhecido */ }

{LT}        { /* LT reconhecido */ }
{GT}        { /* GT reconhecido */ }
{LE}        { /* LE reconhecido */ }
{GE}        { /* GE reconhecido */ }
{EQ}        { /* EQ reconhecido */ }
{NE}        { /* NE reconhecido */ }
{NE2}       { /* NE2 reconhecido */ }

{ASSIGN}    { /* ASSIGN reconhecido */ }
{PLUS_EQ}   { /* PLUS_EQ reconhecido */ }
{MINUS_EQ}  { /* MINUS_EQ reconhecido */ }
{MULT_EQ}   { /* MULT_EQ reconhecido */ }
{DIV_EQ}    { /* DIV_EQ reconhecido */ }
{MOD_EQ}    { /* MOD_EQ reconhecido */ }
{FLOOR_EQ}  { /* FLOOR_EQ reconhecido */ }
{POW_EQ}    { /* POW_EQ reconhecido */ }

{BITAND}    { /* BITAND reconhecido */ }
{BITOR}     { /* BITOR reconhecido */ }
{BITXOR}    { /* BITXOR reconhecido */ }
{BITNOT}    { /* BITNOT reconhecido */ }
{SHIFTL}    { /* SHIFTL reconhecido */ }
{SHIFTR}    { /* SHIFTR reconhecido */ }
{AND_EQ}    { /* AND_EQ reconhecido */ }
{OR_EQ}     { /* OR_EQ reconhecido */ }
{XOR_EQ}    { /* XOR_EQ reconhecido */ }
{SHIFTR_EQ} { /* SHIFTR_EQ reconhecido */ }
{SHIFTL_EQ} { /* SHIFTL_EQ reconhecido */ }

{LPAREN}    { return LPAREN; }
{RPAREN}    { return RPAREN; }
{LBRACKET}  { /* LBRACKET reconhecido */ }
{RBRACKET}  { /* RBRACKET reconhecido */ }
{LBRACE}    { /* LBRACE reconhecido */ }
{RBRACE}    { /* RBRACE reconhecido */ }
{COMMA}     { /* COMMA reconhecido */ }
{COLON}     { /* COLON reconhecido */ }
{DOT}       { /* DOT reconhecido */ }
{SEMICOLON} { return SEMICOLON; }
{DECORATOR} { /* DECORATOR reconhecido */ }
{ARROW}     { /* ARROW reconhecido */ }

{IDENTIFIER}    { /* IDENTIFIER reconhecido */ }

{INTEGER}       { yylval.intval = convert_to_int(yytext); return INTEGER; }
{FLOAT}         { /* FLOAT reconhecido */ }
{HEX}           { /* HEX reconhecido */ }
{OCT}           { /* OCT reconhecido */ }
{BIN}           { /* BIN reconhecido */ }

{STRING_DQ}     { /* STRING_DQ reconhecido */ }
{STRING_SQ}     { /* STRING_SQ reconhecido */ }
{TRIPLE_DQ}     { /* TRIPLE_DQ reconhecido */ }
{TRIPLE_SQ}     { /* TRIPLE_SQ reconhecido */ }

{COMMENT}       { /* COMMENT reconhecido */ }
{INDENT}        { /* INDENT reconhecido */ }

/* Caractere inválido genérico */
. {
    fprintf(stderr, "ERRO LÉXICO na linha %d: Caractere desconhecido: '%s'\n", line_num, yytext);
    return ERROR;
}

%%
