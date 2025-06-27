#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tabela.h"

#define TAM 211

Simbolo *tabela[TAM];
static int escopo_atual = 0;

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
    escopo_atual = 0;
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
    s->escopo = escopo_atual;  // Define o escopo atual
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

    // Organizar por escopo
    for (int escopo = 0; escopo <= escopo_atual; escopo++) {
        bool tem_simbolos = false;

        // Verificar se há símbolos neste escopo
        for (int i = 0; i < TAM; i++) {
            for (Simbolo *s = tabela[i]; s; s = s->proximo) {
                if (s->escopo == escopo) {
                    if (!tem_simbolos) {
                        printf("\nEscopo nível %d\n", escopo);
                        tem_simbolos = true;
                    }
                    printf("Nome: %s Tipo: %d\n", s->nome, s->tipo);
                }
            }
        }
    }
    printf("============================\n");
}

// Libera a memória alocada para a tabela de símbolos
void liberarTabela() {
    for (int i = 0; i < TAM; i++) {
        Simbolo *atual = tabela[i];
        while (atual != NULL) {
            Simbolo *proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
        tabela[i] = NULL;
    }
}

// Funções de controle de escopo
void entrarEscopo() {
    escopo_atual++;
    #ifdef DEBUG
    printf("[DEBUG] Entrando em escopo\n");
    #endif
}

void sairEscopo() {
    if (escopo_atual > 0) {
        // Remove símbolos do escopo atual
        for (int i = 0; i < TAM; i++) {
            Simbolo **atual = &tabela[i];
            while (*atual) {
                if ((*atual)->escopo == escopo_atual) {
                    Simbolo *temp = *atual;
                    *atual = (*atual)->proximo;
                    free(temp);
                } else {
                    atual = &((*atual)->proximo);
                }
            }
        }
        escopo_atual--;
        #ifdef DEBUG
        printf("[DEBUG] Saindo de escopo\n");
        #endif
    }
}

int obterEscopoAtual() {
    return escopo_atual;
}

// Verifica se um símbolo existe na tabela
bool existeSimbolo(char *nome) {
    return buscarSimbolo(nome) != NULL;
}
