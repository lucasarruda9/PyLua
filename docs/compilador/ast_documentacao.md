# Documentação da Árvore Sintática Abstrata (AST)

## Visão Geral

A Árvore Sintática Abstrata (AST) do PyLua é uma estrutura de dados em árvore que representa a estrutura sintática do código Python de forma hierárquica. Cada nó da árvore representa uma construção da linguagem, como expressões, declarações, operadores ou estruturas de controle.

## Arquivos Principais

- **`ast/ast.h`**: Definições de tipos, estruturas e interfaces
- **`ast/ast.c`**: Implementação das funções de criação, manipulação e avaliação
- **`tests/ast/`**: Testes automatizados para validação da AST

## Estrutura de Dados

### Enumeração de Tipos de Nós
```c
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
    NoFuncao,
    NoChamadaFuncao,
    NoPrint
} Tipo;
```

### Estrutura Principal do Nó
```c
typedef struct Arvore{
    Tipo tipo;
    struct Arvore *direita, *meio, *esquerda;
    int valor;
    float valor_float;
    char* valor_str;
    int valor_bool;
    char* var;
    char op;
    bool declarada;
    ListaNo *lista;
}No;
```

### Lista de Nós
```c
typedef struct ListaNo {
    struct Arvore* no;              // Nó atual
    struct ListaNo* prox;           // Próximo nó da lista
} ListaNo;
```

## Funções de Criação

### Literais Básicos
```c
No* CriarNoInteiro(int valor);      // Cria nó para inteiro
No* CriarNoFloat(float valor);      // Cria nó para float
No* CriarNoString(char* valor);     // Cria nó para string
No* CriarNoBool(int valor);         // Cria nó para booleano
```

### Variáveis e Operações
```c
No* CriarNoVariavel(char *var);     // Cria nó para variável
No* CriarNoOperador(No *esq, No *dir, char op); // Operação binária
No* CriaNoAtribuicao(No *var, No *exp);         // Atribuição
```

### Estruturas de Controle
```c
No* CriarNoBloco(ListaNo* lista);   // Bloco de comandos
No* CriarNoIf(No* cond, No* corpo, No* senao);  // Condicional
No* CriarNoWhile(No* cond, No* corpo);          // Loop while
```

### Funções
```c
No* CriarNoFuncao(char* nome, ListaNo* params, No* corpo);
No* CriarNoChamadaFuncao(char* nome, ListaNo* args);
```

### Listas
```c
ListaNo* AdicionarNoLista(ListaNo* lista, No* no);
```

## Funções de Manipulação

### Impressão da Árvore
```c
void imprimeArvore(No *no, int nivel);
void imprimeLista(ListaNo* lista, int nivel);
```

**Exemplo de saída**:
```
Atribuicao
    Variavel: x
    Operacao: +
        Literal: 10
        Literal: 5
```
### Desalocação de Memória
```c
void DesalocarArvore(struct Arvore* no);
```

Percorre a árvore recursivamente liberando toda a memória alocada.

## Exemplos de Uso

### Exemplo 1: Expressão Aritmética
**Código Python**: `x = 10 + 5 * 2`

**Construção da AST**:
```c
No* expr = CriarNoOperador(
    CriarNoInteiro(10),
    CriarNoOperador(
        CriarNoInteiro(5),
        CriarNoInteiro(2),
        '*'
    ),
    '+'
);
No* atrib = CriaNoAtribuicao(CriarNoVariavel("x"), expr);
```

**Estrutura resultante**:
```
Atribuicao
    Variavel: x
    Operacao: +
        Literal: 10
        Operacao: *
            Literal: 5
            Literal: 2
```

### Exemplo 2: Estrutura Condicional
**Código Python**:
```python
if x > 0:
    y = 1
else:
    y = 0
```

**Construção da AST**:
```c
No* condicao = CriarNoOperador(CriarNoVariavel("x"), CriarNoInteiro(0), '>');
No* corpo_if = CriaNoAtribuicao(CriarNoVariavel("y"), CriarNoInteiro(1));
No* corpo_else = CriaNoAtribuicao(CriarNoVariavel("y"), CriarNoInteiro(0));
No* if_node = CriarNoIf(condicao, corpo_if, corpo_else);
```

## Integração com Outros Componentes

### Com o Parser
- O parser cria nós da AST durante a análise sintática
- Cada regra gramatical corresponde a uma função de criação


### Com o Gerador de Código
- O gerador percorre a AST para produzir código Lua
- Cada tipo de nó tem sua estratégia de geração
- Mantém contexto de indentação e escopo

## Limitações e Melhorias Futuras

### Limitações Atuais
- Suporte limitado a estruturas de dados complexas (listas, dicionários)
- Sem suporte a classes e herança
- Tratamento de tipos limitado
- Sem otimizações de AST

### Melhorias Planejadas
- Análise semântica mais robusta
- Otimizações de expressões constantes
- Suporte a mais tipos de dados Python
- Melhor tratamento de erros

## Histórico de Versões

| Versão | Descrição | Autor | Data | Revisor | Data Revisão |
|--------|-----------|-------|------|---------|--------------|
| 1.0 | Criação da documento de ast| [Artur Mendonça](https://github.com/ArtyMend07) | 17/06/2025 | [Lucas Mendonça](https://github.com/lucasarruda9) | 17/06/2025 |
| 2.0 | ajuste da documentação | [Lucas Mendonça](https://github.com/lucasarruda9) | 27/06/2025 | [Artur Mendonça](https://github.com/ArtyMend07) | 27/06/2025 |
