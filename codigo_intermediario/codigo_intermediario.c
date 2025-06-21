#include "codigo_intermediario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static GeradorTAC gerador_tac = {NULL, 0, 0};

void inicializarGeradorTAC(FILE* arquivo_saida) {
    gerador_tac.arquivo_saida = arquivo_saida;
    gerador_tac.contador_temp = 0;
    gerador_tac.contador_label = 0;
}

char* novaVariavelTemp() {
    static char buffer[32];
    snprintf(buffer, sizeof(buffer), "t%d", gerador_tac.contador_temp++);
    return strdup(buffer);
}

char* novoLabel() {
    static char buffer[32];
    snprintf(buffer, sizeof(buffer), "L%d", gerador_tac.contador_label++);
    return strdup(buffer);
}

void imprimirInstrucaoTAC(const char* resultado, const char* op1, char operador, const char* op2) {
    if (operador == 0) {
        fprintf(gerador_tac.arquivo_saida, "%s = %s\n", resultado, op1);
    } else {
        fprintf(gerador_tac.arquivo_saida, "%s = %s %c %s\n", resultado, op1, operador, op2);
    }
}

char* gerarExpressaoTAC(No* no) {
    if (!no) return NULL;

    switch (no->tipo) {
        case NoLiteral: {
            char* temp = malloc(20);
            sprintf(temp, "%d", no->valor);
            return temp;
        }

        case NoFloat: {
            char* temp = malloc(20);
            sprintf(temp, "%.2f", no->valor_float);
            return temp;
        }

        case NoVariavel:
            return strdup(no->var);

        case NoOperacaoBinaria: {
            char* esq = gerarExpressaoTAC(no->esquerda);
            char* dir = gerarExpressaoTAC(no->direita);
            char* temp = novaVariavelTemp();
            
            imprimirInstrucaoTAC(temp, esq, no->op, dir);
            
            free(esq);
            free(dir);
            return temp;
        }

        case NoString:
            return strdup(no->valor_str);

        case NoBool: {
            char* temp = malloc(10);
            sprintf(temp, "%s", no->valor_bool ? "true" : "false");
            return temp;
        }

        default:
            return NULL;
    }
}

char* gerarCodigoTAC(No* no) {
    if (!no) return NULL;

    switch (no->tipo) {
        case NoAtribuicao: {
            char* valor = gerarExpressaoTAC(no->direita);
            if (no->esquerda && no->esquerda->tipo == NoVariavel) {
                imprimirInstrucaoTAC(no->esquerda->var, valor, 0, NULL);
            }
            free(valor);
            return NULL;
        }

        case NoBloco:
            if (no->lista) {
                gerarBlocoTAC(no->lista);
            }
            return NULL;

        case NoIf: {
            char* condicao = gerarExpressaoTAC(no->esquerda);
            char* label_else = novoLabel();
            char* label_fim = novoLabel();
            
            fprintf(gerador_tac.arquivo_saida, "if %s == 0 goto %s\n", condicao, label_else);
            gerarCodigoTAC(no->direita);
            fprintf(gerador_tac.arquivo_saida, "goto %s\n", label_fim);
            fprintf(gerador_tac.arquivo_saida, "%s:\n", label_else);
            
            if (no->meio) {
                gerarCodigoTAC(no->meio);
            }
            
            fprintf(gerador_tac.arquivo_saida, "%s:\n", label_fim);
            
            free(condicao);
            free(label_else);
            free(label_fim);
            return NULL;
        }

        case NoWhile: {
            char* label_inicio = novoLabel();
            char* label_fim = novoLabel();
            
            fprintf(gerador_tac.arquivo_saida, "%s:\n", label_inicio);
            char* condicao = gerarExpressaoTAC(no->esquerda);
            fprintf(gerador_tac.arquivo_saida, "if %s == 0 goto %s\n", condicao, label_fim);
            gerarCodigoTAC(no->direita);
            fprintf(gerador_tac.arquivo_saida, "goto %s\n", label_inicio);
            fprintf(gerador_tac.arquivo_saida, "%s:\n", label_fim);
            
            free(condicao);
            free(label_inicio);
            free(label_fim);
            return NULL;
        }

        case NoFor: {
            char* label_inicio = novoLabel();
            char* label_fim = novoLabel();
            
            if (no->esquerda) {
                gerarCodigoTAC(no->esquerda);
            }
            
            fprintf(gerador_tac.arquivo_saida, "%s:\n", label_inicio);
            
            if (no->meio) {
                char* condicao = gerarExpressaoTAC(no->meio);
                fprintf(gerador_tac.arquivo_saida, "if %s == 0 goto %s\n", condicao, label_fim);
                free(condicao);
            }
            
            if (no->lista) {
                gerarBlocoTAC(no->lista);
            }
            
            if (no->direita) {
                gerarCodigoTAC(no->direita);
            }
            
            fprintf(gerador_tac.arquivo_saida, "goto %s\n", label_inicio);
            fprintf(gerador_tac.arquivo_saida, "%s:\n", label_fim);
            
            free(label_inicio);
            free(label_fim);
            return NULL;
        }

        case NoFuncao: {
            fprintf(gerador_tac.arquivo_saida, "function %s:\n", no->var ? no->var : "func");
            if (no->lista) {
                gerarBlocoTAC(no->lista);
            }
            fprintf(gerador_tac.arquivo_saida, "return\n");
            return NULL;
        }

        case NoChamadaFuncao: {
            if (no->lista) {
                ListaNo* atual = no->lista;
                int param_count = 0;
                while (atual) {
                    char* arg = gerarExpressaoTAC(atual->no);
                    fprintf(gerador_tac.arquivo_saida, "param %s\n", arg);
                    free(arg);
                    param_count++;
                    atual = atual->prox;
                }
            }
            
            char* temp = novaVariavelTemp();
            fprintf(gerador_tac.arquivo_saida, "%s = call %s\n", temp, no->var ? no->var : "func");
            return temp;
        }

        default:
            return gerarExpressaoTAC(no);
    }
}

void gerarBlocoTAC(ListaNo* lista) {
    ListaNo* atual = lista;
    while (atual) {
        gerarCodigoTAC(atual->no);
        atual = atual->prox;
    }
}

void finalizarGeradorTAC() {
    if (gerador_tac.arquivo_saida && gerador_tac.arquivo_saida != stdout) {
        fclose(gerador_tac.arquivo_saida);
    }
    gerador_tac.arquivo_saida = NULL;
    gerador_tac.contador_temp = 0;
    gerador_tac.contador_label = 0;
}
