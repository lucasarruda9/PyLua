# Guia de Testes do Compilador PyLua

Este documento descreve como executar os diferentes tipos de testes e verificações disponíveis no projeto PyLua.

## Índice

1. [Verificação de Dependências](#verificação-de-dependências)
2. [Compilação em Diferentes Modos](#compilação-em-diferentes-modos)
3. [Execução de Testes](#execução-de-testes)
4. [Testes Específicos](#testes-específicos)
5. [Atualização de Gabaritos](#atualização-de-gabaritos)
6. [Verificação de Sintaxe](#verificação-de-sintaxe)
7. [Limpeza de Arquivos](#limpeza-de-arquivos)

## Verificação de Dependências

Antes de compilar o projeto, é importante verificar se todas as dependências necessárias estão instaladas:

```bash
# Torna o script executável (necessário apenas na primeira vez)
chmod +x verificar_deps.sh

# Executa a verificação de dependências
./verificar_deps.sh
```

Este script verifica se as seguintes dependências estão instaladas:
- GCC (compilador C)
- Flex (gerador de analisador léxico)
- Bison (gerador de analisador sintático)
- Make (ferramenta de automação de compilação)

## Compilação em Diferentes Modos

O PyLua pode ser compilado em dois modos diferentes: debug e release.

### Usando o Script de Compilação

```bash
# Torna o script executável (necessário apenas na primeira vez)
chmod +x compilar.sh

# Compilação em modo debug (padrão)
./compilar.sh

# Compilação em modo release (otimizado)
./compilar.sh --release

# Compilação com limpeza prévia dos arquivos
./compilar.sh --limpar

# Compilação e execução imediata do programa
./compilar.sh --executar

# Compilação e execução dos testes
./compilar.sh --testes
```

### Usando o Makefile Diretamente

```bash
# Compilação em modo debug (padrão)
make

# Compilação em modo release (otimizado)
make release

# Compilação explícita em modo debug
make debug
```

## Execução de Testes

Para executar todos os testes automatizados:

```bash
# Torna o script de testes executável (necessário apenas na primeira vez)
chmod +x run_tests.sh

# Executa todos os testes
make test
```

## Testes Específicos

É possível executar apenas um tipo específico de teste:

```bash
# Executa apenas os testes do analisador léxico
make test_lexer

# Executa apenas os testes do analisador sintático
make test_parser

# Executa apenas os testes de análise semântica
make test_semantico
```

## Criação de Novos Testes

Para criar novos testes, adicione arquivos de texto nos diretórios apropriados:

```bash
# Crie diretórios para testes se não existirem
mkdir -p tests/parser tests/lexer tests/semantico tests/expected_outputs

# Exemplo: criar um teste para o parser
echo "x = 10 + 5" > tests/parser/teste_simples.txt

# Exemplo: criar um teste para o lexer
echo "def soma(a, b):\n    return a + b" > tests/lexer/teste_funcao.txt

# Exemplo: criar um teste para análise semântica
echo "x = 10\ny = x + 5\nprint(y)" > tests/semantico/teste_variaveis.txt
```

## Atualização de Gabaritos

Após criar novos testes ou modificar o comportamento do compilador, é necessário atualizar os gabaritos:

```bash
# Atualiza todos os gabaritos de teste
make atualizar_gabaritos
```

Isso executará cada teste e salvará a saída atual como o novo gabarito esperado.

## Verificação de Sintaxe

Para verificar a sintaxe do código fonte sem compilar completamente:

```bash
# Verifica a sintaxe dos arquivos .c
make verificar_sintaxe
```

## Limpeza de Arquivos

Existem dois níveis de limpeza disponíveis:

```bash
# Limpeza básica (remove arquivos gerados e executáveis)
make clean

# Limpeza completa (remove também diretórios de build e arquivos temporários)
make distclean
```

## Verificação da Compilação Condicional

Para verificar se a compilação condicional está funcionando corretamente:

```bash
# Compila em modo debug
make debug
# Verifica o executável gerado
ls -l pylua_debug

# Compila em modo release
make release
# Verifica o executável gerado
ls -l pylua_release

# Compara os dois executáveis
ls -lh pylua_*
```

O executável de release deve ser menor que o de debug, pois não contém símbolos de depuração.

## Estrutura de Diretórios de Teste

```
tests/
├── lexer/           # Testes para o analisador léxico
├── parser/          # Testes para o analisador sintático
├── semantico/       # Testes para análise semântica
└── expected_outputs/ # Gabaritos esperados para cada teste
```

## Arquivos Temporários

Os arquivos temporários gerados durante os testes são armazenados no diretório `temp/`. Eles não são removidos automaticamente após os testes para permitir inspeção manual. Use `make clean` ou `make distclean` para removê-los.