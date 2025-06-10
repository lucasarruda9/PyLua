# Gerador de Código Lua - PyLua

## Visão Geral

O gerador de código Lua é um componente do compilador PyLua que converte a Árvore de Sintaxe Abstrata (AST) gerada pelo parser em código Lua equivalente.

## Funcionalidades Implementadas

### Tipos de Dados Suportados
- **Inteiros**: Números inteiros (ex: `42`)
- **Float**: Números decimais (ex: `3.14`)
- **String**: Strings entre aspas (ex: `"hello"`)
- **Boolean**: Valores booleanos (`true`, `false`)
- **Variáveis**: Identificadores de variáveis

### Operações Suportadas
- **Aritméticas**: `+`, `-`, `*`, `/`, `%`, `^`, `//`
- **Atribuições**: `=`, `+=`, `-=`, `*=`, `/=`, `%=`, `^=`
- **Comparações**: `<`, `>`, `<=`, `>=`, `==`, `!=`
- **Bitwise**: `&`, `|`, `^`, `<<`, `>>`

### Estruturas de Controle
- **Condicionais**: `if-then-else-end`
- **Loops**: `while-do-end`, `for-do-end`
- **Blocos**: Agrupamento de comandos com indentação

### Funções
- **Definição**: `function nome(parametros) ... end`
- **Chamadas**: `nome(argumentos)`

## Como Usar

### Compilação
```bash
make clean
make
```

### Uso Básico

#### 1. Gerar código Lua para arquivo
```bash
./pylua_debug arquivo.py --gerar-lua saida.lua
```

#### 2. Gerar código Lua para stdout
```bash
./pylua_debug arquivo.py --gerar-lua
```

#### 3. Modo interativo com geração de código
```bash
./pylua_debug --gerar-lua
```

### Exemplos

#### Entrada Python:
```python
x = 10
y = 20
z = x + y
resultado = z * 2
```

#### Saída Lua:
```lua
local x = 10
local y = 20
local z = (x + y)
local resultado = (z * 2)
```

## Estrutura do Código

### Arquivos Principais
- `gerador_codigo_final/gerador_codigo_final.h` - Interface do gerador
- `gerador_codigo_final/gerador_codigo_final.c` - Implementação do gerador
- `parser/parser.y` - Integração com o parser

### Funções Principais
- `inicializarGerador()` - Inicializa o gerador
- `gerarCodigoLua()` - Gera código para um nó da AST
- `gerarBlocoLua()` - Gera código para uma lista de nós
- `finalizarGerador()` - Finaliza e limpa o gerador

## Características Técnicas

### Indentação
- Usa 4 espaços por nível de indentação
- Controle automático de níveis de indentação

### Geração de Variáveis Temporárias
- Sistema de geração de variáveis temporárias (`temp_0`, `temp_1`, etc.)
- Contador automático para evitar conflitos

### Tratamento de Erros
- Verificação de ponteiros nulos
- Tratamento seguro de tipos de nós desconhecidos

## Limitações Atuais

1. **Escopo de Variáveis**: Todas as variáveis são declaradas como `local`
2. **Tipos Dinâmicos**: Não há verificação de tipos em tempo de compilação
3. **Estruturas Complexas**: Listas, dicionários e classes não são suportados
4. **Imports**: Não há suporte para importação de módulos

## Testes

Execute o script de teste para verificar o funcionamento:
```bash
chmod +x testar_gerador.sh
./testar_gerador.sh
```

## Próximos Passos

1. Implementar suporte para estruturas de dados complexas
2. Adicionar otimizações de código
3. Melhorar o tratamento de escopo de variáveis
4. Implementar suporte para módulos e imports
5. Adicionar mais testes automatizados
