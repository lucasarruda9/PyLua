# Arquitetura do Compilador PyLua

## Visão Geral

O PyLua é um compilador transpilador que converte código Python em código Lua equivalente. A arquitetura segue o modelo clássico de compiladores com as seguintes fases principais:

```
Código Python → Análise Léxica → Análise Sintática → AST → Geração de Código → Código Lua
```

## Componentes Principais

### 1. Analisador Léxico (Lexer)
- **Arquivo**: `lexer/scanner.l`
- **Ferramenta**: Flex
- **Responsabilidade**: Converter o código fonte Python em tokens
- **Características**:
  - Reconhecimento de tokens Python (palavras-chave, operadores, literais)
  - Tratamento especial de indentação Python (INDENT/DEDENT)
  - Controle de linha e coluna para relatórios de erro
  - Suporte a diferentes tipos de literais (int, float, string, bool)

### 2. Analisador Sintático (Parser)
- **Arquivo**: `parser/parser.y`
- **Ferramenta**: Bison/Yacc
- **Responsabilidade**: Analisar a estrutura sintática e construir a AST
- **Características**:
  - Gramática livre de contexto para Python
  - Precedência e associatividade de operadores
  - Recuperação de erros sintáticos
  - Integração com tabela de símbolos

### 3. Árvore Sintática Abstrata (AST)
- **Arquivos**: `ast/ast.h`, `ast/ast.c`
- **Responsabilidade**: Representar a estrutura do programa
- **Tipos de Nós Suportados**:
  - Literais: `NoLiteral`, `NoFloat`, `NoString`, `NoBool`
  - Operações: `NoOperacaoBinaria`, `NoAtribuicao`
  - Controle: `NoIf`, `NoWhile`, `NoFor`, `NoBloco`
  - Funções: `NoFuncao`, `NoChamadaFuncao`
  - Variáveis: `NoVariavel`

### 4. Tabela de Símbolos
- **Arquivos**: `tabela/tabela.h`, `tabela/tabela.c`
- **Responsabilidade**: Gerenciar informações sobre identificadores
- **Funcionalidades**:
  - Inserção e busca de símbolos
  - Controle de escopo
  - Verificação de tipos
  - Detecção de variáveis não declaradas

### 5. Gerador de Código Intermediário (TAC)
- **Arquivos**: `codigo_intermediario/codigo_intermediario.c`, `codigo_intermediario/codigo_intermediario.h`
- **Responsabilidade**: Converter a AST em código intermediário
- **Características**:
  - Representação abstrata entre a análise e o código final
  - Geração de temporários e labels automáticos
  - Suporte a operações aritméticas, condicionais e controle de fluxo
  - Facilita otimizações como propagação de constantes e eliminação de redundâncias


## Fluxo de Dados

### Fase 1: Análise Léxica
```
Código Python → Scanner (Flex) → Stream de Tokens
```
- O scanner lê o código fonte caractere por caractere
- Identifica padrões usando expressões regulares
- Produz tokens com informações de posição
- Trata indentação Python especialmente

### Fase 2: Análise Sintática
```
Stream de Tokens → Parser (Bison) → AST + Tabela de Símbolos
```
- O parser consome tokens do lexer
- Aplica regras gramaticais para construir a AST
- Popula a tabela de símbolos durante a análise
- Realiza verificações semânticas básicas

### Fase 3: Geração de Código intermediário
```
AST + Tabela de Símbolos → Gerador → Código Lua
```
- Percorre a AST em ordem apropriada
- Mapeia construções Python para Lua
- Gera código com indentação correta
- Aplica otimizações quando possível

## Integração entre Componentes

### Lexer ↔ Parser
- O parser chama `yylex()` para obter próximo token
- Comunicação através de `yylval` para valores
- Informações de posição via `line_num` e `col_num`

### Parser ↔ AST
- Parser cria nós da AST usando funções como `CriarNoInteiro()`
- AST é construída durante parsing
- Nós são avaliados e convertidos para Lua

### Parser ↔ Tabela de Símbolos
- Inserção automática de variáveis durante atribuições
- Busca de símbolos durante uso de variáveis
- Verificação de tipos e escopo

### AST ↔ Gerador de Código
- Gerador percorre AST recursivamente
- Cada tipo de nó tem sua estratégia de geração
- Mantém contexto de indentação e escopo

## Arquivos de Configuração

### Makefile
- **Responsabilidade**: Automação do processo de build
- **Características**:
  - Compilação em modo debug/release
  - Geração automática de lexer e parser
  - Execução de testes
  - Limpeza de arquivos temporários

## Estrutura de Diretórios

```
PyLua/
├── lexer/              # Analisador léxico
│   └── scanner.l       # Definições Flex
├── parser/             # Analisador sintático  
│   └── parser.y        # Gramática Bison
├── ast/                # Árvore sintática abstrata
│   ├── ast.h           # Definições de tipos
│   └── ast.c           # Implementação
|── codigo_intermediario/ # Código intermediário
│   ├── codigo_intermediario.c           # Implementação do coódigo intermediário
│   └── codigo_intermediario.h          # Definição
├── tabela/             # Tabela de símbolos
│   ├── tabela.h        # Interface
│   └── tabela.c        # Implementação
├── gerador_codigo_final/ # Gerador de código
│   ├── gerador_codigo_final.h
│   └── gerador_codigo_final.c
├── src/                # Arquivos gerados (temporários)
├── build/              # Executáveis de teste
├── exemplos_gabaritos/ # Comparação para testes automatizadas
├── exemplos/           # Exemplos de código Python
└── docs/               # Documentação
```

## Pontos de Extensão

### Novos Tipos de Dados
1. Adicionar enum em `ast.h`
2. Implementar funções de criação em `ast.c`
3. Atualizar parser para reconhecer nova sintaxe
4. Implementar geração de código correspondente

### Novas Construções Sintáticas
1. Definir tokens no lexer se necessário
2. Adicionar regras gramaticais no parser
3. Criar tipos de nós AST apropriados
4. Implementar geração de código Lua

### Otimizações
1. Análise de AST para identificar padrões
2. Transformações de AST
3. Geração de código otimizado
4. Análise de fluxo de dados

## Limitações Atuais

- Suporte limitado a estruturas de dados complexas (listas, dicionários)
- Sem suporte a classes e herança
- Geração de código muito básica
- Tratamento de erros pode ser melhorado

## Histórico de Versões

| Versão | Descrição | Autor | Data | Revisor | Data Revisão |
|--------|-----------|-------|------|---------|--------------|
| 1.0 | Criação da documento de arquitetura| [Artur Mendonça](https://github.com/ArtyMend07) | 17/06/2025 | [Lucas Mendonça](https://github.com/lucasarruda9) | 17/06/2025 |
| 2.0 | ajuste da documentação | [Lucas Mendonça](https://github.com/lucasarruda9) | 27/06/2025 | [Artur Mendonça](https://github.com/ArtyMend07) | 27/06/2025 |
