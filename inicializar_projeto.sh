#!/bin/bash

echo "=== Inicializando Projeto PyLua ==="

# Cores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Função para imprimir com cor
print_color() {
    echo -e "${1}${2}${NC}"
}

# Verifica dependências
print_color $BLUE "1. Verificando dependências..."
./verificar_deps.sh
if [ $? -ne 0 ]; then
    print_color $RED "Erro: Dependências não atendidas!"
    exit 1
fi
print_color $GREEN "✓ Dependências verificadas"

# Cria estrutura de diretórios
print_color $BLUE "2. Criando estrutura de diretórios..."
mkdir -p exemplos saidas_lua tests docs/gerados build temp
print_color $GREEN "✓ Diretórios criados"

# Compila o projeto
print_color $BLUE "3. Compilando o projeto..."
make clean > /dev/null 2>&1
make > /dev/null 2>&1
if [ $? -ne 0 ]; then
    print_color $RED "Erro na compilação!"
    exit 1
fi
print_color $GREEN "✓ Projeto compilado com sucesso"

# Gera exemplos Lua
print_color $BLUE "4. Gerando exemplos de código Lua..."
make gerar_exemplos > /dev/null 2>&1
print_color $GREEN "✓ Exemplos gerados"

# Lista arquivos gerados
print_color $BLUE "5. Arquivos Lua gerados:"
if [ -d saidas_lua ] && [ "$(ls -A saidas_lua)" ]; then
    ls -la saidas_lua/
else
    print_color $YELLOW "Nenhum arquivo Lua encontrado em saidas_lua/"
fi

# Executa testes básicos
print_color $BLUE "6. Executando testes básicos..."
make test_gerador > /dev/null 2>&1
if [ $? -eq 0 ]; then
    print_color $GREEN "✓ Testes básicos passaram"
else
    print_color $YELLOW "⚠ Alguns testes podem ter falhado"
fi

# Mostra comandos úteis
print_color $BLUE "7. Comandos úteis:"
echo "   make                    # Compilar o projeto"
echo "   make test_gerador       # Testar gerador de código"
echo "   make gerar_exemplos     # Gerar todos os exemplos"
echo "   make clean              # Limpar arquivos gerados"
echo "   ./pylua_debug --help    # Ajuda do compilador"
echo ""
echo "   Exemplo de uso:"
echo "   ./pylua_debug exemplos/operacoes_basicas.py --gerar-lua teste.lua"

print_color $GREEN "=== Projeto PyLua inicializado com sucesso! ==="
print_color $BLUE "Consulte docs/organizacao_projeto.md para mais informações."
