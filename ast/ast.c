#include "ast.h"

// Função para criar um nó literal (número inteiro)
ASTNode* create_literal_node(int value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_LITERAL;  // Tipo de nó: Literal
    node->left = node->right = NULL;
    node->value = value;
    node->idval = NULL;
    node->op = 0;  // Sem operador
    return node;
}

// Função para criar um nó de variável
ASTNode* create_variable_node(char* id) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_VARIABLE;  // Tipo de nó: Variável
    node->left = node->right = NULL;
    node->value = 0;
    node->idval = strdup(id);  // Copia o nome da variável
    node->op = 0;  // Sem operador
    return node;
}

// Função para criar um nó de operação binária
ASTNode* create_binary_op_node(char op, ASTNode* left, ASTNode* right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_BINARY_OP;  // Tipo de nó: Operação binária
    node->left = left;
    node->right = right;
    node->value = 0;  // Não é um valor literal
    node->idval = NULL;
    node->op = op;  // Armazena o operador
    return node;
}

// Função para criar um nó de atribuição
ASTNode* create_assignment_node(ASTNode* var, ASTNode* expr) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_ASSIGNMENT;  // Tipo de nó: Atribuição
    node->left = var;
    node->right = expr;
    node->value = 0;  // Não é um valor literal
    node->idval = NULL;
    node->op = 0;  // Sem operador
    return node;
}

// Função para criar um nó de operação unária (menos unário)
ASTNode* create_unary_op_node(char op, ASTNode* expr) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_BINARY_OP;  // Tipo de nó: Operação binária (pode ser unário)
    node->left = expr;
    node->right = NULL;
    node->op = op;  // Armazena o operador
    return node;
}
