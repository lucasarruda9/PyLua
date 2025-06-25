#ifndef TABELA_H
#define TABELA_H
#define TAM 211
#include <stdbool.h>

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
    struct simbolo *proximo;
} Simbolo;

typedef struct escopo {
    Simbolo *tabela[TAM];
    struct escopo *pai;
} Escopo;

// Funções da tabela de símbolos
void inicializarTabela();
void entrarEscopo();
void sairEscopo();
void inserirSimbolo(char *nome, TipoSimbolo tipo);
Simbolo *buscarSimbolo(char *nome);
void imprimirTabela();
void liberarTabela();
bool existeSimbolo(char *nome);


TipoSimbolo obterTipo(char *nome);

#endif