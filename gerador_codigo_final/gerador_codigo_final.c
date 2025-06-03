#include "gerador_codigo_final.h"
#include <stdio.h>
#include <stdlib.h>

static GeradorCodigo gerador = {NULL, 0};

void inicializarGerador(FILE* arquivo_saida) {
    gerador.arquivo_saida = arquivo_saida;
    gerador.nivel_indentacao = 0;
}

static void indentar() {
    for (int i = 0; i < gerador.nivel_indentacao; i++) {
        fprintf(gerador.arquivo_saida, "  ");
    }
}

static void gerarExpressao(No* no) {
    if (!no) return;

    switch (no->tipo) {
        case NoLiteral:
            fprintf(gerador.arquivo_saida, "%d", no->valor);
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
            }
            gerarExpressao(no->direito);
            fprintf(gerador.arquivo_saida, ")");
            break;
            
        case NoAtribuicao:
            if (no->esquerdo->tipo == NoVariavel) {
                fprintf(gerador.arquivo_saida, "local %s = ", no->esquerdo->var);
                gerarExpressao(no->direito);
            }
            break;
    }
}

void gerarCodigoLua(No* no) {
    if (!no) return;

    switch (no->tipo) {
        case NoAtribuicao:
            indentar();
            gerarExpressao(no);
            fprintf(gerador.arquivo_saida, "\n");
            break;
            
        default:
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
}