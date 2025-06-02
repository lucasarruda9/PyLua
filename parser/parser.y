%{
#include <stdio.h>
#include <stdlib.h>
#include "../ast/ast.h"
#include "../tabela/tabela.h"
#include <string.h>

int yylex();  // Declaração da função yylex que será chamada pelo parser
void yyerror(const char *s);  // Função de erro para lidar com erros sintáticos
extern FILE *yyin;  // Arquivo de entrada (pode ser stdin ou um arquivo)
extern int line_num;  // Linha atual (definida no scanner)
extern int col_num;   // Coluna atual (definida no scanner)
extern void inicializa_pilha();  // Declaração da função de inicialização da pilha de indentação

void yyerror(const char *s) {
    fprintf(stderr, "[ERRO SINTATICO] %s na linha %d, coluna %d\n", s, line_num, col_num);
}
%}

/* Declaração de tipos para os valores */
%union {
    int intval;
    struct Arvore *no;
    char *string;
}

/* Declaração de tokens */
%token <intval> INTEGER  // O token INTEGER irá carregar um valor inteiro
%token PLUS MINUS MULTIPLY DIVIDE
%token LPAREN RPAREN
%token <string> IDENTIFIER
%token ASSIGN PLUS_EQ MINUS_EQ MULT_EQ DIV_EQ FLOOR_EQ POW_EQ MOD_EQ
%token ERROR  // Token de erro
%token NEWLINE
%token <string> KEYWORD
%token IF ELIF ELSE MATCH CASE
%token FOR WHILE
%token LBRACKET RBRACKET LBRACE RBRACE
%token COMMA COLON DOT DECORATOR ARROW
%token <string> FLOAT HEX OCT BIN
%token <string> STRING_DQ STRING_SQ TRIPLE_DQ TRIPLE_SQ
%token COMMENT
%token INDENT DEDENT

/* Precedência de operadores */
%left PLUS MINUS
%left MULTIPLY DIVIDE
%precedence NEG   /* Operador de menos unário */

/* Tipo de valor para o não-terminal "expr" */
%type <no> expr
%type <no> declaracao
%type <no> line

%%

/* Regras de análise sintática */
input:   /* Produção vazia */
       | input line  // Pode ter várias linhas de expressão
       ;

line:    expr NEWLINE { 
        imprimeArvore($1, 0);
        // Avaliação da expressão vai aqui
        int resultado = avaliarArvore($1);
        printf("Resultado: %d\n", resultado);
        DesalocarArvore($1);
        $$ = NULL;
}
       | declaracao NEWLINE { 
        imprimeArvore($1, 0);
        // Avalia e executa a atribuição na tabela de símbolos
        if ($1->tipo == NoAtribuicao) {
            if ($1->esquerdo->tipo == NoVariavel) {
                int resultado = avaliarArvore($1);
                printf("Resultado da atribuição: %d\n", resultado);
            }
        }
        DesalocarArvore($1);
        $$ = NULL;
}
       | expr /* sem quebra de linha ao final */ { 
        imprimeArvore($1, 0);
        // Avaliação da expressão vai aqui
        int resultado = avaliarArvore($1);
        printf("Resultado: %d\n", resultado);
        DesalocarArvore($1);
        $$ = NULL;
}
       | declaracao /* sem quebra de linha ao final */ { 
        imprimeArvore($1, 0);
        // Avalia e executa a atribuição na tabela de símbolos
        if ($1->tipo == NoAtribuicao) {
            if ($1->esquerdo->tipo == NoVariavel) {
                int resultado = avaliarArvore($1);
                printf("Resultado da atribuição: %d\n", resultado);
            }
        }
        DesalocarArvore($1);
        $$ = NULL;
}
       | NEWLINE { $$ = NULL; } /* Aceitar linhas em branco */
       | error NEWLINE { 
                    printf("[ERRO SINTATICO] Erro recuperado até o final da linha\n"); 
                    yyerrok;
                    $$ = NULL;
                }
       ;

