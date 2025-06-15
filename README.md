# PyLua

PyLua é um compilador que traduz código Python para Lua. Este projeto está sendo desenvolvido como parte da disciplina de Compiladores 1.

## Visão Geral do Projeto

O PyLua está atualmente em estágios iniciais de desenvolvimento. Ele possui um analisador léxico (scanner) para reconhecer tokens Python e um analisador sintático (parser) que pode processar expressões aritméticas básicas.

## Estrutura do Repositório

```
PyLua/
├── ast/                # Árvore Sintática Abstrata
│   ├── ast.c          # Implementação da AST
│   └── ast.h          # Definições da AST
├── build/             # Diretório de compilação
├── docs/              # Documentação
│   ├── Diagramas/     # Diagramas do projeto
│   ├── Metodologia/   # Documentação de metodologia
│   ├── planejamento/  # Documentos de planejamento
│   └── Semana 1/      # Documentos da primeira semana
├── exemplos/          # Exemplos de código Python
├── gerador_codigo_final/ # Gerador de código Lua
├── lexer/             # Analisador léxico
│   └── scanner.l      # Definições Flex
├── parser/            # Analisador sintático
├── tabela/            # Tabela de símbolos
├── tests/             # Testes do compilador
├── .github/           # Templates para GitHub
├── compilar.sh        # Script de compilação
├── inicializar_projeto.sh # Script de inicialização
├── Makefile          # Script de construção
├── README.md         # Este arquivo
├── run_tests.sh      # Script para execução de testes
├── testar_gerador.sh # Script para testar gerador
└── verificar_deps.sh # Script para verificar dependências
```

## Versões de Ferramentas Utilizadas

Este projeto foi construído e testado utilizando as seguintes versões de ferramentas:
* **GCC**: Versão compatível com C11
* **Flex**: 2.6.4
* **Bison**: 3.0 ou superior
* **Make**: 4.2 ou superior

## Pré-requisitos

Para compilar e executar o PyLua, você precisa ter o seguinte instalado:
- Compilador GCC
- Flex
- Bison
- Make

## Compilando o Projeto

Para compilar o projeto completo:
```bash
make
```

Para limpar os arquivos gerados:
```bash
make clean
```

## Executando o Compilador

### Analisador de Expressões Aritméticas

O projeto atual implementa um analisador de expressões aritméticas:
```bash
./expr_parser
```

Este analisador permite digitar expressões matemáticas terminadas com ponto e vírgula (;) e exibe o resultado:
```
Digite expressoes, terminadas com ';'. Pressione Ctrl+D para encerrar.
3+4*2;
Resultado: 11
(3+5)*2;
Resultado: 16
3++2;
[ERRO SINTATICO] Erro recuperado ate ';'
```

## Funcionalidades Atuais

- **Análise Léxica**: 
  - Reconhecimento de tokens Python
  - Identificação de operadores, identificadores, números e símbolos

- **Análise Sintática**:
  - Parser para expressões aritméticas básicas
  - Suporte a operadores +, -, *, / e parênteses
  - Cálculo de resultados das expressões
  - Recuperação de erros sintáticos

## Novidades na AST

Agora a AST do PyLua suporta:
- Novos tipos de nós: float, string, bool, bloco, if, while, for, função, chamada de função.
- Impressão detalhada e hierárquica da árvore, facilitando o debugging.

### Como testar as novidades

1. **Compilando o teste dos novos nós:**
   No terminal, execute:
   ```bash
   gcc -I./ast -I./tabela ./ast/ast.c ./tabela/tabela.c ./tests/ast/test_novos_nos.c -o ./build/test_novos_nos -lm
   ```
   Isso irá compilar o arquivo de teste que cria exemplos de todos os novos tipos de nós.

2. **Executando o teste:**
   Ainda no terminal, rode:
   ```bash
   ./build/test_novos_nos
   ```
   Você verá a impressão detalhada de cada tipo de nó criado, mostrando valores, hierarquia e estrutura.

### Testando estruturas de controle na AST

Para testar a criação e impressão dos nós de estruturas de controle (if, while, for):

1. Compile o teste:
   ```bash
   gcc -I./ast -I./tabela ./ast/ast.c ./tabela/tabela.c ./tests/ast/test_controle.c -o ./build/test_controle -lm
   ```
2. Execute:
   ```bash
   ./build/test_controle
   ```
   Você verá exemplos de if, if-else, while e for impressos de forma detalhada e hierárquica.

### O que foi feito

- Foram adicionados novos tipos de nós na AST para suportar estruturas de controle e funções.
- Implementadas funções de criação para cada novo tipo de nó.
- Melhorada a função de impressão da árvore para mostrar todos os detalhes dos nós.
- Criado um teste automatizado em `tests/ast/test_novos_nos.c` para validar e demonstrar as novidades.

## Em Desenvolvimento

- Geração de código intermediário

## Como Contribuir

Para contribuir com o projeto:

1. Clone o repositório
2. Crie uma branch para sua feature (`git checkout -b feature/nova-funcionalidade`)
3. Faça commit das suas mudanças (`git commit -m 'Adiciona nova funcionalidade'`)
4. Faça push para a branch (`git push origin feature/nova-funcionalidade`)
5. Abra um Pull Request

## Licença

Veja o arquivo [LICENSE](LICENSE) para detalhes.

## Equipe

Grupo 8 - PyLua

| Foto | Nome | GitHub |
|------|------|--------|
| ![Artur Mendonça](https://github.com/ArtyMend07.png?size=100) | Artur Mendonça | [ArtyMend07](https://github.com/ArtyMend07) |
| ![Gabriel Lopes](https://github.com/BrzGab.png?size=100) | Gabriel Lopes | [BrzGab](https://github.com/BrzGab) |
| ![Guilherme Meister](https://github.com/gmeister18.png?size=100) | Guilherme Meister | [gmeister18](https://github.com/gmeister18) |
| ![Lucas Mendonça](https://github.com/lucasarruda9.png?size=100) | Lucas Mendonça | [lucasarruda9](https://github.com/lucasarruda9) |
| ![Matheus Ferreira](https://github.com/matferreira1.png?size=100) | Matheus Ferreira | [matferreira1](https://github.com/matferreira1) |
| ![Samuel Alves](https://github.com/samuelalvess.png?size=100) | Samuel Alves | [samuelalvess](https://github.com/samuelalvess) |


## Histórico de Versões

| Versão | Data | Descrição | Autor | Revisor |
|--------|------|-----------|--------|----------|
| 1.0 | 25/04/2025 | Estrutura inicial do README | [Artur Mendonça](https://github.com/ArtyMend07) | [Lucas Mendonça](https://github.com/lucasarruda9) |
| 1.1 | 10/05/2025 | Atualização da estrutura do repositório e adição de novos tópicos | [Artur Mendonça](https://github.com/ArtyMend07) | [Lucas Mendonça](https://github.com/lucasarruda9) |
| 1.2 | 14/06/2025 | Atualização da estrutura do repositório | [Artur Mendonça](https://github.com/ArtyMend07) | [Gabriel Lopes](https://github.com/BrzGab), [Lucas Mendonça](https://github.com/lucasarruda9) |