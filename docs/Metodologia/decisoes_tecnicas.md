# Decisões Técnicas

## Introdução
Este documento registra as principais decisões técnicas tomadas pela equipe durante o desenvolvimento do compilador PyLua, incluindo justificativas e impactos no projeto.

---

## Refatoração da Gramática e Integração Inicial
### Decisão
A equipe realizou uma refatoração significativa na gramática e no processo de integração entre analisador léxico e sintático.

### Justificativa
1. Conflitos identificados na gramática original
2. Necessidade de melhor integração entre lexer e parser
3. Problemas de dependências no processo de build

### Impacto
- Positivo: Eliminação de conflitos na gramática
- Positivo: Melhor modularização do código
- Negativo: Tempo adicional de desenvolvimento inicial

---

## Resolução de Problemas com Indentação
### Decisão
A equipe enfrentou e resolveu desafios significativos relacionados a erros sintáticos na implementação do sistema de indentação.

### Justificativa
1. Python utiliza indentação como parte da sintaxe
2. Erros sintáticos ocorriam constantemente durante a análise de blocos indentados
3. Necessidade de manter a estrutura hierárquica do código
4. Complexidade na integração com o parser existente

### Solução
A solução para resolver isso foi primeiramente criar uma pilha de indentação para acompanhar os níveis de recuo do código. Além disso, foi criado um estado léxico específico (<IDENT>) para capturar corretamente o início de linhas e calcular a quantidade de espaços e tabulações. Esse mecanismo compara a indentação atual com o topo da pilha, gerando os tokens INDENT e DEDENT conforme necessário. Depois disso veio o erro que toda linha final n era considerada dedentada, então para ajustar essa parte foi necessário utilizar um laço de repetição pra voltar 1 nivel da pilha até zerar, acabando com os erros sintáticos da indentação.

### Impacto
- Positivo: Melhor tratamento de blocos de código
- Positivo: Maior fidelidade à sintaxe Python
- Negativo: Aumento na complexidade do analisador léxico
- Negativo: Tempo adicional para debugar e corrigir erros

---

## Sistema de Escopos
### Decisão
Implementar um sistema de escopos no projeto

### Justificativa

1. É necessário implementar um sistema de escopos para isolar variáveis
2. Facilita o gerenciamento correto da tabela de símbolos, eliminando variáveis fora de contexto automaticamente.
3. Permite suporte a blocos aninhados e linguagens com estruturas complexas de escopo.

### Solução

Utilizou-se um contador global escopo_atual para identificar o nível do escopo atual. Cada símbolo armazenado na tabela possui um campo escopo que indica em qual nível foi declarado. Ao entrar em um novo bloco, incrementa-se escopo_atual, e ao sair do bloco, são removidos todos os símbolos pertencentes ao escopo atual da tabela, garantindo isolamento. Essa abordagem simula uma pilha de escopos, onde os símbolos do escopo mais interno são descartados ao sair dele.

### Impacto
- Positivo: Isolamento de variáveis
- Positivo: Facilita detecção de erros relacionados ao escopo
- Negativo: Aumenta a complexidade da tabela de símbolos, precisando de uma pilha pra sair e entrar em escopos.

---

## Gerador de Código Intermediário
### Decisão
A equipe optou por implementar primeiro a geração de código intermediário (TAC) 

### Justificativa

1. Permite otimizações antes da geração final, como eliminação de redundância e propagação de constantes
2. Facilita a futura adaptação para outras linguagens alvo além de Lua


Impacto

- Positivo: Permite análise e otimização mais robustas antes da geração final
- Negativo: Maior complexidade do compilador

---

## Otimização de Código Final

### Decisão  
A equipe optou por aplicar otimizações diretamente na fase de geração de código final (Lua), após a produção do código intermediário. as if que elimina dead code, constant foldin e constant propagation

### Justificativa  

1. Reduz o tamanho e melhora a eficiência do código gerado  
2. Elimina instruções redundantes ou desnecessárias no código Lua como variáveis nunca utilizadas (dead code)  

### Impacto  

- **Positivo:** Geração de código final mais limpo
- **Positivo:** Redução de custos computacionais na execução  
- **Negativo:** Aumenta a complexidade da etapa final do compilador  

---

## Sistema de Verificação de Tipos
### Decisão
Não implementar um sistema robusto de verificação de tipos.

