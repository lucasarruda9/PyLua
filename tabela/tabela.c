#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tabela.h"

 Escopo *escopo_atual = NULL;

// Função hash para distribuir os símbolos na tabela
unsigned hash(char *s) {
    unsigned h = 0;
    while (*s) h = (h << 4) + *s++;
    return h % TAM;
}

void entrarEscopo() {
    Escopo* novo = malloc(sizeof(Escopo));
    for (int i = 0; i < TAM; i++) novo->tabela[i] = NULL;
    novo->pai = escopo_atual;
    escopo_atual = novo;
    printf("[DEBUG] Entrando em escopo\n");
}

// Sair do escopo atual
void sairEscopo() {
    printf("[DEBUG] Saindo de escopo\n");
    for (int i = 0; i < TAM; i++) {
        Simbolo* s = escopo_atual->tabela[i];
        while (s) {
            Simbolo* temp = s;
            s = s->proximo;
            free(temp);
        }
    }
    Escopo* anterior = escopo_atual->pai;
    free(escopo_atual);
    escopo_atual = anterior;
}

// Insere um novo símbolo na tabela
void inserirSimbolo(char *nome, TipoSimbolo tipo) {
    if (!escopo_atual) entrarEscopo();
    unsigned i = hash(nome);
  

    Simbolo* novo = malloc(sizeof(Simbolo));
    strncpy(novo->nome, nome, 31);
    novo->nome[31] = '\0';
    novo->tipo = tipo;
    novo->proximo = escopo_atual->tabela[i];
    escopo_atual->tabela[i] = novo;
}

// Busca um símbolo na tabela
Simbolo *buscarSimbolo(char *nome) {
    Escopo* esc = escopo_atual;
    while (esc) {
        unsigned i = hash(nome);
        Simbolo* s = esc->tabela[i];
        while (s) {
            if (strcmp(s->nome, nome) == 0) return s;
            s = s->proximo;
        }
        esc = esc->pai;
    }
    return NULL;
}

// Imprime o conteúdo da tabela de símbolos
void imprimirTabela() {// Imprime todos os escopos (debug){
    Escopo* esc = escopo_atual;
    int nivel = 0;
    printf("\n=== Tabela de Símbolos ===\n");
    while (esc) {
        
        printf("\nEscopo nível %d\n", nivel++);
        for (int i = 0; i < TAM; i++) {
            Simbolo* s = esc->tabela[i];
            while (s) {
                printf("Nome: %s Tipo: %d\n", s->nome, s->tipo);
                s = s->proximo;
            }
        }
        esc = esc->pai;
    }
    printf("============================\n");
}

// Libera a memória alocada para a tabela de símbolos
void liberarTabela()  {
    while (escopo_atual != NULL) {
        sairEscopo();
    }
}

// Verifica se um símbolo existe na tabela
bool existeSimbolo(char *nome) {
    return buscarSimbolo(nome) != NULL;
}