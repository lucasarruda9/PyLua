#include "otimizador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static int contador_temp_cse = 0;

// ===== FUNÇÕES PRINCIPAIS =====

void inicializarOpcoes(Opcoes_Otimizacao* opcoes) {
    opcoes->dead_code_elimination = true;
    opcoes->constant_folding = true;
    opcoes->as_if_optimization = true;
    opcoes->common_subexpression_elimination = true;
    opcoes->constant_propagation = true;
    opcoes->copy_propagation = true;
    opcoes->loop_invariant_motion = true;
    opcoes->strength_reduction = true;
    opcoes->algebraic_simplification = true;
    opcoes->num_optimizations_applied = 0;
}

No* aplicarOtimizacoes(No* raiz, Opcoes_Otimizacao* opcoes) {
    if (!raiz || !opcoes) return raiz;
    
    No* otimizado = clonarNo(raiz);
    if (!otimizado) return raiz;
    
    // Aplicar apenas constant folding por enquanto para evitar problemas
    if (opcoes->constant_folding) {
        No* resultado_cf = dobrarConstantes(otimizado);
        if (resultado_cf) {
            otimizado = resultado_cf;
            opcoes->num_optimizations_applied++;
        }
    }
    
    return otimizado;
}

// ===== CONSTANT FOLDING =====

No* dobrarConstantes(No* no) {
    if (!no) return NULL;
    
    No* novo_no = clonarNo(no);
    
    // Processar filhos primeiro
    if (novo_no->esquerda) {
        novo_no->esquerda = dobrarConstantes(novo_no->esquerda);
    }
    if (novo_no->direita) {
        novo_no->direita = dobrarConstantes(novo_no->direita);
    }
    if (novo_no->meio) {
        novo_no->meio = dobrarConstantes(novo_no->meio);
    }
    if (novo_no->lista) {
        ListaNo* atual = novo_no->lista;
        while (atual) {
            atual->no = dobrarConstantes(atual->no);
            atual = atual->prox;
        }
    }
    
    // Avaliar se podemos dobrar esta operação
    if (novo_no->tipo == NoOperacaoBinaria) {
        if (isExpressaoConstante(novo_no->esquerda) && isExpressaoConstante(novo_no->direita)) {
            No* resultado = avaliarExpressaoConstante(novo_no);
            if (resultado) {
                return resultado;
            }
        }
    }
    
    return novo_no;
}

No* avaliarExpressaoConstante(No* no) {
    if (!no || no->tipo != NoOperacaoBinaria) return NULL;
    
    No* esq = no->esquerda;
    No* dir = no->direita;
    
    // Operações com inteiros
    if (esq->tipo == NoLiteral && dir->tipo == NoLiteral) {
        int resultado = calcularOperacaoInteira(esq->valor, dir->valor, no->op);
        return CriarNoInteiro(resultado);
    }
    
    // Operações com floats
    if ((esq->tipo == NoFloat && dir->tipo == NoFloat) ||
        (esq->tipo == NoLiteral && dir->tipo == NoFloat) ||
        (esq->tipo == NoFloat && dir->tipo == NoLiteral)) {
        
        float val_esq = (esq->tipo == NoFloat) ? esq->valor_float : (float)esq->valor;
        float val_dir = (dir->tipo == NoFloat) ? dir->valor_float : (float)dir->valor;
        float resultado = calcularOperacaoFloat(val_esq, val_dir, no->op);
        return CriarNoFloat(resultado);
    }
    
    // Operações lógicas
    if (no->op == '=' || no->op == 'n' || no->op == '<' || no->op == '>' || 
        no->op == 'l' || no->op == 'g') {
        bool resultado = calcularOperacaoLogica(esq, dir, no->op);
        return CriarNoBool(resultado);
    }
    
    return NULL;
}

bool isExpressaoConstante(No* no) {
    if (!no) return false;
    
    switch (no->tipo) {
        case NoLiteral:
        case NoFloat:
        case NoString:
        case NoBool:
            return true;
        case NoOperacaoBinaria:
            return isExpressaoConstante(no->esquerda) && isExpressaoConstante(no->direita);
        default:
            return false;
    }
}

