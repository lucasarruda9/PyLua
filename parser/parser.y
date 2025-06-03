%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include "../ast/ast.h" 
#include "../tabela/tabela.h"
#include "../gerador_codigo_final/gerador_codigo_final.h"  // Modificado

int yylex();  // Declaração da função yylex que será chamada pelo parser
void yyerror(const char *s);  // Função de erro para lidar com erros sintáticos
extern FILE *yyin;  // Arquivo de entrada (pode ser stdin ou um arquivo)
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
        gerarCodigoLua($1);  // Modificado
        // Avaliação da expressão vai aqui
        int resultado = avaliarArvore($1);
        printf("Resultado: %d\n", resultado);
        DesalocarArvore($1);
        $$ = NULL;
}
       | declaracao NEWLINE { 
        imprimeArvore($1, 0);
        gerarCodigoLua($1);  // Modificado
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

/* Função para exibir erros */
void yyerror(const char *s) {
    /* Usando o parâmetro para evitar o warning */
    fprintf(stderr, "%s\n", s);
}

/* Função principal para executar o parser */
int main(int argc, char **argv) {
    inicializarTabela();
    
    char output_filename[256];
    FILE* luaOutput;
    
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            printf("Erro ao abrir arquivo %s\n", argv[1]);
            return 1;
        }
        
        // Extrair nome base do arquivo de entrada
        char *base_name = strrchr(argv[1], '/');
        if (!base_name) base_name = strrchr(argv[1], '\\');
        if (!base_name) 
            base_name = argv[1];
        else 
            base_name++;
            
        // Criar nome do arquivo de saída
        snprintf(output_filename, sizeof(output_filename), 
                "saida_lua/%.*s.lua",  // Modificado: output_lua -> saida_lua
                (int)(strrchr(base_name, '.') - base_name), 
                base_name);
    } else {
        yyin = stdin;
        snprintf(output_filename, sizeof(output_filename), 
                "saida_lua/output.lua");  
    }
    
    // Abrir arquivo de saída
    luaOutput = fopen(output_filename, "w");
    if (!luaOutput) {
        printf("Erro ao criar arquivo de saída: %s\n", output_filename);
        return 1;
    }
    
    inicializarGerador(luaOutput);  // Modificado
    yyparse();
    finalizarGerador();  // Modificado
    
    if (argc > 1) {
        fclose(yyin);
    }
    
    return 0;
}