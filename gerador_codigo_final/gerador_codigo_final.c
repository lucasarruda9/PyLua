#include "gerador_codigo_final.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static GeradorCodigo gerador = {NULL, 0, 0};

void inicializarGerador(FILE* arquivo_saida) {
    gerador.arquivo_saida = arquivo_saida;
    gerador.nivel_indentacao = 0;
    gerador.contador_variaveis_temp = 0;
}

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

        case NoString:
            fprintf(gerador.arquivo_saida, "\"%s\"", no->valor_str ? no->valor_str : "");
            break;

        case NoBool:
            fprintf(gerador.arquivo_saida, "%s", no->valor_bool ? "true" : "false");
            break;

        case NoVariavel:
            fprintf(gerador.arquivo_saida, "%s", no->var);
            break;

        case NoOperacaoBinaria:
            fprintf(gerador.arquivo_saida, "(");
            gerarExpressao(no->esquerdo);
            switch (no->op) {
                case '+': fprintf(gerador.arquivo_saida, " + "); break;
                case '-': fprintf(gerador.arquivo_saida, " - "); break;
                case '*': fprintf(gerador.arquivo_saida, " * "); break;
                case '/': fprintf(gerador.arquivo_saida, " / "); break;
                case '%': fprintf(gerador.arquivo_saida, " %% "); break;
                case 'a': fprintf(gerador.arquivo_saida, " ^ "); break;
                case 'b': fprintf(gerador.arquivo_saida, " // "); break;
                default: fprintf(gerador.arquivo_saida, " ? "); break;
            }
            gerarExpressao(no->direito);
            fprintf(gerador.arquivo_saida, ")");
            break;

        case NoChamadaFuncao:
            fprintf(gerador.arquivo_saida, "%s(", no->nome_funcao ? no->nome_funcao : "funcao");
            if (no->argumentos) {
                ListaNo* atual = no->argumentos;
                while (atual) {
                    gerarExpressao(atual->no);
                    if (atual->prox) {
                        fprintf(gerador.arquivo_saida, ", ");
                    }
                    atual = atual->prox;
                }
            }
            fprintf(gerador.arquivo_saida, ")");
            break;

        default:
            // Para outros tipos que podem aparecer em expressões
            break;
    }
}

void gerarCodigoLua(No* no) {
    if (!no) return;

    switch (no->tipo) {
        case NoAtribuicao:
            indentar();
            if (no->esquerdo && no->esquerdo->tipo == NoVariavel) {
                fprintf(gerador.arquivo_saida, "local %s = ", no->esquerdo->var);
                gerarExpressao(no->direito);
                fprintf(gerador.arquivo_saida, "\n");
            }
            break;

        case NoBloco:
            if (no->lista) {
                gerarBlocoLua(no->lista);
            }
            break;

        case NoIf:
            indentar();
            fprintf(gerador.arquivo_saida, "if ");
            gerarExpressao(no->condicao);
            fprintf(gerador.arquivo_saida, " then\n");
            aumentarIndentacao();
            gerarCodigoLua(no->corpo);
            diminuirIndentacao();
            if (no->senao) {
                indentar();
                fprintf(gerador.arquivo_saida, "else\n");
                aumentarIndentacao();
                gerarCodigoLua(no->senao);
                diminuirIndentacao();
            }
            indentar();
            fprintf(gerador.arquivo_saida, "end\n");
            break;

        case NoWhile:
            indentar();
            fprintf(gerador.arquivo_saida, "while ");
            gerarExpressao(no->condicao);
            fprintf(gerador.arquivo_saida, " do\n");
            aumentarIndentacao();
            gerarCodigoLua(no->corpo);
            diminuirIndentacao();
            indentar();
            fprintf(gerador.arquivo_saida, "end\n");
            break;

        case NoFor:
            indentar();
            fprintf(gerador.arquivo_saida, "for ");
            if (no->esquerdo && no->esquerdo->tipo == NoVariavel) {
                fprintf(gerador.arquivo_saida, "%s = ", no->esquerdo->var);
                gerarExpressao(no->direito);
                fprintf(gerador.arquivo_saida, ", ");
                gerarExpressao(no->condicao);
            }
            fprintf(gerador.arquivo_saida, " do\n");
            aumentarIndentacao();
            gerarCodigoLua(no->corpo);
            diminuirIndentacao();
            indentar();
            fprintf(gerador.arquivo_saida, "end\n");
            break;

        case NoFuncao:
            indentar();
            fprintf(gerador.arquivo_saida, "function %s(", no->nome_funcao ? no->nome_funcao : "funcao");
            if (no->parametros) {
                ListaNo* atual = no->parametros;
                while (atual) {
                    if (atual->no && atual->no->tipo == NoVariavel) {
                        fprintf(gerador.arquivo_saida, "%s", atual->no->var);
                        if (atual->prox) {
                            fprintf(gerador.arquivo_saida, ", ");
                        }
                    }
                    atual = atual->prox;
                }
            }
            fprintf(gerador.arquivo_saida, ")\n");
            aumentarIndentacao();
            gerarCodigoLua(no->corpo);
            diminuirIndentacao();
            indentar();
            fprintf(gerador.arquivo_saida, "end\n");
            break;

        case NoChamadaFuncao:
            indentar();
            gerarExpressao(no);
            fprintf(gerador.arquivo_saida, "\n");
            break;

        default:
            // Para expressões simples ou outros tipos
            indentar();
            gerarExpressao(no);
            fprintf(gerador.arquivo_saida, "\n");
            break;
    }
}

void gerarBlocoLua(ListaNo* lista) {
    ListaNo* atual = lista;
    while (atual) {
        gerarCodigoLua(atual->no);
        atual = atual->prox;
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