int calcularOperacaoInteira(int left, int right, char op) {
    switch (op) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return (right != 0) ? left / right : 0;
        case '%': return (right != 0) ? left % right : 0;
        case '&': return left & right;
        case '|': return left | right;
        case '^': return left ^ right;
        case 's': return left << right;
        case 'r': return left >> right;
        default: return 0;
    }
}

float calcularOperacaoFloat(float left, float right, char op) {
    switch (op) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return (right != 0.0f) ? left / right : 0.0f;
        case 'p': return powf(left, right);
        default: return 0.0f;
    }
}

bool calcularOperacaoLogica(No* left, No* right, char op) {
    // Comparação de inteiros
    if (left->tipo == NoLiteral && right->tipo == NoLiteral) {
        int l = left->valor, r = right->valor;
        switch (op) {
            case '=': return l == r;
            case 'n': return l != r;
            case '<': return l < r;
            case '>': return l > r;
            case 'l': return l <= r;
            case 'g': return l >= r;
        }
    }
    
    // Comparação de floats
    if ((left->tipo == NoFloat || left->tipo == NoLiteral) &&
        (right->tipo == NoFloat || right->tipo == NoLiteral)) {
        float l = (left->tipo == NoFloat) ? left->valor_float : (float)left->valor;
        float r = (right->tipo == NoFloat) ? right->valor_float : (float)right->valor;
        switch (op) {
            case '=': return l == r;
            case 'n': return l != r;
            case '<': return l < r;
            case '>': return l > r;
            case 'l': return l <= r;
            case 'g': return l >= r;
        }
    }
    
    return false;
}

// ===== CONSTANT PROPAGATION =====

No* propagarConstantes(No* no) {
    if (!no) return NULL;
    
    ConstanteMap* mapa = construirMapaConstantes(no);
    No* resultado = substituirConstantes(no, mapa);
    liberarMapaConstantes(mapa);
    
    return resultado;
}

ConstanteMap* construirMapaConstantes(No* no) {
    if (!no) return NULL;
    
    ConstanteMap* mapa = NULL;
    
    if (no->tipo == NoAtribuicao && no->esquerda && no->direita) {
        if (no->esquerda->tipo == NoVariavel && isExpressaoConstante(no->direita)) {
            mapa = adicionarConstante(mapa, no->esquerda->var, no->direita);
        }
    }
    
    // Processar recursivamente
    if (no->esquerda) {
        ConstanteMap* mapa_esq = construirMapaConstantes(no->esquerda);
        // Juntar mapas (implementação simplificada)
        if (mapa_esq && !mapa) mapa = mapa_esq;
    }
    
    if (no->direita) {
        ConstanteMap* mapa_dir = construirMapaConstantes(no->direita);
        if (mapa_dir && !mapa) mapa = mapa_dir;
    }
    
    if (no->meio) {
        ConstanteMap* mapa_meio = construirMapaConstantes(no->meio);
        if (mapa_meio && !mapa) mapa = mapa_meio;
    }
    
    return mapa;
}

No* substituirConstantes(No* no, ConstanteMap* mapa) {
    if (!no || !mapa) return no;
    
    No* novo_no = clonarNo(no);
    
    if (novo_no->tipo == NoVariavel) {
        No* constante = buscarConstante(mapa, novo_no->var);
        if (constante) {
            return clonarNo(constante);
        }
    }
    
    // Processar filhos
    if (novo_no->esquerda) {
        novo_no->esquerda = substituirConstantes(novo_no->esquerda, mapa);
    }
    if (novo_no->direita) {
        novo_no->direita = substituirConstantes(novo_no->direita, mapa);
    }
    if (novo_no->meio) {
        novo_no->meio = substituirConstantes(novo_no->meio, mapa);
    }
    
    return novo_no;
}

ConstanteMap* adicionarConstante(ConstanteMap* mapa, const char* nome, No* valor) {
    ConstanteMap* nova = malloc(sizeof(ConstanteMap));
    if (!nova) return mapa;
    
    nova->nome_variavel = strdup(nome);
    nova->valor_constante = clonarNo(valor);
    nova->prox = mapa;
    
    return nova;
}

