#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
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
    echo "  test-generator        Testa o gerador de código"
    echo "  clean                 Limpa arquivos gerados"
    echo ""
    echo "OPÇÕES DE BUILD:"
    echo "  --release             Compila em modo release"
    echo "  --debug               Compila em modo debug (padrão)"
    echo "  --run                 Executa após compilar"
    echo ""
    echo "OPÇÕES DE TESTE DO GERADOR:"
    echo "  --completo            Testa todos os exemplos (test-generator)"
    echo "  --executar            Tenta executar códigos Lua gerados"
    echo "  --validar             Valida códigos comparando com gabaritos"
    echo "  --otimizar            Aplica otimizações nos códigos Lua gerados"
    echo ""
    echo "EXEMPLOS:"
    echo "  ./pylua.sh init"
    echo "  ./pylua.sh build --release --run"
    echo "  ./pylua.sh test-generator"
    echo "  ./pylua.sh test-generator --completo"
    echo "  ./pylua.sh test-generator --completo --executar --validar"
    echo "  ./pylua.sh test-generator --completo --otimizar --validar"
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
    mkdir -p exemplos saidas_lua docs/gerados build temp
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



# função interna pra teste básico do gerador
_teste_basico_gerador() {
    print_color $BLUE "=== Teste Básico do Gerador ==="

    mkdir -p saidas_lua temp

    local PASSOU=0
    local FALHOU=0
    local TOTAL=0



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

                # mostra prévia (3 primeiras linhas)
                echo "  Prévia:"
                head -3 "$saida" | sed 's/^/    /'
                [ $(wc -l < "$saida") -gt 3 ] && echo "    ..."
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

    # arquivo de log para erros
    local DATA_LOG=$(date +"%d_%m_%Y_%H%M%S")
    local LOG_FILE="logs/teste_completo_${DATA_LOG}.log"
    echo "Log de testes completos - $(date '+%d/%m/%Y às %H:%M:%S')" > "$LOG_FILE"

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
        [ $(wc -l < "$arquivo") -gt 3 ] && echo "    ... ($(wc -l < "$arquivo") linhas)"

        # gera lua
        echo -n "  Gerando... "
        ./pylua_debug "$arquivo" --gerar-lua "$saida" 2>>"$LOG_FILE"

        if [ -f "$saida" ] && [ -s "$saida" ]; then
            print_color $GREEN "OK"
            PASSOU_GER=$((PASSOU_GER+1))

            echo "  Lua gerado:"
            head -3 "$saida" | sed 's/^/    /'
            [ $(wc -l < "$saida") -gt 3 ] && echo "    ... ($(wc -l < "$saida") linhas)"

            # testa execução
            if $LUA_DISPONIVEL; then
                echo -n "  Executando... "
                # timeout de 5 segundos
                if timeout 5s lua "$saida" > temp/out_${nome}.txt 2>&1; then
                    print_color $GREEN "RODA"
                    PASSOU_EXEC=$((PASSOU_EXEC+1))
                elif [ $? -eq 124 ]; then
                    print_color $YELLOW "TIMEOUT"
                    FALHOU_EXEC=$((FALHOU_EXEC+1))
                    echo "    (timeout - possível loop infinito)"
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

    # testa todos os exemplos
    for arquivo in exemplos/*.py; do
        if [ -f "$arquivo" ]; then
            _testar_arquivo_completo "$arquivo"
        fi
    done

    # resumo final
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

    print_color $BLUE "Log salvo em: $LOG_FILE"

    return $FALHOU_GER
}

# função para otimizar códigos Lua já gerados
_otimizar_lua() {
    print_color $BLUE "=== Otimizando Códigos Lua ==="

    if [ ! -d "saidas_lua" ]; then
        print_color $RED "Pasta saidas_lua não encontrada! Execute a geração primeiro."
        return 1
    fi

    # cria pasta de logs se não existir
    mkdir -p logs saidas_tac

    # arquivo de log para otimizações
    local DATA_LOG=$(date +"%d_%m_%Y_%H%M%S")
    local LOG_FILE="logs/otimizacao_${DATA_LOG}.log"
    echo "Log de otimizações - $(date '+%d/%m/%Y às %H:%M:%S')" > "$LOG_FILE"

    local OTIMIZADOS=0
    local FALHAS=0
    local TOTAL=0

    # otimiza arquivos Lua já existentes
    for arquivo_lua in saidas_lua/*.lua; do
        if [ -f "$arquivo_lua" ]; then
            local nome=$(basename "$arquivo_lua" .lua)
            local arquivo_py="exemplos/${nome}.py"
            local arquivo_tac="saidas_tac/${nome}.tac"

            echo -n "Otimizando $nome... "

            # verifica se existe arquivo Python correspondente
            if [ ! -f "$arquivo_py" ]; then
                print_color $YELLOW "PULADO (sem .py)"
                continue
            fi

            # salva versão original para comparação
            local arquivo_original_temp="/tmp/${nome}_original.lua"
            cp "$arquivo_lua" "$arquivo_original_temp"

            # gera TAC primeiro (para log)
            ./pylua_debug "$arquivo_py" --gerar-tac "$arquivo_tac" 2>>"$LOG_FILE"

            # regera o arquivo Lua com otimizações (substitui o original)
            ./pylua_debug "$arquivo_py" --gerar-lua-otimizado "$arquivo_lua" 2>>"$LOG_FILE"

            if [ -f "$arquivo_lua" ] && [ -s "$arquivo_lua" ]; then
                print_color $GREEN "OK"
                OTIMIZADOS=$((OTIMIZADOS+1))

                # mostra estatísticas de otimização
                local linhas_original=$(wc -l < "$arquivo_original_temp")
                local linhas_otimizado=$(wc -l < "$arquivo_lua")
                local reducao=$((linhas_original - linhas_otimizado))

                if [ $reducao -gt 0 ]; then
                    echo "    Redução: $reducao linhas ($linhas_original → $linhas_otimizado)"
                elif [ $reducao -lt 0 ]; then
                    echo "    Expansão: $((-reducao)) linhas ($linhas_original → $linhas_otimizado)"
                else
                    echo "    Otimizações aplicadas ($linhas_original linhas)"
                fi

                echo "=== $nome ===" >> "$LOG_FILE"
                echo "Original: $linhas_original linhas" >> "$LOG_FILE"
                echo "Otimizado: $linhas_otimizado linhas" >> "$LOG_FILE"
                echo "Diferença: $reducao linhas" >> "$LOG_FILE"
                echo "" >> "$LOG_FILE"

                rm -f "$arquivo_original_temp"
            else
                print_color $RED "FALHOU"
                FALHAS=$((FALHAS+1))
                echo "Erro na otimização de $nome" >> "$LOG_FILE"
                # restaura arquivo original se falhou
                if [ -f "$arquivo_original_temp" ]; then
                    cp "$arquivo_original_temp" "$arquivo_lua"
                    rm -f "$arquivo_original_temp"
                fi
            fi
            TOTAL=$((TOTAL+1))
        fi
    done

    echo ""
    print_color $BLUE "Resumo da otimização:"
    print_color $GREEN "Otimizados: $OTIMIZADOS"
    print_color $RED "Falhas: $FALHAS"
    print_color $BLUE "Total: $TOTAL"

    if [ $TOTAL -gt 0 ]; then
        local taxa=$(( 100 * OTIMIZADOS / TOTAL ))
        print_color $BLUE "Taxa de sucesso: $taxa%"
    fi

    print_color $BLUE "Log salvo em: $LOG_FILE"

    return $FALHAS
}

# função pra validar comparando com gabaritos (sem usar luac)
_validar_lua() {
    print_color $BLUE "=== Validando Códigos Lua (comparação de texto) ==="

    if [ ! -d "saidas_lua" ]; then
        print_color $RED "Pasta saidas_lua não encontrada!"
        return 1
    fi

    # cria pasta de gabaritos se não existir
    mkdir -p exemplos_gabaritos

    local PASSOU=0
    local FALHOU=0
    local ATUALIZADOS=0
    local TOTAL=0

    for arquivo in saidas_lua/*.lua; do
        if [ -f "$arquivo" ]; then
            local nome=$(basename "$arquivo" .lua)  # remove .lua
            local gabarito="exemplos_gabaritos/${nome}.txt"  # gabarito é .txt

            echo -n "Validando $nome... "

            # verifica se tem gabarito
            if [ ! -f "$gabarito" ]; then
                print_color $YELLOW "SEM GABARITO"
                echo "  Crie o arquivo: $gabarito"
                ATUALIZADOS=$((ATUALIZADOS+1))
            else
                # compara arquivo .lua com gabarito .txt
                if diff -q "$arquivo" "$gabarito" > /dev/null 2>&1; then
                    print_color $GREEN "OK"
                    PASSOU=$((PASSOU+1))
                else
                    print_color $RED "DIFERENTE"
                    FALHOU=$((FALHOU+1))
                    echo "  Diferenças encontradas:"
                    diff "$gabarito" "$arquivo" | head -3 | sed 's/^/    /'
                fi
            fi
            TOTAL=$((TOTAL+1))
        fi
    done

    echo ""
    print_color $BLUE "Resumo da validação:"
    if [ $ATUALIZADOS -gt 0 ]; then
        print_color $YELLOW "Sem gabarito: $ATUALIZADOS"
    fi
    if [ $TOTAL -gt $ATUALIZADOS ]; then
        print_color $GREEN "Passou: $PASSOU"
        print_color $RED "Falhou: $FALHOU"
        local testados=$((TOTAL - ATUALIZADOS))
        if [ $testados -gt 0 ]; then
            local taxa=$(( 100 * PASSOU / testados ))
            print_color $BLUE "Taxa de sucesso: $taxa%"
        fi
    fi

    if [ $ATUALIZADOS -gt 0 ]; then
        echo ""
        print_color $BLUE "Para criar gabaritos, copie os códigos corretos:"
        for arquivo in saidas_lua/*.lua; do
            if [ -f "$arquivo" ]; then
                local nome=$(basename "$arquivo" .lua)
                local gabarito="exemplos_gabaritos/${nome}.txt"
                if [ ! -f "$gabarito" ]; then
                    print_color $YELLOW "cp $arquivo $gabarito"
                fi
            fi
        done
    fi

    return $FALHOU
}

# função principal do teste do gerador
testar_gerador() {
    local modo="basico"
    local executar_lua=false
    local validar=false
    local otimizar=false

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
            --otimizar)
                otimizar=true
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

    # otimização adicional
    if $otimizar; then
        echo ""
        _otimizar_lua
        local opt_result=$?
        if [ $opt_result -gt 0 ]; then
            resultado=$opt_result
        fi
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
        test-generator)
            shift
            testar_gerador "$@"
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