%{
#include <stdio.h>
#include <stdlib.h>
#include "../ast/ast.h"
#include "../tabela/tabela.h"
#include "../gerador_codigo_final/gerador_codigo_final.h"
#include <string.h>

int yylex();  // Declaração da função yylex que será chamada pelo parser
void yyerror(const char *s);  // Função de erro para lidar com erros sintáticos
extern FILE *yyin;  // Arquivo de entrada (pode ser stdin ou um arquivo)
extern int line_num;  // Linha atual (definida no scanner)
extern int col_num;   // Coluna atual (definida no scanner)
extern void inicializa_pilha();  // Declaração da função de inicialização da pilha de indentação

// Variáveis globais para controle da geração de código
FILE *arquivo_lua = NULL;
int gerar_codigo_lua = 0;

void yyerror(const char *s) {
    fprintf(stderr, "[ERRO SINTATICO] %s na linha %d, coluna %d\n", s, line_num, col_num);
}
%}

/* Declaração de tipos para os valores */
%union {
    int intval;
    struct Arvore *no;
    char *string;
    struct ListaNo *lista;
}

/* Declaração de tokens */
%token <intval> INTEGER  // O token INTEGER irá carregar um valor inteiro
%token PLUS MINUS MULTIPLY DIVIDE MODULO
%token POWER FLOOR_DIV
%token LT GT LE GE EQ NE NE2
%token LPAREN RPAREN
%token <string> IDENTIFIER
%token ASSIGN PLUS_EQ MINUS_EQ MULT_EQ DIV_EQ FLOOR_EQ POW_EQ MOD_EQ
%token BITAND BITOR BITXOR BITNOT
%token SHIFTL SHIFTR AND_EQ OR_EQ XOR_EQ SHIFTR_EQ SHIFTL_EQ
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
%token DEF RETURN

/* Precedência de operadores */
%left BITOR
%left BITXOR
%left BITAND
%left EQ NE NE2
%left LT GT LE GE
%left SHIFTL SHIFTR
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO FLOOR_DIV
%right POWER
%precedence NEG   /* Operador de menos unário */
%precedence BITNOT   /* Operador bitwise NOT unário */

/* Tipo de valor para o não-terminal "expr" */
%type <no> expr
%type <no> declaracao
%type <no> line
%type <no> condicional
%type <lista> bloco
%type <lista> linhas
%type <no> funcao
%type <lista> parametros lista_parametros
%type <lista> lista_elementos

%%

/* Regras de análise sintática */
input:   /* Produção vazia */
       | input line  
       | input DEDENT  // Dentação
       | input INDENT  // identação
       ;

