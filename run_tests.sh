#!/bin/bash

echo "Executando testes do compilador Python para Lua..."
make > /dev/null 2>&1

for file in testes/*.txt; do
    echo "=========================="
    echo "Arquivo: $file"
    echo "--------------------------"
    ./pylua < "$file"
    echo ""
done

echo "Limpando arquivos temporários..."
make clean > /dev/null 2>&1 