# Documentação Técnica do Analisador Léxico

## Visão Geral

O analisador léxico (lexer) do PyLua é implementado usando **Flex** e é responsável por converter o código fonte Python em uma sequência de tokens que serão consumidos pelo parser. O arquivo principal é `lexer/scanner.l`.

## Características Principais

- **Ferramenta**: Flex (Fast Lexical Analyzer Generator)
- **Arquivo fonte**: `lexer/scanner.l`
- **Arquivo gerado**: `src/lex.yy.c`
- **Integração**: Comunica com o parser através de `yylval` e códigos de token

## Tratamento de Indentação com Pilha

No Python, a estrutura de blocos é definida por indentação. Para lidar com isso corretamente no analisador léxico do PyLua, foi necessário criar um mecanismo que interpreta mudanças na indentação.

### Funcionamento com Pilha

- Utiliza-se uma pilha de indentaç~ para registrar os níveis de indentação (em espaços).
- Ao encontrar uma nova linha, o lexer calcula a quantidade de espaços (ou tabulações convertidas) antes do primeiro caractere visível.

#### Regras:

- **Indentação maior que o topo da pilha**:  
  Um novo bloco começa. Gera-se um token INDENT e o novo nível é empilhado.

- **Indentação igual ao topo da pilha**:  
  Nenhuma mudança estrutural. Nenhum token especial é gerado.

- **Indentação menor que o topo da pilha**:  
  O bloco anterior terminou. São gerados um ou mais tokens DEDENT, até que o valor no topo da pilha seja igual ao nível atual.

### Benefícios

Esse tratamento permite que o parser interprete corretamente estruturas aninhadas como `if`, `while`, `for` e funções, sem precisar reescrever as regras de sintaxe para cada nível de indentação.




## Histórico de Versões

| Versão | Data | Descrição | Autor | Revisor |
|--------|------|-----------|--------|----------|
| 1.0 | 17/06/2025 | Criação e edição do documento do analisador léxico | [Artur Mendonça](https://github.com/ArtyMend07) | [Lucas Mendonça](https://github.com/lucasarruda9) |
| 2.0 | ajuste da documentação | [Lucas Mendonça](https://github.com/lucasarruda9) | 27/06/2025 | [Artur Mendonça](https://github.com/ArtyMend07) | 27/06/2025 |
