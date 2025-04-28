%{
#include <stdio.h>
#include <stdlib.h>

int yylex();  // Declaração da função yylex que será chamada pelo parser
void yyerror(const char *s);  // Função de erro para lidar com erros sintáticos
extern FILE *yyin;  // Arquivo de entrada (pode ser stdin ou um arquivo)
%}

/* Declaração de tipos para os valores */
%union {
    int intval;
}

/* Declaração de tokens */
%token <intval> INTEGER  // O token INTEGER irá carregar um valor inteiro
%token PLUS MINUS MULTIPLY DIVIDE
%token SEMICOLON LPAREN RPAREN
%token ERROR  // Token de erro

/* Precedência de operadores */
%left PLUS MINUS
%left MULTIPLY DIVIDE
%precedence NEG   /* Operador de menos unário */

/* Tipo de valor para o não-terminal "expr" */
%type <intval> expr

%%

/* Regras de análise sintática */
input:   /* Produção vazia */
       | input line  // Pode ter várias linhas de expressão
       ;

line:    expr SEMICOLON { 
                    printf("Resultado: %d\n", $1); 
                }
       | error SEMICOLON { 
                    printf("[ERRO SINTATICO] Erro recuperado até ';'\n"); 
                    yyerrok; 
                }
       ;

expr:    INTEGER               { $$ = $1; }  // Se for um número inteiro, atribui seu valor
       | LPAREN expr RPAREN    { $$ = $2; }  // Se for uma expressão entre parênteses, atribui o valor interno
       | expr PLUS expr        { $$ = $1 + $3; }  // Se for uma soma
       | expr MINUS expr       { $$ = $1 - $3; }  // Se for uma subtração
       | expr MULTIPLY expr    { $$ = $1 * $3; }  // Se for uma multiplicação
       | expr DIVIDE expr      { 
                                if ($3 == 0) {  // Verifica se a divisão é por zero
                                    yyerror("Divisão por zero");
                                    $$ = 0;  // Retorna 0 em caso de erro
                                } else {
                                    $$ = $1 / $3;  // Realiza a divisão
                                }
                              }
       | MINUS expr %prec NEG  { $$ = -$2; }  // Se for um número negativo (operador unário)
       ;

%%

/* Função para exibir erros */
void yyerror(const char *s) {
    /* Usando o parâmetro para evitar o warning */
    fprintf(stderr, "%s\n", s);
}

/* Função principal para executar o parser */
int main(int argc, char **argv) {
    /* Configura o arquivo de entrada ou usa stdin */
    if (argc > 1) {
        yyin = fopen(argv[1], "r");  // Abre o arquivo de entrada
        if (yyin == NULL) {
            printf("Erro ao abrir arquivo %s\n", argv[1]);
            return 1;
        }
    } else {
        yyin = stdin;  // Se não passar argumento, usa a entrada padrão
        printf("Digite expressões, terminadas com ';'. Pressione Ctrl+D para encerrar.\n");
    }
    
    /* Executa o parser */
    yyparse();  // Chama o parser para começar a análise
    
    /* Fecha o arquivo se necessário */
    if (argc > 1) {
        fclose(yyin);
    }
    
    return 0;
}
