# Documentação Técnica do Gerador de Código Lua

## Visão Geral

O gerador de código Lua é o componente final do compilador PyLua, responsável por converter a Árvore Sintática Abstrata (AST) em código Lua equivalente e executável. Este módulo implementa um transpilador que mapeia construções Python para suas equivalentes em Lua, mantendo a semântica original do programa.

## Arquitetura do Gerador

### Estrutura Principal
```c
typedef struct {
    FILE* arquivo_saida;           // Arquivo de destino
    int nivel_indentacao;          // Controle de indentação
    int contador_variaveis_temp;   // Contador para variáveis temporárias
} GeradorCodigo;
```

### Fluxo de Processamento
```
AST → Análise de Nós → Mapeamento Python→Lua → Geração de Código → Arquivo Lua
```

## Mapeamento Python → Lua

### Tipos de Dados

| Python | Lua | Exemplo Python | Exemplo Lua |
|--------|-----|----------------|-------------|
| `int` | `number` | `x = 42` | `local x = 42` |
| `float` | `number` | `pi = 3.14` | `local pi = 3.14` |
| `str` | `string` | `nome = "João"` | `local nome = "João"` |
| `bool` | `boolean` | `ativo = True` | `local ativo = true` |
| `None` | `nil` | `valor = None` | `local valor = nil` |

### Operadores Aritméticos

| Python | Lua | Observações |
|--------|-----|-------------|
| `+` | `+` | Soma |
| `-` | `-` | Subtração |
| `*` | `*` | Multiplicação |
| `/` | `/` | Divisão |
| `%` | `%` | Módulo |
| `**` | `^` | Potenciação |
| `//` | `math.floor(a/b)` | Divisão inteira |

### Operadores de Comparação

| Python | Lua | Observações |
|--------|-----|-------------|
| `<` | `<` | Menor que |
| `>` | `>` | Maior que |
| `<=` | `<=` | Menor ou igual |
| `>=` | `>=` | Maior ou igual |
| `==` | `==` | Igual |
| `!=` | `~=` | Diferente |
| `<>` | `~=` | Diferente (alternativo) |

### Operadores Bitwise

| Python | Lua | Implementação |
|--------|-----|---------------|
| `&` | `bit.band(a,b)` | AND bitwise |
| `\|` | `bit.bor(a,b)` | OR bitwise |
| `^` | `bit.bxor(a,b)` | XOR bitwise |
| `~` | `bit.bnot(a)` | NOT bitwise |
| `<<` | `bit.lshift(a,b)` | Shift left |
| `>>` | `bit.rshift(a,b)` | Shift right |

### Estruturas de Controle

#### Condicionais
**Python**:
```python
if condicao:
    comando1
else:
    comando2
```

**Lua**:
```lua
if condicao then
    comando1
else
    comando2
end
```

#### Loops While
**Python**:
```python
while condicao:
    comando
```

**Lua**:
```lua
while condicao do
    comando
end
```

#### Loops For
**Python**:
```python
for i in range(inicio, fim):
    comando
```

**Lua**:
```lua
for i = inicio, fim-1 do
    comando
end
```

### Funções

#### Definição
**Python**:
```python
def funcao(param1, param2):
    return param1 + param2
```

**Lua**:
```lua
function funcao(param1, param2)
    return param1 + param2
end
```

#### Chamada
**Python**:
```python
resultado = funcao(10, 20)
```

**Lua**:
```lua
local resultado = funcao(10, 20)
```

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

## Implementação Técnica

### Arquivos Principais
- **`gerador_codigo_final/gerador_codigo_final.h`**: Interface e definições
- **`gerador_codigo_final/gerador_codigo_final.c`**: Implementação principal
- **`parser/parser.y`**: Integração com o parser

### Funções Principais

#### Inicialização e Finalização
```c
void inicializarGerador(FILE* arquivo_saida);
void finalizarGerador();
```

#### Geração de Código
```c
void gerarCodigoLua(No* no);           // Gera código para um nó
void gerarBlocoLua(ListaNo* lista);    // Gera código para lista de nós
static void gerarExpressao(No* no);    // Gera expressões
```

#### Funções Auxiliares
```c
void aumentarIndentacao();             // Aumenta nível de indentação
void diminuirIndentacao();             // Diminui nível de indentação
char* obterVariavelTemporaria();       // Gera nome de variável temporária
static void indentar();                // Aplica indentação atual
```

### Algoritmo de Geração

#### 1. Análise do Tipo de Nó
```c
void gerarCodigoLua(No* no) {
    if (!no) return;

    switch (no->tipo) {
        case NoAtribuicao:
            // Gera atribuição
            break;
        case NoIf:
            // Gera condicional
            break;
        // ... outros casos
    }
}
```

#### 2. Geração de Expressões
```c
static void gerarExpressao(No* no) {
    switch (no->tipo) {
        case NoLiteral:
            fprintf(gerador.arquivo_saida, "%d", no->valor);
            break;
        case NoVariavel:
            fprintf(gerador.arquivo_saida, "%s", no->var);
            break;
        case NoOperacaoBinaria:
            fprintf(gerador.arquivo_saida, "(");
            gerarExpressao(no->esquerdo);
            fprintf(gerador.arquivo_saida, " %c ", no->op);
            gerarExpressao(no->direito);
            fprintf(gerador.arquivo_saida, ")");
            break;
    }
}
```

#### 3. Controle de Indentação
```c
static void indentar() {
    for (int i = 0; i < gerador.nivel_indentacao; i++) {
        fprintf(gerador.arquivo_saida, "    "); // 4 espaços
    }
}
```

## Exemplos Detalhados de Transformação

