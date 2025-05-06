#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo tipos de nós da AST
typedef enum { 
    NODE_LITERAL, 
    NODE_VARIABLE, 
    NODE_BINARY_OP, 
    NODE_ASSIGNMENT
} NodeType;

// Definindo o tipo do nó da AST
typedef struct ASTNode {
    NodeType type;      // Tipo do nó (literal, variável, operação binária, etc.)
    struct ASTNode* left;   // Filho esquerdo
    struct ASTNode* right;  // Filho direito
    int value;           // Valor (para literais)
    char* idval;         // Para armazenar o nome da variável
    char op;             // Operador (para operações binárias)
} ASTNode;

// Funções para criar nós da AST
ASTNode* create_literal_node(int value);
ASTNode* create_variable_node(char* id);
ASTNode* create_binary_op_node(char op, ASTNode* left, ASTNode* right);
ASTNode* create_assignment_node(ASTNode* var, ASTNode* expr);

#endif