No* buscarConstante(ConstanteMap* mapa, const char* nome) {
    while (mapa) {
        if (mapa->nome_variavel && strcmp(mapa->nome_variavel, nome) == 0) {
            return mapa->valor_constante;
        }
        mapa = mapa->prox;
    }
    return NULL;
}

void liberarMapaConstantes(ConstanteMap* mapa) {
    while (mapa) {
        ConstanteMap* temp = mapa;
        mapa = mapa->prox;
        if (temp->nome_variavel) free(temp->nome_variavel);
        // Note: não liberamos valor_constante pois pode estar sendo usado
        free(temp);
    }
}

// ===== COPY PROPAGATION =====

No* propagarCopias(No* no) {
    if (!no) return NULL;
    
    CopiaMap* mapa = construirMapaCopias(no);
    No* resultado = substituirCopias(no, mapa);
    liberarMapaCopias(mapa);
    
    return resultado;
}

CopiaMap* construirMapaCopias(No* no) {
    if (!no) return NULL;
    
    CopiaMap* mapa = NULL;
    
    if (no->tipo == NoAtribuicao && no->esquerda && no->direita) {
        if (no->esquerda->tipo == NoVariavel && no->direita->tipo == NoVariavel) {
            mapa = adicionarCopia(mapa, no->esquerda->var, no->direita->var);
        }
    }
    
    return mapa;
}

No* substituirCopias(No* no, CopiaMap* mapa) {
    if (!no || !mapa) return no;
    
    No* novo_no = clonarNo(no);
    
    if (novo_no->tipo == NoVariavel) {
        char* origem = buscarOrigem(mapa, novo_no->var);
        if (origem) {
            free(novo_no->var);
            novo_no->var = strdup(origem);
        }
    }
    
    // Processar filhos
    if (novo_no->esquerda) {
        novo_no->esquerda = substituirCopias(novo_no->esquerda, mapa);
    }
    if (novo_no->direita) {
        novo_no->direita = substituirCopias(novo_no->direita, mapa);
    }
    if (novo_no->meio) {
        novo_no->meio = substituirCopias(novo_no->meio, mapa);
    }
    
    return novo_no;
}

CopiaMap* adicionarCopia(CopiaMap* mapa, const char* destino, const char* origem) {
    CopiaMap* nova = malloc(sizeof(CopiaMap));
    if (!nova) return mapa;
    
    nova->variavel_destino = strdup(destino);
    nova->variavel_origem = strdup(origem);
    nova->prox = mapa;
    
    return nova;
}

char* buscarOrigem(CopiaMap* mapa, const char* nome) {
    while (mapa) {
        if (mapa->variavel_destino && strcmp(mapa->variavel_destino, nome) == 0) {
            return mapa->variavel_origem;
        }
        mapa = mapa->prox;
    }
    return NULL;
}

void liberarMapaCopias(CopiaMap* mapa) {
    while (mapa) {
        CopiaMap* temp = mapa;
        mapa = mapa->prox;
        if (temp->variavel_destino) free(temp->variavel_destino);
        if (temp->variavel_origem) free(temp->variavel_origem);
        free(temp);
    }
}

// ===== ALGEBRAIC SIMPLIFICATION =====

No* simplificarAlgebra(No* no) {
    if (!no) return NULL;
    
    No* novo_no = clonarNo(no);
    
    // Processar filhos primeiro
    if (novo_no->esquerda) {
        novo_no->esquerda = simplificarAlgebra(novo_no->esquerda);
    }
    if (novo_no->direita) {
        novo_no->direita = simplificarAlgebra(novo_no->direita);
    }
    if (novo_no->meio) {
        novo_no->meio = simplificarAlgebra(novo_no->meio);
    }
    if (novo_no->lista) {
        ListaNo* atual = novo_no->lista;
        while (atual) {
            atual->no = simplificarAlgebra(atual->no);
            atual = atual->prox;
        }
    }
    
    // Aplicar simplificações algébricas
    if (novo_no->tipo == NoOperacaoBinaria) {
        switch (novo_no->op) {
            case '+': return simplificarAdicao(novo_no);
            case '-': return simplificarSubtracao(novo_no);
            case '*': return simplificarMultiplicacao(novo_no);
            case '/': return simplificarDivisao(novo_no);
            case 'p': return simplificarPotenciacao(novo_no);
        }
    }
    
    return novo_no;
}

