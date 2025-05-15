#ifndef TABELA_H
#define TABELA_H

#include "../ast/ast.h"

typedef enum {
    TIPO_INT,
    TIPO_FLOAT,
    TIPO_STRING,
    TIPO_BOOL,
    TIPO_NONE
} TipoSimbolo;

typedef struct simbolo {
    char nome[32];
    TipoSimbolo tipo;
    int valor;           // Para armazenar valores inteiros
    float valorFloat;    // Para armazenar valores float
    char* valorString;   // Para armazenar strings
    int inicializada;    // Flag para verificar se a variável foi inicializada
    struct simbolo *proximo;
} Simbolo;

// Funções da tabela de símbolos
void inicializarTabela();
void inserirSimbolo(char *nome, TipoSimbolo tipo);
Simbolo *buscarSimbolo(char *nome);
void imprimirTabela();
void liberarTabela();

#endif