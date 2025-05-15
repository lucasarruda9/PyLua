#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela.h"

#define TAM 211

Simbolo *tabela[TAM];

// Função hash para distribuir os símbolos na tabela
unsigned hash(char *s) {
    unsigned h = 0;
    while (*s) h = (h << 4) + *s++;
    return h % TAM;
}

// Inicializa a tabela de símbolos
void inicializarTabela() {
    for (int i = 0; i < TAM; i++) {
        tabela[i] = NULL;
    }
}

// Insere um novo símbolo na tabela
void inserirSimbolo(char *nome, TipoSimbolo tipo) {
    unsigned i = hash(nome);
    Simbolo *s = malloc(sizeof(Simbolo));
    
    if (s == NULL) {
        printf("Erro: Falha ao alocar memória para símbolo\n");
        return;
    }

    strncpy(s->nome, nome, 31);
    s->nome[31] = '\0';  // Garante que a string termina com \0
    s->tipo = tipo;
    s->valor = 0;
    s->valorFloat = 0.0;
    s->valorString = NULL;
    s->inicializada = 0;
    s->proximo = tabela[i];
    tabela[i] = s;
}

// Busca um símbolo na tabela
Simbolo *buscarSimbolo(char *nome) {
    unsigned i = hash(nome);
    for (Simbolo *s = tabela[i]; s; s = s->proximo) {
        if (strcmp(s->nome, nome) == 0) return s;
    }
    return NULL;
}

// Imprime o conteúdo da tabela de símbolos
void imprimirTabela() {
    printf("\n=== Tabela de Símbolos ===\n");
    for (int i = 0; i < TAM; i++) {
        for (Simbolo *s = tabela[i]; s; s = s->proximo) {
            printf("Nome: %s, Tipo: ", s->nome);
            switch (s->tipo) {
                case TIPO_INT:
                    printf("int");
                    if (s->inicializada) printf(" = %d", s->valor);
                    break;
                case TIPO_FLOAT:
                    printf("float");
                    if (s->inicializada) printf(" = %f", s->valorFloat);
                    break;
                case TIPO_STRING:
                    printf("string");
                    if (s->inicializada && s->valorString) printf(" = %s", s->valorString);
                    break;
                case TIPO_BOOL:
                    printf("bool");
                    if (s->inicializada) printf(" = %s", s->valor ? "true" : "false");
                    break;
                case TIPO_NONE:
                    printf("none");
                    break;
            }
            printf("\n");
        }
    }
    printf("========================\n\n");
}

// Libera a memória alocada para a tabela de símbolos
void liberarTabela() {
    for (int i = 0; i < TAM; i++) {
        Simbolo *atual = tabela[i];
        while (atual != NULL) {
            Simbolo *proximo = atual->proximo;
            if (atual->tipo == TIPO_STRING && atual->valorString != NULL) {
                free(atual->valorString);
            }
            free(atual);
            atual = proximo;
        }
        tabela[i] = NULL;
    }
}