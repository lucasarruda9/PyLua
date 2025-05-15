%{
#include <stdio.h>
#include <stdlib.h>
#include "../ast/ast.h" 
#include <string.h>

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
%token SEMICOLON LPAREN RPAREN
%token <string> IDENTIFIER
%token ASSIGN PLUS_EQ MINUS_EQ MULT_EQ DIV_EQ FLOOR_EQ POW_EQ MOD_EQ
%token ERROR  // Token de erro

/* Precedência de operadores */
%left PLUS MINUS
%left MULTIPLY DIVIDE
%precedence NEG   /* Operador de menos unário */

/* Tipo de valor para o não-terminal "expr" */
%type <no> expr
%type <no> declaracao

%%

/* Regras de análise sintática */
input:   /* Produção vazia */
       | input line  // Pode ter várias linhas de expressão
       ;

line:    expr SEMICOLON { 
        imprimeArvore($1, 0);
        DesalocarArvore($1);
}
       | declaracao SEMICOLON { 
        imprimeArvore($1, 0);
        DesalocarArvore($1);
}
       | error SEMICOLON { 
                    printf("[ERRO SINTATICO] Erro recuperado até ';'\n"); 
                    yyerrok; 
                }
       ;

expr:    INTEGER               { $$ = CriarNoInteiro($1); }  // Cria um nó de inteiro
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