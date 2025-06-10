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
BUILD_DIR = build
TEST_DIR = tests
TEMP_DIR = temp
EXEMPLOS_DIR = exemplos
SAIDA_LUA_DIR = saidas_lua
DOCS_DIR = docs

# Arquivos fonte
LEXER = $(LEXER_DIR)/scanner.l
PARSER = $(PARSER_DIR)/parser.y
AST = $(AST_DIR)/ast.c
TABELA = $(TABELA_DIR)/tabela.c
GERADOR = $(GERADOR_DIR)/gerador_codigo_final.c

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
	@mkdir -p $(SRC_DIR) $(BUILD_DIR) $(TEMP_DIR) $(EXEMPLOS_DIR) $(SAIDA_LUA_DIR) $(DOCS_DIR)/gerados

# Compilação em modo release
release:
	@$(MAKE) MODE=release

# Compilação em modo debug (padrão)
debug:
	@$(MAKE) MODE=debug

$(TARGET): $(LEXER_C) $(PARSER_C) $(AST) $(TABELA) $(GERADOR)
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
	rm -f *.lua

# Limpeza completa (inclui arquivos de build e temporários)
distclean: clean
	rm -rf $(BUILD_DIR)
	rm -rf $(TEMP_DIR)

# Executar o programa
run: all
	./$(TARGET)

# Regra para executar todos os testes
test: $(TARGET)
	@chmod +x ./run_tests.sh
	@bash ./run_tests.sh

# Regras para testes específicos
test_parser: $(TARGET)
	@chmod +x ./run_tests.sh
	@bash ./run_tests.sh --test parser

test_lexer: $(TARGET)
	@chmod +x ./run_tests.sh
	@bash ./run_tests.sh --test lexer

test_semantico: $(TARGET)
	@chmod +x ./run_tests.sh
	@bash ./run_tests.sh --test semantico

# Atualizar gabaritos de testes
atualizar_gabaritos: $(TARGET)
	@chmod +x ./run_tests.sh
	@bash ./run_tests.sh --update-gabaritos

# Testar gerador de código
test_gerador: $(TARGET)
	@echo "Testando gerador de código Lua..."
	@chmod +x ./testar_gerador.sh
	@bash ./testar_gerador.sh

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

# Gerar documentação
docs:
	@echo "Gerando documentação..."
	@mkdir -p docs/gerados
	# Adicione comandos para gerar documentação aqui

# Verificar sintaxe do código fonte
verificar_sintaxe:
	@echo "Verificando sintaxe do código fonte..."
	@for file in $(AST_DIR)/*.c $(TABELA_DIR)/*.c $(GERADOR_DIR)/*.c; do \
		$(CC) -fsyntax-only $$file && echo "✓ $$file"; \
	done

.PHONY: all clean distclean run setup verificar_deps debug release test test_parser test_lexer test_semantico atualizar_gabaritos test_gerador gerar_exemplos docs verificar_sintaxe
