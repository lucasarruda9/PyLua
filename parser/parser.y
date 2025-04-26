%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
extern FILE *yyin;

%}

/* Declaração de tipos */
%union {
    int intval;
}

/* Declaração de tokens */
%token <intval> INTEGER
%token PLUS MINUS MULTIPLY DIVIDE
%token SEMICOLON LPAREN RPAREN
%token ERROR

/* Precedência de operadores (do mais baixo para o mais alto) */
%left PLUS MINUS
%left MULTIPLY DIVIDE
%precedence NEG   /* menos unário */

/* Tipo do valor não-terminal */
%type <intval> expr

%%

input:   /* vazio */
       | input line
       ;

line:    expr SEMICOLON { printf("Resultado: %d\n", $1); }
       | error SEMICOLON { printf("[ERRO SINTATICO] Erro recuperado ate ';'\n"); yyerrok; }
       ;

expr:    INTEGER               { $$ = $1; }
       | LPAREN expr RPAREN    { $$ = $2; }
       | expr PLUS expr        { $$ = $1 + $3; }
       | expr MINUS expr       { $$ = $1 - $3; }
       | expr MULTIPLY expr    { $$ = $1 * $3; }
       | expr DIVIDE expr      { 
                                if ($3 == 0) {
                                    yyerror("divisão por zero");
                                    $$ = 0;
                                } else {
                                    $$ = $1 / $3; 
                                }
                              }
       | MINUS expr %prec NEG  { $$ = -$2; }
       ;

%%

void yyerror(const char *s) {
    /* Usando o parâmetro para evitar o warning */
    fprintf(stderr, "%s\n", s);
}

int main(int argc, char **argv) {
    /* Configura o arquivo de entrada ou usa stdin */
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            printf("Erro ao abrir arquivo %s\n", argv[1]);
            return 1;
        }
    } else {
        yyin = stdin;
        printf("Digite expressoes, terminadas com ';'. Pressione Ctrl+D para encerrar.\n");
    }
    
    /* Executa o parser */
    yyparse();
    
    /* Fecha o arquivo se necessário */
    if (argc > 1) {
        fclose(yyin);
    }
    
    return 0;
} 