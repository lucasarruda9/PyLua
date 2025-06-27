# Ata da Sprint 1 - Preparação e Análise Léxica

### Local
Reunião realizada presencialmente em sala de aula.

### Horário da Reunião

|          | Data       | Início| Término |
|----------|------------|-------|---------|
| Previsto | 24/03/2025 | 20:00 | 21:00   |
| Realizado| 04/04/2025 | 20:04 | 21:15   |

### Participantes presentes:
- [Artur Mendonça](https://github.com/ArtyMend07)
- [Gabriel Lopes](https://github.com/BrzGab)
- [Guilherme Meister](https://github.com/gmeister18)
- [Lucas Mendonça](https://github.com/lucasarruda9)
- [Matheus Ferreira](https://github.com/matferreira1)
- [Samuel Alves](https://github.com/samuelalvess)

### Pauta:
- Definir escopo do compilador.
- Discutir a configuração do ambiente de desenvolvimento.
- Revisar as tarefas da Sprint 1 e definir responsáveis.

### Decisões:
- O escopo do compilador foi definido para incluir apenas um subset da linguagem Python, com foco nos principais tokens.
- O repositório foi configurado corretamente, com todas as ferramentas necessárias instaladas.
- O analisador léxico (Scanner) foi a primeira tarefa a ser implementada.

### Próxima Reunião 
09/04/2025 às 20h

### Histórico de versão
Versão  | Data | Descrição | Autor(es) | Revisor(es) | Data da Revisão
-------- | ------ | -------- | ---------- | ----------- | ---------------
1.0 | 05/04/2025 | Ata da Sprint 1 | [Samuel Alves](https://github.com/samuelalvess) | [Artur Mendonça](https://github.com/ArtyMend07) | 05/04/2025

---

# Ata da Sprint 2 - Análise Sintática

### Local
Reunião realizada presencialmente em sala de aula.

### Horário da Reunião

|          | Data       | Início| Término |
|----------|------------|-------|---------|
| Previsto | 10/04/2025 | 20:00 | 21:00   |
| Realizado| 04/04/2025 | 20:04 | 21:15   |

### Participantes presentes:
- [Artur Mendonça](https://github.com/ArtyMend07)
- [Gabriel Lopes](https://github.com/BrzGab)
- [Guilherme Meister](https://github.com/gmeister18)
- [Lucas Mendonça](https://github.com/lucasarruda9)
- [Matheus Ferreira](https://github.com/matferreira1)
- [Samuel Alves](https://github.com/samuelalvess)

### Pauta:
- Definir a gramática do subset Python.
- Discutir a implementação do analisador sintático (Parser).
- Preparar a documentação para o ponto de controle (P1).

### Decisões:
- A gramática para o subset Python foi definida e um esboço inicial do parser foi desenvolvido.
- O sistema de erros sintáticos foi implementado, permitindo uma mensagem de erro clara durante a análise.
- A integração entre o módulo léxico e o sintático foi iniciada e deverá ser concluída até o final da sprint.

### Próxima Reunião 
09/04/2025 às 20h

### Histórico de versão
Versão  | Data | Descrição | Autor(es) | Revisor(es) | Data da Revisão
-------- | ------ | -------- | ---------- | ----------- | ---------------
1.0 | 05/04/2025 | Ata da Sprint 2 | [Samuel Alves](https://github.com/samuelalvess) | [Artur Mendonça](https://github.com/ArtyMend07) | 05/04/2025

---

# Ata da Sprint 3 - Representação Interna

### Local
Reunião realizada presencialmente em sala de aula.

### Horário da Reunião

|          | Data       | Início| Término |
|----------|------------|-------|---------|
| Previsto | 01/05/2025 | 20:00 | 21:00   |
| Realizado| 04/05/2025 | 20:04 | 21:15   |

### Participantes presentes:
- [Artur Mendonça](https://github.com/ArtyMend07)
- [Gabriel Lopes](https://github.com/BrzGab)
- [Guilherme Meister](https://github.com/gmeister18)
- [Lucas Mendonça](https://github.com/lucasarruda9)
- [Matheus Ferreira](https://github.com/matferreira1)
- [Samuel Alves](https://github.com/samuelalvess)

### Pauta:
- Definir estrutura da AST (Árvore de Sintaxe Abstrata).
- Implementar a Tabela de Símbolos.
- Integrar parser com AST.

### Decisões:
- A estrutura da AST foi definida, com classes para cada tipo de expressão.
- A tabela de símbolos foi implementada, com escopos para variáveis e funções.
- A integração entre o parser e a geração de AST foi iniciada, e a visualização da árvore será realizada na próxima reunião.

### Próxima Reunião 
15/05/2025 às 20h

### Histórico de versão
Versão  | Data | Descrição | Autor(es) | Revisor(es) | Data da Revisão
-------- | ------ | -------- | ---------- | ----------- | ---------------
1.0 | 05/05/2025 | Ata da Sprint 3 | [Samuel Alves](https://github.com/samuelalvess) | [Artur Mendonça](https://github.com/ArtyMend07) | 05/05/2025

---

# Ata da Sprint 4 - Análise Semântica e Geração de Código Intermediário

### Local
Reunião realizada presencialmente em sala de aula.

### Horário da Reunião

|          | Data       | Início| Término |
|----------|------------|-------|---------|
| Previsto | 15/05/2025 | 20:00 | 21:00   |
| Realizado| 15/05/2025 | 20:04 | 21:10   |

### Participantes presentes:
- [Artur Mendonça](https://github.com/ArtyMend07)
- [Gabriel Lopes](https://github.com/BrzGab)
- [Guilherme Meister](https://github.com/gmeister18)
- [Lucas Mendonça](https://github.com/lucasarruda9)
- [Matheus Ferreira](https://github.com/matferreira1)
- [Samuel Alves](https://github.com/samuelalvess)

### Pauta:
- Implementar a verificação semântica.
- Definir o sistema de verificação de tipos e escopos.
- Iniciar o desenvolvimento do código intermediário.

### Decisões:
- O sistema de verificação de tipos foi iniciado com foco nas variáveis e expressões aritméticas.
- A verificação de escopo foi iniciada, com controle de variáveis globais e locais.
- A implementação do código intermediário começou, com a definição de estruturas para armazenar o código de saída.

### Próxima Reunião 
02/06/2025 às 20h

### Histórico de versão
Versão  | Data | Descrição | Autor(es) | Revisor(es) | Data da Revisão
-------- | ------ | -------- | ---------- | ----------- | ---------------
1.0 | 20/05/2025 | Ata da Sprint 4 | [Samuel Alves](https://github.com/samuelalvess) | [Artur Mendonça](https://github.com/ArtyMend07) | 20/05/2025

---

# Ata da Sprint 5 - Geração de Código Lua

### Local
Reunião realizada presencialmente em sala de aula.

### Horário da Reunião

|          | Data       | Início| Término |
|----------|------------|-------|---------|
| Previsto | 05/06/2025 | 20:00 | 21:00   |
| Realizado| 05/06/2025 | 20:04 | 21:12   |

### Participantes presentes:
- [Artur Mendonça](https://github.com/ArtyMend07)
- [Gabriel Lopes](https://github.com/BrzGab)
- [Guilherme Meister](https://github.com/gmeister18)
- [Lucas Mendonça](https://github.com/lucasarruda9)
- [Matheus Ferreira](https://github.com/matferreira1)
- [Samuel Alves](https://github.com/samuelalvess)

### Pauta:
- Implementar o mapeamento Python-Lua.
- Desenvolver o gerador de código Lua.
- Iniciar a implementação de uma biblioteca de runtime.

### Decisões:
- O mapeamento entre as funcionalidades Python e Lua foi concluído para as estruturas básicas.
- O gerador de código Lua foi iniciado, com foco em expressões aritméticas e estruturas de controle.
- A biblioteca de runtime começou a ser implementada, com funções auxiliares para execução do código gerado.

### Próxima Reunião 
18/06/2025 às 20h

### Histórico de versão
Versão  | Data | Descrição | Autor(es) | Revisor(es) | Data da Revisão
-------- | ------ | -------- | ---------- | ----------- | ---------------
1.0 | 10/06/2025 | Ata da Sprint 5 | [Samuel Alves](https://github.com/samuelalvess) | [Artur Mendonça](https://github.com/ArtyMend07) | 10/06/2025

---

# Ata da Sprint 6 - Refinamento e Testes

### Local
Reunião realizada presencialmente em sala de aula.

### Horário da Reunião

|          | Data       | Início| Término |
|----------|------------|-------|---------|
| Previsto | 19/06/2025 | 20:00 | 21:00   |
| Realizado| 19/06/2025 | 20:05 | 21:20   |

### Participantes presentes:
- [Artur Mendonça](https://github.com/ArtyMend07)
- [Gabriel Lopes](https://github.com/BrzGab)
- [Guilherme Meister](https://github.com/gmeister18)
- [Lucas Mendonça](https://github.com/lucasarruda9)
- [Matheus Ferreira](https://github.com/matferreira1)
- [Samuel Alves](https://github.com/samuelalvess)

### Pauta:
- Refinar as mensagens de erro do compilador.
- Realizar testes avançados com programas mais complexos.
- Implementar otimizações no código gerado.

### Decisões:
- Melhorias nas mensagens de erro foram realizadas, com mensagens mais claras e específicas para diferentes tipos de erro.
- Testes avançados começaram, focando em cenários mais complexos e programas maiores.
- As otimizações iniciais foram aplicadas, com foco em loops e chamadas de funções.

### Próxima Reunião 
27/06/2025 às 20h

### Histórico de versão
Versão  | Data | Descrição | Autor(es) | Revisor(es) | Data da Revisão
-------- | ------ | -------- | ---------- | ----------- | ---------------
1.0 | 20/06/2025 | Ata da Sprint 6 | [Samuel Alves](https://github.com/samuelalvess) | [Artur Mendonça](https://github.com/ArtyMend07) | 20/06/2025

---

# Ata da Sprint 7 - Apresentação e Fechamento

### Local
Reunião realizada presencialmente em sala de aula.

### Horário da Reunião

|          | Data       | Início| Término |
|----------|------------|-------|---------|
| Previsto | 28/06/2025 | 20:00 | 21:00   |
| Realizado| 28/06/2025 | 20:05 | 21:30   |

### Participantes presentes:
- [Artur Mendonça](https://github.com/ArtyMend07)
- [Gabriel Lopes](https://github.com/BrzGab)
- [Guilherme Meister](https://github.com/gmeister18)
- [Lucas Mendonça](https://github.com/lucasarruda9)
- [Matheus Ferreira](https://github.com/matferreira1)
- [Samuel Alves](https://github.com/samuelalvess)

### Pauta:
- Revisar o código final.
- Preparar os slides para a apresentação.
- Finalizar a documentação do projeto.

### Decisões:
- O código final foi revisado, com pequenos ajustes realizados para garantir a execução correta.
- Os slides da apresentação foram criados e serão apresentados ao professor nas próximas datas.
- A documentação final está em andamento e será concluída até a data da entrega.

### Histórico de versão
Versão  | Data | Descrição | Autor(es) | Revisor(es) | Data da Revisão
-------- | ------ | -------- | ---------- | ----------- | ---------------
1.0 | 02/07/2025 | Ata da Sprint 7 | [Samuel Alves](https://github.com/samuelalvess) | [Artur Mendonça](https://github.com/ArtyMend07) | 02/07/2025

---

Essas são as atas de todas as sprints em formato Markdown. Se precisar de mais ajustes ou adições, estou à disposição!
