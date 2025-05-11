# Diagrama de Classes para Árvore Sintática Abstrata (AST)

## Introdução

Este documento apresenta o diagrama de classes desenvolvido para representar a estrutura de uma Árvore Sintática Abstrata (AST) implementada em C. O diagrama foi criado usando o Lucidchart e reflete a arquitetura orientada a objetos que serve como base para um interpretador ou compilador.

## Visão Geral da Arquitetura

O diagrama modela uma hierarquia de classes que representa os diferentes tipos de nós que podem existir em uma AST. A arquitetura segue o padrão Composite, onde todos os nós derivam de uma classe base comum (`NoAST`), permitindo que a árvore seja manipulada de forma uniforme, independentemente dos tipos específicos de nós.

## Estrutura do Diagrama

O diagrama é composto por:

1. Uma classe base abstrata (`NoAST`)
2. Múltiplas classes derivadas representando diferentes tipos de nós
3. Uma classe auxiliar para listas encadeadas (`ListaNoAST`)
4. Um enum para representar os tipos de dados (`Tipo`)

## Classes Principais

### Classe Base

- **NoAST**: Classe base para todos os nós da AST, contendo atributos e métodos comuns.

### Classes Derivadas

O diagrama inclui mais de 20 classes derivadas, cada uma representando um tipo específico de nó, incluindo:

- Nós literais (`NoInteiro`, `NoFloat`, `NoString`, `NoBool`, `NoNone`)
- Nós de operações (`NoOperacao`, `NoOpUnario`)
- Nós de controle de fluxo (`NoIf`, `NoFor`, `NoWhile`)
- Nós de estruturas de dados (`NoLista`, `NoDicionario`, `NoTupla`)
- Nós de funções (`NoFuncao`, `NoChamadaFunc`, `NoRetorno`)
- Outros nós específicos (`NoImport`, `NoAtributo`, `NoIndice`, etc.)

### Classe Auxiliar

- **ListaNoAST**: Implementa uma lista encadeada de nós, usada para armazenar coleções como parâmetros, argumentos, instruções e itens.

### Enum

- **Tipo**: Enumera os tipos de dados suportados (INT, FLOAT, STRING, BOOL, NONE, ERRO).

## Relacionamentos

O diagrama ilustra vários tipos de relacionamentos:

1. **Herança**: Todas as classes derivadas herdam da classe base `NoAST`.
2. **Associação**: Muitos nós têm associações com outros nós (ex: um `NoOperacao` tem associações com dois nós operandos).
3. **Composição**: Alguns nós contêm coleções de outros nós (ex: `NoBloco` contém uma lista de instruções).
4. **Auto-associação**: `ListaNoAST` tem uma auto-associação para implementar a lista encadeada.

As multiplicidades indicam a cardinalidade de cada relacionamento, como:
- Um `NoIf` tem exatamente uma condição (1..1) e um corpo (1..1), mas o corpo do else é opcional (0..1)
- Um `NoBloco` pode ter zero ou mais instruções (0..*)
- Um `ListaNoAST` contém exatamente um nó (1..1) e pode ter ou não um próximo item (0..1)

## Implementação em Lucidchart

O diagrama foi implementado no Lucidchart seguindo as convenções da UML:
- Classes representadas como retângulos com três compartimentos (nome, atributos, métodos)
- Relacionamentos de herança indicados por setas com triângulo vazio
- Associações indicadas por setas simples com multiplicidades nas extremidades
- Composições indicadas por setas com diamante preenchido

## Considerações de Design

Este diagrama de classes representa uma implementação orientada a objetos para a AST, embora o código original tenha sido implementado em C usando uma abordagem mais estruturada. A versão orientada a objetos oferece vantagens como:

1. Maior modularidade e encapsulamento
2. Facilidade para extensão com novos tipos de nós
3. Melhor representação das relações entre os diferentes componentes
4. Polimorfismo para operações comuns como impressão e liberação de memória

## Conclusão

O diagrama de classes apresentado fornece uma visão abrangente da estrutura da AST, mostrando claramente os diferentes tipos de nós, seus atributos, métodos e relacionamentos. Esta documentação serve como referência para entender a arquitetura do sistema e pode ser usada como base para futuras implementações ou modificações.

![Diagrama de Classes AST](./assets/Diagrama%20de%20classe%20-%20Pylua.png)