line:    expr NEWLINE {
        imprimeArvore($1, 0);
        // Avaliação da expressão
        int resultado = avaliarArvore($1);
        printf("Resultado: %d\n", resultado);

        // Gera código Lua se habilitado
        if (gerar_codigo_lua && arquivo_lua) {
            gerarCodigoLua($1);
        }

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

        // Gera código Lua se habilitado
        if (gerar_codigo_lua && arquivo_lua) {
            gerarCodigoLua($1);
        }

        DesalocarArvore($1);
        $$ = NULL;
}
       | expr /* sem quebra de linha ao final */ {
        imprimeArvore($1, 0);
        // Avaliação da expressão
        int resultado = avaliarArvore($1);
        printf("Resultado: %d\n", resultado);

        // Gera código Lua se habilitado
        if (gerar_codigo_lua && arquivo_lua) {
            gerarCodigoLua($1);
        }

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

        // Gera código Lua se habilitado
        if (gerar_codigo_lua && arquivo_lua) {
            gerarCodigoLua($1);
        }

        DesalocarArvore($1);
        $$ = NULL;
}
        | funcao NEWLINE {
            imprimeArvore($1, 0);
            if (gerar_codigo_lua && arquivo_lua) {
                gerarCodigoLua($1);
            }
            DesalocarArvore($1);
            $$ = NULL;
        }
        | condicional NEWLINE {
            imprimeArvore($1, 0);
            // Avaliar a semântica do condicional
            int resultado = avaliarArvore($1);
            printf("Resultado do condicional: %d\n", resultado);
            DesalocarArvore($1);
            $$ = NULL;
        }
    | condicional {
            imprimeArvore($1, 0);
            // Avaliar a semântica do condicional
            int resultado = avaliarArvore($1);
            printf("Resultado do condicional: %d\n", resultado);
            DesalocarArvore($1);
            $$ = NULL;
        }
       | comando_while NEWLINE {
            imprimeArvore($1, 0);
            if (gerar_codigo_lua && arquivo_lua) {
                gerarCodigoLua($1);
            }
            DesalocarArvore($1);
            $$ = NULL;
        }
       | comando_for NEWLINE {
            imprimeArvore($1, 0);
            if (gerar_codigo_lua && arquivo_lua) {
                gerarCodigoLua($1);
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
       | expr PLUS expr        { $$ = CriarNoOperador($1, $3, '+'); }  // Soma
       | expr MINUS expr       { $$ = CriarNoOperador($1, $3, '-'); }  // Subtração
       | expr MULTIPLY expr    { $$ = CriarNoOperador($1, $3, '*'); }  // Multiplicação
       | expr DIVIDE expr      {
                                if ($3->valor == 0 && $3->tipo == NoLiteral) {
                                    yyerror("Divisão por zero");
                                    $$ = CriarNoInteiro(0);
                                } else {
                                    $$ = CriarNoOperador($1, $3, '/');
                                }
                              }
       | expr MODULO expr      { $$ = CriarNoOperador($1, $3, '%'); }  // Módulo
       | expr POWER expr       { $$ = CriarNoOperador($1, $3, 'p'); }  // Potência
       | expr FLOOR_DIV expr   { $$ = CriarNoOperador($1, $3, 'f'); }  // Divisão inteira
       | expr LT expr          { $$ = CriarNoOperador($1, $3, '<'); }  // Menor que
       | expr GT expr          { $$ = CriarNoOperador($1, $3, '>'); }  // Maior que
       | expr LE expr          { $$ = CriarNoOperador($1, $3, 'l'); }  // Menor ou igual
       | expr GE expr          { $$ = CriarNoOperador($1, $3, 'g'); }  // Maior ou igual
       | expr EQ expr          { $$ = CriarNoOperador($1, $3, '='); }  // Igual
       | expr NE expr          { $$ = CriarNoOperador($1, $3, 'n'); }  // Diferente
       | expr NE2 expr         { $$ = CriarNoOperador($1, $3, 'n'); }  // Diferente (<>)
       | expr BITAND expr      { $$ = CriarNoOperador($1, $3, '&'); }  // AND bitwise
       | expr BITOR expr       { $$ = CriarNoOperador($1, $3, '|'); }  // OR bitwise
       | expr BITXOR expr      { $$ = CriarNoOperador($1, $3, '^'); }  // XOR bitwise
       | expr SHIFTL expr      { $$ = CriarNoOperador($1, $3, 's'); }  // Shift left
       | expr SHIFTR expr      { $$ = CriarNoOperador($1, $3, 'r'); }  // Shift right
       | MINUS expr %prec NEG  { $$ = CriarNoOperador($2, NULL, '-'); }  // Menos unário
       | BITNOT expr %prec BITNOT { $$ = CriarNoOperador($2, NULL, '~'); }  // NOT bitwise
       | LBRACKET lista_elementos RBRACKET { $$ = CriarNoLista($2); }
       | expr LBRACKET expr RBRACKET { $$ = CriarNoIndexacao($1, $3); }
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
       | RETURN expr { $$ = CriarNoReturn($2); }
       ;
bloco:
      INDENT linhas DEDENT { $$ = $2; }
    
    ;


linhas:
      linhas line { $$ = AdicionarNoLista($1, $2); }
    | line { $$ = AdicionarNoLista(NULL, $1);}
    ;
funcao:
    DEF IDENTIFIER LPAREN parametros RPAREN COLON NEWLINE bloco {
        $$ = CriarNoFuncao($2, $4, CriarNoBloco($8));
        inserirSimboloEscopo($2, TIPO_FUNCAO);
        entrarEscopo();
        ListaNo* param = $4;
        while (param) {
            inserirSimboloEscopo(param->no->var, TIPO_INT); // Adapte tipo conforme necessário
            param = param->prox;
        }
        sairEscopo();
    }
;
parametros:
      /* vazio */ { $$ = NULL; }
    | lista_parametros { $$ = $1; }
;
lista_parametros:
      IDENTIFIER { 
          $$ = CriarNoLista(CriarNoVariavel($1), NULL); 
      }
    | lista_parametros COMMA IDENTIFIER {
          $$ = AdicionarNoLista($1, CriarNoVariavel($3));
      }
;
lista_elementos:
      expr { $$ = CriarListaElementos($1, NULL); }
    | lista_elementos COMMA expr { $$ = CriarListaElementos($3, $1); }
;
condicional:
      IF LPAREN expr RPAREN COLON NEWLINE bloco {
          $$ = CriarNoIf($3, CriarNoBloco($7), NULL);
      }
    | IF LPAREN expr RPAREN COLON NEWLINE bloco ELSE COLON NEWLINE bloco {
          $$ = CriarNoIf($3, CriarNoBloco($7), CriarNoBloco($11));
      }
    ;
comando_while:
      WHILE LPAREN expr RPAREN COLON NEWLINE bloco {
          $$ = CriarNoWhile($3, CriarNoBloco($7));
      }
    ;

comando_for:
      FOR IDENTIFIER IN expr COLON NEWLINE bloco {
          $$ = CriarNoFor(CriarNoVariavel($2), $4, NULL, CriarNoBloco($7));
      }
    ;
%%

/* Função principal para executar o parser */
int main(int argc, char **argv) {
    /* Inicializa a tabela de símbolos */
    inicializarTabela();

    /* Inicializa a pilha de indentação */
    inicializa_pilha();

    /* Processa argumentos da linha de comando */
    char *arquivo_entrada = NULL;
    char *arquivo_saida_lua = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--gerar-lua") == 0 && i + 1 < argc) {
            arquivo_saida_lua = argv[i + 1];
            gerar_codigo_lua = 1;
            i++; // Pula o próximo argumento
        } else if (argv[i][0] != '-') {
            arquivo_entrada = argv[i];
        }
    }

    /* Configura o arquivo de entrada */
    if (arquivo_entrada) {
        yyin = fopen(arquivo_entrada, "r");
    }
    entrarEscopo(); // Inicializa escopo global
    
    /* Configura o arquivo de entrada ou usa stdin */
    if (argc > 1) {
        yyin = fopen(argv[1], "r");  // Abre o arquivo de entrada
        if (yyin == NULL) {
            printf("Erro ao abrir arquivo %s\n", arquivo_entrada);
            return 1;
        }
    } else {
        yyin = stdin;
        printf("Digite expressões em Python. Pressione Ctrl+D (Linux/Mac) ou Ctrl+Z seguido de Enter (Windows) para encerrar.\n");
    }

    /* Configura o gerador de código Lua se necessário */
    if (gerar_codigo_lua) {
        if (arquivo_saida_lua) {
            // Se o caminho não contém diretório, salva na pasta saidas_lua
            char caminho_completo[512];
            if (strchr(arquivo_saida_lua, '/') == NULL && strchr(arquivo_saida_lua, '\\') == NULL) {
                snprintf(caminho_completo, sizeof(caminho_completo), "saidas_lua/%s", arquivo_saida_lua);
                arquivo_saida_lua = caminho_completo;
            }

            arquivo_lua = fopen(arquivo_saida_lua, "w");
            if (arquivo_lua == NULL) {
                printf("Erro ao criar arquivo de saída Lua: %s\n", arquivo_saida_lua);
                printf("Tentando criar diretório saidas_lua...\n");
                system("mkdir -p saidas_lua");
                arquivo_lua = fopen(arquivo_saida_lua, "w");
                if (arquivo_lua == NULL) {
                    printf("Erro persistente ao criar arquivo. Usando stdout.\n");
                    arquivo_lua = stdout;
                }
            }

            if (arquivo_lua != stdout) {
                inicializarGerador(arquivo_lua);
                printf("Gerando código Lua em: %s\n", arquivo_saida_lua);
            } else {
                inicializarGerador(arquivo_lua);
                printf("=== CÓDIGO LUA GERADO ===\n");
            }
        } else {
            arquivo_lua = stdout;
            inicializarGerador(arquivo_lua);
            printf("=== CÓDIGO LUA GERADO ===\n");
        }
    }

    /* Executa o parser */
    yyparse();

    /* Finaliza o gerador de código se necessário */
    if (gerar_codigo_lua) {
        finalizarGerador();
        if (arquivo_saida_lua) {
            printf("Código Lua gerado com sucesso!\n");
        } else {
            printf("=== FIM DO CÓDIGO LUA ===\n");
        }
    }

    /* Imprime a tabela de símbolos */
    imprimirTabela();

    /* Libera a tabela de símbolos */
    liberarTabela();

    /* Fecha arquivos se necessário */
    if (arquivo_entrada) {

    sairEscopo(); // Libera escopo global
    }
    /* Fecha o arquivo se necessário */
    if (argc > 1) {
        fclose(yyin);
    }

    return 0;
    
    
}
