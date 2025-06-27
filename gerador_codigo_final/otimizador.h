#ifndef OTIMIZADOR_H
#define OTIMIZADOR_H

#include "../ast/ast.h"
#include <stdbool.h>

// Estrutura para armazenar informações de otimização
typedef struct {
    bool dead_code_elimination;
    bool constant_folding;
    bool as_if_optimization;
    bool common_subexpression_elimination;
    bool constant_propagation;
    bool copy_propagation;
    bool loop_invariant_motion;
    bool strength_reduction;
    bool algebraic_simplification;
    int num_optimizations_applied;
} Opcoes_Otimizacao;

// Estrutura para análise de fluxo de controle
typedef struct {
    bool* variaveis_usadas;
    int num_variaveis;
    bool* blocos_alcancaveis;
    int num_blocos;
} Analise_Fluxo;

// Estrutura para mapeamento de constantes
typedef struct ConstanteMap {
    char* nome_variavel;
    No* valor_constante;
    struct ConstanteMap* prox;
} ConstanteMap;

// Estrutura para mapeamento de cópias
typedef struct CopiaMap {
    char* variavel_destino;
    char* variavel_origem;
    struct CopiaMap* prox;
} CopiaMap;

// Estrutura para expressões constantes
typedef struct ExpressaoConstante {
    No* expressao;
    No* valor_constante;
    struct ExpressaoConstante* prox;
} ExpressaoConstante;

// Estrutura para subexpressões comuns
typedef struct SubexpressaoComum {
    No* expressao;
    char* variavel_temp;
    int contador_uso;
    struct SubexpressaoComum* prox;
} SubexpressaoComum;

// Estrutura para invariantes de loop
typedef struct InvarianteLoop {
    No* expressao;
    char* variavel_temp;
    struct InvarianteLoop* prox;
} InvarianteLoop;

// Funções principais de otimização
No* aplicarOtimizacoes(No* raiz, Opcoes_Otimizacao* opcoes);
No* otimizarArvore(No* no, Opcoes_Otimizacao* opcoes);

// Dead Code Elimination
No* eliminarCodigoMorto(No* no);
bool isCodigoMorto(No* no);
bool temEfeitoColateral(No* no);
void marcarVariaveisUsadas(No* no, bool* variaveis_usadas);

// Constant Folding
No* dobrarConstantes(No* no);
No* avaliarExpressaoConstante(No* no);
bool isExpressaoConstante(No* no);
int calcularOperacaoInteira(int left, int right, char op);
float calcularOperacaoFloat(float left, float right, char op);
bool calcularOperacaoLogica(No* left, No* right, char op);

// Constant Propagation
No* propagarConstantes(No* no);
ConstanteMap* construirMapaConstantes(No* no);
No* substituirConstantes(No* no, ConstanteMap* mapa);
ConstanteMap* adicionarConstante(ConstanteMap* mapa, const char* nome, No* valor);
No* buscarConstante(ConstanteMap* mapa, const char* nome);
void liberarMapaConstantes(ConstanteMap* mapa);

// Copy Propagation
No* propagarCopias(No* no);
CopiaMap* construirMapaCopias(No* no);
No* substituirCopias(No* no, CopiaMap* mapa);
CopiaMap* adicionarCopia(CopiaMap* mapa, const char* destino, const char* origem);
char* buscarOrigem(CopiaMap* mapa, const char* nome);
void liberarMapaCopias(CopiaMap* mapa);

// Common Subexpression Elimination (melhorado)
No* eliminarSubexpressoesComuns(No* no);
SubexpressaoComum* encontrarSubexpressoesComuns(No* no);
SubexpressaoComum* adicionarSubexpressao(SubexpressaoComum* lista, No* expr);
bool expressaoEquivalente(No* a, No* b);
char* gerarVariavelTemporariaCSE();

// Loop Invariant Code Motion
No* moverInvariantesLoop(No* no);
InvarianteLoop* encontrarInvariantesLoop(No* loop_node);
bool isInvarianteLoop(No* expr, No* loop_node);
void liberarInvariantesLoop(InvarianteLoop* lista);

// Strength Reduction
No* reduzirForca(No* no);
No* otimizarMultiplicacao(No* no);
No* otimizarPotenciacao(No* no);
No* otimizarDivisao(No* no);

// Algebraic Simplification
No* simplificarAlgebra(No* no);
No* simplificarAdicao(No* no);
No* simplificarSubtracao(No* no);
No* simplificarMultiplicacao(No* no);
No* simplificarDivisao(No* no);
No* simplificarPotenciacao(No* no);

// As-if Optimization
No* otimizacaoAsIf(No* no);
bool podeMoverInstrucao(No* no);
bool afetaComportamentoObservavel(No* no);

// Otimizações específicas para estruturas de controle
No* otimizarIf(No* no);
No* otimizarWhile(No* no);
No* otimizarFor(No* no);

// Funções auxiliares
No* clonarNo(No* no);
ListaNo* clonarLista(ListaNo* lista);
void liberarExpressaoConstante(ExpressaoConstante* expr);
void liberarSubexpressaoComum(SubexpressaoComum* subexpr);
bool isOperacaoComutativa(char op);
void inicializarOpcoes(Opcoes_Otimizacao* opcoes);

// Análise de fluxo de dados
Analise_Fluxo* analisarFluxo(No* no);
void liberarAnaliseFluxo(Analise_Fluxo* analise);

// Utilitários avançados
bool isVariavel(No* no, const char* nome);
bool modificaVariavel(No* no, const char* nome);
bool usaVariavel(No* no, const char* nome);
No* criarNoConstante(int valor);
No* criarNoConstanteFloat(float valor);

// Debugging e estatísticas
void imprimirEstatisticasOtimizacao(Opcoes_Otimizacao* opcoes);
void debug_imprimir_otimizacao(const char* mensagem, No* antes, No* depois);

#endif // OTIMIZADOR_H 