# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -I$(SRC_DIR)

# Diretórios
SRC_DIR = src
LEXER_DIR = lexer
PARSER_DIR = parser
BUILD_DIR = build

# Arquivos fonte
LEXER = $(LEXER_DIR)/scanner.l
PARSER = $(PARSER_DIR)/parser.y

# Arquivos gerados (saída no diretório src)
LEXER_C = $(SRC_DIR)/lex.yy.c
PARSER_C = $(SRC_DIR)/parser.tab.c
PARSER_H = $(SRC_DIR)/parser.tab.h

# Nome do executável 
TARGET = expr_parser

# Regra principal
all: setup $(TARGET)

# Criar diretórios necessários
setup:
	@mkdir -p $(SRC_DIR) $(BUILD_DIR)

$(TARGET): $(LEXER_C) $(PARSER_C)
	$(CC) $(CFLAGS) -o $@ $^ -lfl

# Gerar parser.tab.c e parser.tab.h usando bison
$(PARSER_C) $(PARSER_H): $(PARSER) | setup
	bison -d -o $(PARSER_C) $<

# Gerar lex.yy.c usando flex
$(LEXER_C): $(LEXER) $(PARSER_H) | setup
	flex -o $@ $<

clean:
	rm -f $(SRC_DIR)/*.c $(SRC_DIR)/*.h
	rm -f $(TARGET)

# Executar o programa
run: all
	./$(TARGET)

.PHONY: all clean run setup 