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
    struct Arvore *direito, *esquerdo;
    int valor;
    float valor_float;
    char* valor_str;
    int valor_bool;
    char* var;
    char op;
    // Para blocos e listas
    ListaNo* lista;
    // Para if/while/for
    struct Arvore* condicao;
    struct Arvore* corpo;
    struct Arvore* senao;
    // Para funções
    char* nome_funcao;
    ListaNo* parametros;
    ListaNo* argumentos;
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
No* CriarNoFor(No* var, No* inicio, No* fim, No* corpo);
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

// Nova função para avaliação da AST
int avaliarArvore(No* no);

#endif // AST_H