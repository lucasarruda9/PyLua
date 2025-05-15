#ifndef AST_H
#define AST_H

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

#endif // AST_H