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
    NoLiteral,          // Literais inteiros
    NoVariavel,         // Identificadores/variáveis
    NoOperacaoBinaria,  // Operações binárias
    NoAtribuicao,       // Atribuições
    NoFloat,            // Literais de ponto flutuante
    NoString,           // Literais de string
    NoBool,             // Literais booleanos
    NoBloco,            // Blocos de código
    NoIf,               // Estruturas condicionais
    NoWhile,            // Loops while
    NoFor,              // Loops for
    NoFuncao,           // Definições de função
    NoChamadaFuncao     // Chamadas de função
} Tipo;
```

### Estrutura Principal do Nó
```c
typedef struct Arvore {
    Tipo tipo;                      // Tipo do nó
    struct Arvore *direito, *esquerdo; // Filhos da árvore
    
    // Valores para diferentes tipos
    int valor;                      // Para inteiros
    float valor_float;              // Para floats
    char* valor_str;                // Para strings
    int valor_bool;                 // Para booleanos
    char* var;                      // Para variáveis
    char op;                        // Para operadores
    
    // Para estruturas complexas
    ListaNo* lista;                 // Para blocos
    struct Arvore* condicao;        // Para if/while/for
    struct Arvore* corpo;           // Para if/while/for/função
    struct Arvore* senao;           // Para if-else
    
    // Para funções
    char* nome_funcao;              // Nome da função
    ListaNo* parametros;            // Parâmetros da função
    ListaNo* argumentos;            // Argumentos de chamada
} No;
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
No* CriarNoFor(No* var, No* inicio, No* fim, No* corpo); // Loop for
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

## Operadores Suportados

### Aritméticos
- `+` : Soma
- `-` : Subtração (binária e unária)
- `*` : Multiplicação
- `/` : Divisão
- `%` : Módulo
- `p` : Potência (**)
- `f` : Divisão inteira (//)

### Comparação
- `<` : Menor que
- `>` : Maior que
- `l` : Menor ou igual (<=)
- `g` : Maior ou igual (>=)
- `e` : Igual (==)
- `d` : Diferente (!=)
- `n` : Diferente (<>)

### Bitwise
- `&` : AND bitwise
- `|` : OR bitwise
- `^` : XOR bitwise
- `~` : NOT bitwise (unário)
- `s` : Shift left (<<)
- `r` : Shift right (>>)

### Atribuição Composta
- `a` : Usado internamente para operações compostas (+=, -=, etc.)

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

### Avaliação da Árvore
```c
int avaliarArvore(No* no);
```

A função `avaliarArvore` percorre a AST e calcula o resultado das expressões:
- **Literais**: Retorna o valor direto
- **Variáveis**: Busca na tabela de símbolos
- **Operações**: Calcula recursivamente os operandos
- **Atribuições**: Atualiza a tabela de símbolos

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

### Exemplo 3: Função
**Código Python**:
```python
def soma(a, b):
    return a + b
```

**Construção da AST**:
```c
ListaNo* params = NULL;
params = AdicionarNoLista(params, CriarNoVariavel("a"));
params = AdicionarNoLista(params, CriarNoVariavel("b"));

No* corpo = CriarNoOperador(CriarNoVariavel("a"), CriarNoVariavel("b"), '+');
No* funcao = CriarNoFuncao("soma", params, corpo);
```

## Integração com Outros Componentes

### Com o Parser
- O parser cria nós da AST durante a análise sintática
- Cada regra gramatical corresponde a uma função de criação
- A AST é construída bottom-up

### Com a Tabela de Símbolos
- `avaliarArvore` consulta a tabela para resolver variáveis
- Atribuições atualizam a tabela de símbolos
- Verificação de variáveis não declaradas

### Com o Gerador de Código
- O gerador percorre a AST para produzir código Lua
- Cada tipo de nó tem sua estratégia de geração
- Mantém contexto de indentação e escopo

## Testes Automatizados

### Teste de Novos Nós (`test_novos_nos.c`)
```bash
gcc -I./ast -I./tabela ./ast/ast.c ./tabela/tabela.c ./tests/ast/test_novos_nos.c -o ./build/test_novos_nos -lm
./build/test_novos_nos
```

### Teste de Estruturas de Controle (`test_controle.c`)
```bash
gcc -I./ast -I./tabela ./ast/ast.c ./tabela/tabela.c ./tests/ast/test_controle.c -o ./build/test_controle -lm
./build/test_controle
```

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

| Versão | Data | Descrição | Autor | Revisor |
|--------|------|-----------|--------|----------|
| 1.0 | 17/06/2025 | Criação e edição da documentação da ast | [Artur Mendonça](https://github.com/ArtyMend07) | [Lucas Mendonça](https://github.com/lucasarruda9) |
