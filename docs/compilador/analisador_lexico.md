# Documentação Técnica do Analisador Léxico

## Visão Geral

O analisador léxico (lexer) do PyLua é implementado usando **Flex** e é responsável por converter o código fonte Python em uma sequência de tokens que serão consumidos pelo parser. O arquivo principal é `lexer/scanner.l`.

## Características Principais

- **Ferramenta**: Flex (Fast Lexical Analyzer Generator)
- **Arquivo fonte**: `lexer/scanner.l`
- **Arquivo gerado**: `src/lex.yy.c`
- **Integração**: Comunica com o parser através de `yylval` e códigos de token

## Estrutura do Arquivo

### Seção de Declarações C
```c
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/parser.tab.h"
%}
```

### Opções do Flex
```c
%option noyywrap noinput nounput nomain
```
- `noyywrap`: Não usa função yywrap() padrão
- `noinput`: Remove função input() não utilizada
- `nounput`: Remove função unput() não utilizada  
- `nomain`: Não gera função main() automática

## Tokens Suportados

### 1. Palavras-chave Python
```flex
KEYWORD: and|as|assert|break|class|continue|def|del|except|False|finally|from|global|import|in|is|lambda|None|nonlocal|not|or|pass|raise|return|True|try|with|yield
```

**Tokens específicos**:
- `IF`, `ELIF`, `ELSE`: Condicionais
- `FOR`, `WHILE`: Loops
- `ASYNC`, `AWAIT`: Programação assíncrona
- `MATCH`, `CASE`: Pattern matching (Python 3.10+)

### 2. Operadores Aritméticos
```flex
PLUS: "+"          MINUS: "-"         MULTIPLY: "*"
DIVIDE: "/"        MODULO: "%"        POWER: "**"
FLOOR_DIV: "//"
```

### 3. Operadores de Comparação
```flex
LT: "<"           GT: ">"            LE: "<="
GE: ">="          EQ: "=="           NE: "!="
NE2: "<>"         # Operador alternativo de diferença
```

### 4. Operadores de Atribuição
```flex
ASSIGN: "="       PLUS_EQ: "+="      MINUS_EQ: "-="
MULT_EQ: "*="     DIV_EQ: "/="       MOD_EQ: "%="
FLOOR_EQ: "//="   POW_EQ: "**="
```

### 5. Operadores Bitwise
```flex
BITAND: "&"       BITOR: "|"         BITXOR: "^"
BITNOT: "~"       SHIFTL: "<<"       SHIFTR: ">>"
AND_EQ: "&="      OR_EQ: "|="        XOR_EQ: "^="
SHIFTR_EQ: ">>="  SHIFTL_EQ: "<<="
```

### 6. Delimitadores
```flex
LPAREN: "("       RPAREN: ")"        LBRACKET: "["
RBRACKET: "]"     LBRACE: "{"        RBRACE: "}"
COMMA: ","        COLON: ":"         DOT: "."
DECORATOR: "@"    ARROW: "->"
```

### 7. Literais

#### Identificadores
```flex
IDENTIFIER: [a-zA-Z_][a-zA-Z0-9_]*
```
- Começam com letra ou underscore
- Podem conter letras, dígitos e underscores

#### Números
```flex
INTEGER: [0-9]+                                    # Inteiros decimais
FLOAT: [0-9]*\.[0-9]+([eE][-+]?[0-9]+)?           # Ponto flutuante
HEX: 0[xX][0-9a-fA-F]+                            # Hexadecimal
OCT: 0[oO][0-7]+                                  # Octal
BIN: 0[bB][01]+                                   # Binário
```

#### Strings
```flex
STRING_DQ: \"([^\"\n\\]|\\(.|\n))*\"              # Aspas duplas
STRING_SQ: \'([^\'\n\\]|\\(.|\n))*\'              # Aspas simples
TRIPLE_DQ: \"\"\"([^\\]|\\.)*?\"\"\"              # Triple quotes duplas
TRIPLE_SQ: \'\'\'([^\\]|\\.)*?\'\'\'              # Triple quotes simples
```

## Tratamento de Indentação Python

### Pilha de Indentação
```c
int pilha_indentacao[100];  // Pilha para níveis de indentação
int topo_pilha = 0;         // Topo da pilha
```

