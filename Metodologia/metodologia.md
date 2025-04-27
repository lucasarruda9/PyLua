# Metodologia do Projeto – Compilador Python para Lua

## Introdução

Este documento descreve a metodologia adotada pelo grupo para o desenvolvimento do compilador de Python para Lua. Após a análise das necessidades do projeto e das práticas de desenvolvimento ágil, optamos por utilizar o **Scrum** pela sua capacidade de organizar e evoluir projetos de forma incremental, garantindo transparência e colaboração entre os membros da equipe.

O Scrum permite entregas frequentes e feedback contínuo, possibilitando ajustes durante o desenvolvimento das diferentes fases do compilador: análise léxica, análise sintática, análise semântica e geração de código.

## Escopo da Metodologia

O presente documento abrange:
- A definição da metodologia adotada.
- A estrutura e os papéis atribuídos dentro do Scrum.
- Os fluxos de trabalho e os padrões/convenções utilizados na gestão dos artefatos, como o controle de versão com Git e GitHub Pages.
- Os processos para criação e gerenciamento de issues e pull requests.

**O que é Scrum?**  
Scrum é um framework ágil para o gerenciamento e desenvolvimento de projetos, fundamentado em ciclos de trabalho chamados *sprints*. Cada sprint possibilita uma entrega incremental do produto, permitindo feedback constante e ajustes rápidos conforme as necessidades do projeto. Esse método enfatiza a colaboração, a transparência e a adaptabilidade do time, contribuindo para a melhoria contínua do processo de desenvolvimento.

## Abordagem e Estrutura do Scrum

No Scrum, o trabalho é dividido em ciclos curtos (*sprints*) que facilitam a revisão constante e a entrega incremental das diferentes fases do compilador. Para este projeto, os papéis foram definidos da seguinte forma:

- **Product Owner:**  
  - **Gabriel Lopes**  
  - Responsável por definir as prioridades do projeto, garantir que o produto atenda às necessidades do cliente e maximizar o valor do trabalho da equipe.

- **Scrum Master:**  
  - **Artur Mendonça**  
  - Responsável por facilitar os processos, remover impedimentos e assegurar a aplicação correta dos princípios do Scrum.

- **Equipe de Desenvolvimento:**  
  - Composta pelos demais membros do grupo, que executam as atividades de implementação das diferentes fases do compilador.

## Padrões e Convenções de Desenvolvimento

Para manter a qualidade e a rastreabilidade dos artefatos, adotamos as seguintes práticas:

- **GitHub Pages e Git:**
  - **Pull Requests (PRs):** Alterações são submetidas via PRs para permitir a revisão colaborativa e garantir a integração contínua das modificações.
  - **Issues:** Utilizadas para reportar e gerenciar tarefas, bugs e solicitações de melhorias, contendo descrições detalhadas e critérios de aceitação.
  - **Branches:** Nomeadas conforme o padrão `<tipo>/<descricao-breve>`, por exemplo, `feat/lexer` ou `fix/parser`.
  - **Histórico de Versões:** Atualizado de forma padronizada para documentar as mudanças realizadas, bem como os responsáveis por elas.

- **Tipos de Branches – Padrões Comuns**

| Tipo        | Uso                                                   | Exemplo                          |
|-------------|--------------------------------------------------------|----------------------------------|
| `feat`      | Adição de nova funcionalidade                          | `feat/lexer`                    |
| `fix`       | Correção de bugs                                       | `fix/parser-error`              |
| `docs`      | Atualizações na documentação                           | `docs/grammar`                  |
| `style`     | Mudanças de estilo (semântica, formatação, etc)        | `style/code-format`             |
| `refactor`  | Refatorações (sem mudança de comportamento)            | `refactor/ast`                  |
| `test`      | Inclusão ou modificação de testes                      | `test/lexer-coverage`           |
| `chore`     | Tarefas de manutenção (ex: dependências, configs)      | `chore/update-dependencies`     |
| `hotfix`    | Correção urgente diretamente em produção               | `hotfix/critical-bug`           |

Fonte: Tabela elaborada pelo autor – Artur, 2025.

- **Commits:**  
    As mensagens de commit devem seguir um padrão similar ao das branches, mas utilizando o separador `:` em vez de `/`. Por exemplo:  
    - `docs: atualizar seção de padrões e convenções`  
    - `feat: adicionar endpoint de autenticação`  
    - `bugfix: corrigir erro de validação de formulário`

- **Labels Padrão:**  
  Para facilitar a organização e priorização das issues e pull requests, utilizamos as seguintes *labels*:
  - **documentation:** Indicada para questões e melhorias relacionadas à documentação.
  - **bug:** Utilizada para reportar erros ou problemas identificados no sistema.
  - **duplicate:** Para identificar issues que são cópias de outras já existentes.
  - **enhancement:** Sinaliza solicitações de melhorias ou novas funcionalidades.
  - **good first issue:** Para tarefas adequadas a colaboradores que estão iniciando.
  - **help wanted:** Indica que determinada tarefa necessita de colaboração ou apoio adicional.
  - **invalid:** Utilizada para issues que não se aplicam ou que foram identificadas como incorretas.
  - **question:** Para dúvidas ou solicitações de esclarecimento sobre algum aspecto do projeto.
  - **wontfix:** Indicada para issues que, por decisão da equipe, não serão corrigidas.
  - **ata:** Utilizada para issues relacionadas às atas de reuniões.
  - **ponto de controle:** Para issues relacionadas aos pontos de controle do projeto.
  - **inspeção:** Utilizada para issues que representam inspeções realizadas em artefatos.

