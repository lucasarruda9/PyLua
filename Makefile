# Compilador e flags
CC = gcc
CFLAGS_COMMON = -Wall -Wextra -I$(SRC_DIR) -lm
CFLAGS_DEBUG = $(CFLAGS_COMMON) -g -DDEBUG
CFLAGS_RELEASE = $(CFLAGS_COMMON) -O2

# Configuração padrão (debug ou release)
ifeq ($(MODE),release)
	CFLAGS = $(CFLAGS_RELEASE)
	BUILD_SUFFIX = _release
else
	CFLAGS = $(CFLAGS_DEBUG)
	BUILD_SUFFIX = _debug
endif

# Diretórios
SRC_DIR = src
LEXER_DIR = lexer
PARSER_DIR = parser
AST_DIR = ast
TABELA_DIR = tabela
GERADOR_DIR = gerador_codigo_final
CODIGO_INTER_DIR = codigo_intermediario
BUILD_DIR = build
TEMP_DIR = temp
EXEMPLOS_DIR = exemplos
SAIDA_LUA_DIR = saidas_lua
SAIDA_TAC_DIR = saidas_tac
DOCS_DIR = docs

# Arquivos fonte
LEXER = $(LEXER_DIR)/scanner.l
PARSER = $(PARSER_DIR)/parser.y
AST = $(AST_DIR)/ast.c
TABELA = $(TABELA_DIR)/tabela.c
GERADOR = $(GERADOR_DIR)/gerador_codigo_final.c
OTIMIZADOR = $(GERADOR_DIR)/otimizador.c
CODIGO_INTER = $(CODIGO_INTER_DIR)/codigo_intermediario.c

# Arquivos gerados (saída no diretório src)
LEXER_C = $(SRC_DIR)/lex.yy.c
PARSER_C = $(SRC_DIR)/parser.tab.c
PARSER_H = $(SRC_DIR)/parser.tab.h

# Nome do executável 
TARGET = pylua$(BUILD_SUFFIX)

# Verificação de dependências
REQUIRED_BINS = gcc flex bison
MISSING_BINS = $(shell for bin in $(REQUIRED_BINS); do which $$bin >/dev/null 2>&1 || echo $$bin; done)

# Regra principal
all: verificar_deps setup $(TARGET)

# Verificar dependências
verificar_deps:
ifneq ($(MISSING_BINS),)
	@echo "ERRO: As seguintes dependências estão faltando: $(MISSING_BINS)"
	@echo "Por favor, instale as dependências necessárias e tente novamente."
	@exit 1
endif

# Criar diretórios necessários
setup:
	@mkdir -p $(SRC_DIR) $(BUILD_DIR) $(TEMP_DIR) $(EXEMPLOS_DIR) $(SAIDA_LUA_DIR) $(SAIDA_TAC_DIR) $(DOCS_DIR)/gerados

# Compilação em modo release
release:
	@$(MAKE) MODE=release

# Compilação em modo debug (padrão)
debug:
	@$(MAKE) MODE=debug

$(TARGET): $(LEXER_C) $(PARSER_C) $(AST) $(TABELA) $(GERADOR) $(OTIMIZADOR) $(CODIGO_INTER)
	$(CC) $(CFLAGS) -o $@ $^ -lfl -lm
	@echo "Compilação concluída: $@"

# Gerar parser.tab.c e parser.tab.h usando bison
$(PARSER_C) $(PARSER_H): $(PARSER) | setup
	bison -d -o $(PARSER_C) $<

# Gerar lex.yy.c usando flex
$(LEXER_C): $(LEXER) $(PARSER_H) | setup
	flex -o $@ $<

# Limpeza básica
clean:
	rm -f $(SRC_DIR)/*.c $(SRC_DIR)/*.h
	rm -f pylua pylua_debug pylua_release
	rm -rf $(TEMP_DIR)/*
	rm -rf saidas_lua
	rm -rf saidas_tac
	rm -f *.lua *.tac
	rm -rf logs

# limpeza dos arquivos de builds e os temporários
distclean: clean
	rm -rf $(BUILD_DIR)
	rm -rf $(TEMP_DIR)

# Executar o programa
run: all
	./$(TARGET)



# Testar gerador de código
test_gerador: $(TARGET)
	@echo "Testando gerador de código Lua..."
	@chmod +x ./pylua.sh
	@./pylua.sh test-generator

# vai testar os arquivos em python do diretório de exemplos
test_exemplos: $(TARGET)
	@echo "Testando todos os exemplos automaticamente..."
	@chmod +x ./pylua.sh
	@./pylua.sh test-generator --completo

# vê se a sintaxe do codigo lua está correto
validar_lua:
	@echo "Validando sintaxe dos códigos Lua..."
	@chmod +x ./pylua.sh
	@./pylua.sh test-generator --validar

# otimiza os códigos lua usando TAC
otimizar_lua: $(TARGET)
	@echo "Otimizando códigos Lua..."
	@chmod +x ./pylua.sh
	@./pylua.sh test-generator --completo --otimizar

# teste completo com otimização
test_otimizacao: $(TARGET)
	@echo "Testando gerador com otimizações..."
	@chmod +x ./pylua.sh
	@./pylua.sh test-generator --completo --otimizar --validar

# Gerar exemplos Lua
gerar_exemplos: $(TARGET)
	@echo "Gerando exemplos de código Lua..."
	@mkdir -p $(SAIDA_LUA_DIR)
	@for arquivo in $(EXEMPLOS_DIR)/*.py; do \
		if [ -f "$$arquivo" ]; then \
			nome=$$(basename "$$arquivo" .py); \
			echo "Processando $$arquivo -> $(SAIDA_LUA_DIR)/$$nome.lua"; \
			./$(TARGET) "$$arquivo" --gerar-lua "$(SAIDA_LUA_DIR)/$$nome.lua"; \
		fi \
	done

# Gerar documentação (placeholder)
docs:
	@echo "Documentação não implementada ainda"
	@mkdir -p docs/gerados

# Verificar sintaxe do código fonte
verificar_sintaxe:
	@echo "Verificando sintaxe do código fonte..."
	@for file in $(AST_DIR)/*.c $(TABELA_DIR)/*.c $(GERADOR_DIR)/*.c $(CODIGO_INTER_DIR)/*.c; do \
		$(CC) -I$(AST_DIR) -I$(TABELA_DIR) -I$(GERADOR_DIR) -fsyntax-only $$file && echo "✓ $$file"; \
	done


.PHONY: all clean distclean run setup verificar_deps debug release test test_parser test_lexer test_semantico atualizar_gabaritos test_gerador test_exemplos validar_lua otimizar_lua test_otimizacao clean_scripts gerar_exemplos docs verificar_sintaxe