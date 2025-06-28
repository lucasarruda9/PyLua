# Documentação Técnica do Analisador Sintático

## Visão Geral

O analisador sintático (parser) do PyLua é implementado usando **Bison/Yacc** e é responsável por analisar a estrutura sintática do código Python, construir a Árvore Sintática Abstrata (AST) e integrar com a tabela de símbolos. O arquivo principal é `parser/parser.y`.

## Características Principais

- **Ferramenta**: Bison (GNU Yacc)
- **Arquivo fonte**: `parser/parser.y`
- **Arquivo gerado**: `src/parser.tab.c` e `src/parser.tab.h`
- **Integração**: AST, Tabela de Símbolos, Gerador de Código Lua, Gerador de código intermediário


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

