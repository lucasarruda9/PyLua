#!/bin/bash

# Compila o projeto
make > /dev/null 2>&1

echo "Executando testes automatizados do compilador PyLua..."

test_only=""
update_gabaritos=false

# Opções de linha de comando
while [[ $# -gt 0 ]]; do
    case $1 in
        --update-gabaritos)
            update_gabaritos=true
            shift
            ;;
        --test)
            test_only="$2"
            shift 2
            ;;
        *)
            shift
            ;;
    esac
done

TEST_DIR="tests/parser"
EXPECTED_DIR="tests/expected_outputs"
PASS=0
FAIL=0
TOTAL=0
FAILED_TESTS=()

for file in $TEST_DIR/*.txt; do
    base=$(basename "$file" .txt)
    if [[ -n "$test_only" && "$base" != "$test_only" ]]; then
        continue
    fi
    expected="$EXPECTED_DIR/${base}.txt"
    output="tmp_${base}_output.txt"
    ./pylua_debug < "$file" > "$output"
    if $update_gabaritos || [ ! -f "$expected" ]; then
        cp "$output" "$expected"
        echo "[GABARITO] $base gerado/atualizado."
    else
        if diff -q "$output" "$expected" > /dev/null; then
            echo "[PASS] $base"
            PASS=$((PASS+1))
        else
            echo "[FAIL] $base"
            echo "Diferenças:" 
            diff "$output" "$expected"
            FAIL=$((FAIL+1))
            FAILED_TESTS+=("$base")
        fi
    fi
    rm -f "$output"
    TOTAL=$((TOTAL+1))
done

if ! $update_gabaritos; then
    echo "Resumo: $PASS passaram, $FAIL falharam, $TOTAL total."
    if [ $TOTAL -gt 0 ]; then
        percent=$(( 100 * PASS / TOTAL ))
        echo "Porcentagem de acertos: $percent%"
    fi
    if [ $FAIL -gt 0 ]; then
        echo "Testes que falharam: ${FAILED_TESTS[*]}"
        exit 1
    fi
fi

# Limpa arquivos temporários e build
make clean > /dev/null 2>&1