# Definição do Projeto: Pylua

## Introdução

O objetivo deste projeto é desenvolver um **compilador** que converte código escrito em Python para código em Lua. Este compilador passará por todas as fases essenciais da construção de um compilador: análise léxica, análise sintática, geração de código intermediário e execução. A principal motivação é proporcionar uma maneira de converter scripts Python para Lua, mantendo a semelhança de funcionalidade entre as duas linguagens.

## Descrição do Sistema

O Python e o Lua são duas linguagens de programação amplamente usadas, mas com diferenças significativas em suas sintaxes e paradigmas. O objetivo deste compilador é ler, interpretar e gerar código Lua equivalente ao código Python fornecido. O sistema deve ser capaz de analisar um código Python, entender sua estrutura e transformá-lo em Lua, que pode então ser executado.

## Funcionalidades

O compilador Python para Lua implementará as seguintes funcionalidades:

- **Analisador Léxico**: O analisador léxico será responsável por dividir o código Python em tokens, como palavras-chave, identificadores, operadores e literais.

- **Analisador Sintático**: O analisador sintático irá validar a estrutura gramatical do código Python, criando uma árvore de sintaxe abstrata (AST), que é uma representação intermediária e simplificada da estrutura do programa.

- **Gerador de Código Lua**: A partir da AST gerada, o compilador será responsável por converter a estrutura do código Python em código Lua equivalente.

- **Tratamento de Erros**: O compilador deve fornecer mensagens de erro detalhadas para problemas léxicos, sintáticos e semânticos encontrados durante a tradução e execução.

## Requisitos Funcionais

- O compilador deve ser capaz de ler um código Python válido.
- O código Python deve ser analisado sintaticamente para garantir sua validade.
- O compilador deve gerar código Lua equivalente que seja executável.
- O compilador deve exibir os resultados da execução ou mensagens de erro conforme o código fornecido.

## Requisitos Não-Funcionais

- O compilador deve ser desenvolvido em C usando Flex 2.6.4 e Bison 3.0
- O código gerado deve ser compatível com Lua 5.4
- O compilador deve suportar Python 3.8
- Deve ser possível compilar o projeto usando Make
- Deve incluir testes automatizados

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

## Referências Bibliográficas

- Aho, A. V.; Lam, M. S.; Sethi, R.; Ullman, J. D. *Compilers: Principles, Techniques, and Tools*. 2nd Edition. Pearson, 2006.
- Appel, A. W. *Modern Compiler Implementation in C*. Cambridge University Press, 1998.
- Ierusalimschy, R. *Programming in Lua*. 4th Edition. Lua.org, 2016.
- Van Rossum, G.; Drake, F. L. *Python 3 Reference Manual*. Python Software Foundation, 2023.
- IEEE. *IEEE Std 830-1998 - IEEE Recommended Practice for Software Requirements Specifications*. IEEE, 1998.
- Wiegers, K.; Beatty, J. *Software Requirements*. 3rd Edition. Microsoft Press, 2013.
- Sommerville, I. *Software Engineering*. 10th Edition. Pearson, 2015.
- Pressman, R. S. *Software Engineering: A Practitioner's Approach*. 8th Edition. McGraw-Hill, 2014.

## Histórico de Versões

| Versão | Descrição | Autor(es) | Data | Revisor(es) | Data de Revisão |
|--------|-----------|-----------|------|-------------|-----------------|
| 1.0 | Criação inicial do documento de definição | [Guilherme Meister](https://github.com/gmeister18) | 28/04/2025 |  |  |
| 1.1 | Atualização do documento da definição | [Artur Mendonça](https://github.com/ArtyMend07) | 02/05/2025 | [Gabriel Lopes](https://github.com/BrzGab) | 03/05/2025 |
