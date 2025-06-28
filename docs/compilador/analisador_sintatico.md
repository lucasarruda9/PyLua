# Documentação Técnica do Analisador Sintático

## Visão Geral

O analisador sintático (parser) do PyLua é implementado usando **Bison/Yacc** e é responsável por analisar a estrutura sintática do código Python, construir a Árvore Sintática Abstrata (AST) e integrar com a tabela de símbolos. O arquivo principal é `parser/parser.y`.

## Características Principais

- **Ferramenta**: Bison (GNU Yacc)
- **Arquivo fonte**: `parser/parser.y`
- **Arquivo gerado**: `src/parser.tab.c` e `src/parser.tab.h`
- **Integração**: AST, Tabela de Símbolos, Gerador de Código Lua, Gerador de código intermediário

## Estrutura do Arquivo

### Seção de Declarações C
```c
%{
#include <stdio.h>
#include <stdlib.h>
#include "../ast/ast.h"
#include "../tabela/tabela.h"
#include "../gerador_codigo_final/gerador_codigo_final.h"
#include <string.h>
%}
```

### União de Tipos
```c
%union {
    int intval;              // Para valores inteiros
    struct Arvore *no;       // Para nós da AST
    char *string;            // Para strings e identificadores
    struct ListaNo *lista;   // Para listas de nós
}
```

## Tokens Declarados

### Tokens com Valores
```yacc
%token <intval> INTEGER          // Números inteiros
%token <string> IDENTIFIER       // Identificadores

```

### Tokens de Operadores
```yacc
%token PLUS MINUS MULTIPLY DIVIDE MODULO POWER FLOOR_DIV
%token LT GT LE GE EQ NE NE2
%token ASSIGN PLUS_EQ MINUS_EQ MULT_EQ DIV_EQ FLOOR_EQ POW_EQ MOD_EQ
```

### Tokens de Estrutura
```yacc
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE
%token COMMA COLON
%token IF ELIF ELSE WHILE
%token INDENT DEDENT NEWLINE ERROR
```

## Precedência de Operadores

A precedência segue a hierarquia padrão do Python:

```yacc
%left EQ NE NE2               // ==, !=, <>
%left LT GT LE GE             // <, >, <=, >=
%left PLUS MINUS              // +, -
%left MULTIPLY DIVIDE MODULO FLOOR_DIV  // *, /, %, //
%right POWER                  // ** (maior precedência)

```

## Tipos de Não-Terminais

```yacc
%type <no> expr               // Expressões
%type <no> declaracao         // Declarações/atribuições
%type <no> line               // Linha de código
%type <no> condicional        // Estruturas condicionais
%type <lista> bloco           // Blocos de código
%type <lista> linhas          // Lista de linhas
```

## Gramática Principal

### Regra de Entrada
```yacc
input: /* Produção vazia */
     | input line
     | input DEDENT
     | input INDENT
     ;
```

### Regras de Linha
```yacc
line: expr NEWLINE {
        imprimeArvore($1, 0);
        int resultado = avaliarArvore($1);
        printf("Resultado: %d\n", resultado);
        
        if (gerar_codigo_lua && arquivo_lua) {
            gerarCodigoLua($1);
        }
        
        DesalocarArvore($1);
        $$ = NULL;
    }
    | declaracao NEWLINE { /* Similar para declarações */ }
    | condicional NEWLINE { /* Similar para condicionais */ }
    | NEWLINE { $$ = NULL; }  // Linhas em branco
    | error NEWLINE {         // Recuperação de erro
        printf("[ERRO SINTATICO] Erro recuperado até o final da linha\n");
        yyerrok;
        $$ = NULL;
    }
    ;
```

## Expressões

### Literais e Identificadores
```yacc
expr: INTEGER { $$ = CriarNoInteiro($1); }
    | IDENTIFIER {
        Simbolo *s = buscarSimbolo($1);
        if (s == NULL) {
            printf("[AVISO] Variável '%s' não declarada\n", $1);
            inserirSimbolo($1, TIPO_INT);
        }
        $$ = CriarNoVariavel($1);
    }
    | LPAREN expr RPAREN { $$ = $2; }
    ;
```

### Operadores Binários
```yacc
expr: expr PLUS expr        { $$ = CriarNoOperador($1, $3, '+'); }
    | expr MINUS expr       { $$ = CriarNoOperador($1, $3, '-'); }
    | expr MULTIPLY expr    { $$ = CriarNoOperador($1, $3, '*'); }
    | expr DIVIDE expr      {
        if ($3->valor == 0 && $3->tipo == NoLiteral) {
            yyerror("Divisão por zero");
            $$ = CriarNoInteiro(0);
        } else {
            $$ = CriarNoOperador($1, $3, '/');
        }
    }
    | expr MODULO expr      { $$ = CriarNoOperador($1, $3, '%'); }
    | expr POWER expr       { $$ = CriarNoOperador($1, $3, 'p'); }
    ;
```

### Operadores de Comparação
```yacc
expr: expr LT expr          { $$ = CriarNoOperador($1, $3, '<'); }
    | expr GT expr          { $$ = CriarNoOperador($1, $3, '>'); }
    | expr LE expr          { $$ = CriarNoOperador($1, $3, 'l'); }
    | expr GE expr          { $$ = CriarNoOperador($1, $3, 'g'); }
    | expr EQ expr          { $$ = CriarNoOperador($1, $3, 'e'); }
    | expr NE expr          { $$ = CriarNoOperador($1, $3, 'd'); }
    | expr NE2 expr         { $$ = CriarNoOperador($1, $3, 'n'); }
    ;
```

