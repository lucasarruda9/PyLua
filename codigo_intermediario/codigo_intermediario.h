#ifndef CODIGO_INTERMEDIARIO_H
#define CODIGO_INTERMEDIARIO_H

#include "../ast/ast.h"
#include <stdio.h>

typedef struct {
    FILE* arquivo_saida;
    int contador_temp;
    int contador_label;
} GeradorTAC;

void inicializarGeradorTAC(FILE* arquivo_saida);
char* gerarCodigoTAC(No* no);
void gerarBlocoTAC(ListaNo* lista);
void finalizarGeradorTAC();

char* novaVariavelTemp();
char* novoLabel();
char* gerarExpressaoTAC(No* no);
void imprimirInstrucaoTAC(const char* resultado, const char* op1, char operador, const char* op2);

#endif
