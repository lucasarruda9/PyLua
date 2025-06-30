#include "gerador_codigo_final.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static GeradorCodigo gerador = {NULL, 0, 0, {0}};

void inicializarGerador(FILE* arquivo_saida) {
    gerador.arquivo_saida = arquivo_saida;
    gerador.nivel_indentacao = 0;
    gerador.contador_variaveis_temp = 0;
    // Inicializar opções de otimização com valores padrão
    inicializarOpcoes(&gerador.opcoes_otimizacao);
}

// ===== NOVAS FUNÇÕES DE OTIMIZAÇÃO =====

void gerarCodigoLuaOtimizado(No* no) {
    if (!no) return;
    
    // Aplicar otimizações antes de gerar o código
    No* no_otimizado = aplicarOtimizacoes(no, &gerador.opcoes_otimizacao);
    
    // Gerar código para o nó otimizado
    gerarCodigoLua(no_otimizado);
    
    // Imprimir estatísticas se houver otimizações aplicadas
    if (gerador.opcoes_otimizacao.num_optimizations_applied > 0) {
        fprintf(stderr, "=== OTIMIZAÇÕES APLICADAS ===\n");
        fprintf(stderr, "Total: %d otimizações\n", gerador.opcoes_otimizacao.num_optimizations_applied);
        fprintf(stderr, "=============================\n");
    }
}

void configurarOtimizacoes(bool dce, bool cf, bool asif, bool cse) {
    gerador.opcoes_otimizacao.dead_code_elimination = dce;
    gerador.opcoes_otimizacao.constant_folding = cf;
    gerador.opcoes_otimizacao.as_if_optimization = asif;
    gerador.opcoes_otimizacao.common_subexpression_elimination = cse;
}

void habilitarTodasOtimizacoes() {
    configurarOtimizacoes(true, true, true, true);
}

void desabilitarTodasOtimizacoes() {
    configurarOtimizacoes(false, false, false, false);
}

// ===== FUNÇÕES EXISTENTES (sem alteração) =====

void aumentarIndentacao() {
    gerador.nivel_indentacao++;
}

void diminuirIndentacao() {
    if (gerador.nivel_indentacao > 0) {
        gerador.nivel_indentacao--;
    }
}

char* obterVariavelTemporaria() {
    static char buffer[32];
    snprintf(buffer, sizeof(buffer), "temp_%d", gerador.contador_variaveis_temp++);
    return buffer;
}

static void indentar() {
    for (int i = 0; i < gerador.nivel_indentacao; i++) {
        fprintf(gerador.arquivo_saida, "    ");
    }
}

static void gerarExpressao(No* no) {
    if (!no) return;

    switch (no->tipo) {
        case NoLiteral:
            fprintf(gerador.arquivo_saida, "%d", no->valor);
            break;

        case NoFloat:
            fprintf(gerador.arquivo_saida, "%.6f", no->valor_float);
            break;

        case NoString: {
            char* str = no->valor_str;
            if (str && strlen(str) >= 2) {
                int len = strlen(str);
                if ((str[0] == '"' && str[len-1] == '"') || 
                    (str[0] == '\'' && str[len-1] == '\'')) {
                    fprintf(gerador.arquivo_saida, "%s", str);
                } else {
                    fprintf(gerador.arquivo_saida, "\"%s\"", str);
                }
            } else {
                fprintf(gerador.arquivo_saida, "\"\"");
            }
            break;
        }

        case NoBool:
            fprintf(gerador.arquivo_saida, "%s", no->valor_bool ? "true" : "false");
            break;

        case NoVariavel:
            fprintf(gerador.arquivo_saida, "%s", no->var);
            break;

        case NoOperacaoBinaria:
            fprintf(gerador.arquivo_saida, "(");
            gerarExpressao(no->esquerda);
            switch (no->op) {
                case '+': fprintf(gerador.arquivo_saida, " + "); break;
                case '-': fprintf(gerador.arquivo_saida, " - "); break;
                case '*': fprintf(gerador.arquivo_saida, " * "); break;
                case '/': fprintf(gerador.arquivo_saida, " / "); break;
                case '%': fprintf(gerador.arquivo_saida, " %% "); break;
                case 'p': fprintf(gerador.arquivo_saida, " ^ "); break;
                case 'f': fprintf(gerador.arquivo_saida, " // "); break;
                case '=': fprintf(gerador.arquivo_saida, " == "); break;
                case '<': fprintf(gerador.arquivo_saida, " < "); break;
                case '>': fprintf(gerador.arquivo_saida, " > "); break;
                case 'l': fprintf(gerador.arquivo_saida, " <= "); break;
                case 'g': fprintf(gerador.arquivo_saida, " >= "); break;
                case 'n': fprintf(gerador.arquivo_saida, " ~= "); break;
                case '&': fprintf(gerador.arquivo_saida, " & "); break;
                case '|': fprintf(gerador.arquivo_saida, " | "); break;
                case '^': fprintf(gerador.arquivo_saida, " ~ "); break;
                case 's': fprintf(gerador.arquivo_saida, " << "); break;
                case 'r': fprintf(gerador.arquivo_saida, " >> "); break;
                default: fprintf(gerador.arquivo_saida, " ? "); break;
            }
            gerarExpressao(no->direita);
            fprintf(gerador.arquivo_saida, ")");
            break;

        default:
            // Para outros tipos que podem aparecer em expressões
            break;
    }
}
//usado para converter listas em código lua
void gerarBlocoLua(ListaNo* lista) {
    ListaNo* atual = lista;
    while (atual) {
        gerarCodigoLua(atual->no);
        atual = atual->prox;
    }
}

