%{
#include <stdio.h>
%}

/* Definições de padrões de token e ações */
%%

"if"        { printf("KW_IF\n"); }
"else"      { printf("KW_ELSE\n"); }
"elif"      { printf("KW_ELIF\n"); }
"while"     { printf("KW_WHILE\n"); }
"for"       { printf("KW_FOR\n"); }
"in"        { printf("KW_IN\n"); }
"def"       { printf("KW_DEF\n"); }
"return"    { printf("KW_RETURN\n"); }
"True"      { printf("KW_TRUE\n"); }
"False"     { printf("KW_FALSE\n"); }
"None"      { printf("KW_NONE\n"); }

"+"         { printf("OPERATOR(%s)\n", yytext); }
"-"         { printf("OPERATOR(%s)\n", yytext); }
"*"         { printf("OPERATOR(%s)\n", yytext); }
"/"         { printf("OPERATOR(%s)\n", yytext); }
"="         { printf("OPERATOR(%s)\n", yytext); }
"=="        { printf("OPERATOR(%s)\n", yytext); }
"!="        { printf("OPERATOR(%s)\n", yytext); }
"<"         { printf("OPERATOR(%s)\n", yytext); }
">"         { printf("OPERATOR(%s)\n", yytext); }
"<="        { printf("OPERATOR(%s)\n", yytext); }
">="        { printf("OPERATOR(%s)\n", yytext); }

"("         { printf("DELIM(%s)\n", yytext); }
")"         { printf("DELIM(%s)\n", yytext); }
"["         { printf("DELIM(%s)\n", yytext); }
"]"         { printf("DELIM(%s)\n", yytext); }
"{"         { printf("DELIM(%s)\n", yytext); }
"}"         { printf("DELIM(%s)\n", yytext); }
":"         { printf("DELIM(%s)\n", yytext); }
","         { printf("DELIM(%s)\n", yytext); }
"."         { printf("DELIM(%s)\n", yytext); }

"#".*       { /* Ignorar comentários de linha */ }

\"([^\"\n\\]|\\.)*\"  { printf("STRING(%s)\n", yytext); }
'([^'\n\\]|\\.)*'     { printf("STRING(%s)\n", yytext); }

[0-9]+                { printf("NUMBER(%s)\n", yytext); }
[0-9]+\.[0-9]+        { printf("NUMBER(%s)\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*  { printf("IDENT(%s)\n", yytext); }

[ \t\n]+  { /* Ignorar espaços em branco */ }

.  { printf("UNKNOWN(%s)\n", yytext); }

%%

/* Função auxiliar do Flex (quando termina o arquivo de entrada) */
int yywrap(void) {
    return 1;
}

/* Função principal: executa o analisador léxico */
int main(void) {
    yylex();
    return 0;
}

