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


### Operadores de Comparação

| Python | Lua | Observações |
|--------|-----|-------------|
| `<` | `<` | Menor que |
| `>` | `>` | Maior que |
| `<=` | `<=` | Menor ou igual |
| `>=` | `>=` | Maior ou igual |
| `==` | `==` | Igual |
| `!=` | `~=` | Diferente |
| `and` | `and` | E lógico |
| `or` | `or` | OU lógico |
| `not` | `not` | NÃO lógico |

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
make clean && make
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

### 4. Gerar código lua para testes 
```bash
./pylua.sh 
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

- **`gerador_codigo_final/gerador_codigo_final.c`**: Implementação principal
- **`ast/ast.c`**: Definições das estruturas da AST utilizando nós para a construção do código final
- **`tabela/tabela.c`**: Utilizado para buscar simbolos na tabela e gerar o código com base nisso
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
#### 3.  Argumentos de print
```c
//como se fosse gerarBlocoLua mas imprime com vírgula (para print)
void gerarListaArgumentosPrint(ListaNo* lista) {
    ListaNo* atual = lista;
    while (atual) {
        gerarExpressao(atual->no);  // imprime argumento
        if (atual->prox) {
            fprintf(gerador.arquivo_saida, ", ");
        }
        atual = atual->prox;
    }
}
```
#### 4.  Argumentos de print
```c
//usado para converter listas em código lua
void gerarBlocoLua(ListaNo* lista) {
    ListaNo* atual = lista;
    while (atual) {
        gerarCodigoLua(atual->no);
        atual = atual->prox;
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

### Fluxo de Execução
1. **Inicialização**: `inicializarGerador(arquivo_saida)`
2. **Processamento**: Para cada nó da AST, chama `gerarCodigoLua(no)`
3. **Finalização**: `finalizarGerador()` fecha arquivos e limpa estado

## Otimizações Implementadas

- As-if (elimina dead codes)
- Propagação

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

### Script de Testes geral
```bash
./pylua.sh test-generator --completo --validar
```

### Casos de Teste Cobertos
1. **Expressões aritméticas**: Maioria das operações básicas
2. **Atribuições**: Simples e compostas
3. **Condicionais**: If-else simples e aninhados
4. **Loops**: While básico
5. **Funções**: Definição e chamada
6. **Tipos de dados**: Inteiros, floats, strings, booleanos

### Validação de Saída
```bash
# Compilar um único arquivo Python para Lua 
./pylua exemplo.py --gerar-lua exemplo.lua

```

## Limitações e Trabalhos Futuros

### Limitações Atuais
1. **Estruturas de Dados**: Sem suporte a listas/dicionários
2. **Classes**: Orientação a objetos não implementada
3. **Módulos**: Sem sistema de imports
4. **Exceções**: Tratamento de erros limitado


### Melhorias Planejadas

1. **Estruturas Complexas**: Suporte a listas e dicionários Python
2. **Análise Semântica**: Verificação de tipos mais robusta
3. **Compatibilidade**: Suporte a mais construções Python

# Melhorias feitas
1. **Escopo Global**: Todas as declarações de variáveis são `local` a não ser que seja definida global
2. **Tipos Dinâmicos**: verificação de tipos na tabela de símbolos
## Histórico de Versões
3. **Debugging**: Preservar informações de linha do erro sintático

## Histórico de Versões

| Versão | Descrição | Autor | Data | Revisor | Data Revisão |
|--------|-----------|-------|------|---------|--------------|
| 1.0 | Criação do documento de codigo lua| [Artur Mendonça](https://github.com/ArtyMend07) | 17/06/2025 | [Lucas Mendonça](https://github.com/lucasarruda9) | 17/06/2025 |
| 2.0 | ajuste da documentação | [Lucas Mendonça](https://github.com/lucasarruda9) | 27/06/2025 | [Artur Mendonça](https://github.com/ArtyMend07) | 27/06/2025 |
