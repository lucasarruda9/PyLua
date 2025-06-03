#!/bin/bash

echo "=== Testando o Gerador de Código Lua ==="

# Cria diretórios necessários
mkdir -p saidas_lua exemplos tests

# Compila o projeto
echo "Compilando o projeto..."
make clean > /dev/null 2>&1
make > /dev/null 2>&1

if [ $? -ne 0 ]; then
    echo "Erro na compilação!"
    exit 1
fi

echo "Compilação bem-sucedida!"

# Testa o gerador com arquivo de entrada
echo ""
echo "=== Teste 1: Gerando código Lua para arquivo de teste ==="
echo "Conteúdo do arquivo de teste:"
cat tests/teste_gerador.py
echo ""

echo "Executando: ./pylua_debug tests/teste_gerador.py --gerar-lua teste_basico.lua"
./pylua_debug tests/teste_gerador.py --gerar-lua teste_basico.lua

if [ -f saidas_lua/teste_basico.lua ]; then
    echo ""
    echo "Código Lua gerado (saidas_lua/teste_basico.lua):"
    cat saidas_lua/teste_basico.lua
else
    echo "Arquivo saidas_lua/teste_basico.lua não foi criado!"
fi

# Testa o gerador com exemplo completo
echo ""
echo "=== Teste 2: Gerando código para exemplo completo ==="
if [ -f exemplos/exemplo_completo.py ]; then
    echo "Conteúdo do exemplo completo:"
    cat exemplos/exemplo_completo.py
    echo ""

    echo "Executando: ./pylua_debug exemplos/exemplo_completo.py --gerar-lua exemplo_completo.lua"
    ./pylua_debug exemplos/exemplo_completo.py --gerar-lua exemplo_completo.lua

    if [ -f saidas_lua/exemplo_completo.lua ]; then
        echo ""
        echo "Código Lua gerado (saidas_lua/exemplo_completo.lua):"
        cat saidas_lua/exemplo_completo.lua
    fi
else
    echo "Arquivo exemplos/exemplo_completo.py não encontrado!"
fi

# Testa o gerador com entrada interativa
echo ""
echo "=== Teste 3: Geração de código para expressões simples ==="
echo "Testando expressões: x = 5, y = x + 3"
echo -e "x = 5\ny = x + 3\n" | ./pylua_debug --gerar-lua

# Lista arquivos gerados
echo ""
echo "=== Arquivos Lua gerados ==="
if [ -d saidas_lua ]; then
    ls -la saidas_lua/
else
    echo "Diretório saidas_lua não encontrado!"
fi

echo ""
echo "=== Fim dos testes ==="
