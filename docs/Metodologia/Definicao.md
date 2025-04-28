# Definição do Projeto: Compilador Python para Lua

## Introdução

O objetivo deste projeto é desenvolver um **compilador** que converte código escrito em Python para código em Lua. Este compilador passará por todas as fases essenciais da construção de um compilador: análise léxica, análise sintática, geração de código intermediário e execução. A principal motivação é proporcionar uma maneira de converter scripts Python para Lua, mantendo a semelhança de funcionalidade entre as duas linguagens.

## Descrição do Sistema

O Python e o Lua são duas linguagens de programação amplamente usadas, mas com diferenças significativas em suas sintaxes e paradigmas. O objetivo deste compilador é ler, interpretar e gerar código Lua equivalente ao código Python fornecido. O sistema deve ser capaz de analisar um código Python, entender sua estrutura e transformá-lo em Lua, que pode então ser executado.

## Funcionalidades

O compilador Python para Lua implementará as seguintes funcionalidades:

- **Analisador Léxico**: O analisador léxico será responsável por dividir o código Python em tokens, como palavras-chave, identificadores, operadores e literais.

- **Analisador Sintático**: O analisador sintático irá validar a estrutura gramatical do código Python, criando uma árvore de sintaxe abstrata (AST), que é uma representação intermediária e simplificada da estrutura do programa.

- **Gerador de Código Lua**: A partir da AST gerada, o compilador será responsável por converter a estrutura do código Python em código Lua equivalente.

- **Execução**: O código Lua gerado será executado para verificar se ele se comporta de maneira semelhante ao código Python original.

- **Tratamento de Erros**: O compilador deve fornecer mensagens de erro detalhadas para problemas léxicos, sintáticos e semânticos encontrados durante a tradução e execução.

## Requisitos Funcionais

- O compilador deve ser capaz de ler um código Python válido.
- O código Python deve ser analisado sintaticamente para garantir sua validade.
- O compilador deve gerar código Lua equivalente que seja executável.
- O compilador deve exibir os resultados da execução ou mensagens de erro conforme o código fornecido.

## Arquitetura

### Componentes Principais

- **Scanner (Analisador Léxico)**: Responsável por dividir o código Python em tokens, identificando palavras-chave, identificadores, literais, operadores e outros componentes sintáticos essenciais.

- **Parser (Analisador Sintático)**: O parser verifica a sintaxe do código Python, construindo a árvore de sintaxe abstrata (AST) que representa a estrutura do código. O parser é responsável por validar que o código segue as regras da gramática do Python.

- **Gerador de Código Lua**: A partir da AST gerada, o compilador converte a estrutura do código Python em código Lua correspondente. Isso envolve mapeamento de construções Python para Lua, como `def` para funções, `if` para condicionais, e `for` para loops.

- **Executor**: O executor será responsável por rodar o código Lua gerado, realizando a execução e retornando os resultados.

- **Gerenciador de Erros**: O gerenciador de erros captura e exibe erros léxicos (quando um token não pode ser reconhecido), sintáticos (quando o código não segue as regras da gramática) e semânticos (quando o código não é válido semanticamente, como variáveis não definidas).

### Fluxo de Execução

1. **Entrada do código Python**: O código-fonte em Python é fornecido ao scanner.
2. **Análise Léxica**: O scanner converte o código Python em tokens.
3. **Análise Sintática**: O parser valida a sintaxe do código Python e gera uma árvore de sintaxe abstrata (AST).
4. **Geração de Código Lua**: A AST gerada é convertida para código Lua.
5. **Execução**: O código Lua gerado é executado.
6. **Tratamento de Erros**: Durante o processo de análise e execução, erros são detectados e mensagens são retornadas ao usuário.

### Exemplo de Fluxo de Código

1. **Entrada Python**:

    ```python
    def soma(a, b):
        return a + b

    print(soma(3, 4))
    ```

2. **Analisador Léxico**: Identificação dos tokens:
    - `def`
    - `soma`
    - `(`
    - `a`
    - `,`
    - `b`
    - `)`
    - `:`
    - `return`
    - `a`
    - `+`
    - `b`
    - `print`
    - `(`
    - `soma`
    - `(`
    - `3`
    - `,`
    - `4`
    - `)`
    - `)`

3. **Analisador Sintático**: Geração da AST.

4. **Geração de Código Lua**:

    ```lua
    function soma(a, b)
        return a + b
    end

    print(soma(3, 4))
    ```

5. **Execução**: O código Lua gerado é executado e imprime `7`.

## Histórico de Versão

| Versão | Data       | Descrição                       |
|--------|------------|---------------------------------|
| 1.0    | 03/04/2025 | Versão inicial com análise léxica e sintática implementadas.|
| 1.1    | 05/04/2025 | Adicionada a geração de código Lua e a execução.|
| 1.2    | 10/04/2025 | Melhorias no tratamento de erros e otimização da execução. |

## Etapas para Implementação

1. **Desenvolvimento do Scanner (Analisador Léxico)**:
    - Criar um lexer usando **Flex** ou similar para identificar os tokens do Python, como palavras-chave, identificadores, operadores, etc.
   
2. **Desenvolvimento do Parser (Analisador Sintático)**:
    - Usar uma ferramenta como **Bison** ou **ANTLR** para criar o parser que construa a árvore de sintaxe abstrata (AST) a partir dos tokens identificados.

3. **Desenvolvimento do Gerador de Código Lua**:
    - Implementar uma fase de geração de código Lua, que converte a AST Python em código Lua equivalente. Isso envolve mapear as construções da linguagem Python para Lua.

4. **Execução do Código Lua**:
    - Usar a funcionalidade de execução Lua, que pode ser realizada através de um interpretador Lua integrado, ou por meio de uma interface para rodar o código gerado.

5. **Tratamento de Erros**:
    - Implementar um sistema de tratamento de erros para capturar erros léxicos, sintáticos e semânticos durante a análise e execução.

## Conclusão

Este projeto de compilador Python para Lua segue a abordagem clássica de um compilador, com fases de análise léxica, sintática e execução, e inclui um tratamento robusto de erros. Ele visa proporcionar uma ferramenta eficaz para traduzir código Python para Lua e executar o código gerado, mantendo a semelhança funcional entre as duas linguagens.
