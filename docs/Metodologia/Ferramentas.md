# Ferramentas Utilizadas no Projeto PyLua

O projeto **PyLua** é um compilador que converte código **Python** em **Lua**. Durante o desenvolvimento, foram utilizadas diversas ferramentas e bibliotecas para facilitar o processo de construção do compilador, como analisadores léxicos e sintáticos. Abaixo, seguem as ferramentas utilizadas e suas funções no projeto.

## 1. **GCC (GNU Compiler Collection)**

- **Função:** Compilador C utilizado para compilar o código C gerado pelo **Flex** e **Bison**.
- **Uso no Projeto:** O GCC é utilizado para compilar os arquivos C que são gerados durante o processo de construção do compilador. Sem ele, a construção do projeto não seria possível.
- **Instalação:** Pode ser instalado diretamente pelo gerenciador de pacotes do sistema operacional. Exemplo para sistemas baseados em Debian (Ubuntu, etc.):
  ```bash
  sudo apt-get install build-essential