expr:    INTEGER               { $$ = CriarNoInteiro($1); }  // Cria um nó de inteiro
       | IDENTIFIER            { 
                               Simbolo *s = buscarSimbolo($1);
                               if (s == NULL) {
                                   printf("[AVISO] Variável '%s' não declarada\n", $1);
                                   inserirSimbolo($1, TIPO_INT);
                               }
                               $$ = CriarNoVariavel($1); 
                              }
       | LPAREN expr RPAREN    { $$ = $2; }  // Expressão entre parênteses
       | expr PLUS expr        { $$ = CriarNoOperador($1, $3, '+'); }  // Cria nó de soma
       | expr MINUS expr       { $$ = CriarNoOperador($1, $3, '-'); }  // Cria nó de subtração
       | expr MULTIPLY expr    { $$ = CriarNoOperador($1, $3, '*'); }  // Cria nó de multiplicação
       | expr DIVIDE expr      { 
                                if ($3->valor == 0 && $3->tipo == NoLiteral) {  
                                    yyerror("Divisão por zero");
                                    $$ = CriarNoInteiro(0);  // Retorna 0 em caso de erro
                                } else {
                                    $$ = CriarNoOperador($1, $3, '/');
                                }
                              }
       | MINUS expr %prec NEG  { $$ = CriarNoOperador($2, NULL, '-'); }  // Operador unário
       ;

declaracao:  IDENTIFIER ASSIGN expr { 
            $$ = CriaNoAtribuicao(CriarNoVariavel($1), $3);
} 
       | IDENTIFIER PLUS_EQ expr { 
            $$ = CriaNoAtribuicao(CriarNoVariavel($1), CriarNoOperador(CriarNoVariavel($1), $3, '+'));
} 
       | IDENTIFIER MINUS_EQ expr { 
            $$ = CriaNoAtribuicao(CriarNoVariavel($1), CriarNoOperador(CriarNoVariavel($1), $3, '-'));
}  
       | IDENTIFIER MULT_EQ expr { 
            $$ = CriaNoAtribuicao(CriarNoVariavel($1), CriarNoOperador(CriarNoVariavel($1), $3, '*'));
} 
       | IDENTIFIER DIV_EQ expr { 
            $$ = CriaNoAtribuicao(CriarNoVariavel($1), CriarNoOperador(CriarNoVariavel($1), $3, '/'));
}  
       | IDENTIFIER MOD_EQ expr { 
            $$ = CriaNoAtribuicao(CriarNoVariavel($1), CriarNoOperador(CriarNoVariavel($1), $3, '%'));
} 
       | IDENTIFIER FLOOR_EQ expr { 
            $$ = CriaNoAtribuicao(CriarNoVariavel($1), CriarNoOperador(CriarNoVariavel($1), $3, 'b'));
}  
       | IDENTIFIER POW_EQ expr { 
            $$ = CriaNoAtribuicao(CriarNoVariavel($1), CriarNoOperador(CriarNoVariavel($1), $3, 'a'));
} 
       ;
%%

/* Função principal para executar o parser */
int main(int argc, char **argv) {
    /* Inicializa a tabela de símbolos */
    inicializarTabela();
    
    /* Inicializa a pilha de indentação */
    inicializa_pilha();
    
    /* Configura o arquivo de entrada ou usa stdin */
    if (argc > 1) {
        yyin = fopen(argv[1], "r");  // Abre o arquivo de entrada
        if (yyin == NULL) {
            printf("Erro ao abrir arquivo %s\n", argv[1]);
            return 1;
        }
    } else {
        yyin = stdin;  // Se não passar argumento, usa a entrada padrão
        printf("Digite expressões em Python. Pressione Ctrl+D (Linux/Mac) ou Ctrl+Z seguido de Enter (Windows) para encerrar.\n");
    }
    
    /* Executa o parser */
    yyparse();  // Chama o parser para começar a análise
    
    /* Imprime a tabela de símbolos */
    imprimirTabela();
    
    /* Libera a tabela de símbolos */
    liberarTabela();
    
    /* Fecha o arquivo se necessário */
    if (argc > 1) {
        fclose(yyin);
    }
    
    return 0;
}
