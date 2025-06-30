%{
#include <stdio.h>
#include <stdlib.h>
#include "../ast/ast.h"
#include "../tabela/tabela.h"
#include "../gerador_codigo_final/gerador_codigo_final.h"
#include "../codigo_intermediario/codigo_intermediario.h"
#include <string.h>

int yylex();  // Declaração da função yylex que será chamada pelo parser
void yyerror(const char *s);  // Função de erro para lidar com erros sintáticos
extern FILE *yyin;  // Arquivo de entrada 
extern int line_num;  // Linha atual (definida no scanner)
extern void inicializa_pilha();  // Declaração da função de inicialização da pilha de indentação
// No início do parser.y
ListaNo* ast_global = NULL;

// Variáveis globais para controle da geração de código
FILE *arquivo_lua = NULL;
int gerar_codigo_lua = 0;
int gerar_codigo_lua_otimizado = 0;
FILE *arquivo_tac = NULL;
int gerar_codigo_tac = 0;
int total_erros = 0;

// Variável global para parâmetros de função em processamento
ListaNo* parametros_funcao_atual = NULL;

void yyerror(const char *s) {
    fprintf(stderr, "[ERRO SINTATICO] %s na linha %d\n", s, line_num);
    total_erros++;
}

void verificarDeclaracao(No *no) {
    if (no == NULL) return;

    if (no->tipo == NoVariavel) {
        Simbolo *s = buscarSimbolo(no->var);
        if (s == NULL) {
            printf("[ERRO] Variável '%s' usada mas não declarada na linha %d\n", no->var, line_num);
            total_erros++;
        }
    }

    // Verifica recursivamente os filhos
    verificarDeclaracao(no->esquerda);
    verificarDeclaracao(no->direita);
}

void DeclararVar(char *var){
    Simbolo *s = buscarSimbolo(var);
    if (s == NULL){
        inserirSimbolo(var, TIPO_INT);
    }
}

// Função para determinar o tipo baseado no nó da AST
TipoSimbolo determinarTipo(No *no) {
    if (no == NULL) return TIPO_INT;
    
    switch (no->tipo) {
        case NoLiteral:
            // Verifica se é um float (se valor_float está sendo usado)
            if (no->valor_float != 0.0) {
                return TIPO_FLOAT;
            }
            return TIPO_INT;
        case NoFloat:  // Tipo específico para floats
            return TIPO_FLOAT;
        case NoString:
            return TIPO_STRING;
        case NoBool:
            return TIPO_BOOL;
        case NoVariavel:
            // Para variáveis, consulta o tipo na tabela
            {
                Simbolo *s = buscarSimbolo(no->var);
                return s ? s->tipo : TIPO_INT;
            }
        default:
            return TIPO_INT;
    }
}


%}

/* Declaração de tipos para os valores */
%union {
    int intval;
    float floatval;
    struct Arvore *no;
    char *string;
    struct ListaNo *lista;
}

/* Declaração de tokens */
%token <intval> INTEGER  
%token <floatval> FLOAT
%token <intval> TRUE FALSE
%token PLUS MINUS MULTIPLY DIVIDE MODULO
%token POWER FLOOR_DIV
%token LT GT LE GE EQ NE NE2
%token LPAREN RPAREN
%token <string> IDENTIFIER
%token ASSIGN PLUS_EQ MINUS_EQ MULT_EQ DIV_EQ FLOOR_EQ POW_EQ MOD_EQ
%token BITAND BITOR BITXOR BITNOT
%token SHIFTL SHIFTR AND_EQ OR_EQ XOR_EQ SHIFTR_EQ SHIFTL_EQ
%token ERROR
%token NEWLINE
%token <string> KEYWORD
%token IF ELIF ELSE MATCH CASE
%token FOR WHILE
%token DEF RETURN
%token AND OR NOT
%token LBRACKET RBRACKET LBRACE RBRACE
%token COMMA COLON DOT DECORATOR ARROW
%token <string> HEX OCT BIN
%token <string> STRING_DQ STRING_SQ TRIPLE_DQ TRIPLE_SQ
%token COMMENT
%token INDENT DEDENT
%token PRINT 

/* Precedência de operadores */
%left OR
%left AND
%left BITOR
%left BITXOR
%left BITAND
%left EQ NE NE2
%left LT GT LE GE
%left SHIFTL SHIFTR
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO FLOOR_DIV
%right POWER
%precedence NEG  
%precedence BITNOT 
%precedence NOT  

