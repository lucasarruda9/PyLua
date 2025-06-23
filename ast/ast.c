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

No* CriarNoFloat(float valor) {
    No* no = malloc(sizeof(No));
    no->tipo = NoFloat;
    no->valor_float = valor;
    no->direito = no->esquerdo = NULL;
    no->valor = 0;
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

No* CriarNoString(char* valor) {
    No* no = malloc(sizeof(No));
    no->tipo = NoString;
    no->valor_str = valor;
    no->direito = no->esquerdo = NULL;
    no->valor = 0;
    no->valor_float = 0.0;
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

No* CriarNoBool(int valor) {
    No* no = malloc(sizeof(No));
    no->tipo = NoBool;
    no->valor_bool = valor;
    no->direito = no->esquerdo = NULL;
    no->valor = 0;
    no->valor_float = 0.0;
    no->valor_str = NULL;
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

No* CriarNoBloco(ListaNo* lista) {
    No* no = malloc(sizeof(No));
    no->tipo = NoBloco;
    no->lista = lista;
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

No* CriarNoIf(No* condicao, No* corpo, No* senao) {
    No* no = malloc(sizeof(No));
    no->tipo = NoIf;
    no->condicao = condicao;
    no->corpo = corpo;
    no->senao = senao;
    no->direito = no->esquerdo = NULL;
    no->valor = 0;
    no->valor_float = 0.0;
    no->valor_str = NULL;
    no->valor_bool = 0;
    no->var = NULL;
    no->op = 0;
    no->lista = NULL;
    no->parametros = NULL;
    no->argumentos = NULL;
    return no;
}

No* CriarNoWhile(No* condicao, No* corpo) {
    No* no = malloc(sizeof(No));
    no->tipo = NoWhile;
    no->condicao = condicao;
    no->corpo = corpo;
    no->direito = no->esquerdo = NULL;
    no->valor = 0;
    no->valor_float = 0.0;
    no->valor_str = NULL;
    no->valor_bool = 0;
    no->var = NULL;
    no->op = 0;
    no->lista = NULL;
    no->senao = NULL;
    no->nome_funcao = NULL;
    no->parametros = NULL;
    no->argumentos = NULL;
    return no;
}

No* CriarNoFor(No* var, No* inicio, No* fim, No* corpo) {
    No* no = malloc(sizeof(No));
    no->tipo = NoFor;
    no->esquerdo = var;
    no->direito = inicio;
    no->valor = 0;
    no->valor_float = 0.0;
    no->valor_str = NULL;
    no->valor_bool = 0;
    no->var = NULL;
    no->op = 0;
    no->lista = NULL;
    no->condicao = fim;
    no->corpo = corpo;
    no->senao = NULL;
    no->nome_funcao = NULL;
    no->parametros = NULL;
    no->argumentos = NULL;
    return no;
}

No* CriarNoFuncao(char* nome, ListaNo* parametros, No* corpo) {
    No* no = malloc(sizeof(No));
    no->tipo = NoFuncao;
    no->nome_funcao = nome;
    no->parametros = parametros;
    no->corpo = corpo;
    no->direito = no->esquerdo = NULL;
    no->valor = 0;
    no->valor_float = 0.0;
    no->valor_str = NULL;
    no->valor_bool = 0;
    no->var = NULL;
    no->op = 0;
    no->lista = NULL;
    no->condicao = NULL;
    no->senao = NULL;
    no->argumentos = NULL;
    return no;
}

No* CriarNoChamadaFuncao(char* nome, ListaNo* argumentos) {
    No* no = malloc(sizeof(No));
    no->tipo = NoChamadaFuncao;
    no->nome_funcao = nome;
    no->argumentos = argumentos;
    no->direito = no->esquerdo = NULL;
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
    no->parametros = NULL;
    return no;
}

void DesalocarArvore(No *raiz){
    if(raiz == NULL){
        return;
    }
    DesalocarArvore(raiz->esquerdo);
    DesalocarArvore(raiz->direito);
    free(raiz);
}

void imprimeLista(ListaNo* lista, int nivel) {
    ListaNo* atual = lista;
    while (atual) {
        imprimeArvore(atual->no, nivel);
        atual = atual->prox;
    }
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
        case NoFloat:
            printf("Float: %f\n", no->valor_float);
            break;
        case NoString:
            printf("String: '%s'\n", no->valor_str);
            break;
        case NoBool:
            printf("Bool: %s\n", no->valor_bool ? "True" : "False");
            break;
        case NoVariavel:
            printf("Variavel: %s\n", no->var);
            break;
        case NoOperacaoBinaria:
            printf("Operacao: %c\n", no->op);
            if (no->esquerdo) imprimeArvore(no->esquerdo, nivel + 1);
            if (no->direito) imprimeArvore(no->direito, nivel + 1);
            break;
        case NoAtribuicao:
            printf("Atribuicao\n");
            if (no->esquerdo) imprimeArvore(no->esquerdo, nivel + 1);
            if (no->direito) imprimeArvore(no->direito, nivel + 1);
            break;
        case NoBloco:
            printf("Bloco:\n");
            imprimeLista(no->lista, nivel + 1);
            break;
        case NoIf:
            printf("If:\n");
            for (i = 0; i < nivel + 1; i++) printf("    ");
            printf("Condicao:\n");
            imprimeArvore(no->condicao, nivel + 2);
            for (i = 0; i < nivel + 1; i++) printf("    ");
            printf("Corpo:\n");
            imprimeArvore(no->corpo, nivel + 2);
            if (no->senao) {
                for (i = 0; i < nivel + 1; i++) printf("    ");
                printf("Senao:\n");
                imprimeArvore(no->senao, nivel + 2);
            }
            break;
        case NoWhile:
            printf("While:\n");
            for (i = 0; i < nivel + 1; i++) printf("    ");
            printf("Condicao:\n");
            imprimeArvore(no->condicao, nivel + 2);
            for (i = 0; i < nivel + 1; i++) printf("    ");
            printf("Corpo:\n");
            imprimeArvore(no->corpo, nivel + 2);
            break;
        case NoFor:
            printf("For:\n");
            for (i = 0; i < nivel + 1; i++) printf("    ");
            printf("Var:\n");
            imprimeArvore(no->esquerdo, nivel + 2);
            for (i = 0; i < nivel + 1; i++) printf("    ");
            printf("Inicio:\n");
            imprimeArvore(no->direito, nivel + 2);
            for (i = 0; i < nivel + 1; i++) printf("    ");
            printf("Fim:\n");
            imprimeArvore(no->condicao, nivel + 2);
            for (i = 0; i < nivel + 1; i++) printf("    ");
            printf("Corpo:\n");
            imprimeArvore(no->corpo, nivel + 2);
            break;
        case NoFuncao:
            printf("Funcao: %s\n", no->nome_funcao);
            for (i = 0; i < nivel + 1; i++) printf("    ");
            printf("Parametros:\n");
            imprimeLista(no->parametros, nivel + 2);
            for (i = 0; i < nivel + 1; i++) printf("    ");
            printf("Corpo:\n");
            imprimeArvore(no->corpo, nivel + 2);
            break;
        case NoChamadaFuncao:
            printf("ChamadaFuncao: %s\n", no->nome_funcao);
            for (i = 0; i < nivel + 1; i++) printf("    ");
            printf("Argumentos:\n");
            imprimeLista(no->argumentos, nivel + 2);
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

        case NoChamadaFuncao:
            printf("[INFO] Chamada de função '%s' (avaliação simbólica)\n", no->nome_funcao);
            // Aqui pode-se implementar chamada real no futuro
            return 0;

        case NoFloat:
            return (int)no->valor_float; // Retorna o valor float convertido para int (ajuste conforme necessário)
        case NoString:
            printf("String: '%s'\n", no->valor_str);
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