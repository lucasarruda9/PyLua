#ifndef GERADOR_CODIGO_FINAL_H
#define GERADOR_CODIGO_FINAL_H

#include "../ast/ast.h"
#include <stdio.h>

// Estrutura para controlar a geração de código
typedef struct {
    FILE* arquivo_saida;
    int nivel_indentacao;
    int contador_variaveis_temp;
} GeradorCodigo;

// Funções principais do gerador de código
void inicializarGerador(FILE* arquivo_saida);
void gerarCodigoLua(No* no);
void gerarBlocoLua(ListaNo* lista);
void finalizarGerador();

// Funções auxiliares
void aumentarIndentacao();
void diminuirIndentacao();
char* obterVariavelTemporaria();

#endif