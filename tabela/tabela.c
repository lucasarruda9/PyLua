#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tabela.h"

#define TAM 211

Simbolo *tabela[TAM];

Escopo *escopo_atual = NULL;

void entrarEscopo() {
    Escopo *novo = (Escopo *)malloc(sizeof(Escopo));
    novo->tabela = NULL;
    novo->anterior = escopo_atual;
    escopo_atual = novo;
}

void sairEscopo() {
    if (escopo_atual) {
        Simbolo *s = escopo_atual->tabela;
        while (s) {
            Simbolo *tmp = s;
            s = s->proximo;
            free(tmp);
        }
        Escopo *tmp = escopo_atual;
        escopo_atual = escopo_atual->anterior;
        free(tmp);
    }
}

Simbolo *buscarSimboloEscopo(const char *nome) {
    Escopo *esc = escopo_atual;
    while (esc) {
        Simbolo *s = esc->tabela;
        while (s) {
            if (strcmp(s->nome, nome) == 0)
                return s;
            s = s->proximo;
        }
        esc = esc->anterior;
    }
    return NULL;
}

void inserirSimboloEscopo(const char *nome, int tipo) {
    if (!escopo_atual) entrarEscopo();
    // Verifica redeclaração no escopo atual
    Simbolo *s = escopo_atual->tabela;
    while (s) {
        if (strcmp(s->nome, nome) == 0) {
            printf("[ERRO] Variável '%s' já declarada neste escopo\n", nome);
            return;
        }
        s = s->proximo;
    }
    Simbolo *novo = (Simbolo *)malloc(sizeof(Simbolo));
    strcpy(novo->nome, nome);
    novo->tipo = tipo;
    novo->proximo = escopo_atual->tabela;
    escopo_atual->tabela = novo;
}

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
            printf("Nome: %s, Tipo: %d", s->nome, s->tipo);
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

// Verifica se um símbolo existe na tabela
bool existeSimbolo(char *nome) {
    return buscarSimbolo(nome) != NULL;
}
