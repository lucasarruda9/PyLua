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

No* CriarNoFloat(float valor) {
    No *raiz = CriarNo(NoFloat, NULL, NULL);
    raiz->valor_float = valor;
    return raiz;
}

No* CriarNoString(char* valor) {
    No *raiz = CriarNo(NoString, NULL, NULL);
    raiz->valor_str = valor;
    return raiz;
}

No* CriarNoBool(int valor) {
    No *raiz = CriarNo(NoBool, NULL, NULL);
    raiz->valor_bool = valor;
    return raiz;
}

No* CriarNoWhile(No* condicao, No* corpo) {
    No *raiz = CriarNo(NoWhile, condicao, NULL);
    raiz->meio = corpo;
    return raiz;
}

No* CriarNoFor(No* init, No* cond, No* inc, No* corpo) {
    No *raiz = CriarNo(NoFor, init, inc);
    raiz->meio = cond;
    // Armazenar corpo na lista para manter consistência
    raiz->lista = AdicionarNoLista(NULL, corpo);
    return raiz;
}

No* CriarNoFuncao(char* nome, ListaNo* parametros, No* corpo) {
    No *raiz = CriarNo(NoFuncao, NULL, NULL);
    raiz->var = nome;
    raiz->lista = AdicionarNoLista(NULL, corpo);
    // TODO: tratar parâmetros
    return raiz;
}

No* CriarNoChamadaFuncao(char* nome, ListaNo* argumentos) {
    No *raiz = CriarNo(NoChamadaFuncao, NULL, NULL);
    raiz->var = nome;
    raiz->lista = argumentos;
    return raiz;
}
No* CriarNoLista(ListaNo* elementos) {
    No* no = malloc(sizeof(No));
    no->tipo = NoBloco; // Ou crie um tipo específico, ex: NoLista
    no->lista = elementos;
    no->direito = no->esquerdo = NULL;
    no->valor = 0;
    no->valor_float = 0.0;
    no->valor_str = NULL;
    no->valor_bool = 0;
    no->var = NULL;
    no->op = 0;
    no->condicao = NULL;
    no->corpo = NULL;
    no->senao = NULL;
    no->nome_funcao = NULL;
    no->parametros = NULL;
    no->argumentos = NULL;
    return no;
}

No* CriarNoIndexacao(No* lista, No* indice) {
    No* no = malloc(sizeof(No));
    no->tipo = NoOperacaoBinaria; // Ou crie um tipo específico, ex: NoIndexacao
    no->esquerdo = lista;
    no->direito = indice;
    no->valor = 0;
    no->valor_float = 0.0;
    no->valor_str = NULL;
    no->valor_bool = 0;
    no->var = NULL;
    no->op = '@'; // Use um símbolo especial para indexação
    no->lista = NULL;
    no->condicao = NULL;
    no->corpo = NULL;
    no->senao = NULL;
    no->nome_funcao = NULL;
    no->parametros = NULL;
    no->argumentos = NULL;
    return no;
}
No* CriarNoReturn(No* valor) {
    No* no = malloc(sizeof(No));
    no->tipo = NoReturn;
    no->esquerdo = valor;
    no->direito = NULL;
    no->valor = 0;
    no->valor_float = 0.0;
    no->valor_str = NULL;
    no->valor_bool = 0;
    no->var = NULL;
    no->op = 0;
    no->lista = NULL;
    no->condicao = NULL;
    no->corpo = NULL;
    no->senao = NULL;
    no->nome_funcao = NULL;
    no->parametros = NULL;
    no->argumentos = NULL;
    return no;
}

ListaNo* CriarListaElementos(No* elemento, ListaNo* prox) {
    ListaNo* lista = malloc(sizeof(ListaNo));
    lista->no = elemento;
    lista->prox = prox;
    return lista;
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
        case NoFloat:
            printf("Float: %.2f\n", no->valor_float);
            break;
        case NoString:
            printf("String: %s\n", no->valor_str);
            break;
        case NoBool:
            printf("Bool: %s\n", no->valor_bool ? "True" : "False");
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
        case NoFuncao:
            printf("Funcao: %s\n", no->var ? no->var : "anonima");
            if (no->lista) {
                for (i = 0; i < nivel + 1; i++) printf("    ");
                printf("Corpo:\n");
                imprimeLista(no->lista, nivel + 2);
            }
            break;
        case NoChamadaFuncao:
            printf("ChamadaFuncao: %s\n", no->var ? no->var : "anonima");
            if (no->lista) {
                for (i = 0; i < nivel + 1; i++) printf("    ");
                printf("Argumentos:\n");
                imprimeLista(no->lista, nivel + 2);
            }
            break;
        default:
            printf("[Tipo de nó desconhecido]\n");
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
            if (no->direito == NULL && no->op == '!') {
                return !valorEsq;
            }
            
            valorDir = avaliarArvore(no->direito);
            
            switch (no->op) {
                case '+': resultado = valorEsq + valorDir; break;
                case '-': resultado = valorEsq - valorDir; break;
                case '*': resultado = valorEsq * valorDir; break;
                case '!': resultado = !valorEsq; break;
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
                // Operadores de comparação
                case '<': resultado = (valorEsq < valorDir) ? 1 : 0; break;  // Menor que
                case '>': resultado = (valorEsq > valorDir) ? 1 : 0; break;  // Maior que
                case 'l': resultado = (valorEsq <= valorDir) ? 1 : 0; break; // Menor ou igual
                case 'g': resultado = (valorEsq >= valorDir) ? 1 : 0; break; // Maior ou igual
                case '=': resultado = (valorEsq == valorDir) ? 1 : 0; break; // igual de comparação
                case 'n': resultado = (valorEsq != valorDir) ? 1 : 0; break; // diferente de
                case '&': resultado = valorEsq & valorDir; break;
                case '|': resultado = valorEsq | valorDir; break;
                case '^': resultado = valorEsq ^ valorDir; break;
                case 's': resultado = valorEsq << valorDir; break; // Shift left
                case 'r': resultado = valorEsq >> valorDir; break; // Shift right
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

        case NoBloco:
            // Avaliar todas as instruções do bloco
            if (no->lista == NULL) return 0;

            ListaNo* atual = no->lista;
            int ultimoResultado = 0;
            while (atual) {
                if (atual->no) {
                    ultimoResultado = avaliarArvore(atual->no);
                }
                atual = atual->prox;
            }
            return ultimoResultado;

        case NoIf:
            
            int condicao = avaliarArvore(no->condicao);

            if (condicao) {
                return avaliarArvore(no->corpo);
            } else if (no->senao) {
                return avaliarArvore(no->senao);
            }

            return 0;

        default:
            printf("[ERRO] Tipo de nó desconhecido: %d\n", no->tipo);
            return 0;
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