### Justificativa
1. Python é uma linguagem dinamicamente tipada
2. Lua também suporta tipagem dinâmica
3. A verificação de tipos não é um requisito essencial para a funcionalidade do compilador
4. Foco em features mais importantes para a tradução Python-Lua

### Impacto
- Positivo: Maior fidelidade ao comportamento dinâmico do Python
- Positivo: Simplificação do processo de compilação
- Negativo: Menor capacidade de detectar erros de tipo em tempo de compilação

---

## Problema de Line Endings (CRLF vs LF)
### Decisão
Implementação de scripts para conversão automática entre line endings CRLF (Windows) e LF (Unix/Linux) para compatibilidade com WSL.

### Justificativa
1. O script `pylua.sh` não executava corretamente no WSL devido aos line endings CRLF (padrão Windows)
2. Testes de validação falhavam na comparação de arquivos por diferenças de line endings
3. Necessidade de manter compatibilidade tanto para desenvolvimento Windows quanto para execução em WSL
4. Evitar conflitos no Git causados por conversões automáticas de line endings

### Solução Implementada
Criação de dois comandos para conversão manual conforme necessário:

**Conversão para LF (para testes no WSL):**
```bash
find . -type f \( -name "*.txt" -o -name "*.sh" -o -name "*.py" -o -name "*.c" -o -name "*.h" -o -name "*.md" \) -exec dos2unix {} \;
```

**Conversão para CRLF (padrão Windows):**
```bash
find . -type f \( -name "*.txt" -o -name "*.sh" -o -name "*.py" -o -name "*.c" -o -name "*.h" -o -name "*.md" \) -exec unix2dos {} \;
```

### Impacto
- Positivo: Scripts funcionam corretamente no WSL
- Positivo: Testes de validação executam sem falhas
- Positivo: Compatibilidade mantida para desenvolvedores Windows
- Positivo: Controle manual evita conflitos automáticos no Git
- Negativo: Necessidade de conversão manual antes de testar no WSL

---

## Referências Bibliográficas

- COOPER, K.; TORCZON, L. *Engineering a Compiler*. 3rd Edition. Morgan Kaufmann, 2022. Disponível em: <https://www.elsevier.com/books/engineering-a-compiler/cooper/978-0-12-815412-0>

- MUCHNICK, S. S. *Advanced Compiler Design and Implementation*. Morgan Kaufmann, 1997. Disponível em: <https://www.elsevier.com/books/advanced-compiler-design-and-implementation/muchnick/978-1-55860-320-2>

- GRUNE, D.; VAN REEUWIJK, K.; BAL, H. E.; JACOBS, C. J.; LANGENDOEN, K. *Modern Compiler Design*. 2nd Edition. Springer, 2012. Disponível em: <https://link.springer.com/book/10.1007/978-1-4614-4699-6>

- KENNEDY, K.; ALLEN, J. R. *Optimizing Compilers for Modern Architectures: A Dependence-based Approach*. Morgan Kaufmann, 2001. Disponível em: <https://www.elsevier.com/books/optimizing-compilers-for-modern-architectures/kennedy/978-1-55860-286-1>

- SCOTT, M. L. *Programming Language Pragmatics*. 4th Edition. Morgan Kaufmann, 2015. Disponível em: <https://www.elsevier.com/books/programming-language-pragmatics/scott/978-0-12-410409-9>

## Histórico de Versões

| Versão | Descrição | Autor | Data | Revisor | Data Revisão |
|--------|-----------|-------|------|---------|--------------|
| 1.0 | Criação do documento e registro das decisões iniciais | [Artur Mendonça](https://github.com/ArtyMend07) | 15/06/2025 | [Lucas Mendonça](https://github.com/lucasarruda9) | 15/06/2025 |
| 1.1 | Adição da seção sobre problema de line endings (CRLF vs LF) e solução implementada | [Artur Mendonça](https://github.com/ArtyMend07) | 27/06/2025 | [Lucas Mendonça](https://github.com/lucasarruda9) e [Gabriel Lopes](https://github.com/gabriellopes7) | 27/06/2025 |
| 1.2 | Adição de desafios da geração de código intermediário, otimização e escopos  | 27/06/2025 | [Lucas Mendonça](https://github.com/lucasarruda9) e [Artur Mendonça](https://github.com/gabriellopes7) | 27/06/2025 |