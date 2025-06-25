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
    echo "  clean-scripts         Remove scripts externos desnecessários"
    echo ""
    echo "OPÇÕES DE BUILD:"
    echo "  --release             Compila em modo release"
    echo "  --debug               Compila em modo debug (padrão)"
    echo "  --run                 Executa após compilar"
    echo ""
    echo "OPÇÕES DE TESTE:"
    echo "  --update-gabaritos    Atualiza gabaritos dos testes"
    echo "  --test [nome]         Executa teste específico"
    echo "  --completo            Testa todos os exemplos (test-generator)"
    echo "  --executar            Tenta executar códigos Lua gerados"
    echo "  --validar             Valida sintaxe dos códigos Lua"
    echo ""
    echo "EXEMPLOS:"
    echo "  ./pylua.sh init"
    echo "  ./pylua.sh build --release --run"
    echo "  ./pylua.sh test --test test3"
    echo "  ./pylua.sh test-generator"
    echo "  ./pylua.sh test-generator --completo"
    echo "  ./pylua.sh test-generator --completo --executar --validar"
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

# função interna pra teste básico do gerador
_teste_basico_gerador() {
    print_color $BLUE "=== Teste Básico do Gerador ==="

    mkdir -p saidas_lua temp

    local PASSOU=0
    local FALHOU=0
    local TOTAL=0

    # testa arquivo básico primeiro
    if [ -f "tests/teste_gerador.py" ]; then
        print_color $YELLOW "Testando arquivo básico..."
        echo "Conteúdo:"
        cat tests/teste_gerador.py
        echo ""

        ./pylua_debug tests/teste_gerador.py --gerar-lua saidas_lua/teste_basico.lua 2>/dev/null

        if [ -f "saidas_lua/teste_basico.lua" ] && [ -s "saidas_lua/teste_basico.lua" ]; then
            print_color $GREEN "[OK] Arquivo básico gerado"
            echo "Código Lua:"
            cat saidas_lua/teste_basico.lua
            echo ""
            PASSOU=$((PASSOU+1))
        else
            print_color $RED "[ERRO] Falha no arquivo básico"
            FALHOU=$((FALHOU+1))
        fi
        TOTAL=$((TOTAL+1))
        echo "---"
    fi

    # testa alguns exemplos principais
    for arquivo in exemplos/*.py; do
        if [ -f "$arquivo" ]; then
            nome=$(basename "$arquivo" .py)
            saida="saidas_lua/${nome}.lua"

            echo -n "Testando $nome... "
            ./pylua_debug "$arquivo" --gerar-lua "$saida" 2>/dev/null

            if [ -f "$saida" ] && [ -s "$saida" ]; then
                print_color $GREEN "OK"
                PASSOU=$((PASSOU+1))

                # mostra prévia
                echo "  Prévia:"
                head -3 "$saida" | sed 's/^/    /'
                if [ $(wc -l < "$saida") -gt 3 ]; then
                    echo "    ..."
                fi
            else
                print_color $RED "FALHOU"
                FALHOU=$((FALHOU+1))
            fi
            TOTAL=$((TOTAL+1))
            echo ""
        fi
    done

    print_color $BLUE "Resumo: $PASSOU/$TOTAL passaram"
    return $FALHOU
}

# função interna pra teste completo
_teste_completo_gerador() {
    print_color $PURPLE "=== TESTE COMPLETO DOS EXEMPLOS ==="

    # verifica se lua tá disponível
    local LUA_DISPONIVEL=false
    if command -v lua &> /dev/null; then
        LUA_DISPONIVEL=true
        print_color $CYAN "Lua encontrado! Testando execução também"
    else
        print_color $YELLOW "Lua não encontrado. Só testando geração"
    fi

    mkdir -p saidas_lua temp logs

    # arquivo de log
    local LOG_FILE="logs/teste_completo_$(date +%Y%m%d_%H%M%S).log"
    echo "Log de testes completos - $(date)" > "$LOG_FILE"

    local PASSOU_GER=0
    local FALHOU_GER=0
    local PASSOU_EXEC=0
    local FALHOU_EXEC=0
    local TOTAL=0

    # função interna pra testar um arquivo
    _testar_arquivo_completo() {
        local arquivo="$1"
        local nome=$(basename "$arquivo" .py)
        local saida="saidas_lua/${nome}.lua"

        echo "=== $nome ===" >> "$LOG_FILE"
        print_color $YELLOW "Testando $nome..."

        # mostra código python
        echo "  Python:"
        head -3 "$arquivo" | sed 's/^/    /'
        if [ $(wc -l < "$arquivo") -gt 3 ]; then
            echo "    ... ($(wc -l < "$arquivo") linhas)"
        fi

        # gera lua
        echo -n "  Gerando... "
        ./pylua_debug "$arquivo" --gerar-lua "$saida" 2>>"$LOG_FILE"

        if [ -f "$saida" ] && [ -s "$saida" ]; then
            print_color $GREEN "OK"
            PASSOU_GER=$((PASSOU_GER+1))

            echo "  Lua gerado:"
            head -3 "$saida" | sed 's/^/    /'
            if [ $(wc -l < "$saida") -gt 3 ]; then
                echo "    ... ($(wc -l < "$saida") linhas)"
            fi

            # testa se o codigo roda mesmo
            if $LUA_DISPONIVEL; then
                echo -n "  Executando... "
                # timeout de 5 segundos pra nao travar em loop infinito
                if timeout 5s lua "$saida" > temp/out_${nome}.txt 2>&1; then
                    print_color $GREEN "RODA"
                    PASSOU_EXEC=$((PASSOU_EXEC+1))
                elif [ $? -eq 124 ]; then
                    print_color $YELLOW "TIMEOUT"
                    FALHOU_EXEC=$((FALHOU_EXEC+1))
                    echo "    (provavelmente loop infinito ou algo assim)"
                else
                    print_color $RED "ERRO"
                    FALHOU_EXEC=$((FALHOU_EXEC+1))
                fi
            fi
        else
            print_color $RED "FALHOU"
            FALHOU_GER=$((FALHOU_GER+1))
        fi

        TOTAL=$((TOTAL+1))
        echo ""
    }

    # testa arquivo básico
    if [ -f "tests/teste_gerador.py" ]; then
        _testar_arquivo_completo "tests/teste_gerador.py"
    fi

    # testa todos os exemplos
    for arquivo in exemplos/*.py; do
        if [ -f "$arquivo" ]; then
            _testar_arquivo_completo "$arquivo"
        fi
    done

    # resumo final das parada
    print_color $PURPLE "=== RESUMO FINAL ==="
    print_color $BLUE "Total testado: $TOTAL"
    print_color $GREEN "Gerou código: $PASSOU_GER"
    print_color $RED "Não gerou código: $FALHOU_GER"

    if $LUA_DISPONIVEL; then
        print_color $GREEN "Executou: $PASSOU_EXEC"
        print_color $RED "Não executou: $FALHOU_EXEC"
    fi

    if [ $TOTAL -gt 0 ]; then
        local taxa_geracao=$(( 100 * PASSOU_GER / TOTAL ))
        print_color $BLUE "Taxa de geração: $taxa_geracao%"

        if $LUA_DISPONIVEL && [ $PASSOU_GER -gt 0 ]; then
            local taxa_execucao=$(( 100 * PASSOU_EXEC / PASSOU_GER ))
            print_color $BLUE "Taxa de execução: $taxa_execucao%"
        fi
    fi

    print_color $BLUE "Log salvo: $LOG_FILE"

    return $FALHOU_GER
}

#função pra validar sintaxe lua
_validar_lua() {
    print_color $BLUE "=== Validando Códigos Lua ==="

    if ! command -v lua &> /dev/null; then
        print_color $RED "Lua não encontrado!"
        print_color $YELLOW "Instale: sudo apt-get install lua5.3"
        return 1
    fi

    if [ ! -d "saidas_lua" ]; then
        print_color $RED "Pasta saidas_lua não encontrada!"
        return 1
    fi

    local VALIDOS=0
    local INVALIDOS=0
    local TOTAL=0

    for arquivo in saidas_lua/*.lua; do
        if [ -f "$arquivo" ]; then
            local nome=$(basename "$arquivo")
            echo -n "Validando $nome... "

            # tenta validar sintaxe com luac primeiro
            if command -v luac &> /dev/null; then
                if luac -p "$arquivo" 2>/dev/null; then
                    print_color $GREEN "OK"
                    VALIDOS=$((VALIDOS+1))
                else
                    print_color $RED "ERRO"
                    INVALIDOS=$((INVALIDOS+1))
                    echo "  Erro de sintaxe:"
                    luac -p "$arquivo" 2>&1 | head -2 | sed 's/^/    /'
                fi
            else
                # se não tem luac, tenta carregar o arquivo
                if lua -e "dofile('$arquivo')" 2>/dev/null; then
                    print_color $GREEN "OK"
                    VALIDOS=$((VALIDOS+1))
                else
                    print_color $RED "ERRO"
                    INVALIDOS=$((INVALIDOS+1))
                    echo "  Erro:"
                    lua -e "dofile('$arquivo')" 2>&1 | head -2 | sed 's/^/    /'
                fi
            fi
            TOTAL=$((TOTAL+1))
        fi
    done

    print_color $BLUE "Resumo: $VALIDOS válidos, $INVALIDOS inválidos"
    return $INVALIDOS
}

# função principal do teste do gerador
testar_gerador() {
    local modo="basico"
    local executar_lua=false
    local validar=false

    # processa argumentos
    while [[ $# -gt 0 ]]; do
        case $1 in
            --completo)
                modo="completo"
                shift
                ;;
            --executar)
                executar_lua=true
                shift
                ;;
            --validar)
                validar=true
                shift
                ;;
            *)
                shift
                ;;
        esac
    done

    print_color $BLUE "=== Testando Gerador de Código ==="

    # compila
    if [ ! -f "./pylua_debug" ]; then
        print_color $BLUE "Compilando..."
        make clean > /dev/null 2>&1
        make > /dev/null 2>&1

        if [ $? -ne 0 ]; then
            print_color $RED "Erro na compilação!"
            return 1
        fi
    fi

    local resultado=0

    # executa o teste apropriado
    if [ "$modo" = "completo" ]; then
        _teste_completo_gerador
        resultado=$?
    else
        _teste_basico_gerador
        resultado=$?
    fi

    # validação adicional
    if $validar; then
        echo ""
        _validar_lua
        local val_result=$?
        if [ $val_result -gt 0 ]; then
            resultado=$val_result
        fi
    fi

    # roda mais uns testes se o usuario pediu
    if $executar_lua && command -v lua &> /dev/null; then
        echo ""
        print_color $BLUE "=== Rodando Mais Uns Testes ==="
        for arquivo in saidas_lua/*.lua; do
            if [ -f "$arquivo" ]; then
                nome=$(basename "$arquivo")
                echo -n "Executando $nome... "
                # timeout de 5 segundos aqui tambem
                if timeout 5s lua "$arquivo" > /dev/null 2>&1; then
                    print_color $GREEN "OK"
                elif [ $? -eq 124 ]; then
                    print_color $YELLOW "TIMEOUT"
                    resultado=1
                else
                    print_color $RED "ERRO"
                    resultado=1
                fi
            fi
        done
    fi

    return $resultado
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
            shift
            testar_gerador "$@"
            ;;
        clean)
            print_color $BLUE "Limpando arquivos..."
            make clean
            print_color $GREEN "✓ Limpeza concluída"
            ;;
        clean-scripts)
            limpar_scripts_externos
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