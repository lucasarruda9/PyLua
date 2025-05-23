#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../ast/ast.h"
#include "../tabela/tabela.h"

No *CriarNoInteiro(int valor){
    No *raiz = malloc(sizeof(No));
    raiz->tipo = NoLiteral;
    raiz->direito = NULL;
    raiz->esquerdo = NULL;
    raiz->valor = valor;
    raiz->var = NULL;
    raiz->op = 0;
    return raiz;
}

No *CriarNoVariavel(char *var){
    No *raiz = malloc(sizeof(No));
    raiz->tipo = NoVariavel;
    raiz->direito = NULL;
    raiz->esquerdo = NULL;
    raiz->valor = 0;
    raiz->var = var;
    raiz->op = 0;
    return raiz;
}

No *CriarNoOperador(No *esquerda, No *direita, char op){
    No *raiz = malloc(sizeof(No));
    raiz->tipo = NoOperacaoBinaria;
    raiz->direito = direita;
    raiz->esquerdo = esquerda;
    raiz->op = op;
    raiz->valor = 0;
    raiz->var = NULL;
    return raiz;
}

No *CriaNoAtribuicao(No *var, No *exp){
    No *raiz = malloc(sizeof(No));
    raiz->tipo = NoAtribuicao;
    raiz->esquerdo = var;
    raiz->direito = exp;
    raiz->op = 0;
    raiz->valor = 0;
    raiz->var = NULL;
    return raiz;
}

void DesalocarArvore(No *raiz){
    if(raiz == NULL){
        return;
    }
    DesalocarArvore(raiz->esquerdo);
    DesalocarArvore(raiz->direito);
    free(raiz);
}

void imprimeArvore(No *no, int nivel) {
    int i;

    if (no == NULL) return;

    // Imprime o nó atual
    for (i = 0; i < nivel; i++) {
        printf("    ");  // Indentação
    }

    switch (no->tipo) {
        case NoLiteral:
            printf("Literal: %d\n", no->valor);
            break;
        case NoVariavel:
            printf("Variavel: %s\n", no->var);
            break;
        case NoOperacaoBinaria:
            printf("Operacao: %c\n", no->op);
            break;
        case NoAtribuicao:
            printf("Atribuicao\n");
            break;
    }

    // Imprime os filhos com indentação
    if (no->esquerdo != NULL) {
        imprimeArvore(no->esquerdo, nivel + 1);
    }
    if (no->direito != NULL) {
        imprimeArvore(no->direito, nivel + 1);
    }
}

// Nova função para avaliação da AST
int avaliarArvore(No* no) {
    if (no == NULL) return 0;
    
    int valorEsq, valorDir, resultado;
    Simbolo* simbolo;
    
    switch (no->tipo) {
        case NoLiteral:
            return no->valor;
            
        case NoVariavel:
            simbolo = buscarSimbolo(no->var);
            if (simbolo == NULL) {
                printf("[ERRO] Variável '%s' não encontrada\n", no->var);
                return 0;
            }
            if (!simbolo->inicializada) {
                printf("[AVISO] Variável '%s' usada sem inicialização\n", no->var);
                return 0;
            }
            return simbolo->valor;
            
        case NoOperacaoBinaria:
            valorEsq = avaliarArvore(no->esquerdo);
            
            // Operador unário (negação)
            if (no->direito == NULL && no->op == '-') {
                return -valorEsq;
            }
            
            valorDir = avaliarArvore(no->direito);
            
            switch (no->op) {
                case '+': resultado = valorEsq + valorDir; break;
                case '-': resultado = valorEsq - valorDir; break;
                case '*': resultado = valorEsq * valorDir; break;
                case '/': 
                    if (valorDir == 0) {
                        printf("[ERRO] Divisão por zero\n");
                        return 0;
                    }
                    resultado = valorEsq / valorDir; 
                    break;
                case '%': 
                    if (valorDir == 0) {
                        printf("[ERRO] Módulo por zero\n");
                        return 0;
                    }
                    resultado = valorEsq % valorDir; 
                    break;
                case 'a': // Power **=
                    resultado = (int)pow(valorEsq, valorDir);
                    break;
                case 'b': // Floor division //=
                    if (valorDir == 0) {
                        printf("[ERRO] Divisão por zero\n");
                        return 0;
                    }
                    resultado = valorEsq / valorDir;
                    break;
                default:
                    printf("[ERRO] Operador desconhecido: %c\n", no->op);
                    resultado = 0;
            }
            return resultado;
            
        case NoAtribuicao:
            if (no->esquerdo->tipo != NoVariavel) {
                printf("[ERRO] Lado esquerdo da atribuição deve ser uma variável\n");
                return 0;
            }
            
            resultado = avaliarArvore(no->direito);
            
            simbolo = buscarSimbolo(no->esquerdo->var);
            if (simbolo == NULL) {
                inserirSimbolo(no->esquerdo->var, TIPO_INT);
                simbolo = buscarSimbolo(no->esquerdo->var);
            }
            
            simbolo->valor = resultado;
            simbolo->inicializada = 1;
            
            return resultado;
            
        default:
            printf("[ERRO] Tipo de nó desconhecido: %d\n", no->tipo);
            return 0;
    }
}