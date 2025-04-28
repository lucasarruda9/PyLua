# Plano de Sprints para Compilador Python-Lua

## Informações Gerais

**Disciplina:** FGA0003 - Compiladores 1  
**Semestre:** 2025/1  
**Professor:** Dr. Sergio Antônio Andrade de Freitas  
**Projeto:** Compilador de Python para Lua  
**Entregas Principais:**
- Ponto de Controle P1: 30/04/2025
- Ponto de Controle P2: 04/06/2025
- Entrega Final: 27/06/2025
- Entrevistas Finais: 30/06/2025 e 02/07/2025

## Equipe

| Nome | GitHub |
|------|--------|
| Artur Mendonça | [ArtyMend07](https://github.com/ArtyMend07) 
| Gabriel Lopes | [BrzGab](https://github.com/BrzGab) 
| Guilherme Meister | [gmeister18](https://github.com/gmeister18)
| Lucas Mendonça | [lucasarruda9](https://github.com/lucasarruda9)
| Matheus Ferreira | [matferreira1](https://github.com/matferreira1)
| Samuel Alves | [samuelalvess](https://github.com/samuelalvess) 

## Visão Geral das Sprints

| Sprint | Período | Foco | Entregas | Status |
|--------|---------|------|----------|--------|
| 1 | 24/03 - 09/04 | Preparação e Análise Léxica | Analisador Léxico Funcional | ✅ Finalizada |
| 2 | 10/04 - 28/04 | Análise Sintática | Parser e P1 | 🔄 Iniciada |
| 3 | 01/05 - 14/05 | Representação Interna | AST e Tabela de Símbolos | 🟡 Não iniciado |
| 4 | 15/05 - 02/06 | Análise Semântica | Verificador Semântico e P2 | 🟡 Não iniciado |
| 5 | 05/06 - 18/06 | Geração de Código | Gerador de Código Lua | 🟡 Não iniciado |
| 6 | 19/06 - 27/06 | Refinamento e Testes | Compilador Completo | 🟡 Não iniciado |
| 7 | 28/06 - 09/07 | Apresentação e Fechamento | Documentação Final e Entrevista | 🟡 Não iniciado |

## Detalhamento das Sprints

### Sprint 1: Preparação e Análise Léxica
**Período:** 24/03/2025 - 09/04/2025

| Tarefa | Descrição | Responsável | Prazo | Status |
|--------|-----------|-------------|-------|--------|
| Definição de Escopo | Delimitar funcionalidades do compilador | [Artur Mendonça](https://github.com/ArtyMend07), [Gabriel Lopes](https://github.com/BrzGab), [Guilherme Meister](https://github.com/gmeister18), [Lucas Mendonça](https://github.com/lucasarruda9), [Matheus Ferreira](https://github.com/matferreira1), [Samuel Alves](https://github.com/samuelalvess) | 26/03 | ✅ |
| Configuração do Ambiente | Setup do repositório e ferramentas | [Lucas Mendonça](https://github.com/lucasarruda9) | 26/03 | ✅ |
| Pesquisa Comparativa | Estudo das diferenças Python-Lua | [Artur Mendonça](https://github.com/ArtyMend07) | 31/03 | ✅ |
| Definição de Tokens | Listar tokens Python a serem suportados | [Guilherme Meister](https://github.com/gmeister18), [Matheus Ferreira](https://github.com/matferreira1), [Samuel Alves](https://github.com/samuelalvess) | 31/03 | ✅ |
| Implementação do Scanner | Código do analisador léxico | [Artur Mendonça](https://github.com/ArtyMend07), [Gabriel Lopes](https://github.com/BrzGab), [Lucas Mendonça](https://github.com/lucasarruda9)| 07/04 | ✅ ||

**Entregável:** Analisador léxico capaz de reconhecer todos os tokens da linguagem Python (subset definido)  
**Critérios de Aceitação:** 
- Scanner reconhece corretamente todos os tokens definidos

### Sprint 2: Análise Sintática
**Período:** 10/04/2025 - 28/04/2025

| Tarefa | Descrição | Responsável | Prazo | Status |
|--------|-----------|-------------|-------|--------|
| Definição da Gramática | Criar gramática para subset Python | [Gabriel Lopes](https://github.com/BrzGab), [Artur Mendonça](https://github.com/ArtyMend07) | 14/04 | 🔄 |
| Implementação do Parser | Desenvolvimento do analisador sintático | [Lucas Mendonça](https://github.com/lucasarruda9), [Samuel Alves](https://github.com/samuelalvess) | 21/04 | 🔄 |
| Tratamento de Erros | Sistema de mensagens de erro sintático | [Matheus Ferreira](https://github.com/matferreira1) | 23/04 | 🔄 |
| Integração Léxico-Sintático | Conectar os dois módulos | [Guilherme Meister](https://github.com/gmeister18) | 25/04 | 🔄 |
| Preparação para P1 | Documentação e slides | [Artur Mendonça](https://github.com/ArtyMend07), [Gabriel Lopes](https://github.com/BrzGab), [Guilherme Meister](https://github.com/gmeister18), [Lucas Mendonça](https://github.com/lucasarruda9), [Matheus Ferreira](https://github.com/matferreira1), [Samuel Alves](https://github.com/samuelalvess) | 28/04 | 🔄 |
| Apresentação P1 | Apresentação para o professor | [Artur Mendonça](https://github.com/ArtyMend07), [Gabriel Lopes](https://github.com/BrzGab), [Guilherme Meister](https://github.com/gmeister18), [Lucas Mendonça](https://github.com/lucasarruda9), [Matheus Ferreira](https://github.com/matferreira1), [Samuel Alves](https://github.com/samuelalvess) | 30/04 | 🔄 |

**Entregável:** Parser funcional e apresentação do Ponto de Controle 1  
**Critério de Aceitação:** 
- Parser reconhece estruturas básicas Python
- Integração com análise léxica
- Documentação clara para P1
- Formulário P1 preenchido até 28/04

### Sprint 3: Representação Interna
**Período:** 01/05/2025 - 14/05/2025

| Tarefa | Descrição | Responsável | Prazo | Status |
|--------|-----------|-------------|-------|--------|
| Design da AST | Estruturar classes para AST | [Gabriel Lopes](https://github.com/BrzGab), [Guilherme Meister](https://github.com/gmeister18) | 05/05 | 🟡 |
| Implementação da AST | Código para construção da AST | [Artur Mendonça](https://github.com/ArtyMend07), [Lucas Mendonça](https://github.com/lucasarruda9) | 09/05 | 🟡 |
| Tabela de Símbolos | Implementação da tabela de símbolos | [Samuel Alves](https://github.com/samuelalvess) | 09/05 | 🟡 |
| Visualização da AST | Ferramenta para visualizar a AST gerada | [Matheus Ferreira](https://github.com/matferreira1) | 12/05 | 🟡 |
| Integração Parser-AST | Conectar parser à geração de AST | [Guilherme Meister](https://github.com/gmeister18) | 14/05 | 🟡 |
| Documentação | Documentar estruturas de dados | [Artur Mendonça](https://github.com/ArtyMend07) | 14/05 | 🟡 |

**Entregável:** Representação interna (AST) e tabela de símbolos funcionais  
**Critério de Aceitação:**
- AST gerada corretamente para programas de teste
- Tabela de símbolos mantém informações de escopo
- Visualização da AST para depuração

### Sprint 4: Análise Semântica e Geração de Código Intermediário
**Período:** 15/05/2025 - 02/06/2025

| Tarefa | Descrição | Responsável | Prazo | Status |
|--------|-----------|-------------|-------|--------|
| Verificação de Tipos | Sistema de verificação de tipos | [Gabriel Lopes](https://github.com/BrzGab), [Lucas Mendonça](https://github.com/lucasarruda9) | 19/05 | 🟡 |
| Verificação de Escopo | Validação de escopo de variáveis | [Artur Mendonça](https://github.com/ArtyMend07) | 21/05 | 🟡 |
| Verificação Semântica | Outras regras semânticas de Python | [Guilherme Meister](https://github.com/gmeister18), [Matheus Ferreira](https://github.com/matferreira1) | 26/05 | 🟡 |
| Código Intermediário | Estruturas para representação intermediária | [Lucas Mendonça](https://github.com/lucasarruda9), [Samuel Alves](https://github.com/samuelalvess) | 28/05 | 🟡 |
| Preparação para P2 | Documentação e slides | [Artur Mendonça](https://github.com/ArtyMend07), [Gabriel Lopes](https://github.com/BrzGab), [Guilherme Meister](https://github.com/gmeister18), [Lucas Mendonça](https://github.com/lucasarruda9), [Matheus Ferreira](https://github.com/matferreira1), [Samuel Alves](https://github.com/samuelalvess) | 02/06 | 🟡 |
| Apresentação P2 | Apresentação para o professor | [Artur Mendonça](https://github.com/ArtyMend07), [Gabriel Lopes](https://github.com/BrzGab), [Guilherme Meister](https://github.com/gmeister18), [Lucas Mendonça](https://github.com/lucasarruda9), [Matheus Ferreira](https://github.com/matferreira1), [Samuel Alves](https://github.com/samuelalvess) | 04/06 | 🟡 |

**Entregável:** Analisador semântico e representação intermediária  
**Critério de Aceitação:**
- Detecção de erros semânticos em programas de teste
- Representação intermediária gerada corretamente
- Formulário P2 preenchido até 02/06

### Sprint 5: Geração de Código Lua
**Período:** 05/06/2025 - 18/06/2025

| Tarefa | Descrição | Responsável | Prazo | Status |
|--------|-----------|-------------|-------|--------|
| Mapeamento Python-Lua | Definir equivalências entre linguagens | [Artur Mendonça](https://github.com/ArtyMend07), [Lucas Mendonça](https://github.com/lucasarruda9) | 09/06 | 🟡 |
| Gerador de Código | Implementação do gerador de código Lua | [Gabriel Lopes](https://github.com/BrzGab), [Matheus Ferreira](https://github.com/matferreira1) | 12/06 | 🟡 |
| Biblioteca de Runtime | Funções auxiliares para executar código gerado | [Samuel Alves](https://github.com/samuelalvess) | 12/06 | 🟡 |
| Disponibilização GitHub | Garantir acesso ao professor | [Lucas Mendonça](https://github.com/lucasarruda9) | 11/06 | 🟡 |
| Otimizações Básicas | Implementação de otimizações simples | [Artur Mendonça](https://github.com/ArtyMend07), [Guilherme Meister](https://github.com/gmeister18) | 16/06 | 🟡 |
| Testes de Integração | Testes end-to-end do compilador | [Matheus Ferreira](https://github.com/matferreira1), [Samuel Alves](https://github.com/samuelalvess) | 18/06 | 🟡 |

**Entregável:** Gerador de código Lua funcional  
**Critério de Aceitação:**
- Código Lua gerado é executável
- Estruturas básicas Python convertidas corretamente
- GitHub disponibilizado para o professor até 11/06

### Sprint 6: Refinamento e Testes
**Período:** 19/06/2025 - 27/06/2025

| Tarefa | Descrição | Responsável | Prazo | Status |
|--------|-----------|-------------|-------|--------|
| Mensagens de Erro | Melhoria nas mensagens de erro | [Gabriel Lopes](https://github.com/BrzGab) | 21/06 | 🟡 |
| Testes Avançados | Testes com programas complexos | [Artur Mendonça](https://github.com/ArtyMend07), [Guilherme Meister](https://github.com/gmeister18) | 23/06 | 🟡 |
| Otimizações Avançadas | Refinamento do código gerado | [Matheus Ferreira](https://github.com/matferreira1) | 25/06 | 🟡 |
| Documentação Final | Manual do usuário e técnico | [Samuel Alves](https://github.com/samuelalvess) | 25/06 | 🟡 |
| Preparação da Entrega | Empacotamento final | [Lucas Mendonça](https://github.com/lucasarruda9) | 27/06 | 🟡 |
| Entrega Final | Submissão via Teams | [Lucas Mendonça](https://github.com/lucasarruda9) | 27/06 | 🟡 |

**Entregável:** Compilador completo e documentação  
**Critério de Aceitação:**
- Compilador robusto com tratamento de erros
- Documentação completa
- Entrega submetida até 27/06 via Teams

### Sprint 7: Apresentação e Fechamento
**Período:** 28/06/2025 - 09/07/2025

| Tarefa | Descrição | Responsável | Prazo | Status |
|--------|-----------|-------------|-------|--------|
| Preparação para Entrevista | Revisão do código e slides | [Artur Mendonça](https://github.com/ArtyMend07), [Gabriel Lopes](https://github.com/BrzGab), [Guilherme Meister](https://github.com/gmeister18), [Lucas Mendonça](https://github.com/lucasarruda9), [Matheus Ferreira](https://github.com/matferreira1), [Samuel Alves](https://github.com/samuelalvess) | 29/06 | 🟡 |
| Entrevista Técnica | Apresentação para o professor | [Artur Mendonça](https://github.com/ArtyMend07), [Gabriel Lopes](https://github.com/BrzGab), [Guilherme Meister](https://github.com/gmeister18), [Lucas Mendonça](https://github.com/lucasarruda9), [Matheus Ferreira](https://github.com/matferreira1), [Samuel Alves](https://github.com/samuelalvess) | 30/06 ou 02/07 | 🟡 |
| Correções Pós-feedback | Ajustes baseados no feedback | [Gabriel Lopes](https://github.com/BrzGab), [Lucas Mendonça](https://github.com/lucasarruda9) | 07/07 | 🟡 |
| Fechamento | Documentação de lições aprendidas | [Artur Mendonça](https://github.com/ArtyMend07), [Guilherme Meister](https://github.com/gmeister18), [Matheus Ferreira](https://github.com/matferreira1) | 09/07 | 🟡 |

**Entregável:** Apresentação final e fechamento do projeto  
**Critério de Aceitação:**
- Entrevista bem-sucedida
- Documentação de lições aprendidas
- Projeto finalizado com todos os requisitos atendidos

## Funcionalidades do Compilador

| Categoria | Funcionalidade | Prioridade | Responsável | Status |
|-----------|---------------|------------|-------------|--------|
| **Estruturas Básicas** | Variáveis e atribuições | Alta | [Lucas Mendonça](https://github.com/lucasarruda9) | 🟡 |
| | Operadores aritméticos e lógicos | Alta | [Artur Mendonça](https://github.com/ArtyMend07) | 🟡 |
| | Estruturas condicionais (if/else) | Alta | [Gabriel Lopes](https://github.com/BrzGab) | 🟡 |
| | Loops (while, for) | Alta | [Guilherme Meister](https://github.com/gmeister18) | 🟡 |
| | Funções e procedimentos | Alta | [Matheus Ferreira](https://github.com/matferreira1) | 🟡 |
| **Estruturas de Dados** | Listas | Alta | [Samuel Alves](https://github.com/samuelalvess) | 🟡 |
| | Dicionários | Média | [Lucas Mendonça](https://github.com/lucasarruda9) | 🟡 |
| | Tuplas | Média | [Artur Mendonça](https://github.com/ArtyMend07) | 🟡 |
| **Recursos Python** | Indentação para blocos | Alta | [Gabriel Lopes](https://github.com/BrzGab) | 🟡 |
| | List comprehensions | Média | [Guilherme Meister](https://github.com/gmeister18) | 🟡 |
| | Funções lambda | Baixa | [Matheus Ferreira](https://github.com/matferreira1) | 🟡 |
| | Imports de módulos | Média | [Samuel Alves](https://github.com/samuelalvess) | 🟡 |
| **Recursos Avançados** | Classes e métodos | Baixa | [Lucas Mendonça](https://github.com/lucasarruda9) | 🟡 |
| | Tratamento de exceções | Baixa | [Artur Mendonça](https://github.com/ArtyMend07) | 🟡 |
| | Geradores | Baixa | [Gabriel Lopes](https://github.com/BrzGab) | 🟡 |

## Métricas e Acompanhamento

### Velocidade da Equipe
- Pontos planejados/concluídos por sprint
- Tarefas concluídas por sprint

### Qualidade
- Cobertura de testes (meta: >80%)
- Número de bugs encontrados/resolvidos
- Complexidade ciclomática (meta: <10 por método)

### Reuniões da Equipe
- **Reunião de Sprint**: Semanalmente, segunda-feira após a aula, via Discord
- **Revisão de Código**: Quarta-feira após a aula prática

## Riscos e Mitigações

| Risco | Probabilidade | Impacto | Estratégia de Mitigação | Responsável |
|-------|--------------|---------|-------------------------|-------------|
| Atraso em entregas | Média | Alto | Priorização das funcionalidades essenciais | [Lucas Mendonça](https://github.com/lucasarruda9) |
| Complexidade subestimada | Alta | Alto | Começar com subset mínimo de Python | [Artur Mendonça](https://github.com/ArtyMend07) |
| Problemas técnicos | Média | Médio | Manter ambiente alternativo e backups | [Gabriel Lopes](https://github.com/BrzGab) |
| Dificuldades de integração | Alta | Médio | Testes de integração contínuos | [Guilherme Meister](https://github.com/gmeister18) |
| Sobrecarga acadêmica | Alta | Médio | Distribuição balanceada de tarefas | [Matheus Ferreira](https://github.com/matferreira1) |

## Ferramentas e Tecnologias

| Categoria | Ferramenta | Propósito |
|-----------|------------|-----------|
| Linguagem de Implementação | [Python/Lua/C] | Desenvolvimento do compilador |
| Controle de Versão | Git/GitHub | Versionamento e colaboração |
| Gerenciamento de Projeto | GitHub Projects | Acompanhamento de tarefas |
| Comunicação | Discord/Teams | Reuniões e comunicação assíncrona |
| Documentação | Markdown| Documentação técnica |

---

*Este plano de sprints está sujeito a ajustes conforme o andamento do projeto e feedback do professor.*
## Histórico de versões

| Versão | Descrição | Autor(es) | Data | Revisor(es) | Data de Revisão |
| :----: | --------- | --------- | ---- | ----------- | :-------------: |
| 1.0 | Criação da documentação das sprints | [Lucas Mendonça](https://github.com/lucasarruda9) | 20/04/2025 | [Gabriel Lopes](https://github.com/BrzGab) | 20/04/2025 |
| 2.0 | Atualização do status das sprints e responsáveis | [Gabriel Lopes](https://github.com/BrzGab) | 22/04/2025 | [Lucas Mendonça](https://github.com/lucasarruda9) | 22/04/2025 |