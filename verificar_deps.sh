#!/bin/bash

# Script para verificar dependências do projeto PyLua

echo "Verificando dependências do projeto PyLua..."

# Lista de dependências necessárias
DEPS=("gcc" "flex" "bison" "make")
MISSING=()

# Verifica cada dependência
for dep in "${DEPS[@]}"; do
    echo -n "Verificando $dep... "
    if command -v $dep &> /dev/null; then
        echo "OK"
        # Verifica a versão
        case $dep in
            gcc)
                VERSION=$(gcc --version | head -n1 | grep -oP '\d+\.\d+\.\d+' | head -1)
                echo "  Versão: $VERSION"
                ;;
            flex)
                VERSION=$(flex --version | grep -oP '\d+\.\d+\.\d+' | head -1)
                echo "  Versão: $VERSION"
                ;;
            bison)
                VERSION=$(bison --version | grep -oP '\d+\.\d+(\.\d+)?' | head -1)
                echo "  Versão: $VERSION"
                ;;
            make)
                VERSION=$(make --version | grep -oP '\d+\.\d+(\.\d+)?' | head -1)
                echo "  Versão: $VERSION"
                ;;
        esac
    else
        echo "NÃO ENCONTRADO"
        MISSING+=("$dep")
    fi
done

# Verifica se há dependências faltando
if [ ${#MISSING[@]} -gt 0 ]; then
    echo -e "\nAs seguintes dependências estão faltando:"
    for dep in "${MISSING[@]}"; do
        echo "  - $dep"
    done
    echo -e "\nPor favor, instale as dependências faltantes e tente novamente."
    echo "Em sistemas baseados em Debian/Ubuntu, você pode usar:"
    echo "  sudo apt-get install gcc flex bison make"
    exit 1
else
    echo -e "\nTodas as dependências necessárias estão instaladas!"
    exit 0
fi