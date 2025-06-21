%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/parser.tab.h"

int convert_to_int(char *text) {
    return atoi(text);
}

int line_num = 1;
int pilha_indentacao[100];
int topo_pilha = 0;


void inicializa_pilha() {
    pilha_indentacao[0] = 0;
    topo_pilha = 0;
}
%}

%option noyywrap noinput nomain

%x IDENT
/* Definição de tokens */

/* Palavras-chave do Python */
KEYWORD     and|as|assert|break|class|continue|del|except|finally|from|global|import|in|is|lambda|None|nonlocal|not|or|pass|raise|return|try|with|yield

/* Booleanos */
TRUE        "True"
FALSE       "False"

/* Definição de função */
DEF         "def"
RETURN      "return"

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

/* Regras */
%%

{TRUE}      { yylval.intval = 1; return TRUE; }
{FALSE}     { yylval.intval = 0; return FALSE; }

{DEF}       { return DEF; }
{RETURN}    { return RETURN; }

{KEYWORD}   { yylval.string = strdup(yytext); return KEYWORD; }

{IF}        { return IF; }
{ELIF}      { return ELIF; }
{ELSE}      { return ELSE; }
{MATCH}     { return MATCH; }
{CASE}      { return CASE; }

{FOR}       { return FOR; }
{WHILE}     { return WHILE; }

{POWER}     { return POWER; }
{FLOOR_DIV} { return FLOOR_DIV; }
{PLUS_EQ}   { return PLUS_EQ; }
{MINUS_EQ}  { return MINUS_EQ; }
{MULT_EQ}   { return MULT_EQ; }
{DIV_EQ}    { return DIV_EQ; }
{MOD_EQ}    { return MOD_EQ; }
{FLOOR_EQ}  { return FLOOR_EQ; }
{POW_EQ}    { return POW_EQ; }
{EQ}        { return EQ; }
{NE}        { return NE; }
{NE2}       { return NE2; }
{LE}        { return LE; }
{GE}        { return GE; }
{LT}        { return LT; }
{GT}        { return GT; }
{PLUS}      { return PLUS; }
{MINUS}     { return MINUS; }
{MULTIPLY}  { return MULTIPLY; }
{DIVIDE}    { return DIVIDE; }
{MODULO}    { return MODULO; }
{ASSIGN}    { return ASSIGN; }
{SHIFTL}    { return SHIFTL; }
{SHIFTR}    { return SHIFTR; }
{AND_EQ}    { return AND_EQ; }
{OR_EQ}     { return OR_EQ; }
{XOR_EQ}    { return XOR_EQ; }
{SHIFTR_EQ} { return SHIFTR_EQ; }
{SHIFTL_EQ} { return SHIFTL_EQ; }
{BITAND}    { return BITAND; }
{BITOR}     { return BITOR; }
{BITXOR}    { return BITXOR; }
{BITNOT}    { return BITNOT; }

{LPAREN}    { return LPAREN; }
{RPAREN}    { return RPAREN; }
{LBRACKET}  { return LBRACKET; }
{RBRACKET}  { return RBRACKET; }
{LBRACE}    { return LBRACE; }
{RBRACE}    { return RBRACE; }
{COMMA}     { return COMMA; }
{COLON}     { return COLON; }
{DOT}       { return DOT; }
{DECORATOR} { return DECORATOR; }
{ARROW}     { return ARROW; }

{IDENTIFIER} {  
    yylval.string = strdup(yytext); 
    return IDENTIFIER; 
}

{INTEGER}   { 
    yylval.intval = convert_to_int(yytext); 
    return INTEGER; 
}

{FLOAT}     { 
    yylval.floatval = atof(yytext); 
    return FLOAT; 
}

{HEX}       { 
    yylval.string = strdup(yytext); 
    return HEX; 
}

{OCT}       { 
    yylval.string = strdup(yytext); 
    return OCT; 
}

{BIN}       { 
    yylval.string = strdup(yytext); 
    return BIN; 
}

{STRING_DQ} { 
    yylval.string = strdup(yytext); 
    return STRING_DQ; 
}

{STRING_SQ} { 
    yylval.string = strdup(yytext); 
    return STRING_SQ; 
}

{TRIPLE_DQ} { 
    char *p = yytext;
    while (*p) {
        if (*p == '\n') {
            line_num++;
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
        } 
        p++;
    }
    yylval.string = strdup(yytext); 
    return TRIPLE_SQ; 
}

{COMMENT}   { 
    /* Ignorar comentários - não retornar token */
}



\n {
    line_num++;
    // Após uma quebra de linha, verificar a próxima indentação
    BEGIN(IDENT);
    return NEWLINE;
}


<IDENT>^[ \t]+ {
    int espacos = 0;
    for (int i = 0; i < yyleng; i++) {
        if (yytext[i] == ' ') espacos++;
        else if (yytext[i] == '\t') espacos += 4; // Ajuste conforme necessário
    }
    
    if (espacos > pilha_indentacao[topo_pilha]) {
        pilha_indentacao[++topo_pilha] = espacos;
        BEGIN(INITIAL);
        return INDENT;
    } else if (espacos < pilha_indentacao[topo_pilha]) {
        while(topo_pilha > 0 && espacos < pilha_indentacao[topo_pilha]){
            topo_pilha--;
        }
        BEGIN(INITIAL);
        return DEDENT;
    }
    BEGIN(INITIAL);
}

<IDENT>^[^ \t\n] {
    unput(yytext[0]); 
    if (pilha_indentacao[topo_pilha] > 0) {
        // Se estávamos indentados, gera DEDENT
        topo_pilha--;
        BEGIN(INITIAL);
        return DEDENT;
    }
    BEGIN(INITIAL);
}

[ \t\r]+    {}
.           {
    fprintf(stderr, "ERRO LÉXICO na linha %d, Caractere desconhecido: '%s'\n",
            line_num,yytext);

    return ERROR;
}
<<EOF>>     {

    if (topo_pilha > 0) {
        topo_pilha--;
        return DEDENT;
    }
    yyterminate();  
}
%%
