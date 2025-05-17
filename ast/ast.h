#ifndef AST_H
#define AST_H

#include "../tabela/tabela.h"  // Incluindo a tabela de símbolos

typedef enum {
    NoLiteral,
    NoVariavel,
    NoOperacaoBinaria,
    NoAtribuicao
} Tipo;

typedef struct Arvore{
    Tipo tipo;
    struct Arvore *direito, *esquerdo;
    int valor;
    char* var;
    char op;
}No;

No* CriarNoInteiro(int valor);
No* CriarNoVariavel(char *var);
No* CriarNoOperador(No *esquerda, No *direita, char op);
No* CriaNoAtribuicao(No *var, No *exp);
void DesalocarArvore(struct Arvore* no);
void imprimeArvore(No *no, int nivel);

// Nova função para avaliação da AST
int avaliarArvore(No* no);

#endif // AST_H