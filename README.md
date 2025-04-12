# PyLua

PyLua é um compilador que traduz código Python para Lua. Este projeto está sendo desenvolvido como parte da disciplina de Compiladores 1.

## Visão Geral do Projeto

O PyLua está atualmente em estágios iniciais de desenvolvimento. No momento, ele pode reconhecer expressões regulares e realizar análise léxica básica.

## Estrutura do Repositório

```
COMPILADORES1-GP-8/
├── lexer/              # Componentes de análise léxica
│   ├── scanner.l       # Definição do scanner Flex
│   └── teste.txt       # Arquivo de entrada para testes
├── parser/             # Componentes de análise sintática
├── src/                # Código fonte
├── .gitignore          # Arquivo Git ignore
├── LICENSE             # Arquivo de licença
└── README.md           # Este arquivo
```

## Versões de Ferramentas Utilizadas

Este projeto foi construído e testado utilizando as seguintes versões de ferramentas:
* **Clang**: 16.0.0 (clang-1600.0.26.6) ou **GCC**
* **Flex**: 2.6.4
* **Bison**: 2.3

## Pré-requisitos

Para compilar e executar o PyLua, você precisa ter o seguinte instalado:
- Compilador C/C++ (Clang 16.0.0 ou GCC)
- Flex 2.6.4
- Bison 2.3
- Make (opcional, mas recomendado)

## Compilando o Projeto

1. Clone o repositório:
```
git clone https://github.com/lucasarruda9/Compiladores1-gp-8
cd Compiladores1-gp-8
```

2. Compile o scanner:
```
cd lexer
flex scanner.l
cc lex.yy.c -o scanner -ll
```

## Executando o Compilador

Atualmente, você pode testar o analisador léxico com:
```
cd lexer
./scanner < teste.txt
```

## Funcionalidades Atuais

- Reconhecimento de expressões regulares
- Análise léxica básica

## Em Desenvolvimento

- Análise léxica completa
- Análise sintática
- Geração de código
- Tradução de Python para Lua

## Contribuindo

Este projeto está sendo desenvolvido. As contribuições dos membros da equipe devem seguir os padrões de codificação e o fluxo de trabalho de desenvolvimento acordados.

## Licença

Veja o arquivo [LICENSE](LICENSE) para detalhes.

## Equipe

Grupo 8 - PyLua