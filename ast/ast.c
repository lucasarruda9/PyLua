#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../ast/ast.h"
#include "../tabela/tabela.h"

No *CriarNo(Tipo t, No *esquerda, No *direita){
    No *raiz = malloc(sizeof(No));
    raiz->esquerda = esquerda;
    raiz->direita = direita;
    raiz->meio = NULL;
    raiz->valor = 0;
    raiz->var = NULL;
    raiz->op = 0;
    raiz->tipo = t;
    return raiz;
}

No *CriarNoInteiro(int valor){
    No *raiz = CriarNo(NoLiteral, NULL, NULL);
    raiz->valor = valor;
    return raiz;
}

No *CriarNoVariavel(char *var){
    No *raiz = CriarNo(NoVariavel, NULL, NULL);
    raiz->var = var;
    return raiz;
}

No *CriarNoOperador(No *esquerda, No *direita, char op){
    No *raiz = CriarNo(NoOperacaoBinaria, esquerda, direita);
    raiz->op = op;
    return raiz;
}

No *CriaNoAtribuicao(No *var, No *exp){
    No *raiz = CriarNo(NoAtribuicao, var, exp);
    return raiz;
}

No* CriarNoBloco(ListaNo* lista) {
    No *raiz = CriarNo(NoBloco, NULL, NULL);
    raiz->lista = lista;
    return raiz;
}

No* CriarNoIf(No* condicao, No* corpo, No* senao) {
    No *raiz = CriarNo(NoIf, condicao, senao);
    raiz->meio = corpo;
    return raiz;
}
No *CriarNoFloat(float valor_float){
    No *raiz = CriarNo(NoFloat, NULL, NULL);
    raiz->valor_float = valor_float;
    return raiz;
}

void DesalocarArvore(No *raiz){
    if(raiz == NULL){
        return;
    }
    DesalocarArvore(raiz->esquerda);
    DesalocarArvore(raiz->direita);
    DesalocarArvore(raiz->meio);
    free(raiz);
}

void imprimeLista(ListaNo* lista, int nivel) {
    ListaNo* atual = lista;
    while (atual != NULL) {
        imprimeArvore(atual->no, nivel);
        atual = atual->prox;
    }
}

void apagaLista(ListaNo* lista) {
    ListaNo *atual = lista;
    while(atual != NULL){
        DesalocarArvore(atual->no);
        ListaNo *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

}

//essa funcao so serve pra debug
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
        case NoFloat:
            printf("Float: %.2f\n", no->valor_float);
            break;
        case NoVariavel:
            printf("Variavel: %s\n", no->var);
            break;
        case NoOperacaoBinaria:
            printf("Operacao: %c\n", no->op);
            if (no->esquerda) imprimeArvore(no->esquerda, nivel + 1);
            if (no->direita) imprimeArvore(no->direita, nivel + 1);
            break;
        case NoAtribuicao:
            printf("Atribuicao\n");
            if (no->esquerda) imprimeArvore(no->esquerda, nivel + 1);
            if (no->direita) imprimeArvore(no->direita, nivel + 1);
            break;
        case NoBloco:
            printf("Bloco:\n");
            imprimeLista(no->lista, nivel + 1);
            break;
        case NoIf:
            printf("If:\n");
            for (i = 0; i < nivel + 1; i++) printf("    ");
            printf("Condicao:\n");
            imprimeArvore(no->esquerda, nivel + 2);
            for (i = 0; i < nivel + 1; i++) printf("    ");
            printf("Corpo:\n");
            imprimeArvore(no->meio, nivel + 2);
            if (no->direita) {
                for (i = 0; i < nivel + 1; i++) printf("    ");
                printf("Senao:\n");
                imprimeArvore(no->direita, nivel + 2);
            }
            break;
        case NoWhile:
            printf("While:\n");
            for (i = 0; i < nivel + 1; i++) printf("    ");
            printf("Condicao:\n");
            imprimeArvore(no->esquerda, nivel + 2);
            for (i = 0; i < nivel + 1; i++) printf("    ");
            printf("Corpo:\n");
            imprimeArvore(no->meio, nivel + 2);
            break;
        case NoFor:
            printf("For:\n");
            for (i = 0; i < nivel + 1; i++) printf("    ");
            printf("Var:\n");
            imprimeArvore(no->esquerda, nivel + 2);
            for (i = 0; i < nivel + 1; i++) printf("    ");
            printf("Inicio:\n");
            imprimeArvore(no->direita, nivel + 2);
            for (i = 0; i < nivel + 1; i++) printf("    ");
            printf("Fim:\n");
            imprimeArvore(no->esquerda, nivel + 2);
            for (i = 0; i < nivel + 1; i++) printf("    ");
            printf("Corpo:\n");
            imprimeArvore(no->meio, nivel + 2);
            break;
            printf("[Tipo de nó desconhecido]\n");
    }
}

ListaNo* AdicionarNoLista(ListaNo* lista, No* no) {
    ListaNo* novo = malloc(sizeof(ListaNo));
    novo->no = no;
    novo->prox = NULL;
    if (!lista) return novo;
    ListaNo* atual = lista;
    while (atual->prox) atual = atual->prox;
    atual->prox = novo;
    return lista;
}




