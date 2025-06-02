%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/parser.tab.h"  /* Caminho ajustado para o novo local do arquivo gerado */

int convert_to_int(char *text) {
    return atoi(text);
}

int line_num = 1;
int col_num = 1;

/* Função para atualizar a posição da coluna */
void atualiza_coluna(int tamanho) {
    col_num += tamanho;
}

/* Função para tratar nova linha */
void nova_linha() {
    line_num++;
    col_num = 1;
}
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
TRIPLE_DQ   \"\"\"([^\\]|\\.)*?\"\"\"
TRIPLE_SQ   \'\'\'([^\\]|\\.)*?\'\'\'

/* Comentários */
COMMENT     #.*

/* Indentação */
INDENT      ^[ \t]+
DEDENT      ^

/* Regras */
%%

{KEYWORD}   { 
    atualiza_coluna(yyleng);
    if (strcmp(yytext, "and") == 0) return AND;
    else if (strcmp(yytext, "or") == 0) return OR;
    else if (strcmp(yytext, "not") == 0) return NOT;
    else if (strcmp(yytext, "if") == 0) return IF_KW;
    else if (strcmp(yytext, "elif") == 0) return ELIF_KW;
    else if (strcmp(yytext, "else") == 0) return ELSE_KW;
    else if (strcmp(yytext, "for") == 0) return FOR_KW;
    else if (strcmp(yytext, "while") == 0) return WHILE_KW;
    else if (strcmp(yytext, "def") == 0) return DEF;
    else if (strcmp(yytext, "return") == 0) return RETURN;
    else if (strcmp(yytext, "True") == 0) return TRUE_KW;
    else if (strcmp(yytext, "False") == 0) return FALSE_KW;
    else if (strcmp(yytext, "None") == 0) return NONE;
    else if (strcmp(yytext, "class") == 0) return CLASS;
    else if (strcmp(yytext, "import") == 0) return IMPORT;
    else if (strcmp(yytext, "from") == 0) return FROM;
    else if (strcmp(yytext, "as") == 0) return AS;
    else if (strcmp(yytext, "try") == 0) return TRY;
    else if (strcmp(yytext, "except") == 0) return EXCEPT;
    else if (strcmp(yytext, "finally") == 0) return FINALLY;
    else if (strcmp(yytext, "with") == 0) return WITH;
    else if (strcmp(yytext, "in") == 0) return IN;
    else if (strcmp(yytext, "is") == 0) return IS;
    else if (strcmp(yytext, "lambda") == 0) return LAMBDA;
    else if (strcmp(yytext, "pass") == 0) return PASS;
    else if (strcmp(yytext, "break") == 0) return BREAK;
    else if (strcmp(yytext, "continue") == 0) return CONTINUE;
    else if (strcmp(yytext, "yield") == 0) return YIELD;
    else if (strcmp(yytext, "global") == 0) return GLOBAL;
    else if (strcmp(yytext, "nonlocal") == 0) return NONLOCAL;
    else if (strcmp(yytext, "assert") == 0) return ASSERT;
    else if (strcmp(yytext, "del") == 0) return DEL;
    else if (strcmp(yytext, "raise") == 0) return RAISE;
    else return KEYWORD_TOKEN;
}

{UNDERLINE}  { atualiza_coluna(yyleng); return UNDERLINE_TOKEN; }
{ASYNC}      { atualiza_coluna(yyleng); return ASYNC_TOKEN; }
{AWAIT}      { atualiza_coluna(yyleng); return AWAIT_TOKEN; }
{MATCH}      { atualiza_coluna(yyleng); return MATCH_TOKEN; }
{CASE}       { atualiza_coluna(yyleng); return CASE_TOKEN; }
{IF}         { atualiza_coluna(yyleng); return IF_TOKEN; }
{ELIF}       { atualiza_coluna(yyleng); return ELIF_TOKEN; }
{ELSE}       { atualiza_coluna(yyleng); return ELSE_TOKEN; }
{FOR}        { atualiza_coluna(yyleng); return FOR_TOKEN; }
{WHILE}      { atualiza_coluna(yyleng); return WHILE_TOKEN; }

