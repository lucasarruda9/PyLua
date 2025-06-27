#ifndef GERADOR_CODIGO_FINAL_H
#define GERADOR_CODIGO_FINAL_H

#include "../ast/ast.h"
#include "otimizador.h"
#include <stdio.h>

// Estrutura para controlar a geração de código
typedef struct {
    FILE* arquivo_saida;
    int nivel_indentacao;
    int contador_variaveis_temp;
    Opcoes_Otimizacao opcoes_otimizacao;
} GeradorCodigo;

// Funções principais do gerador de código
void inicializarGerador(FILE* arquivo_saida);
void gerarCodigoLua(No* no);
void gerarBlocoLua(ListaNo* lista);
void finalizarGerador();

// Nova função para geração otimizada
void gerarCodigoLuaOtimizado(No* no);
void configurarOtimizacoes(bool dce, bool cf, bool asif, bool cse);
void habilitarTodasOtimizacoes();
void desabilitarTodasOtimizacoes();

// Funções auxiliares
void aumentarIndentacao();
void diminuirIndentacao();
char* obterVariavelTemporaria();

#endif