# Ferramentas Utilizadas no Projeto PyLua

O projeto **PyLua** é um compilador que converte código **Python** em **Lua**. Durante o desenvolvimento, foram utilizadas diversas ferramentas e bibliotecas para facilitar o processo de construção do compilador, como analisadores léxicos e sintáticos. Abaixo, seguem as ferramentas utilizadas e suas funções no projeto.

### 1. **GCC (GNU Compiler Collection)**

- **Função:** Compilador C utilizado para compilar o código C gerado pelo **Flex** e **Bison**.

- **Uso no Projeto:** O GCC é utilizado para compilar os arquivos C que são gerados durante o processo de construção do compilador. Sem ele, a construção do projeto não seria possível.

- **Instalação:** Pode ser instalado diretamente pelo gerenciador de pacotes do sistema operacional. Exemplo para sistemas baseados em Debian (Ubuntu, etc.):
  ```bash
  sudo apt-get install build-essential

### 2. **FLEX**

- **Função:** Flex é um gerador de analisadores léxicos (scanners) utilizado para dividir o código Python em tokens, ou seja, em unidades léxicas como palavras-chave, operadores, identificadores, etc.

- **Uso no Projeto:** Flex é usado para construir o analisador léxico do compilador, o qual recebe o código Python e o divide em partes que podem ser mais facilmente analisadas no passo seguinte.

- **Instalação:** Flex pode ser instalado através do gerenciador de pacotes:
  ```bash
  sudo apt-get install flex

### 3. **BISON**

- **Função:** Bison é um gerador de analisadores sintáticos (parsers) que constrói uma árvore sintática a partir dos tokens gerados pelo Flex.

- **Uso no Projeto:** Bison é utilizado para interpretar a estrutura do código Python e convertê-lo em um formato que pode ser convertido em Lua. Ele ajuda a identificar a hierarquia das expressões e comandos Python.

- **Instalação:** Bison pode ser instalado com o seguinte comando:
  ```bash
  sudo apt-get install bison

### 4. **MAKE**

- **Função:** Make é uma ferramenta de automação que ajuda a compilar e construir o projeto de forma eficiente, gerenciando as dependências entre os arquivos e etapas de compilação.

- **Uso no Projeto:** Make é utilizado para compilar automaticamente o projeto. Com ele, basta rodar o comando **make** na raiz do projeto para compilar os arquivos C gerados pelo Flex e Bison e produzir o executável final.

- **Instalação:** Make pode ser instalado por meio do seguinte comando:
  ```bash
  sudo apt-get install make

### 5. **GIT** 

- **Função:** Git é um sistema de controle de versão amplamente utilizado para gerenciar o código-fonte e facilitar o trabalho em equipe.

- **Uso no Projeto:** Git é utilizado para versionar o código do compilador, registrar alterações e permitir a colaboração entre os desenvolvedores.

- **Instalação:** Para instalar o Git, use:
  ```bash
  sudo apt-get install git

### 6. **WHATSAPP**

- **Função:** WhatsApp é uma ferramenta de comunicação essencial para o desenvolvimento em equipe, facilitando a troca rápida de informações, discussões sobre o progresso do projeto e a colaboração entre os membros da equipe.

- **Uso no Projeto:** A equipe utiliza o WhatsApp para comunicação em tempo real, discussão sobre problemas técnicos e envio de materiais relevantes relacionados ao projeto.

- **Instalação:** O WhatsApp pode ser instalado em dispositivos móveis, ou na versão desktop para Windows ou macOS.

### 7. **VISUAL STUDIO CODE (VSCode)**

- **Função:** VSCode é um editor de código-fonte muito utilizado no desenvolvimento de software devido à sua leveza, extensões poderosas e suporte a múltiplas linguagens de programação.

- **Uso no Projeto:** A equipe utiliza o VSCode para editar e desenvolver os scripts do compilador em C, Python e para criar os arquivos de configuração como Makefile.

- **Instalação:** O Visual Studio Code pode ser instalado de diversas formas, incluindo via gerenciador de pacotes em sistemas Linux:
  ```bash
  sudo snap install --classic code

## Histórico de Versão

| Versão | Data | Descrição | Autor | Revisor |
|--------|------|-----------|--------|----------|
| 1.0 | 17/06/2025 | Criação e edição do documento do analisador sintático |  | [Artur Mendonça](https://github.com/ArtMendy07) |
| 2.0 | ajuste da documentação | [Lucas Mendonça](https://github.com/lucasarruda9) | 27/06/2025 | [Artur Mendonça](https://github.com/ArtyMend07) | 27/06/2025 |


