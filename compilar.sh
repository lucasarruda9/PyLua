#!/bin/bash

# Script para facilitar a compilação do projeto PyLua

# Verifica dependências primeiro
./verificar_deps.sh
if [ $? -ne 0 ]; then
    echo "Erro: Dependências faltando. Abortando compilação."
    exit 1
fi

# Processa argumentos
MODO="debug"
LIMPAR=false
EXECUTAR=false
TESTES=false

while [[ $# -gt 0 ]]; do
    case $1 in
        --release)
            MODO="release"
            shift
            ;;
        --debug)
            MODO="debug"
            shift
            ;;
        --limpar)
            LIMPAR=true
            shift
            ;;
        --executar)
            EXECUTAR=true
            shift
            ;;
        --testes)
            TESTES=true
            shift
            ;;
        *)
            echo "Opção desconhecida: $1"
            echo "Uso: ./compilar.sh [--release|--debug] [--limpar] [--executar] [--testes]"
            exit 1
            ;;
    esac
done

# Limpa os arquivos se solicitado
if $LIMPAR; then
    echo "Limpando arquivos anteriores..."
    make clean
fi

# Compila o projeto
echo "Compilando em modo $MODO..."
if [ "$MODO" = "release" ]; then
    make release
else
    make debug
fi

# Verifica se a compilação foi bem-sucedida
if [ $? -ne 0 ]; then
    echo "Erro durante a compilação. Abortando."
    exit 1
fi

echo "Compilação concluída com sucesso!"

# Executa o programa se solicitado
if $EXECUTAR; then
    echo "Executando o programa..."
    if [ "$MODO" = "release" ]; then
        ./pylua_release
    else
        ./pylua_debug
    fi
fi

# Executa os testes se solicitado
if $TESTES; then
    echo "Executando testes..."
    make test
fi

exit 0