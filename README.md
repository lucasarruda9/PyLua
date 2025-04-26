# PyLua

PyLua é um compilador que traduz código Python para Lua. Este projeto está sendo desenvolvido como parte da disciplina de Compiladores 1.

## Visão Geral do Projeto

O PyLua está atualmente em estágios iniciais de desenvolvimento. Ele possui um analisador léxico (scanner) para reconhecer tokens Python e um analisador sintático (parser) que pode processar expressões aritméticas básicas.

## Estrutura do Repositório

```
PyLua/
├── lexer/              # Analisador léxico
│   └── scanner.l       # Definição do scanner Flex
├── parser/             # Analisador sintático
│   └── parser.y        # Definição do parser Bison
├── src/                # Código fonte gerado automaticamente
├── build/              # Diretório para arquivos de compilação
├── Makefile            # Script de construção
├── .gitignore          # Arquivo Git ignore
├── LICENSE             # Arquivo de licença
└── README.md           # Este arquivo
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

## Em Desenvolvimento

- Análise léxica completa para Python
- Análise sintática para estruturas Python
- Geração de código intermediário
- Tradução de Python para Lua

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