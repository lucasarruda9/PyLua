# Guia de Testes do Compilador PyLua

Este documento descreve como executar os diferentes tipos de testes e verificações disponíveis no projeto PyLua.

## Índice

1. [Verificação de Dependências](#verificação-de-dependências)
2. [Compilação em Diferentes Modos](#compilação-em-diferentes-modos)
3. [Execução de Testes do Gerador](#execução-de-testes-do-gerador)
4. [Problema de Line Endings (CRLF vs LF)](#problema-de-line-endings-crlf-vs-lf)
5. [Verificação de Sintaxe](#verificação-de-sintaxe)
6. [Limpeza de Arquivos](#limpeza-de-arquivos)

## Verificação de Dependências

Antes de compilar o projeto, é importante verificar se todas as dependências necessárias estão instaladas:

```bash
# Executa a verificação de dependências
./pylua.sh deps
```

Este comando verifica se as seguintes dependências estão instaladas:
- GCC (compilador C)
- Flex (gerador de analisador léxico)
- Bison (gerador de analisador sintático)
- Make (ferramenta de automação de compilação)

## Compilação em Diferentes Modos

O PyLua pode ser compilado em dois modos diferentes: debug e release.

### Usando o Script pylua.sh

```bash
# Compilação em modo debug (padrão)
./pylua.sh build

# Compilação em modo release (otimizado)
./pylua.sh build --release

# Compilação e execução imediata do programa
./pylua.sh build --run

# Compilação release e execução
./pylua.sh build --release --run
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

## Execução de Testes do Gerador

O PyLua possui um sistema de testes focado no gerador de código Python para Lua:

### Teste Básico do Gerador

```bash
# Executa teste básico do gerador de código
./pylua.sh test-generator
```

### Teste Completo com Todos os Exemplos

```bash
# Executa teste completo com todos os exemplos
./pylua.sh test-generator --completo

# Teste completo com execução dos códigos Lua gerados
./pylua.sh test-generator --completo --executar

# Teste completo com validação usando gabaritos
./pylua.sh test-generator --completo --validar

# Teste completo com execução e validação
./pylua.sh test-generator --completo --executar --validar
```

### Usando o Makefile

```bash
# Teste básico do gerador
make test_gerador

# Teste de todos os exemplos
make test_exemplos

# Validação dos códigos Lua gerados
make validar_lua

# Geração de exemplos
make gerar_exemplos
```

## Problema de Line Endings (CRLF vs LF)

### Descrição do Problema

Durante o desenvolvimento, foi identificado um problema crítico relacionado aos line endings dos arquivos:

- **Windows** usa CRLF (`\r\n`) como padrão para quebras de linha
- **Linux/Unix/WSL** usa LF (`\n`) como padrão
- O script `pylua.sh` não executava corretamente no WSL devido aos line endings CRLF
- Os testes de validação falhavam na comparação de arquivos por diferenças de line endings

### Solução Implementada

Para resolver este problema, foram criados dois comandos para conversão manual dos line endings:

#### Conversão para LF (necessário para executar no WSL)

```bash
find . -type f \( -name "*.txt" -o -name "*.sh" -o -name "*.py" -o -name "*.c" -o -name "*.h" -o -name "*.md" \) -exec dos2unix {} \;
```

#### Conversão para CRLF (padrão Windows)

```bash
find . -type f \( -name "*.txt" -o -name "*.sh" -o -name "*.py" -o -name "*.c" -o -name "*.h" -o -name "*.md" \) -exec unix2dos {} \;
```

### Fluxo de Trabalho Recomendado

1. **Para desenvolvimento normal no Windows:** Manter arquivos em CRLF
2. **Para executar testes no WSL:**
   - Converter para LF usando o primeiro comando
   - Executar os testes: `./pylua.sh test-generator --completo --validar`
   - Converter de volta para CRLF usando o segundo comando
3. **Para commits no Git:** Manter em CRLF para evitar conflitos com outros desenvolvedores Windows

### Arquivos Afetados

Os comandos de conversão afetam os seguintes tipos de arquivo:
- `*.txt` - Arquivos de texto e gabaritos
- `*.sh` - Scripts bash
- `*.py` - Arquivos Python de exemplo
- `*.c` e `*.h` - Código fonte C
- `*.md` - Documentação Markdown

## Criação de Novos Exemplos

Para criar novos exemplos de código Python para testar o gerador:

```bash
# Adicione arquivos Python na pasta exemplos
echo "x = 10 + 5\nprint(x)" > exemplos/novo_exemplo.py

# Execute o gerador para criar o código Lua correspondente
./pylua.sh test-generator --completo
```

## Atualização de Gabaritos

Os gabaritos são arquivos `.txt` na pasta `exemplos_gabaritos` que contêm o código Lua esperado para cada exemplo Python.

Para criar ou atualizar gabaritos:

```bash
# 1. Execute o gerador para criar os arquivos Lua
make gerar_exemplos

# 2. Copie manualmente os códigos Lua corretos para os gabaritos
cp saidas_lua/exemplo_correto.lua exemplos_gabaritos/exemplo_correto.txt

# 3. Valide os gabaritos
./pylua.sh test-generator --validar
```

**Importante:** Só copie códigos Lua que estejam funcionando corretamente para os gabaritos.

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
exemplos/              # Arquivos Python de exemplo
exemplos_gabaritos/    # Gabaritos esperados (códigos Lua corretos)
saidas_lua/           # Códigos Lua gerados pelo compilador
temp/                 # Arquivos temporários
logs/                 # Logs de testes (quando executados)
```

## Arquivos Temporários

Os arquivos temporários gerados durante os testes são armazenados no diretório `temp/`. Os logs de teste são salvos em `logs/` com timestamp. Use `make clean` para remover arquivos temporários e logs.

## Histórico de Versões

| Versão | Descrição | Autor | Data | Revisor | Data Revisão |
|--------|-----------|-------|------|---------|--------------|
| 1.0 | Criação do documento inicial com testes do parser | [Artur Mendonça](https://github.com/ArtyMend07) | 15/06/2025 | [Lucas Mendonça](https://github.com/lucasarruda9) | 15/06/2025 |
| 2.0 | Refatoração completa: remoção de testes do parser, foco em testes do gerador, adição da seção sobre line endings (CRLF vs LF) | [Artur Mendonça](https://github.com/ArtyMend07) | 27/06/2025 | [Gabriel Lopes](https://github.com/gabriellopes7) | 27/06/2025 |