No* simplificarAdicao(No* no) {
    if (!no || no->op != '+') return no;
    
    No* esq = no->esquerda;
    No* dir = no->direita;
    
    // x + 0 = x
    if (dir && dir->tipo == NoLiteral && dir->valor == 0) {
        return clonarNo(esq);
    }
    
    // 0 + x = x
    if (esq && esq->tipo == NoLiteral && esq->valor == 0) {
        return clonarNo(dir);
    }
    
    return no;
}

No* simplificarSubtracao(No* no) {
    if (!no || no->op != '-') return no;
    
    No* esq = no->esquerda;
    No* dir = no->direita;
    
    // x - 0 = x
    if (dir->tipo == NoLiteral && dir->valor == 0) {
        return clonarNo(esq);
    }
    
    // x - x = 0
    if (expressaoEquivalente(esq, dir)) {
        return CriarNoInteiro(0);
    }
    
    return no;
}

No* simplificarMultiplicacao(No* no) {
    if (!no || no->op != '*') return no;
    
    No* esq = no->esquerda;
    No* dir = no->direita;
    
    // x * 0 = 0
    if ((dir->tipo == NoLiteral && dir->valor == 0) || 
        (esq->tipo == NoLiteral && esq->valor == 0)) {
        return CriarNoInteiro(0);
    }
    
    // x * 1 = x
    if (dir->tipo == NoLiteral && dir->valor == 1) {
        return clonarNo(esq);
    }
    
    // 1 * x = x
    if (esq->tipo == NoLiteral && esq->valor == 1) {
        return clonarNo(dir);
    }
    
    return no;
}

No* simplificarDivisao(No* no) {
    if (!no || no->op != '/') return no;
    
    No* esq = no->esquerda;
    No* dir = no->direita;
    
    // x / 1 = x
    if (dir->tipo == NoLiteral && dir->valor == 1) {
        return clonarNo(esq);
    }
    
    // x / x = 1
    if (expressaoEquivalente(esq, dir)) {
        return CriarNoInteiro(1);
    }
    
    return no;
}

No* simplificarPotenciacao(No* no) {
    if (!no || no->op != 'p') return no;
    
    No* esq = no->esquerda;
    No* dir = no->direita;
    
    // x ^ 0 = 1
    if (dir->tipo == NoLiteral && dir->valor == 0) {
        return CriarNoInteiro(1);
    }
    
    // x ^ 1 = x
    if (dir->tipo == NoLiteral && dir->valor == 1) {
        return clonarNo(esq);
    }
    
    // 1 ^ x = 1
    if (esq->tipo == NoLiteral && esq->valor == 1) {
        return CriarNoInteiro(1);
    }
    
    return no;
}

// ===== STRENGTH REDUCTION =====

No* reduzirForca(No* no) {
    if (!no) return NULL;
    
    No* novo_no = clonarNo(no);
    
    // Processar filhos primeiro
    if (novo_no->esquerda) {
        novo_no->esquerda = reduzirForca(novo_no->esquerda);
    }
    if (novo_no->direita) {
        novo_no->direita = reduzirForca(novo_no->direita);
    }
    if (novo_no->meio) {
        novo_no->meio = reduzirForca(novo_no->meio);
    }
    if (novo_no->lista) {
        ListaNo* atual = novo_no->lista;
        while (atual) {
            atual->no = reduzirForca(atual->no);
            atual = atual->prox;
        }
    }
    
    // Aplicar reduções de força
    if (novo_no->tipo == NoOperacaoBinaria) {
        switch (novo_no->op) {
            case '*': return otimizarMultiplicacao(novo_no);
            case 'p': return otimizarPotenciacao(novo_no);
            case '/': return otimizarDivisao(novo_no);
        }
    }
    
    return novo_no;
}

