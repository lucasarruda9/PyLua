#include <stdio.h>
#include <stdlib.h>
#include "../ast/ast.h"

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

void imprimeArvore(No *no) {
    if (no == NULL) return;

    if (no->tipo == NoLiteral) {
        printf("%d", no->valor);
    } else if (no->tipo == NoVariavel) {
        printf("%s", no->var);
    } else if (no->tipo == NoOperacaoBinaria) {
        printf("(");
        imprimeArvore(no->esquerdo);  // Imprime a subexpressão esquerda
        printf(" %c ", no->op);       // Imprime o operador
        imprimeArvore(no->direito);   // Imprime a subexpressão direita
        printf(")");
    } else if (no->tipo == NoAtribuicao) {
        imprimeArvore(no->esquerdo);  // Imprime a variável
        printf(" = ");
        imprimeArvore(no->direito);   // Imprime a expressão do lado direito
    }
}