/* Tipo de valor para o não-terminal "expr" */
%type <no> expr
%type <no> declaracao
%type <no> line
%type <no> condicional
%type <no> bloco
%type <lista> linhas
%type <no> line_exec
%type <no> funcao
%type <lista> print_args
%type <no> print
%type <lista> chamada_args
%type <lista> funcao_args


%%

/* Regras de análise sintática */
input:   /* Produção vazia */
       | input line  
       ;

line:    expr NEWLINE {
        imprimeArvore($1, 0);
        if (gerar_codigo_lua && arquivo_lua && $1->tipo != NoIf) {
            if (gerar_codigo_lua_otimizado) {
                gerarCodigoLuaOtimizado($1);
            } else {
                gerarCodigoLua($1);
            }
        }

        DesalocarArvore($1);
        $$ = NULL;
}
       | declaracao NEWLINE {
        imprimeArvore($1, 0);

        // Gera código Lua se habilitado
        if (gerar_codigo_lua && arquivo_lua) {
            if (gerar_codigo_lua_otimizado) {
                gerarCodigoLuaOtimizado($1);
            } else {
                gerarCodigoLua($1);
            }
        }

        // gera o código de três endereços
        if (gerar_codigo_tac && arquivo_tac) {
            gerarCodigoTAC($1);
        }

        DesalocarArvore($1);
        $$ = NULL;
}
       | expr /* sem quebra de linha ao final */ {
        imprimeArvore($1, 0);

        // Gera código Lua se habilitado
        if (gerar_codigo_lua && arquivo_lua) {
            if (gerar_codigo_lua_otimizado) {
                gerarCodigoLuaOtimizado($1);
            } else {
                gerarCodigoLua($1);
            }
        }

        //gera código TAC se habilitado
        if (gerar_codigo_tac && arquivo_tac) {
            gerarCodigoTAC($1);
        }

        DesalocarArvore($1);
        $$ = NULL;
}
       | declaracao /* sem quebra de linha ao final */ {
        imprimeArvore($1, 0);
        // Gera código Lua se habilitado
        if (gerar_codigo_lua && arquivo_lua) {
            if (gerar_codigo_lua_otimizado) {
                gerarCodigoLuaOtimizado($1);
            } else {
                gerarCodigoLua($1);
            }
        }

        //gera o código de três endereços (TAC)
        if (gerar_codigo_tac && arquivo_tac) {
            gerarCodigoTAC($1);
        }

        DesalocarArvore($1);
        $$ = NULL;
}
    | funcao {
            imprimeArvore($1, 0);
            if (gerar_codigo_lua && arquivo_lua) {
                if (gerar_codigo_lua_otimizado) {
                    gerarCodigoLuaOtimizado($1);
                } else {
                    gerarCodigoLua($1);
                }
            }
            DesalocarArvore($1);
            $$ = NULL;
        }
    | condicional {
            imprimeArvore($1, 0);
            if (gerar_codigo_lua && arquivo_lua) {
                if (gerar_codigo_lua_otimizado) {
                    gerarCodigoLuaOtimizado($1);
                } else {
                    gerarCodigoLua($1);
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
       | print NEWLINE {
            imprimeArvore($1, 0);
            if (gerar_codigo_lua && arquivo_lua){
                if (gerar_codigo_lua_otimizado) {
                    gerarCodigoLuaOtimizado($1);
                } else {
                    gerarCodigoLua($1);
                }
            }
            DesalocarArvore($1);
            $$ = NULL;
       }
       | print {
            imprimeArvore($1, 0);
            if (gerar_codigo_lua && arquivo_lua){
                if (gerar_codigo_lua_otimizado) {
                    gerarCodigoLuaOtimizado($1);
                } else {
                    gerarCodigoLua($1);
                }
            }
            DesalocarArvore($1);
            $$ = NULL;
       }
       ;

expr:    INTEGER               { $$ = CriarNoInteiro($1); }  // Cria um nó de inteiro
       | FLOAT                 { $$ = CriarNoFloat($1); }  // Cria um nó float
       | TRUE                  { $$ = CriarNoBool($1); }  // Cria um nó bool true
       | FALSE                 { $$ = CriarNoBool($1); }  // Cria um nó bool false
       | STRING_DQ             { $$ = CriarNoString($1); }  // String com aspas duplas
       | STRING_SQ             { $$ = CriarNoString($1); }  // String com aspas simples
       | IDENTIFIER            { $$ = CriarNoVariavel($1);}
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
       | expr AND expr         { $$ = CriarNoOperador($1, $3, 'A'); }  // AND lógico
       | expr OR expr          { $$ = CriarNoOperador($1, $3, 'O'); }  // OR lógico
       | MINUS expr %prec NEG  { $$ = CriarNoOperador($2, NULL, '-'); }  // Menos unário
       | BITNOT expr %prec BITNOT { $$ = CriarNoOperador($2, NULL, '~'); }  // NOT bitwise
       | NOT expr              { $$ = CriarNoOperador($2, NULL, 'N'); }  // NOT lógico
       | IDENTIFIER LPAREN RPAREN {
           if (!existeSimbolo($1)) {
               printf("[ERRO] Função '%s' não declarada na linha %d\n", $1, line_num);
               total_erros++;
           }
           $$ = CriarNoChamadaFuncao($1, NULL);
       }
       | IDENTIFIER LPAREN chamada_args RPAREN {
           if (!existeSimbolo($1)) {
               printf("[ERRO] Função '%s' não declarada na linha %d\n", $1, line_num);
               total_erros++;
           }
           $$ = CriarNoChamadaFuncao($1, $3);
       }
       ;

declaracao:  IDENTIFIER ASSIGN expr { 
 
        Simbolo *sim = buscarSimbolo($1);
        if (sim == NULL) {
            TipoSimbolo tipo = determinarTipo($3);
            inserirSimbolo($1, tipo);
            $$ = CriaNoAtribuicao(CriarNoVariavel($1), $3);
            $$->declarada = true;  // primeira vez declarando
        } else {
            $$ = CriaNoAtribuicao(CriarNoVariavel($1), $3);
            $$->declarada = false;  // já declarada
        }
        verificarDeclaracao($3);
    
} 
       | IDENTIFIER PLUS_EQ expr {
            verificarDeclaracao($3);
            $$ = CriaNoAtribuicao(CriarNoVariavel($1), CriarNoOperador(CriarNoVariavel($1), $3, '+'));
}
       | IDENTIFIER MINUS_EQ expr {
            verificarDeclaracao($3);
            $$ = CriaNoAtribuicao(CriarNoVariavel($1), CriarNoOperador(CriarNoVariavel($1), $3, '-'));
}
       | IDENTIFIER MULT_EQ expr {
            verificarDeclaracao($3);
            $$ = CriaNoAtribuicao(CriarNoVariavel($1), CriarNoOperador(CriarNoVariavel($1), $3, '*'));
}
       | IDENTIFIER DIV_EQ expr {
            verificarDeclaracao($3);
            $$ = CriaNoAtribuicao(CriarNoVariavel($1), CriarNoOperador(CriarNoVariavel($1), $3, '/'));
}
       | IDENTIFIER MOD_EQ expr {
            verificarDeclaracao($3);
            $$ = CriaNoAtribuicao(CriarNoVariavel($1), CriarNoOperador(CriarNoVariavel($1), $3, '%'));
} 
       | IDENTIFIER FLOOR_EQ expr { 
 
            $$ = CriaNoAtribuicao(CriarNoVariavel($1), CriarNoOperador(CriarNoVariavel($1), $3, 'b'));
}  
       | IDENTIFIER POW_EQ expr { 
 
            $$ = CriaNoAtribuicao(CriarNoVariavel($1), CriarNoOperador(CriarNoVariavel($1), $3, 'a'));
} 
       ;

//nao terminal pra processar blocos
line_exec:
      expr NEWLINE         { $$ = $1; }
    | declaracao NEWLINE   { $$ = $1; }
    | condicional          { $$ = $1; }
    | expr                 { $$ = $1; }
    | declaracao           { $$ = $1; }
    | RETURN expr NEWLINE  {
        verificarDeclaracao($2);
        $$ = CriarNoReturn($2);
    }
    | RETURN expr          {
        verificarDeclaracao($2);
        $$ = CriarNoReturn($2);
    }
    | RETURN NEWLINE       { $$ = CriarNoReturn(NULL); }
    | RETURN               { $$ = CriarNoReturn(NULL); }
    ;

//linhas podem ter 1 ou mais line_exec
linhas:
      linhas line_exec { $$ = AdicionarNoLista($1, $2); }
    | line_exec       { $$ = AdicionarNoLista(NULL, $1); }
    ;

//é considerado bloco se tiver indentado corretamente
bloco:
      INDENT { 
          entrarEscopo(); 
          
          // Se há parâmetros de função esperando, insere eles no escopo atual
          if (parametros_funcao_atual != NULL) {
              ListaNo *param = parametros_funcao_atual;
              while (param) {
                  inserirSimbolo(param->no->var, TIPO_INT);  // Assume tipo int por padrão
                  param = param->prox;
              }
          }
      } linhas DEDENT {
          sairEscopo();
          $$ = CriarNoBloco($3);
      }
    ;



funcao:
      DEF IDENTIFIER LPAREN RPAREN COLON NEWLINE bloco {
          inserirSimbolo($2, TIPO_FUNCAO);
          $$ = CriarNoFuncao($2, NULL, $7);
      }
    | DEF IDENTIFIER LPAREN funcao_args RPAREN COLON NEWLINE {
          inserirSimbolo($2, TIPO_FUNCAO);
          parametros_funcao_atual = $4;  // Salva os parâmetros para uso no bloco
      } bloco {
          parametros_funcao_atual = NULL;  // Limpa os parâmetros
          $$ = CriarNoFuncao($2, $4, $9);
      }
    ;

funcao_args:
        IDENTIFIER { $$ = AdicionarNoLista(NULL, CriarNoVariavel($1)); }
        | funcao_args COMMA IDENTIFIER { $$ = AdicionarNoLista($1, CriarNoVariavel($3)); }

condicional:
      IF LPAREN expr RPAREN COLON NEWLINE bloco {
          $$ = CriarNoIf($3, $7, NULL);
      }

    |  IF expr COLON NEWLINE bloco {
          $$ = CriarNoIf($2, $5, NULL);
      }
      
    | IF LPAREN expr RPAREN COLON NEWLINE bloco ELSE COLON NEWLINE bloco {
          $$ = CriarNoIf($3, $7, $11);
      }
    | IF expr COLON NEWLINE bloco ELSE COLON NEWLINE bloco{
          $$ = CriarNoIf($2, $5, $9);
      }
    | WHILE expr COLON NEWLINE bloco {
          $$ = CriarNoWhile($2, $5);
      }
    | WHILE LPAREN expr RPAREN COLON NEWLINE bloco {
          $$ = CriarNoWhile($3, $7);
      }
    ;

print:  
     PRINT LPAREN print_args RPAREN {$$ = CriarNoPrint($3); }

print_args:
    expr              {$$ = AdicionarNoLista(NULL, $1); }
    | print_args COMMA expr {$$ = AdicionarNoLista($1, $3); }

chamada_args:
    expr              {$$ = AdicionarNoLista(NULL, $1); }
    | chamada_args COMMA expr {$$ = AdicionarNoLista($1, $3); }

%%

/* Função principal para executar o parser */
int main(int argc, char **argv) {
    /* Inicializa contador de erros */
    total_erros = 0;

    /* Inicializa a tabela de símbolos */
    inicializarTabela();

    /* Inicializa a pilha de indentação */
    inicializa_pilha();

    /* Processa argumentos da linha de comando */
    char *arquivo_entrada = NULL;
    char *arquivo_saida_lua = NULL;
    char *arquivo_saida_tac = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--gerar-lua") == 0 && i + 1 < argc) {
            arquivo_saida_lua = argv[i + 1];
            gerar_codigo_lua = 1;
            i++; // Pula o próximo argumento
        } else if (strcmp(argv[i], "--gerar-lua-otimizado") == 0 && i + 1 < argc) {
            arquivo_saida_lua = argv[i + 1];
            gerar_codigo_lua = 1;
            gerar_codigo_lua_otimizado = 1;
            i++; // Pula o próximo argumento
        } else if (strcmp(argv[i], "--gerar-tac") == 0 && i + 1 < argc) {
            arquivo_saida_tac = argv[i + 1];
            gerar_codigo_tac = 1;
            i++; // Pula o próximo argumento
        } else if (strcmp(argv[i], "--gerar-lua") == 0) {
            gerar_codigo_lua = 1;
        } else if (strcmp(argv[i], "--gerar-lua-otimizado") == 0) {
            gerar_codigo_lua = 1;
            gerar_codigo_lua_otimizado = 1;
        } else if (strcmp(argv[i], "--otimizar") == 0) {
            gerar_codigo_lua_otimizado = 1;
        } else if (strcmp(argv[i], "--gerar-tac") == 0) {
            gerar_codigo_tac = 1;
        } else if (argv[i][0] != '-') {
            arquivo_entrada = argv[i];
        }
    }

    /* Configura o arquivo de entrada */
    if (arquivo_entrada) {
        yyin = fopen(arquivo_entrada, "r");
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

    /* configurando gerador de código intermediario */
    if (gerar_codigo_tac) {
        if (arquivo_saida_tac) {
            // Se o caminho não contém diretório, salva na pasta saidas_tac
            char caminho_completo_tac[512];
            if (strchr(arquivo_saida_tac, '/') == NULL && strchr(arquivo_saida_tac, '\\') == NULL) {
                snprintf(caminho_completo_tac, sizeof(caminho_completo_tac), "saidas_tac/%s", arquivo_saida_tac);
                arquivo_saida_tac = caminho_completo_tac;
            }

            arquivo_tac = fopen(arquivo_saida_tac, "w");
            if (arquivo_tac == NULL) {
                printf("Erro ao criar arquivo de saída TAC: %s\n", arquivo_saida_tac);
                printf("Tentando criar diretório saidas_tac...\n");
                system("mkdir -p saidas_tac");
                arquivo_tac = fopen(arquivo_saida_tac, "w");
                if (arquivo_tac == NULL) {
                    printf("Erro criar arquivo TAC.\n");
                    arquivo_tac = stdout;
                }
            }

            if (arquivo_tac != stdout) {
                inicializarGeradorTAC(arquivo_tac);
                printf("Gerando código TAC em: %s\n", arquivo_saida_tac);
            } else {
                inicializarGeradorTAC(arquivo_tac);
                printf("=== CÓDIGO TAC GERADO ===\n");
            }
        } else {
            arquivo_tac = stdout;
            inicializarGeradorTAC(arquivo_tac);
            printf("=== CÓDIGO TAC GERADO ===\n");
        }
    }

    /* Executa o parser */
    yyparse();

    /* Verifica se houve erros antes de finalizar a geração de código */
    if (total_erros > 0) {
        printf("\n[TOTAL DE ERROS] Compilação falhou com %d erro(s).\n", total_erros);

        /* Remove arquivos de saída se foram criados */
        if (gerar_codigo_lua && arquivo_lua && arquivo_lua != stdout) {
            fclose(arquivo_lua);
            if (arquivo_saida_lua) {
                remove(arquivo_saida_lua);
                printf("Arquivo %s removido devido à erros\n", arquivo_saida_lua);
            }
        }
        if (gerar_codigo_tac && arquivo_tac && arquivo_tac != stdout) {
            fclose(arquivo_tac);
            if (arquivo_saida_tac) {
                remove(arquivo_saida_tac);
                printf("Arquivo TAC %s removido devido à erros\n", arquivo_saida_tac);
            }
        }
        if (arquivo_entrada) {
            fclose(yyin);
        }
        liberarTabela();
        return 1;
    }

    /* Finaliza o gerador de código se necessário */
    if (gerar_codigo_lua) {
        finalizarGerador();
        if (arquivo_saida_lua) {
            printf("Código Lua gerado com sucesso!\n");
        } else {
            printf("=== FIM DO CÓDIGO LUA ===\n");
        }
    }

    /* Finaliza o gerador de código de três endereços se necessário */
    if (gerar_codigo_tac) {
        finalizarGeradorTAC();
        if (arquivo_saida_tac) {
            printf("Código TAC gerado com sucesso!\n");
        } else {
            printf("=== FIM DO CÓDIGO TAC ===\n");
        }
    }

    /* Imprime a tabela de símbolos */
    imprimirTabela();

    /* Libera a tabela de símbolos */
    liberarTabela();

    /* Fecha arquivos se necessário */
    if (arquivo_entrada) {
        fclose(yyin);
    }

    return 0;
}
