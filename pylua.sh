#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

print_color() {
    echo -e "${1}${2}${NC}"
}

mostrar_ajuda() {
    echo "PyLua - Compilador Python para Lua"
    echo ""
    echo "Uso: ./pylua.sh [COMANDO] [OPÇÕES]"
    echo ""
    echo "COMANDOS:"
    echo "  init                  Inicializa o projeto"
    echo "  deps                  Verifica dependências"
    echo "  build                 Compila o projeto"
    echo "  test                  Executa testes do parser"
    echo "  test-generator        Testa o gerador de código"
    echo "  clean                 Limpa arquivos gerados"
    echo ""
    echo "OPÇÕES DE BUILD:"
    echo "  --release             Compila em modo release"
    echo "  --debug               Compila em modo debug (padrão)"
    echo "  --run                 Executa após compilar"
    echo ""
    echo "OPÇÕES DE TESTE:"
    echo "  --update-gabaritos    Atualiza gabaritos dos testes"
    echo "  --test [nome]         Executa teste específico"
    echo ""
    echo "EXEMPLOS:"
    echo "  ./pylua.sh init"
    echo "  ./pylua.sh build --release --run"
    echo "  ./pylua.sh test --test test3"
    echo "  ./pylua.sh test-generator"
}

verificar_deps() {
    print_color $BLUE "Verificando dependências..."
    
    DEPS=("gcc" "flex" "bison" "make")
    FALTANDO=()
    
    for dep in "${DEPS[@]}"; do
        echo -n "Verificando $dep... "
        if command -v $dep &> /dev/null; then
            echo "OK"
        else
            echo "NÃO ENCONTRADO"
            FALTANDO+=("$dep")
        fi
    done
    
    if [ ${#FALTANDO[@]} -gt 0 ]; then
        print_color $RED "Dependências faltando:"
        for dep in "${FALTANDO[@]}"; do
            echo "  - $dep"
        done
        print_color $YELLOW "Para instalar: sudo apt-get install gcc flex bison make"
        return 1
    else
        print_color $GREEN "✓ Todas as dependências instaladas!"
        return 0
    fi
}

compilar_projeto() {
    local modo="debug"
    local limpar_antes=false
    local executar_depois=false
    
    while [[ $# -gt 0 ]]; do
        case $1 in
            --release)
                modo="release"
                shift
                ;;
            --debug)
                modo="debug"
                shift
                ;;
            --clean)
                limpar_antes=true
                shift
                ;;
            --run)
                executar_depois=true
                shift
                ;;
            *)
                shift
                ;;
        esac
    done
    
    verificar_deps
    if [ $? -ne 0 ]; then
        print_color $RED "Erro: Dependências faltando."
        return 1
    fi
    
    if $limpar_antes; then
        print_color $BLUE "Limpando arquivos anteriores..."
        make clean
    fi
    
    print_color $BLUE "Compilando em modo $modo..."
    if [ "$modo" = "release" ]; then
        make release
    else
        make debug
    fi
    
    if [ $? -ne 0 ]; then
        print_color $RED "Erro durante compilação."
        return 1
    fi
    
    print_color $GREEN "✓ Compilação concluída!"
    
    if $executar_depois; then
        print_color $BLUE "Executando programa..."
        if [ "$modo" = "release" ]; then
            ./pylua_release
        else
            ./pylua_debug
        fi
    fi
}

inicializar_projeto() {
    print_color $BLUE "=== Inicializando Projeto PyLua ==="
    
    print_color $BLUE "1. Verificando dependências..."
    verificar_deps
    if [ $? -ne 0 ]; then
        return 1
    fi
    
    print_color $BLUE "2. Criando diretórios..."
    mkdir -p exemplos saidas_lua tests docs/gerados build temp
    print_color $GREEN "✓ Diretórios criados"
    
    print_color $BLUE "3. Compilando projeto..."
    make clean > /dev/null 2>&1
    make > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        print_color $RED "Erro na compilação!"
        return 1
    fi
    print_color $GREEN "✓ Projeto compilado"
    
    print_color $BLUE "4. Gerando exemplos..."
    make gerar_exemplos > /dev/null 2>&1
    print_color $GREEN "✓ Exemplos gerados"
    
    print_color $BLUE "5. Executando testes básicos..."
    make test_gerador > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        print_color $GREEN "✓ Testes passaram"
    else
        print_color $YELLOW "⚠ Alguns testes falharam"
    fi
    
    print_color $GREEN "=== Projeto inicializado com sucesso! ==="
}

