%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/parser.tab.h"

int convert_to_int(char *text) {
    return atoi(text);
}

int line_num = 1;
int col_num = 1;

void atualiza_coluna() {
    col_num += yyleng;
}

void reset_coluna() {
    col_num = 1;
}

int nivel_indentacao = 0;
int pilha_indentacao[100];
int topo_pilha = 0;

void inicializa_pilha() {
    pilha_indentacao[0] = 0;
    topo_pilha = 0;
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
INDENT      ^[ \t]+

/* Regras */
%%

{KEYWORD}   { atualiza_coluna(); yylval.string = strdup(yytext); return KEYWORD; }

{IF}        { atualiza_coluna(); return IF; }
{ELIF}      { atualiza_coluna(); return ELIF; }
{ELSE}      { atualiza_coluna(); return ELSE; }
{MATCH}     { atualiza_coluna(); return MATCH; }
{CASE}      { atualiza_coluna(); return CASE; }

{FOR}       { atualiza_coluna(); return FOR; }
{WHILE}     { atualiza_coluna(); return WHILE; }

{LPAREN}    { atualiza_coluna(); return LPAREN; }
{RPAREN}    { atualiza_coluna(); return RPAREN; }
{LBRACKET}  { atualiza_coluna(); return LBRACKET; }
{RBRACKET}  { atualiza_coluna(); return RBRACKET; }
{LBRACE}    { atualiza_coluna(); return LBRACE; }
{RBRACE}    { atualiza_coluna(); return RBRACE; }
{COMMA}     { atualiza_coluna(); return COMMA; }
{COLON}     { atualiza_coluna(); return COLON; }
{DOT}       { atualiza_coluna(); return DOT; }
{DECORATOR} { atualiza_coluna(); return DECORATOR; }
{ARROW}     { atualiza_coluna(); return ARROW; }

{IDENTIFIER} { 
    atualiza_coluna(); 
    yylval.string = strdup(yytext); 
    return IDENTIFIER; 
}

{INTEGER}   { 
    atualiza_coluna(); 
    yylval.intval = convert_to_int(yytext); 
    return INTEGER; 
}

{FLOAT}     { 
    atualiza_coluna(); 
    yylval.string = strdup(yytext); 
    return FLOAT; 
}

{HEX}       { 
    atualiza_coluna(); 
    yylval.string = strdup(yytext); 
    return HEX; 
}

{OCT}       { 
    atualiza_coluna(); 
    yylval.string = strdup(yytext); 
    return OCT; 
}

{BIN}       { 
    atualiza_coluna(); 
    yylval.string = strdup(yytext); 
    return BIN; 
}

{STRING_DQ} { 
    atualiza_coluna(); 
    yylval.string = strdup(yytext); 
    return STRING_DQ; 
}

{STRING_SQ} { 
    atualiza_coluna(); 
    yylval.string = strdup(yytext); 
    return STRING_SQ; 
}

{TRIPLE_DQ} { 
    char *p = yytext;
    while (*p) {
        if (*p == '\n') {
            line_num++;
            reset_coluna();
        } else {
            col_num++;
        }
        p++;
    }
    yylval.string = strdup(yytext); 
    return TRIPLE_DQ; 
}

{TRIPLE_SQ} { 
    char *p = yytext;
    while (*p) {
        if (*p == '\n') {
            line_num++;
            reset_coluna();
        } else {
            col_num++;
        }
        p++;
    }
    yylval.string = strdup(yytext); 
    return TRIPLE_SQ; 
}

{COMMENT}   { 
    atualiza_coluna(); 
    return COMMENT; 
}

{INDENT}    {
    if (yytext[0] == '\n') {
        line_num++;
        reset_coluna();
    } else {
        atualiza_coluna();
    }
    
    int espacos = 0;
    for (int i = 0; i < yyleng; i++) {
        if (yytext[i] == ' ') {
            espacos++;
        } else if (yytext[i] == '\t') {
            espacos += 8 - (espacos % 8);
        }
    }
    
    if (espacos > pilha_indentacao[topo_pilha]) {
        topo_pilha++;
        pilha_indentacao[topo_pilha] = espacos;
        return INDENT;
    } else if (espacos < pilha_indentacao[topo_pilha]) {
        int dedents = 0;
        while (topo_pilha > 0 && espacos < pilha_indentacao[topo_pilha]) {
            topo_pilha--;
            dedents++;
        }
        
        if (espacos != pilha_indentacao[topo_pilha]) {
            fprintf(stderr, "ERRO LÉXICO na linha %d, coluna %d: Indentação inconsistente\n", line_num, col_num);
            return ERROR;
        }
        
        return DEDENT;
    }
}

\n          { 
    line_num++; 
    reset_coluna(); 
    return NEWLINE; 
}

[ \t\r]+    { atualiza_coluna(); }

.           { 
    fprintf(stderr, "ERRO LÉXICO na linha %d, coluna %d: Caractere desconhecido: '%s'\n", 
            line_num, col_num, yytext); 
    atualiza_coluna();
    return ERROR; 
}

%%