### Operadores Bitwise
```yacc
expr: expr BITAND expr      { $$ = CriarNoOperador($1, $3, '&'); }
    | expr BITOR expr       { $$ = CriarNoOperador($1, $3, '|'); }
    | expr BITXOR expr      { $$ = CriarNoOperador($1, $3, '^'); }
    | expr SHIFTL expr      { $$ = CriarNoOperador($1, $3, 's'); }
    | expr SHIFTR expr      { $$ = CriarNoOperador($1, $3, 'r'); }
    ;
```

### Operadores Unários
```yacc
expr: MINUS expr %prec NEG     { $$ = CriarNoOperador($2, NULL, '-'); }
    | BITNOT expr %prec BITNOT { $$ = CriarNoOperador($2, NULL, '~'); }
    ;
```

## Declarações e Atribuições

### Atribuição Simples
```yacc
declaracao: IDENTIFIER ASSIGN expr {
    $$ = CriaNoAtribuicao(CriarNoVariavel($1), $3);
}
```

### Atribuições Compostas
```yacc
declaracao: IDENTIFIER PLUS_EQ expr {
    $$ = CriaNoAtribuicao(CriarNoVariavel($1), 
                         CriarNoOperador(CriarNoVariavel($1), $3, '+'));
}
| IDENTIFIER MINUS_EQ expr {
    $$ = CriaNoAtribuicao(CriarNoVariavel($1),
                         CriarNoOperador(CriarNoVariavel($1), $3, '-'));
}
| IDENTIFIER MULT_EQ expr {
    $$ = CriaNoAtribuicao(CriarNoVariavel($1),
                         CriarNoOperador(CriarNoVariavel($1), $3, '*'));
}
// ... outros operadores compostos
```

## Estruturas de Controle

### Blocos de Código
```yacc
bloco: INDENT linhas DEDENT { $$ = $2; }
     ;

linhas: linhas line { $$ = AdicionarNoLista($1, $2); }
      | line        { $$ = AdicionarNoLista(NULL, $1); }
      ;
```

### Condicionais
```yacc
condicional: IF LPAREN expr RPAREN COLON NEWLINE bloco {
    $$ = CriarNoIf($3, CriarNoBloco($7), NULL);
}
| IF LPAREN expr RPAREN COLON NEWLINE bloco ELSE COLON NEWLINE bloco {
    $$ = CriarNoIf($3, CriarNoBloco($7), CriarNoBloco($11));
}
;
```

## Integração com Componentes

### Integração com AST
- Cada regra gramatical cria nós da AST usando funções como:
  - `CriarNoInteiro(valor)`
  - `CriarNoVariavel(nome)`
  - `CriarNoOperador(esq, dir, op)`
  - `CriaNoAtribuicao(var, expr)`
  - `CriarNoIf(cond, corpo, senao)`

### Integração com Tabela de Símbolos
```c
// Verificação de variáveis não declaradas
Simbolo *s = buscarSimbolo($1);
if (s == NULL) {
    printf("[AVISO] Variável '%s' não declarada\n", $1);
    inserirSimbolo($1, TIPO_INT);
}
```

### Integração com Gerador de Código
```c
// Geração automática de código Lua
if (gerar_codigo_lua && arquivo_lua) {
    gerarCodigoLua($1);
}
```

## Tratamento de Erros

### Função de Erro
```c
void yyerror(const char *s) {
    fprintf(stderr, "[ERRO SINTATICO] %s na linha %d, coluna %d\n", 
            s, line_num, col_num);
}
```

### Recuperação de Erros
```yacc
line: error NEWLINE {
    printf("[ERRO SINTATICO] Erro recuperado até o final da linha\n");
    yyerrok;  // Reinicia o parser
    $$ = NULL;
}
```

### Verificações Semânticas
```yacc
// Verificação de divisão por zero
expr: expr DIVIDE expr {
    if ($3->valor == 0 && $3->tipo == NoLiteral) {
        yyerror("Divisão por zero");
        $$ = CriarNoInteiro(0);
    } else {
        $$ = CriarNoOperador($1, $3, '/');
    }
}
```

## Fluxo de Processamento

1. **Análise**: Parser consome tokens do lexer
2. **Construção**: Cria nós da AST para cada construção
3. **Verificação**: Consulta/atualiza tabela de símbolos
4. **Geração**: Produz código Lua equivalente se habilitado
5. **Limpeza**: Desaloca memória da AST

## Limitações Atuais

- Suporte limitado a estruturas de dados complexas
- Sem suporte a classes e métodos
- Loops `for` parcialmente implementado
- Tratamento de exceções básicas

## Histórico de Versões

| Versão | Data | Descrição | Autor | Revisor |
|--------|------|-----------|--------|----------|
| 1.0 | 17/06/2025 | Criação e edição do documento do analisador sintático | [Artur Mendonça](https://github.com/ArtyMend07) | [Lucas Mendonça](https://github.com/lucasarruda9) |
| 2.0 | ajuste da documentação | [Lucas Mendonça](https://github.com/lucasarruda9) | 27/06/2025 | [Artur Mendonça](https://github.com/ArtyMend07) | 27/06/2025 |

