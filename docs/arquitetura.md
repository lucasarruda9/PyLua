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

### 5. Gerador de Código Lua
- **Arquivos**: `gerador_codigo_final/gerador_codigo_final.h`, `gerador_codigo_final/gerador_codigo_final.c`
- **Responsabilidade**: Converter a AST em código Lua
- **Características**:
  - Mapeamento direto Python → Lua
  - Controle de indentação Lua
  - Geração de código otimizado
  - Suporte a diferentes construções Python

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

### Fase 3: Geração de Código
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
- AST é construída bottom-up durante parsing
- Nós são avaliados e/ou convertidos para Lua

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

### Scripts de Automação
- `compilar.sh`: Script principal de compilação
- `run_tests.sh`: Execução de testes automatizados
- `verificar_deps.sh`: Verificação de dependências
- `testar_gerador.sh`: Teste específico do gerador

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
├── tabela/             # Tabela de símbolos
│   ├── tabela.h        # Interface
│   └── tabela.c        # Implementação
├── gerador_codigo_final/ # Gerador de código
│   ├── gerador_codigo_final.h
│   └── gerador_codigo_final.c
├── src/                # Arquivos gerados (temporários)
├── build/              # Executáveis de teste
├── tests/              # Testes automatizados
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
- Análise semântica básica
- Geração de código não otimizada
- Tratamento de erros pode ser melhorado

## Histórico de Versões

| Versão | Data | Descrição | Autor | Revisor |
|--------|------|-----------|--------|----------|
| 1.0 | 17/06/2025 | Criação e edição do documento de arquitetura | [Artur Mendonça](https://github.com/ArtyMend07) | [Lucas Mendonça](https://github.com/lucasarruda9) |
