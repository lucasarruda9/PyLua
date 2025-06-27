#ifndef TABELA_H
#define TABELA_H

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
    int escopo;          // Nível do escopo onde foi declarada
    struct simbolo *proximo;
} Simbolo;

// Funções da tabela de símbolos
void inicializarTabela();
void inserirSimbolo(char *nome, TipoSimbolo tipo);
Simbolo *buscarSimbolo(char *nome);
void imprimirTabela();
void liberarTabela();

// Funções de controle de escopo
void entrarEscopo();
void sairEscopo();
int obterEscopoAtual();

// Novas funções para melhorar a funcionalidade
bool existeSimbolo(char *nome);

TipoSimbolo obterTipo(char *nome);

#endif