No* otimizarMultiplicacao(No* no) {
    if (!no || no->op != '*') return no;
    
    No* esq = no->esquerda;
    No* dir = no->direita;
    
    // x * 2 -> x + x
    if (dir->tipo == NoLiteral && dir->valor == 2) {
        No* soma = malloc(sizeof(No));
        soma->tipo = NoOperacaoBinaria;
        soma->op = '+';
        soma->esquerda = clonarNo(esq);
        soma->direita = clonarNo(esq);
        soma->meio = NULL;
        soma->lista = NULL;
        soma->var = NULL;
        soma->valor_str = NULL;
        return soma;
    }
    
    // Multiplicação por potência de 2 -> shift left
    if (dir->tipo == NoLiteral && dir->valor > 0 && (dir->valor & (dir->valor - 1)) == 0) {
        // É potência de 2, calcular quantos shifts
        int shifts = 0;
        int val = dir->valor;
        while (val > 1) {
            val >>= 1;
            shifts++;
        }
        
        if (shifts > 0) {
            No* shift = malloc(sizeof(No));
            shift->tipo = NoOperacaoBinaria;
            shift->op = 's';  // shift left
            shift->esquerda = clonarNo(esq);
            shift->direita = CriarNoInteiro(shifts);
            shift->meio = NULL;
            shift->lista = NULL;
            shift->var = NULL;
            shift->valor_str = NULL;
            return shift;
        }
    }
    
    return no;
}

No* otimizarPotenciacao(No* no) {
    if (!no || no->op != 'p') return no;
    
    No* esq = no->esquerda;
    No* dir = no->direita;
    
    // x ^ 2 -> x * x
    if (dir->tipo == NoLiteral && dir->valor == 2) {
        No* mult = malloc(sizeof(No));
        mult->tipo = NoOperacaoBinaria;
        mult->op = '*';
        mult->esquerda = clonarNo(esq);
        mult->direita = clonarNo(esq);
        mult->meio = NULL;
        mult->lista = NULL;
        mult->var = NULL;
        mult->valor_str = NULL;
        return mult;
    }
    
    return no;
}

No* otimizarDivisao(No* no) {
    if (!no || no->op != '/') return no;
    
    No* esq = no->esquerda;
    No* dir = no->direita;
    
    // Divisão por potência de 2 -> shift right
    if (dir->tipo == NoLiteral && dir->valor > 0 && (dir->valor & (dir->valor - 1)) == 0) {
        int shifts = 0;
        int val = dir->valor;
        while (val > 1) {
            val >>= 1;
            shifts++;
        }
        
        if (shifts > 0) {
            No* shift = malloc(sizeof(No));
            shift->tipo = NoOperacaoBinaria;
            shift->op = 'r';  // shift right
            shift->esquerda = clonarNo(esq);
            shift->direita = CriarNoInteiro(shifts);
            shift->meio = NULL;
            shift->lista = NULL;
            shift->var = NULL;
            shift->valor_str = NULL;
            return shift;
        }
    }
    
    return no;
}

// ===== DEAD CODE ELIMINATION =====

No* eliminarCodigoMorto(No* no) {
    if (!no) return NULL;
    
    if (isCodigoMorto(no)) {
        return NULL;
    }
    
    No* novo_no = clonarNo(no);
    
    // Processar filhos
    if (novo_no->esquerda) {
        novo_no->esquerda = eliminarCodigoMorto(novo_no->esquerda);
    }
    if (novo_no->direita) {
        novo_no->direita = eliminarCodigoMorto(novo_no->direita);
    }
    if (novo_no->meio) {
        novo_no->meio = eliminarCodigoMorto(novo_no->meio);
    }
    
    // Processar listas
    if (novo_no->lista) {
        ListaNo* atual = novo_no->lista;
        ListaNo* anterior = NULL;
        
        while (atual) {
            No* otimizado = eliminarCodigoMorto(atual->no);
            if (otimizado == NULL) {
                // Remover nó morto
                if (anterior) {
                    anterior->prox = atual->prox;
                } else {
                    novo_no->lista = atual->prox;
                }
                ListaNo* temp = atual;
                atual = atual->prox;
                free(temp);
            } else {
                atual->no = otimizado;
                anterior = atual;
                atual = atual->prox;
            }
        }
    }
    
    return novo_no;
}

