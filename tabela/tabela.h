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
    int valor;           // Para armazenar valores inteiros
    float valorFloat;    // Para armazenar valores float
    char* valorString;   // Para armazenar strings
    int inicializada;    // Flag para verificar se a variável foi inicializada
    struct simbolo *proximo;
} Simbolo;

typedef struct Escopo {
    Simbolo *tabela;           // Ponteiro para a tabela de símbolos deste escopo
    struct Escopo *anterior;   // Ponteiro para o escopo anterior (pilha)
} Escopo;

extern Escopo *escopo_atual;

// Funções para manipular escopos
void entrarEscopo();
void sairEscopo();
Simbolo *buscarSimboloEscopo(const char *nome);
void inserirSimboloEscopo(const char *nome, int tipo);

// Funções da tabela de símbolos
void inicializarTabela();
void inserirSimbolo(char *nome, TipoSimbolo tipo);
Simbolo *buscarSimbolo(char *nome);
void imprimirTabela();
void liberarTabela();

// Novas funções para melhorar a funcionalidade
bool existeSimbolo(char *nome);
void definirValorInteiro(char *nome, int valor);
void definirValorFloat(char *nome, float valor);
void definirValorString(char *nome, char *valor);
void definirValorBool(char *nome, bool valor);
int obterValorInteiro(char *nome);
float obterValorFloat(char *nome);
char* obterValorString(char *nome);
bool obterValorBool(char *nome);
TipoSimbolo obterTipo(char *nome);

#endif