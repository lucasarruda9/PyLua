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

// Verifica se um símbolo existe na tabela
bool existeSimbolo(char *nome) {
    return buscarSimbolo(nome) != NULL;
}

// Define um valor inteiro para um símbolo
void definirValorInteiro(char *nome, int valor) {
    Simbolo *s = buscarSimbolo(nome);
    
    if (s == NULL) {
        inserirSimbolo(nome, TIPO_INT);
        s = buscarSimbolo(nome);
    } else if (s->tipo != TIPO_INT) {
        printf("[AVISO] Conversão de tipo para '%s' (de %d para int)\n", nome, s->tipo);
        s->tipo = TIPO_INT;
    }
    
    s->valor = valor;
    s->inicializada = 1;
}

// Define um valor float para um símbolo
void definirValorFloat(char *nome, float valor) {
    Simbolo *s = buscarSimbolo(nome);
    
    if (s == NULL) {
        inserirSimbolo(nome, TIPO_FLOAT);
        s = buscarSimbolo(nome);
    } else if (s->tipo != TIPO_FLOAT) {
        printf("[AVISO] Conversão de tipo para '%s' (de %d para float)\n", nome, s->tipo);
        s->tipo = TIPO_FLOAT;
    }
    
    s->valorFloat = valor;
    s->inicializada = 1;
}

// Define um valor string para um símbolo
void definirValorString(char *nome, char *valor) {
    Simbolo *s = buscarSimbolo(nome);
    
    if (s == NULL) {
        inserirSimbolo(nome, TIPO_STRING);
        s = buscarSimbolo(nome);
    } else if (s->tipo != TIPO_STRING) {
        printf("[AVISO] Conversão de tipo para '%s' (de %d para string)\n", nome, s->tipo);
        s->tipo = TIPO_STRING;
        if (s->valorString != NULL) {
            free(s->valorString);
            s->valorString = NULL;
        }
    }
    
    // Libera a string anterior, se existir
    if (s->valorString != NULL) {
        free(s->valorString);
    }
    
    // Aloca e copia a nova string
    s->valorString = strdup(valor);
    s->inicializada = 1;
}

// Define um valor booleano para um símbolo
void definirValorBool(char *nome, bool valor) {
    Simbolo *s = buscarSimbolo(nome);
    
    if (s == NULL) {
        inserirSimbolo(nome, TIPO_BOOL);
        s = buscarSimbolo(nome);
    } else if (s->tipo != TIPO_BOOL) {
        printf("[AVISO] Conversão de tipo para '%s' (de %d para bool)\n", nome, s->tipo);
        s->tipo = TIPO_BOOL;
    }
    
    s->valor = valor ? 1 : 0;
    s->inicializada = 1;
}

// Obtém o valor inteiro de um símbolo
int obterValorInteiro(char *nome) {
    Simbolo *s = buscarSimbolo(nome);
    
    if (s == NULL) {
        printf("[ERRO] Tentativa de acessar variável não declarada: '%s'\n", nome);
        return 0;
    }
    
    if (!s->inicializada) {
        printf("[AVISO] Tentativa de acessar variável não inicializada: '%s'\n", nome);
        return 0;
    }
    
    if (s->tipo != TIPO_INT) {
        printf("[AVISO] Conversão implícita de tipo ao acessar '%s'\n", nome);
        
        switch (s->tipo) {
            case TIPO_FLOAT:
                return (int)s->valorFloat;
            case TIPO_BOOL:
                return s->valor;
            case TIPO_STRING:
                printf("[ERRO] Não é possível converter string para int: '%s'\n", nome);
                return 0;
            default:
                return 0;
        }
    }
    
    return s->valor;
}

// Obtém o valor float de um símbolo
float obterValorFloat(char *nome) {
    Simbolo *s = buscarSimbolo(nome);
    
    if (s == NULL) {
        printf("[ERRO] Tentativa de acessar variável não declarada: '%s'\n", nome);
        return 0.0;
    }
    
    if (!s->inicializada) {
        printf("[AVISO] Tentativa de acessar variável não inicializada: '%s'\n", nome);
        return 0.0;
    }
    
    if (s->tipo != TIPO_FLOAT) {
        printf("[AVISO] Conversão implícita de tipo ao acessar '%s'\n", nome);
        
        switch (s->tipo) {
            case TIPO_INT:
                return (float)s->valor;
            case TIPO_BOOL:
                return (float)s->valor;
            case TIPO_STRING:
                printf("[ERRO] Não é possível converter string para float: '%s'\n", nome);
                return 0.0;
            default:
                return 0.0;
        }
    }
    
    return s->valorFloat;
}

// Obtém o valor string de um símbolo
char* obterValorString(char *nome) {
    Simbolo *s = buscarSimbolo(nome);
    
    if (s == NULL) {
        printf("[ERRO] Tentativa de acessar variável não declarada: '%s'\n", nome);
        return NULL;
    }
    
    if (!s->inicializada) {
        printf("[AVISO] Tentativa de acessar variável não inicializada: '%s'\n", nome);
        return NULL;
    }
    
    if (s->tipo != TIPO_STRING) {
        printf("[AVISO] Variável '%s' não é do tipo string\n", nome);
        return NULL;
    }
    
    return s->valorString;
}

// Obtém o valor booleano de um símbolo
bool obterValorBool(char *nome) {
    Simbolo *s = buscarSimbolo(nome);
    
    if (s == NULL) {
        printf("[ERRO] Tentativa de acessar variável não declarada: '%s'\n", nome);
        return false;
    }
    
    if (!s->inicializada) {
        printf("[AVISO] Tentativa de acessar variável não inicializada: '%s'\n", nome);
        return false;
    }
    
    if (s->tipo != TIPO_BOOL) {
        printf("[AVISO] Conversão implícita de tipo ao acessar '%s'\n", nome);
        
        switch (s->tipo) {
            case TIPO_INT:
                return s->valor != 0;
            case TIPO_FLOAT:
                return s->valorFloat != 0.0;
            case TIPO_STRING:
                return s->valorString != NULL && s->valorString[0] != '\0';
            default:
                return false;
        }
    }
    
    return s->valor != 0;
}

// Obtém o tipo de um símbolo
TipoSimbolo obterTipo(char *nome) {
    Simbolo *s = buscarSimbolo(nome);
    
    if (s == NULL) {
        printf("[ERRO] Tentativa de obter tipo de variável não declarada: '%s'\n", nome);
        return TIPO_NONE;
    }
    
    return s->tipo;
}