### Algoritmo de Indentação
```c
{INDENT} {
    int espacos = 0;
    // Calcula espaços (tab = 8 espaços)
    for (int i = 0; i < yyleng; i++) {
        if (yytext[i] == ' ') {
            espacos++;
        } else if (yytext[i] == '\t') {
            espacos += 8 - (espacos % 8);
        }
    }
    
    if (espacos > pilha_indentacao[topo_pilha]) {
        // Aumento de indentação
        topo_pilha++;
        pilha_indentacao[topo_pilha] = espacos;
        return INDENT;
    } else if (espacos < pilha_indentacao[topo_pilha]) {
        // Diminuição de indentação
        while (topo_pilha > 0 && espacos < pilha_indentacao[topo_pilha]) {
            topo_pilha--;
        }
        return DEDENT;
    }
}
```

### Tratamento de EOF
```c
<<EOF>> {
    // Gera DEDENTs pendentes no final do arquivo
    if (topo_pilha > 0) {
        topo_pilha--;
        return DEDENT;
    }
    yyterminate();
}
```

## Controle de Posição

### Variáveis Globais
```c
int line_num = 1;    // Linha atual
int col_num = 1;     // Coluna atual
```

### Funções Auxiliares
```c
void atualiza_coluna() {
    col_num += yyleng;  // Adiciona comprimento do token
}

void reset_coluna() {
    col_num = 1;        // Reset para início da linha
}
```

### Tratamento de Quebras de Linha
```c
\n { 
    line_num++; 
    reset_coluna(); 
    return NEWLINE; 
}
```

## Tratamento de Erros

### Caracteres Desconhecidos
```c
. {
    fprintf(stderr, "ERRO LÉXICO na linha %d, Caractere desconhecido: '%s'\n",
            line_num, yytext);
    atualiza_coluna();
    return ERROR;
}
```

### Indentação Inconsistente
```c
if (espacos != pilha_indentacao[topo_pilha]) {
    fprintf(stderr, "ERRO LÉXICO na linha %d, coluna %d: Indentação inconsistente\n", 
            line_num, col_num);
    return ERROR;
}
```

## Integração com o Parser

### Comunicação de Valores
```c
%union {
    int intval;           // Para números inteiros
    char *string;         // Para strings e identificadores
    struct Arvore *no;    // Para nós da AST
    struct ListaNo *lista; // Para listas de nós
}
```

### Exemplos de Retorno de Tokens
```c
{INTEGER} { 
    atualiza_coluna(); 
    yylval.intval = convert_to_int(yytext);  // Converte para int
    return INTEGER; 
}

{IDENTIFIER} { 
    atualiza_coluna(); 
    yylval.string = strdup(yytext);          // Copia string
    return IDENTIFIER; 
}
```

## Funções Auxiliares

### Conversão de Tipos
```c
int convert_to_int(char *text) {
    return atoi(text);
}
```

### Inicialização da Pilha
```c
void inicializa_pilha() {
    pilha_indentacao[0] = 0;
    topo_pilha = 0;
    eof_dedents_pendentes = 0;
    eof_encontrado = 0;
}
```

## Exemplos Práticos

### Exemplo 1: Expressão Aritmética
**Entrada Python**:
```python
x = 10 + 5 * 2
```

**Tokens Gerados**:
```
IDENTIFIER("x") ASSIGN INTEGER(10) PLUS INTEGER(5) MULTIPLY INTEGER(2) NEWLINE
```

### Exemplo 2: Estrutura Condicional
**Entrada Python**:
```python
if x > 0:
    print("positivo")
```

**Tokens Gerados**:
```
IF IDENTIFIER("x") GT INTEGER(0) COLON NEWLINE INDENT IDENTIFIER("print") LPAREN STRING_DQ("positivo") RPAREN NEWLINE DEDENT
```

## Limitações Conhecidas

1. **Strings f-string**: Não suportadas completamente
2. **Comentários multilinha**: Apenas `#` suportado
3. **Números complexos**: Não implementados
4. **Raw strings**: Suporte limitado
5. **Encoding**: Assume UTF-8

## Histórico de Versões

| Versão | Data | Descrição | Autor | Revisor |
|--------|------|-----------|--------|----------|
| 1.0 | 17/06/2025 | Criação e edição do documento do analisador léxico | [Artur Mendonça](https://github.com/ArtyMend07) | [Lucas Mendonça](https://github.com/lucasarruda9) |
