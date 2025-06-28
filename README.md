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

#### Gerar Ast pelo terminal
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
./pylua_debug exemplo.py --gerar-lua saida.lua
```

**Saída Lua (`saida.lua`)**:
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
| **Código intermediário** | `tabela/tabela.{h,c}` | Ajuda na compilação de futuras otimizações|
| **Gerador** | `gerador_codigo_final/` | Geração de código Lua |

## Funcionalidades

### Implementado
- **Tipos de Dados**: `int`, `float`, `str`, `bool`
- **Operadores**: Aritméticos, comparação, atribuição
- **Estruturas de Controle**: `if-else`, `while`
- **Funções**: Definição e chamada
- **Expressões**: Complexas com precedência correta
- **Recuperação de Erros**: Parser com recuperação de erros sintáticos e declarações indevidas

### Em Desenvolvimento
- Estruturas de dados (listas, dicionários)
- Classes e herança
- Módulos e imports

## Documentação Técnica

### Documentação Detalhada
- **[Atas](docs/atas)**: Atas de reuniões onlines (whatsapp)
- **[Compilador](docs/compilador)**: Documentação sobre esturturas(léxico, parser...), arquitetura, e testes
- **[Diagrama](docs/Diagramas)**: Documentação do contendo a idealização da ast (diagrama)
- **[Metodologia](docs/analisador_sintatico.md)**: Divisão da equipe, como metodologia e decisões
- **[Planejamento](docs/planejamento)**: Planejamento inicial do projeto

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
|── codigo_intermediario/ # Código intermediário
│   ├── codigo_intermediario.c           # Implementação do coódigo intermediário
│   └── codigo_intermediario.h          # Definição
├── tabela/             # Tabela de símbolos
│   ├── tabela.h        # Interface
│   └── tabela.c        # Implementação
├── gerador_codigo_final/ # Gerador de código
│   ├── gerador_codigo_final.h
│   └── gerador_codigo_final.c
├── src/                # Arquivos gerados (temporários)
├── build/              # Executáveis de teste
├── exemplos_gabaritos/ # Comparação para testes automatizadas
├── exemplos/           # Exemplos de código Python
└── docs/               # Documentação
```

## Testes

### Executar Todos os Testes verificando arquivos gerados, não gerados e que não passaram nos testes
```bash
./pylua.sh test-generator --completo --validar
```

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