## Gestão de Issues e Pull Requests

Para padronizar e organizar o fluxo de trabalho, estabelecemos diretrizes específicas para a criação e gestão de issues e pull requests:

### Criação de Issues

Todas as issues devem obrigatoriamente seguir o template fornecido no repositório, que pode ser encontrado em `.github/ISSUE_TEMPLATE/`. O uso do template garante a padronização e a inclusão de todas as informações necessárias. Uma issue completa deve conter:

1. **Título claro e descritivo**: Que indique o objetivo principal da issue.
2. **Descrição detalhada**: Contexto e informações necessárias para compreender o escopo da tarefa.
3. **Tarefas específicas**: Listadas em formato de checklist para acompanhamento do progresso.
4. **Labels apropriadas**: Que categorizem adequadamente o tipo de trabalho a ser realizado.
5. **Responsáveis designados**: Os membros da equipe que irão trabalhar na issue.
6. **Prazo de entrega**: Quando aplicável, a data limite para conclusão da tarefa.
7. **Pull Request vinculado**: Quando a issue for resolvida, deve ser vinculada ao PR correspondente.

### Hierarquia de Issues

Para facilitar a organização e o acompanhamento das atividades, implementamos um sistema de hierarquia de issues:

1. **Issues Mães (Parent Issues)**: 
   - Representam fases principais do compilador (lexer, parser, semântica, codegen)
   - São identificadas com a label `fase-compilador`.
   - Contêm links para todas as issues filhas relacionadas.
   - Exemplo: "Implementação do Analisador Léxico".

2. **Issues Filhas (Child Issues)**:
   - Representam tarefas específicas dentro de cada fase.
   - São vinculadas à issue mãe correspondente.
   - Exemplo: "Implementar reconhecimento de números".

3. **Issues de Atas**:
   - Para cada reunião, será criada uma issue específica para a ata.
   - As atas individuais serão vinculadas à issue mãe do ponto de controle correspondente.
   - Serão identificadas com a label `ata`.
   - Uma issue mãe de "Atas do Ponto de Controle X" conterá todas as atas individuais daquele período.

### Pull Requests (PRs)

Todos os pull requests devem seguir o template disponível em `.github/PULL_REQUEST_TEMPLATE.md`. Um PR adequado deve:

1. **Utilizar o template**: Preenchendo todos os campos relevantes.
2. **Vincular à issue correspondente**: Utilizando palavras-chave como "Closes #123" ou "Fixes #123".
3. **Descrever claramente as mudanças**: Explicando o que foi feito e por quê.
4. **Designar revisores**: Ao menos um membro da equipe deve revisar antes do merge.
5. **Incluir testes**: Quando aplicável, para demonstrar o funcionamento das alterações.
6. **Ter testes passando**: Se houver testes automatizados no projeto.

### Atas de Reunião vs. Inspeções

É importante diferenciar entre atas de reunião e inspeções:

- **Atas de Reunião**: 
  - Documentam as decisões, discussões e encaminhamentos das reuniões regulares da equipe.
  - São categorizadas com a label `ata`.
  - Seguem um formato padronizado que inclui data, participantes, pauta, decisões e próximos passos.

- **Inspeções**: 
  - **Não são atas**, mas sim avaliações técnicas de artefatos do compilador.
  - São categorizadas com a label `inspeção`.
  - Podem ser realizadas pelo próprio grupo ou por grupos externos.
  - Documentam a análise crítica de um artefato (lexer, parser, etc), identificando pontos fortes, deficiências e sugestões de melhoria.
  - Servem como base para ações corretivas e aprimoramento dos artefatos.

## Referências Bibliográficas

- Aho, A. V.; Lam, M. S.; Sethi, R.; Ullman, J. D. *Compilers: Principles, Techniques, and Tools*. 2nd Edition. Pearson, 2006.
- Appel, A. W. *Modern Compiler Implementation in C*. Cambridge University Press, 1998.
- Ierusalimschy, R. *Programming in Lua*. 4th Edition. Lua.org, 2016.
- Van Rossum, G.; Drake, F. L. *Python 3 Reference Manual*. Python Software Foundation, 2023.
- Schwaber, K.; Sutherland, J. *The Scrum Guide*. Disponível em: [https://www.scrumguides.org/](https://www.scrumguides.org/).
- GITHUB. *GitHub Docs – Collaborating with issues and pull requests*. Disponível em: [https://docs.github.com/en/issues](https://docs.github.com/en/issues).

## Histórico de Versões

| Versão | Descrição | Autor(es) | Data | Revisor(es) | Data de Revisão |
|--------|-----------|-----------|------|-------------|-----------------|
| 1.0 | Criação da documentação da metodologia | [Artur Mendonça](https://github.com/ArtyMend07) | 27/04/2025 | [Lucas Mendonça](https://github.com/lucasarruda9) | 27/04/2025 |
