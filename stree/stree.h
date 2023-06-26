#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H

#include "../lexer/lexer.h"


typedef struct bexpr_node *BINARY_EXPR;

BINARY_EXPR createBinExpression(TOKEN token);
void setLeftNode(BINARY_EXPR exp,TOKEN token);
void setRightNode(BINARY_EXPR exp,TOKEN token);
void printBinaryExp(BINARY_EXPR exp);

#endif