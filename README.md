# PyLua - Compilador Python para Lua

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)]()
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Version](https://img.shields.io/badge/version-1.2-orange.svg)]()

PyLua é um **Compilador** que converte código Python em código Lua equivalente, desenvolvido como projeto da disciplina de Compiladores 1. O projeto implementa todas as fases clássicas de um compilador: análise léxica, análise sintática, construção de AST, análise semântica básica e geração de código.

## Características Principais

- **Análise Léxica Completa**: Reconhecimento de todos os tokens Python essenciais
- **Parser Robusto**: Análise sintática com recuperação de erros
- **AST Hierárquica**: Representação estruturada do código fonte
- **Geração de Código Lua**: Transpilação direta Python → Lua
- **Tabela de Símbolos**: Gerenciamento de variáveis e escopo
- **Testes Automatizados**: Suite completa de testes de validação

## Índice

- [Instalação e Uso](#-instalação-e-uso)
- [Exemplos Práticos](#-exemplos-práticos)
- [Arquitetura](#-arquitetura)
- [Funcionalidades](#-funcionalidades)
- [Documentação Técnica](#-documentação-técnica)
- [Desenvolvimento](#-desenvolvimento)
- [Equipe](#-equipe)

## Instalação e Uso

### Pré-requisitos
- **GCC** (versão 7.0+)
- **Flex** (versão 2.6.4+)
- **Bison** (versão 3.0+)
- **Make** (versão 4.2+)

### Verificação de Dependências
```bash
chmod +x verificar_deps.sh
./verificar_deps.sh
```

### Compilação
```bash
# Compilação completa
make clean && make

# Ou usando o script
./compilar.sh
```

### Uso Básico

#### Compilar arquivo Python para Lua
```bash
./pylua_debug arquivo.py --gerar-lua saida.lua
```

#### Modo interativo
```bash
./pylua_debug
```

#### Gerar código para stdout
```bash
./pylua_debug arquivo.py --gerar-lua
```

## Exemplos Práticos

### Exemplo 1: Operações Aritméticas
**Entrada Python (`exemplo.py`)**:
```python
x = 10
y = 20
resultado = (x + y) * 2
print(resultado)
```

**Comando**:
```bash
./pylua_debug exemplo.py --gerar-lua
```

**Saída Lua**:
```lua
local x = 10
local y = 20
local resultado = ((x + y) * 2)
print(resultado)
```

### Exemplo 2: Estruturas Condicionais
**Entrada Python**:
```python
idade = 18
if idade >= 18:
    status = "adulto"
else:
    status = "menor"
```

**Saída Lua**:
```lua
local idade = 18
if (idade >= 18) then
    local status = "adulto"
else
    local status = "menor"
end
```

### Exemplo 3: Funções
**Entrada Python**:
```python
def soma(a, b):
    return a + b

resultado = soma(10, 5)
```

**Saída Lua**:
```lua
function soma(a, b)
    return (a + b)
end

local resultado = soma(10, 5)
```

## Arquitetura

O PyLua segue a arquitetura clássica de compiladores:

```
Código Python → Lexer → Parser → AST → Gerador → Código Lua
```

### Componentes Principais

| Componente | Arquivo | Responsabilidade |
|------------|---------|------------------|
| **Lexer** | `lexer/scanner.l` | Análise léxica e tokenização |
| **Parser** | `parser/parser.y` | Análise sintática e construção da AST |
| **AST** | `ast/ast.{h,c}` | Representação da estrutura do programa |
| **Tabela de Símbolos** | `tabela/tabela.{h,c}` | Gerenciamento de variáveis |
| **Gerador** | `gerador_codigo_final/` | Geração de código Lua |

## Funcionalidades

### Implementado
- **Tipos de Dados**: `int`, `float`, `str`, `bool`
- **Operadores**: Aritméticos, comparação, bitwise, atribuição
- **Estruturas de Controle**: `if-else`, `while`, `for`
- **Funções**: Definição e chamada
- **Expressões**: Complexas com precedência correta
- **Recuperação de Erros**: Parser robusto com recuperação

### Em Desenvolvimento
- Estruturas de dados (listas, dicionários)
- Classes e herança
- Módulos e imports
- Tratamento de exceções

## Documentação Técnica

### Documentação Detalhada
- **[Arquitetura do Compilador](docs/arquitetura.md)**: Visão geral da arquitetura
- **[Analisador Léxico](docs/analisador_lexico.md)**: Documentação do lexer
- **[Analisador Sintático](docs/analisador_sintatico.md)**: Documentação do parser
- **[AST](docs/ast_documentacao.md)**: Estrutura da árvore sintática
- **[Gerador de Código](docs/gerador_codigo.md)**: Transpilação Python→Lua
- **[Guia de Desenvolvimento](docs/guia_desenvolvimento.md)**: Para contribuidores
- **[Metodologia](docs/Metodologia/metodologia.md)**: Processo de desenvolvimento
- **[Testes](docs/testes.md)**: Guia de testes automatizados

### Estrutura do Projeto
```
PyLua/
├── lexer/              # Analisador léxico
│   └── scanner.l       # Definições Flex
├── parser/             # Analisador sintático  
│   └── parser.y        # Gramática Bison
├── ast/                # Árvore sintática abstrata
│   ├── ast.h           # Definições de tipos
│   └── ast.c           # Implementação
├── tabela/             # Tabela de símbolos
│   ├── tabela.h        # Interface
│   └── tabela.c        # Implementação
├── gerador_codigo_final/ # Gerador de código
│   ├── gerador_codigo_final.h
│   └── gerador_codigo_final.c
├── src/                # Arquivos gerados (temporários)
├── build/              # Executáveis de teste
├── tests/              # Testes automatizados
├── exemplos/           # Exemplos de código Python
└── docs/               # Documentação
```

## Testes

### Executar Todos os Testes
```bash
make test
```

### Testes Específicos
```bash
# Testar AST
make test_ast

# Testar gerador de código
./testar_gerador.sh

# Gerar exemplos
make gerar_exemplos
```

### Validação com Valgrind
```bash
make valgrind
```

### Comandos Úteis
```bash
# Verificar dependências
./verificar_deps.sh

# Compilar em modo debug
make debug

# Executar com debugging
gdb ./pylua_debug

# Verificar vazamentos de memória
valgrind --leak-check=full ./pylua_debug arquivo.py
```

Consulte o **[Guia de Desenvolvimento](docs/guia_desenvolvimento.md)** para informações detalhadas.

## Licença

Este projeto está licenciado sob a Licença MIT - veja o arquivo [LICENSE](LICENSE) para detalhes.

## Equipe

**Grupo 8 - PyLua** | Compiladores 1 - 2025.1

<table>
<tr>
<td align="center">
<img src="https://github.com/ArtyMend07.png?size=100" width="100px" alt="Artur Mendonça"/><br/>
<b>Artur Mendonça</b><br/>
<i>Scrum Master</i><br/>
<a href="https://github.com/ArtyMend07">@ArtyMend07</a>
</td>
<td align="center">
<img src="https://github.com/BrzGab.png?size=100" width="100px" alt="Gabriel Lopes"/><br/>
<b>Gabriel Lopes</b><br/>
<i>Product Owner</i><br/>
<a href="https://github.com/BrzGab">@BrzGab</a>
</td>
<td align="center">
<img src="https://github.com/gmeister18.png?size=100" width="100px" alt="Guilherme Meister"/><br/>
<b>Guilherme Meister</b><br/>
<i>Developer</i><br/>
<a href="https://github.com/gmeister18">@gmeister18</a>
</td>
</tr>
<tr>
<td align="center">
<img src="https://github.com/lucasarruda9.png?size=100" width="100px" alt="Lucas Mendonça"/><br/>
<b>Lucas Mendonça</b><br/>
<i>Developer</i><br/>
<a href="https://github.com/lucasarruda9">@lucasarruda9</a>
</td>
<td align="center">
<img src="https://github.com/matferreira1.png?size=100" width="100px" alt="Matheus Ferreira"/><br/>
<b>Matheus Ferreira</b><br/>
<i>Developer</i><br/>
<a href="https://github.com/matferreira1">@matferreira1</a>
</td>
<td align="center">
<img src="https://github.com/samuelalvess.png?size=100" width="100px" alt="Samuel Alves"/><br/>
<b>Samuel Alves</b><br/>
<i>Developer</i><br/>
<a href="https://github.com/samuelalvess">@samuelalvess</a>
</td>
</tr>
</table>

---

## Estatísticas do Projeto

- **Linguagem Principal**: C (Flex/Bison)
- **Linhas de Código**: ~3000+
- **Testes**: 50+ casos de teste
- **Cobertura**: Lexer, Parser, AST, Gerador
- **Documentação**: 8 documentos técnicos

## Links Úteis

- **[Documentação Completa](docs/)**
- **[Exemplos de Código](exemplos/)**
- **[Testes Automatizados](tests/)**
- **[Metodologia Scrum](docs/Metodologia/metodologia.md)**

## Histórico de Versões

| Versão | Data | Descrição | Autor | Revisor |
|--------|------|-----------|--------|----------|
| 1.0 | 25/04/2025 | Estrutura inicial do README | [Gabriel Lopes](https://github.com/BrzGab) | [Lucas Mendonça](https://github.com/lucasarruda9) |
| 2.0| 17/06/2025 | Atualização da estrutura do repositório | [Artur Mendonça](https://github.com/ArtyMend07) | [Lucas Mendonça](https://github.com/lucasarruda9) |