executar_testes() {
    local teste_especifico=""
    local atualizar_gabaritos=false
    
    while [[ $# -gt 0 ]]; do
        case $1 in
            --update-gabaritos)
                atualizar_gabaritos=true
                shift
                ;;
            --test)
                teste_especifico="$2"
                shift 2
                ;;
            *)
                shift
                ;;
        esac
    done
    
    make > /dev/null 2>&1
    
    print_color $BLUE "Executando testes..."
    
    DIR_TESTES="tests/parser"
    DIR_ESPERADOS="tests/expected_outputs"
    PASSOU=0
    FALHOU=0
    TOTAL=0
    TESTES_FALHOS=()
    
    for arquivo in $DIR_TESTES/*.txt; do
        base=$(basename "$arquivo" .txt)
        if [[ -n "$teste_especifico" && "$base" != "$teste_especifico" ]]; then
            continue
        fi
        esperado="$DIR_ESPERADOS/${base}.txt"
        saida="tmp_${base}_output.txt"
        ./pylua_debug < "$arquivo" > "$saida"
        if $atualizar_gabaritos || [ ! -f "$esperado" ]; then
            cp "$saida" "$esperado"
            print_color $YELLOW "[GABARITO] $base atualizado."
        else
            if diff -q "$saida" "$esperado" > /dev/null; then
                print_color $GREEN "[PASSOU] $base"
                PASSOU=$((PASSOU+1))
            else
                print_color $RED "[FALHOU] $base"
                diff "$saida" "$esperado"
                FALHOU=$((FALHOU+1))
                TESTES_FALHOS+=("$base")
            fi
        fi
        rm -f "$saida"
        TOTAL=$((TOTAL+1))
    done
    
    if ! $atualizar_gabaritos; then
        print_color $BLUE "Resumo: $PASSOU passaram, $FALHOU falharam, $TOTAL total."
        if [ $TOTAL -gt 0 ]; then
            porcentagem=$(( 100 * PASSOU / TOTAL ))
            print_color $BLUE "Porcentagem: $porcentagem%"
        fi
        if [ $FALHOU -gt 0 ]; then
            print_color $RED "Testes que falharam: ${TESTES_FALHOS[*]}"
            return 1
        fi
    fi
    
    make clean > /dev/null 2>&1
}

testar_gerador() {
    print_color $BLUE "=== Testando Gerador de Código ==="
    
    mkdir -p saidas_lua exemplos tests
    
    print_color $BLUE "Compilando..."
    make clean > /dev/null 2>&1
    make > /dev/null 2>&1
    
    if [ $? -ne 0 ]; then
        print_color $RED "Erro na compilação!"
        return 1
    fi
    
    print_color $GREEN "✓ Compilado com sucesso!"
    
    if [ -f tests/teste_gerador.py ]; then
        print_color $BLUE "=== Teste 1: Arquivo básico ==="
        echo "Conteúdo:"
        cat tests/teste_gerador.py
        echo ""
        
        ./pylua_debug tests/teste_gerador.py --gerar-lua teste_basico.lua
        
        if [ -f saidas_lua/teste_basico.lua ]; then
            print_color $GREEN "Código gerado:"
            cat saidas_lua/teste_basico.lua
        fi
    fi
    
    if [ -f exemplos/exemplo_completo.py ]; then
        print_color $BLUE "=== Teste 2: Exemplo completo ==="
        ./pylua_debug exemplos/exemplo_completo.py --gerar-lua exemplo_completo.lua
        
        if [ -f saidas_lua/exemplo_completo.lua ]; then
            print_color $GREEN "Código gerado:"
            cat saidas_lua/exemplo_completo.lua
        fi
    fi
    
    print_color $BLUE "=== Arquivos gerados ==="
    if [ -d saidas_lua ]; then
        ls -la saidas_lua/
    fi
    
    print_color $GREEN "=== Testes concluídos ==="
}

main() {
    if [ $# -eq 0 ]; then
        mostrar_ajuda
        exit 0
    fi
    
    case "$1" in
        init)
            inicializar_projeto
            ;;
        deps)
            verificar_deps
            ;;
        build)
            shift
            compilar_projeto "$@"
            ;;
        test)
            shift
            executar_testes "$@"
            ;;
        test-generator)
            testar_gerador
            ;;
        clean)
            print_color $BLUE "Limpando arquivos..."
            make clean
            print_color $GREEN "✓ Limpeza concluída"
            ;;
        help|--help|-h)
            mostrar_ajuda
            ;;
        *)
            print_color $RED "Comando desconhecido: $1"
            echo ""
            mostrar_ajuda
            exit 1
            ;;
    esac
}

main "$@"