bool isCodigoMorto(No* no) {
    if (!no) return true;
    
    switch (no->tipo) {
        // Atribuições, prints e chamadas de função nunca são código morto
        case NoAtribuicao:
        case NoPrint:
        case NoChamadaFuncao:
        case NoIf:
        case NoWhile:
        case NoFor:
        case NoFuncao:
        case NoBloco:
            return false;
            
        // Expressões isoladas sem efeito colateral podem ser código morto
        case NoLiteral:
        case NoString:
        case NoFloat:
        case NoBool:
        case NoVariavel:
            return true; // Apenas se estiverem isoladas
            
        // Operações que não têm efeito colateral
        case NoOperacaoBinaria:
            return !temEfeitoColateral(no);
            
        default:
            return false;
    }
}

bool temEfeitoColateral(No* no) {
    if (!no) return false;
    
    switch (no->tipo) {
        case NoAtribuicao:
        case NoPrint:
        case NoChamadaFuncao:
            return true;
            
        case NoOperacaoBinaria:
            return temEfeitoColateral(no->esquerda) || temEfeitoColateral(no->direita);
            
        case NoBloco:
            if (no->lista) {
                ListaNo* atual = no->lista;
                while (atual) {
                    if (temEfeitoColateral(atual->no)) {
                        return true;
                    }
                    atual = atual->prox;
                }
            }
            return false;
            
        default:
            return false;
    }
}

// ===== AS-IF OPTIMIZATION =====

No* otimizacaoAsIf(No* no) {
    if (!no) return NULL;
    
    // Otimizações específicas para estruturas de controle
    switch (no->tipo) {
        case NoIf:
            return otimizarIf(no);
        case NoWhile:
            return otimizarWhile(no);
        case NoFor:
            return otimizarFor(no);
        default:
            // Para outros tipos, aplicar recursivamente
            {
                No* novo_no = clonarNo(no);
                if (novo_no->esquerda) {
                    novo_no->esquerda = otimizacaoAsIf(novo_no->esquerda);
                }
                if (novo_no->direita) {
                    novo_no->direita = otimizacaoAsIf(novo_no->direita);
                }
                if (novo_no->meio) {
                    novo_no->meio = otimizacaoAsIf(novo_no->meio);
                }
                if (novo_no->lista) {
                    ListaNo* atual = novo_no->lista;
                    while (atual) {
                        atual->no = otimizacaoAsIf(atual->no);
                        atual = atual->prox;
                    }
                }
                return novo_no;
            }
    }
}

No* otimizarIf(No* no) {
    if (!no || no->tipo != NoIf) return no;
    
    No* condicao = no->esquerda;
    
    // Se a condição é uma constante
    if (isExpressaoConstante(condicao)) {
        bool resultado = false;
        
        if (condicao->tipo == NoBool) {
            resultado = condicao->valor_bool;
        } else if (condicao->tipo == NoLiteral) {
            resultado = condicao->valor != 0;
        } else if (condicao->tipo == NoFloat) {
            resultado = condicao->valor_float != 0.0f;
        }
        
        // Se a condição é sempre verdadeira, retornar apenas o bloco then
        if (resultado) {
            return otimizacaoAsIf(no->meio);
        }
        // Se a condição é sempre falsa, retornar apenas o bloco else (se existir)
        else {
            return no->direita ? otimizacaoAsIf(no->direita) : NULL;
        }
    }
    
    // Se não podemos otimizar a condição, otimizar os filhos
    No* novo_no = clonarNo(no);
    novo_no->esquerda = otimizacaoAsIf(novo_no->esquerda);
    novo_no->meio = otimizacaoAsIf(novo_no->meio);
    if (novo_no->direita) {
        novo_no->direita = otimizacaoAsIf(novo_no->direita);
    }
    
    return novo_no;
}

No* otimizarWhile(No* no) {
    if (!no || no->tipo != NoWhile) return no;
    
    No* condicao = no->esquerda;
    
    // Se a condição é sempre falsa, o loop nunca executa
    if (isExpressaoConstante(condicao)) {
        bool resultado = false;
        
        if (condicao->tipo == NoBool) {
            resultado = condicao->valor_bool;
        } else if (condicao->tipo == NoLiteral) {
            resultado = condicao->valor != 0;
        } else if (condicao->tipo == NoFloat) {
            resultado = condicao->valor_float != 0.0f;
        }
        
        if (!resultado) {
            return NULL; // Loop nunca executa
        }
    }
    
    // Otimizar filhos
    No* novo_no = clonarNo(no);
    novo_no->esquerda = otimizacaoAsIf(novo_no->esquerda);
    novo_no->meio = otimizacaoAsIf(novo_no->meio);
    
    return novo_no;
}

