#ifndef GERADOR_CODIGO_FINAL_H 
#define GERADOR_CODIGO_FINAL_H

#include "../ast/ast.h"
#include <stdio.h>

// Estrutura para controlar a geração de código
typedef struct {
    FILE* arquivo_saida;
    int nivel_indentacao;
} GeradorCodigo;

// Funções do gerador de código
void inicializarGerador(FILE* arquivo_saida);
void gerarCodigoLua(No* no);
void finalizarGerador();

#endif