### Exemplo 1: Expressões Aritméticas Complexas
**Entrada Python**:
```python
resultado = (a + b) * (c - d) / 2
```

**AST Gerada**:
```
Atribuicao
    Variavel: resultado
    Operacao: /
        Operacao: *
            Operacao: +
                Variavel: a
                Variavel: b
            Operacao: -
                Variavel: c
                Variavel: d
        Literal: 2
```

**Saída Lua**:
```lua
local resultado = (((a + b) * (c - d)) / 2)
```

### Exemplo 2: Estrutura Condicional Complexa
**Entrada Python**:
```python
if x > 0 and y < 10:
    z = x + y
else:
    z = 0
```

**Saída Lua**:
```lua
if (x > 0) and (y < 10) then
    local z = (x + y)
else
    local z = 0
end
```

### Exemplo 3: Loop com Atribuições Compostas
**Entrada Python**:
```python
i = 0
while i < 10:
    i += 1
    soma += i
```

**Saída Lua**:
```lua
local i = 0
while (i < 10) do
    local i = (i + 1)
    local soma = (soma + i)
end
```

### Exemplo 4: Função com Múltiplos Parâmetros
**Entrada Python**:
```python
def calcular(a, b, c):
    return a * b + c
```

**Saída Lua**:
```lua
function calcular(a, b, c)
    return ((a * b) + c)
end
```

## Características Técnicas Avançadas

### Sistema de Indentação
```c
static GeradorCodigo gerador = {NULL, 0, 0};

void aumentarIndentacao() {
    gerador.nivel_indentacao++;
}

void diminuirIndentacao() {
    if (gerador.nivel_indentacao > 0) {
        gerador.nivel_indentacao--;
    }
}

static void indentar() {
    for (int i = 0; i < gerador.nivel_indentacao; i++) {
        fprintf(gerador.arquivo_saida, "    "); // 4 espaços
    }
}
```

### Geração de Variáveis Temporárias
```c
char* obterVariavelTemporaria() {
    static char buffer[32];
    snprintf(buffer, sizeof(buffer), "temp_%d",
             gerador.contador_variaveis_temp++);
    return buffer;
}
```

### Tratamento de Operadores Especiais
```c
// Mapeamento de operadores Python para Lua
switch (no->op) {
    case 'd': // != em Python
        fprintf(arquivo, " ~= ");
        break;
    case 'n': // <> em Python
        fprintf(arquivo, " ~= ");
        break;
    case 'p': // ** em Python
        fprintf(arquivo, " ^ ");
        break;
    // ... outros mapeamentos
}
```

## Integração com o Compilador

### Ativação no Parser
```c
// No parser.y
if (gerar_codigo_lua && arquivo_lua) {
    gerarCodigoLua($1);
}
```

### Configuração via Linha de Comando
```bash
# Gerar para arquivo específico
./pylua arquivo.py --gerar-lua saida.lua

# Gerar para stdout
./pylua arquivo.py --gerar-lua

# Modo interativo
./pylua --gerar-lua
```

### Fluxo de Execução
1. **Inicialização**: `inicializarGerador(arquivo_saida)`
2. **Processamento**: Para cada nó da AST, chama `gerarCodigoLua(no)`
3. **Finalização**: `finalizarGerador()` fecha arquivos e limpa estado

## Otimizações Implementadas

### Parentização Inteligente
- Adiciona parênteses apenas quando necessário para preservar precedência
- Reduz código gerado desnecessário

### Reutilização de Expressões
- Evita recálculo de subexpressões idênticas
- Usa variáveis temporárias quando apropriado

### Controle de Escopo
- Declara variáveis como `local` por padrão
- Mantém contexto de escopo durante geração

## Testes e Validação

### Scripts de Teste
```bash
# Teste básico do gerador
chmod +x testar_gerador.sh
./testar_gerador.sh

# Gerar exemplos completos
make gerar_exemplos
```

### Casos de Teste Cobertos
1. **Expressões aritméticas**: Todas as operações básicas
2. **Atribuições**: Simples e compostas
3. **Condicionais**: If-else simples e aninhados
4. **Loops**: While e for básicos
5. **Funções**: Definição e chamada
6. **Tipos de dados**: Inteiros, floats, strings, booleanos

### Validação de Saída
```bash
# Compilar Python para Lua
./pylua exemplo.py --gerar-lua exemplo.lua

# Executar código Lua gerado
lua exemplo.lua

# Comparar resultados
python exemplo.py
```

## Limitações e Trabalhos Futuros

### Limitações Atuais
1. **Escopo Global**: Todas as variáveis são `local`
2. **Estruturas de Dados**: Sem suporte a listas/dicionários
3. **Classes**: Orientação a objetos não implementada
4. **Módulos**: Sem sistema de imports
5. **Exceções**: Tratamento de erros limitado
6. **Tipos Dinâmicos**: Sem verificação de tipos

### Melhorias Planejadas
1. **Sistema de Escopo**: Implementar escopo global/local correto
2. **Estruturas Complexas**: Suporte a listas e dicionários Python
3. **Otimizações**: Eliminação de código morto, constant folding
4. **Análise Semântica**: Verificação de tipos mais robusta
5. **Debugging**: Preservar informações de linha/coluna
6. **Compatibilidade**: Suporte a mais construções Python

## Histórico de Versões

## Histórico de Versões

| Versão | Data | Descrição | Autor | Revisor |
|--------|------|-----------|--------|----------|
| 1.0 | 17/06/2025 | Criação e edição do documento do gerador de código lua | [Artur Mendonça](https://github.com/ArtyMend07) | [Lucas Mendonça](https://github.com/lucasarruda9) |