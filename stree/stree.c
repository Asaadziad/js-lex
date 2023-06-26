
#include "stree.h"

/*
 AN EXPRESSION  is a lexeme / token
*/
typedef struct expr_t {
    TOKEN literal_token;
} *EXPR;

//Binary expression
struct bexpr_node {
    BINARY_EXPR left;
    TOKEN node_op;
    BINARY_EXPR right;
};

BINARY_EXPR createBinExpression(TOKEN token){
    if(!token) return NULL;
    BINARY_EXPR new_exp = (BINARY_EXPR)malloc(sizeof(*new_exp));
    if(!new_exp) return NULL;

    new_exp->node_op = token;
    new_exp->left = NULL;
    new_exp->right = NULL;
}

void setLeftNode(BINARY_EXPR exp, TOKEN token){
    if(!exp) return;
    if(exp->left) { exp->left->node_op = token; return; }
    BINARY_EXPR left_exp = (BINARY_EXPR)malloc(sizeof(*left_exp));
    if(!left_exp) return NULL;
    left_exp->node_op = token;
    left_exp->left = NULL;
    left_exp->right = NULL;
    return left_exp;
}
void setRightNode(BINARY_EXPR exp,TOKEN token){
    if(!exp) return;
    if(exp->right) { exp->right->node_op = token; return; }
    BINARY_EXPR right_exp = (BINARY_EXPR)malloc(sizeof(*right_exp));
    if(!right_exp) return NULL;
    right_exp->node_op = token;
    right_exp->right = NULL;
    right_exp->right = NULL;
    return right_exp;
}


void printBinaryExp(BINARY_EXPR exp){
    if(!exp) return;
    tokenPrint(exp->node_op);
    printBinaryExp(exp->left);
    printBinaryExp(exp->right);
}