{PLUS}       { atualiza_coluna(yyleng); return PLUS; }
{MINUS}      { atualiza_coluna(yyleng); return MINUS; }
{MULTIPLY}   { atualiza_coluna(yyleng); return MULTIPLY; }
{DIVIDE}     { atualiza_coluna(yyleng); return DIVIDE; }
{MODULO}     { atualiza_coluna(yyleng); return MODULO_TOKEN; }
{POWER}      { atualiza_coluna(yyleng); return POWER_TOKEN; }
{FLOOR_DIV}  { atualiza_coluna(yyleng); return FLOOR_DIV_TOKEN; }
{LT}         { atualiza_coluna(yyleng); return LT_TOKEN; }
{GT}         { atualiza_coluna(yyleng); return GT_TOKEN; }
{LE}         { atualiza_coluna(yyleng); return LE_TOKEN; }
{GE}         { atualiza_coluna(yyleng); return GE_TOKEN; }
{EQ}         { atualiza_coluna(yyleng); return EQ_TOKEN; }
{NE}         { atualiza_coluna(yyleng); return NE_TOKEN; }
{NE2}        { atualiza_coluna(yyleng); return NE2_TOKEN; }
{ASSIGN}     { atualiza_coluna(yyleng); return ASSIGN; }
{PLUS_EQ}    { atualiza_coluna(yyleng); return PLUS_EQ; }
{MINUS_EQ}   { atualiza_coluna(yyleng); return MINUS_EQ; }
{MULT_EQ}    { atualiza_coluna(yyleng); return MULT_EQ; }
{DIV_EQ}     { atualiza_coluna(yyleng); return DIV_EQ; }
{MOD_EQ}     { atualiza_coluna(yyleng); return MOD_EQ; }
{FLOOR_EQ}   { atualiza_coluna(yyleng); return FLOOR_EQ; }
{POW_EQ}     { atualiza_coluna(yyleng); return POW_EQ; }
{BITAND}     { atualiza_coluna(yyleng); return BITAND_TOKEN; }
{BITOR}      { atualiza_coluna(yyleng); return BITOR_TOKEN; }
{BITXOR}     { atualiza_coluna(yyleng); return BITXOR_TOKEN; }
{BITNOT}     { atualiza_coluna(yyleng); return BITNOT_TOKEN; }
{SHIFTL}     { atualiza_coluna(yyleng); return SHIFTL_TOKEN; }
{SHIFTR}     { atualiza_coluna(yyleng); return SHIFTR_TOKEN; }
{AND_EQ}     { atualiza_coluna(yyleng); return AND_EQ_TOKEN; }
{OR_EQ}      { atualiza_coluna(yyleng); return OR_EQ_TOKEN; }
{XOR_EQ}     { atualiza_coluna(yyleng); return XOR_EQ_TOKEN; }
{SHIFTR_EQ}  { atualiza_coluna(yyleng); return SHIFTR_EQ_TOKEN; }
{SHIFTL_EQ}  { atualiza_coluna(yyleng); return SHIFTL_EQ_TOKEN; }

{LPAREN}     { atualiza_coluna(yyleng); return LPAREN; }
{RPAREN}     { atualiza_coluna(yyleng); return RPAREN; }
{LBRACKET}   { atualiza_coluna(yyleng); return LBRACKET_TOKEN; }
{RBRACKET}   { atualiza_coluna(yyleng); return RBRACKET_TOKEN; }
{LBRACE}     { atualiza_coluna(yyleng); return LBRACE_TOKEN; }
{RBRACE}     { atualiza_coluna(yyleng); return RBRACE_TOKEN; }
{COMMA}      { atualiza_coluna(yyleng); return COMMA_TOKEN; }
{COLON}      { atualiza_coluna(yyleng); return COLON_TOKEN; }
{DOT}        { atualiza_coluna(yyleng); return DOT_TOKEN; }
{DECORATOR}  { atualiza_coluna(yyleng); return DECORATOR_TOKEN; }
{ARROW}      { atualiza_coluna(yyleng); return ARROW_TOKEN; }

{IDENTIFIER} { 
    atualiza_coluna(yyleng); 
    yylval.string = strdup(yytext); 
    return IDENTIFIER; 
}

{INTEGER}    { 
    atualiza_coluna(yyleng); 
    yylval.intval = convert_to_int(yytext); 
    return INTEGER; 
}

{FLOAT}      { 
    atualiza_coluna(yyleng); 
    yylval.floatval = atof(yytext); 
    return FLOAT_TOKEN; 
}

{HEX}        { 
    atualiza_coluna(yyleng); 
    yylval.intval = (int)strtol(yytext+2, NULL, 16); 
    return HEX_TOKEN; 
}

{OCT}        { 
    atualiza_coluna(yyleng); 
    yylval.intval = (int)strtol(yytext+2, NULL, 8); 
    return OCT_TOKEN; 
}

{BIN}        { 
    atualiza_coluna(yyleng); 
    yylval.intval = (int)strtol(yytext+2, NULL, 2); 
    return BIN_TOKEN; 
}

{STRING_DQ}  { 
    atualiza_coluna(yyleng); 
    yylval.string = strdup(yytext); 
    return STRING_DQ_TOKEN; 
}

{STRING_SQ}  { 
    atualiza_coluna(yyleng); 
    yylval.string = strdup(yytext); 
    return STRING_SQ_TOKEN; 
}

{TRIPLE_DQ}  { 
    char *texto = strdup(yytext);
    int i;
    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == '\n') {
            nova_linha();
        } else {
            col_num++;
        }
    }
    yylval.string = texto;
    return TRIPLE_DQ_TOKEN; 
}

{TRIPLE_SQ}  { 
    char *texto = strdup(yytext);
    int i;
    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == '\n') {
            nova_linha();
        } else {
            col_num++;
        }
    }
    yylval.string = texto;
    return TRIPLE_SQ_TOKEN; 
}

{COMMENT}    { 
    atualiza_coluna(yyleng); 
    return COMMENT_TOKEN; 
}

{INDENT}     {
    atualiza_coluna(yyleng);
    yylval.intval = yyleng;  /* Armazena o tamanho da indentação */
    return INDENT_TOKEN;
}

\n           { 
    nova_linha(); 
    return NEWLINE; 
}

[ \t\r]+     { 
    atualiza_coluna(yyleng); 
    /* ignora outros espaços em branco */ 
}

.            { 
    fprintf(stderr, "ERRO LÉXICO na linha %d, coluna %d: Caractere desconhecido: '%s'\n", 
            line_num, col_num, yytext); 
    atualiza_coluna(yyleng);
    return ERROR; 
}

%%
