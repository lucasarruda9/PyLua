%{
#include <stdio.h>
#include <stdlib.h>
#include "../ast/ast.h"  // Caminho correto para o arquivo AST

// Funções de criação de nós da AST
ASTNode* create_unary_op_node(char op, ASTNode* expr);
ASTNode* create_binary_op_node(char op, ASTNode* left, ASTNode* right);

int yylex();  // Declaração da função yylex que será chamada pelo parser
void yyerror(const char *s);  // Função de erro para lidar com erros sintáticos
extern FILE *yyin;  // Arquivo de entrada (pode ser stdin ou um arquivo)
%}

/* Declaração de tipos para os valores */
%union {
    int intval;      // Para valores inteiros
    ASTNode* node;   // Para armazenar nós da AST
}

/* Declaração de tokens */
%token <intval> INTEGER
%token PLUS MINUS MULTIPLY DIVIDE
%token SEMICOLON LPAREN RPAREN
%token ERROR  // Token de erro

/* Precedência de operadores */
%left PLUS MINUS
%left MULTIPLY DIVIDE
%precedence NEG   /* Operador de menos unário */

/* Tipo de valor para o não-terminal "expr" */
%type <node> expr

%%

/* Regras de análise sintática */
input:   /* Produção vazia */
       | input line  // Pode ter várias linhas de expressão
       ;

line:    expr SEMICOLON { 
                    printf("Resultado: %d\n", $1->value); 
                }
       | error SEMICOLON { 
                    printf("[ERRO SINTATICO] Erro recuperado até ';'\n"); 
                    yyerrok; 
                }
       ;

expr:    INTEGER               { $$ = create_literal_node($1); }  // Se for um número inteiro, cria um nó de literal
       | LPAREN expr RPAREN    { $$ = $2; }  // Se for uma expressão entre parênteses, retorna a subexpressão
       | expr PLUS expr        { $$ = create_binary_op_node('+', $1, $3); }  // Se for uma soma, cria um nó binário
       | expr MINUS expr       { $$ = create_binary_op_node('-', $1, $3); }  // Se for uma subtração, cria um nó binário
       | expr MULTIPLY expr    { $$ = create_binary_op_node('*', $1, $3); }  // Se for uma multiplicação, cria um nó binário
       | expr DIVIDE expr      { 
                                if ($3 == 0) {  // Verifica se a divisão é por zero
                                    yyerror("Divisão por zero");
                                    $$ = create_literal_node(0);  // Retorna 0 em caso de erro
                                } else {
                                    $$ = create_binary_op_node('/', $1, $3);  // Realiza a divisão
                                }
                              }
       | MINUS expr %prec NEG  { $$ = create_unary_op_node('-', $2); }  // Se for um número negativo (operador unário)
       ;

%%

/* Função para exibir erros */
void yyerror(const char *s) {
    fprintf(stderr, "%s\n", s);
}

/* Função principal para executar o parser */
int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            printf("Erro ao abrir arquivo %s\n", argv[1]);
            return 1;
        }
    } else {
        yyin = stdin;
        printf("Digite expressões, terminadas com ';'. Pressione Ctrl+D para encerrar.\n");
    }
    
    yyparse();  // Inicia o parser
    
    if (argc > 1) {
        fclose(yyin);
    }
    
    return 0;
}