//como se fosse gerarBlocoLua mas imprime com vírgula (para print)
void gerarListaArgumentosPrint(ListaNo* lista) {
    ListaNo* atual = lista;
    while (atual) {
        gerarExpressao(atual->no);  // imprime argumento
        if (atual->prox) {
            fprintf(gerador.arquivo_saida, ", ");
        }
        atual = atual->prox;
    }
}

void gerarCodigoLua(No* no) {
    if (!no) return;

    switch (no->tipo) {
        case NoAtribuicao:
            indentar();
            if (no->declarada == true) {
                fprintf(gerador.arquivo_saida, "local %s = ", no->esquerda->var);
            } else {
                fprintf(gerador.arquivo_saida, "%s = ", no->esquerda->var);
            }
            gerarExpressao(no->direita);
            fprintf(gerador.arquivo_saida, "\n");
            break;

        case NoBloco:
            if (no->lista) {
                gerarBlocoLua(no->lista);
            }
            break;

        case NoIf:
            indentar();
            fprintf(gerador.arquivo_saida, "if ");
            gerarExpressao(no->esquerda);
            fprintf(gerador.arquivo_saida, " then\n");
            aumentarIndentacao();
            if (no->meio && no->meio->tipo == NoBloco) {
                gerarBlocoLua(no->meio->lista);
            } 
            else if (no->meio) {
                gerarCodigoLua(no->meio);
        }
            diminuirIndentacao();
            if (no->direita) {
                indentar();
                fprintf(gerador.arquivo_saida, "else\n");
                aumentarIndentacao();
                gerarCodigoLua(no->direita);
                diminuirIndentacao();
            }
            indentar();
            fprintf(gerador.arquivo_saida, "end\n");
            break;

        case NoWhile:
            indentar();
            fprintf(gerador.arquivo_saida, "while ");
            gerarExpressao(no->esquerda);
            fprintf(gerador.arquivo_saida, " do\n");
            aumentarIndentacao();
            gerarCodigoLua(no->meio);
            diminuirIndentacao();
            indentar();
            fprintf(gerador.arquivo_saida, "end\n");
            break;

        case NoFor:
            indentar();
            fprintf(gerador.arquivo_saida, "for ");
            if (no->esquerda && no->esquerda->tipo == NoVariavel) {
                fprintf(gerador.arquivo_saida, "%s = ", no->esquerda->var);
                gerarExpressao(no->direita);
                fprintf(gerador.arquivo_saida, ", ");
                gerarExpressao(no->esquerda);
            }
            fprintf(gerador.arquivo_saida, " do\n");
            aumentarIndentacao();
            gerarCodigoLua(no->meio);
            diminuirIndentacao();
            indentar();
            fprintf(gerador.arquivo_saida, "end\n");
            break;

        case NoFuncao:
            indentar();
            fprintf(gerador.arquivo_saida, "function %s()\n", no->var ? no->var : "anonima");
            aumentarIndentacao();
            if (no->lista) {
                gerarBlocoLua(no->lista);
            }
            diminuirIndentacao();
            indentar();
            fprintf(gerador.arquivo_saida, "end\n");
            break;
        case NoPrint:
            indentar();
            fprintf(gerador.arquivo_saida, "print(");
            gerarListaArgumentosPrint(no->lista);
            fprintf(gerador.arquivo_saida, ")\n");
            break;
        default:
            // Para expressões simples ou outros tipos
            indentar();
            gerarExpressao(no);
            fprintf(gerador.arquivo_saida, "\n");
            break;
    }
}

void finalizarGerador() {
    if (gerador.arquivo_saida && gerador.arquivo_saida != stdout) {
        fclose(gerador.arquivo_saida);
    }
    gerador.arquivo_saida = NULL;
    gerador.nivel_indentacao = 0;
    gerador.contador_variaveis_temp = 0;
}