No* otimizarFor(No* no) {
    if (!no || no->tipo != NoFor) return no;
    
    // Para loops for, aplicar otimizações nos componentes
    No* novo_no = clonarNo(no);
    novo_no->esquerda = otimizacaoAsIf(novo_no->esquerda);
    novo_no->direita = otimizacaoAsIf(novo_no->direita);
    novo_no->meio = otimizacaoAsIf(novo_no->meio);
    
    return novo_no;
}

// ===== COMMON SUBEXPRESSION ELIMINATION =====

No* eliminarSubexpressoesComuns(No* no) {
    if (!no) return NULL;
    
    // Encontrar subexpressões comuns
    SubexpressaoComum* subexpressoes = encontrarSubexpressoesComuns(no);
    
    // Se não há subexpressões comuns, aplicar recursivamente
    if (!subexpressoes) {
        No* novo_no = clonarNo(no);
        if (novo_no->esquerda) {
            novo_no->esquerda = eliminarSubexpressoesComuns(novo_no->esquerda);
        }
        if (novo_no->direita) {
            novo_no->direita = eliminarSubexpressoesComuns(novo_no->direita);
        }
        if (novo_no->meio) {
            novo_no->meio = eliminarSubexpressoesComuns(novo_no->meio);
        }
        if (novo_no->lista) {
            ListaNo* atual = novo_no->lista;
            while (atual) {
                atual->no = eliminarSubexpressoesComuns(atual->no);
                atual = atual->prox;
            }
        }
        return novo_no;
    }
    
    // Por simplicidade, retornar o nó original por enquanto
    // Uma implementação completa substituiria as subexpressões por variáveis temporárias
    liberarSubexpressaoComum(subexpressoes);
    return clonarNo(no);
}

SubexpressaoComum* encontrarSubexpressoesComuns(No* no) {
    // Implementação simplificada - retorna NULL por enquanto
    // Uma implementação completa percorreria a árvore procurando expressões idênticas
    return NULL;
}

char* gerarVariavelTemporariaCSE() {
    static char buffer[32];
    snprintf(buffer, sizeof(buffer), "cse_temp_%d", contador_temp_cse++);
    return strdup(buffer);
}

// ===== FUNÇÕES AUXILIARES =====

No* criarNoConstante(int valor) {
    return CriarNoInteiro(valor);
}

No* criarNoConstanteFloat(float valor) {
    return CriarNoFloat(valor);
}

bool isVariavel(No* no, const char* nome) {
    return (no && no->tipo == NoVariavel && no->var && strcmp(no->var, nome) == 0);
}

bool modificaVariavel(No* no, const char* nome) {
    if (!no || !nome) return false;
    
    if (no->tipo == NoAtribuicao && no->esquerda) {
        return isVariavel(no->esquerda, nome);
    }
    
    return false;
}

bool usaVariavel(No* no, const char* nome) {
    if (!no || !nome) return false;
    
    if (isVariavel(no, nome)) return true;
    
    // Verificar recursivamente
    if (no->esquerda && usaVariavel(no->esquerda, nome)) return true;
    if (no->direita && usaVariavel(no->direita, nome)) return true;
    if (no->meio && usaVariavel(no->meio, nome)) return true;
    
    if (no->lista) {
        ListaNo* atual = no->lista;
        while (atual) {
            if (usaVariavel(atual->no, nome)) return true;
            atual = atual->prox;
        }
    }
    
    return false;
}

