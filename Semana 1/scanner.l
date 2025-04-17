%{
#include <stdio.h>
%}

/* Definições de padrões de token e ações */
%%

"hello"    {    printf("Encontrou o token 'hello'\n"); 
                printf("Hello, World!\n");  }
[ \t\n]+   { /* Ignorar espaços em branco */ }
.         { printf("Unknown character: %s\n", yytext); }

%%

/* Função auxiliar do Flex (quando termina o arquivo de entrada) */
int yywrap(void) {
    return 1;
}

/* Função principal: executa o analisador léxico */
int main(void) {
    printf("Iniciando o scanner...\n");
    yylex();  // Chama o scanner
    return 0;
}
