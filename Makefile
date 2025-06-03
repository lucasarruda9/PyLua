# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -I$(SRC_DIR) -lm

# Diretórios
SRC_DIR = src
LEXER_DIR = lexer
PARSER_DIR = parser
AST_DIR = ast
TABELA_DIR = tabela
GERADOR_CODIGO_FINAL_DIR = gerador_codigo_final
BUILD_DIR = build
SAIDA_DIR = saida_lua 

# Arquivos fonte
LEXER = $(LEXER_DIR)/scanner.l
PARSER = $(PARSER_DIR)/parser.y
AST = $(AST_DIR)/ast.c
TABELA = $(TABELA_DIR)/tabela.c
GERADOR_CODIGO_FINAL = $(GERADOR_CODIGO_FINAL_DIR)/gerador_codigo_final.c 

# Arquivos gerados (saída no diretório src)
LEXER_C = $(SRC_DIR)/lex.yy.c
PARSER_C = $(SRC_DIR)/parser.tab.c
PARSER_H = $(SRC_DIR)/parser.tab.h

# Nome do executável 
TARGET = pylua

# Regra principal
all: setup $(TARGET)

# Criar diretórios necessários
setup:
	@mkdir -p $(SRC_DIR) $(BUILD_DIR) $(SAIDA_DIR)

$(TARGET): $(LEXER_C) $(PARSER_C) $(AST) $(TABELA) $(GERADOR_CODIGO_FINAL)
	$(CC) $(CFLAGS) -o $@ $^ -lfl -lm

# Gerar parser.tab.c e parser.tab.h usando bison
$(PARSER_C) $(PARSER_H): $(PARSER) | setup
	bison -d -o $(PARSER_C) $<

# Gerar lex.yy.c usando flex
$(LEXER_C): $(LEXER) $(PARSER_H) | setup
	flex -o $@ $<

clean:
	rm -f $(SRC_DIR)/*.c $(SRC_DIR)/*.h
	rm -f $(TARGET)
	rm -rf $(SAIDA_DIR)  

# Executar o programa
run: all
	./$(TARGET)

# Regra para executar testess
test: $(TARGET)
	@chmod +x run_tests.sh
	@./run_tests.sh

.PHONY: all clean run setup