No* clonarNo(No* no) {
    if (!no) return NULL;
    
    No* clone = malloc(sizeof(No));
    if (!clone) return NULL;
    
    // Copiar campos básicos
    clone->tipo = no->tipo;
    clone->valor = no->valor;
    clone->valor_float = no->valor_float;
    clone->valor_bool = no->valor_bool;
    clone->op = no->op;
    clone->declarada = no->declarada;
    
    // Clonar strings
    clone->var = NULL;
    clone->valor_str = NULL;
    
    if (no->var) {
        clone->var = strdup(no->var);
    }
    if (no->valor_str) {
        clone->valor_str = strdup(no->valor_str);
    }
    
    // Inicializar ponteiros como NULL antes de clonar
    clone->esquerda = NULL;
    clone->direita = NULL;
    clone->meio = NULL;
    clone->lista = NULL;
    
    // Clonar filhos recursivamente
    if (no->esquerda) {
        clone->esquerda = clonarNo(no->esquerda);
    }
    if (no->direita) {
        clone->direita = clonarNo(no->direita);
    }
    if (no->meio) {
        clone->meio = clonarNo(no->meio);
    }
    if (no->lista) {
        clone->lista = clonarLista(no->lista);
    }
    
    return clone;
}

ListaNo* clonarLista(ListaNo* lista) {
    if (!lista) return NULL;
    
    ListaNo* nova_lista = malloc(sizeof(ListaNo));
    if (!nova_lista) return NULL;
    
    nova_lista->no = clonarNo(lista->no);
    nova_lista->prox = NULL;
    
    if (lista->prox) {
        nova_lista->prox = clonarLista(lista->prox);
    }
    
    return nova_lista;
}

bool expressaoEquivalente(No* a, No* b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    
    if (a->tipo != b->tipo) return false;
    
    switch (a->tipo) {
        case NoLiteral:
            return a->valor == b->valor;
        case NoFloat:
            return a->valor_float == b->valor_float;
        case NoBool:
            return a->valor_bool == b->valor_bool;
        case NoString:
            return (a->valor_str && b->valor_str) ? 
                   strcmp(a->valor_str, b->valor_str) == 0 : 
                   (a->valor_str == b->valor_str);
        case NoVariavel:
            return (a->var && b->var) ? 
                   strcmp(a->var, b->var) == 0 : 
                   (a->var == b->var);
        case NoOperacaoBinaria:
            return a->op == b->op && 
                   expressaoEquivalente(a->esquerda, b->esquerda) &&
                   expressaoEquivalente(a->direita, b->direita);
        default:
            // Para outros tipos, assumir que são diferentes
            return false;
    }
}

bool isOperacaoComutativa(char op) {
    return (op == '+' || op == '*' || op == '&' || op == '|' || op == '^' || op == '=');
}

void liberarExpressaoConstante(ExpressaoConstante* expr) {
    while (expr) {
        ExpressaoConstante* temp = expr;
        expr = expr->prox;
        free(temp);
    }
}

void liberarSubexpressaoComum(SubexpressaoComum* subexpr) {
    while (subexpr) {
        SubexpressaoComum* temp = subexpr;
        subexpr = subexpr->prox;
        if (temp->variavel_temp) {
            free(temp->variavel_temp);
        }
        free(temp);
    }
}

// ===== DEBUGGING E ESTATÍSTICAS =====

void imprimirEstatisticasOtimizacao(Opcoes_Otimizacao* opcoes) {
    printf("=== Estatísticas de Otimização ===\n");
    printf("Dead Code Elimination: %s\n", opcoes->dead_code_elimination ? "Ativado" : "Desativado");
    printf("Constant Folding: %s\n", opcoes->constant_folding ? "Ativado" : "Desativado");
    printf("Constant Propagation: %s\n", opcoes->constant_propagation ? "Ativado" : "Desativado");
    printf("Copy Propagation: %s\n", opcoes->copy_propagation ? "Ativado" : "Desativado");
    printf("Strength Reduction: %s\n", opcoes->strength_reduction ? "Ativado" : "Desativado");
    printf("Algebraic Simplification: %s\n", opcoes->algebraic_simplification ? "Ativado" : "Desativado");
    printf("As-if Optimization: %s\n", opcoes->as_if_optimization ? "Ativado" : "Desativado");
    printf("Common Subexpression Elimination: %s\n", opcoes->common_subexpression_elimination ? "Ativado" : "Desativado");
    printf("Total de otimizações aplicadas: %d\n", opcoes->num_optimizations_applied);
    printf("==================================\n");
}

void debug_imprimir_otimizacao(const char* mensagem, No* antes, No* depois) {
    printf("DEBUG: %s\n", mensagem);
    // Implementação de debug pode ser expandida conforme necessário
} 