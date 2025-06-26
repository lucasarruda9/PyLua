#ifndef AST_H
#define AST_H

#include "../tabela/tabela.h"  // Incluindo a tabela de símbolos

typedef enum {
    NoLiteral,
    NoVariavel,
    NoOperacaoBinaria,
    NoAtribuicao,
    NoFloat,
    NoString,
    NoBool,
    NoBloco,
    NoIf,
    NoWhile,
    NoFor,
    NoReturn,
    NoFuncao,
    NoChamadaFuncao
} Tipo;

// Lista de nós (para blocos, argumentos, parâmetros, etc)
typedef struct ListaNo {
    struct Arvore* no;
    struct ListaNo* prox;
} ListaNo;

typedef struct Arvore{
    Tipo tipo;
    struct Arvore *direita, *meio, *esquerda;
    int valor;
    float valor_float;
    char* valor_str;
    int valor_bool;
    char* var;
    char op;
    ListaNo *lista;
}No;

No* CriarNoInteiro(int valor);
No* CriarNoVariavel(char *var);
No* CriarNoOperador(No *esquerda, No *direita, char op);
No* CriaNoAtribuicao(No *var, No *exp);

// Funções de criação para novos tipos de nó
No* CriarNoFloat(float valor);
No* CriarNoString(char* valor);
No* CriarNoBool(int valor);
No* CriarNoBloco(ListaNo* lista);
No* CriarNoIf(No* condicao, No* corpo, No* senao);
No* CriarNoWhile(No* condicao, No* corpo);
No* CriarNoFor(No* init, No* cond, No* inc, No* corpo);
No* CriarNoFuncao(char* nome, ListaNo* parametros, No* corpo);
No* CriarNoChamadaFuncao(char* nome, ListaNo* argumentos);
No* CriarNoLista(ListaNo* elementos);
No* CriarNoIndexacao(No* lista, No* indice);
No* CriarNoReturn(No* valor);
ListaNo* CriarListaElementos(No* elemento, ListaNo* prox);
ListaNo* AdicionarNoLista(ListaNo* lista, No* no);

void DesalocarArvore(struct Arvore* no);
void imprimeArvore(No *no, int nivel);
void imprimeLista(ListaNo* lista, int nivel);


#endif // AST_H