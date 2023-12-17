
#include <stdlib.h>
#include <stdio.h>

enum AST_TYPE
{
    AST_ADD,
    AST_SUB,
    AST_MUL,
    AST_DIV,
    AST_IN,
    AST_OUT,
    AST_LD,
    AST_ST,
    AST_JLT,
    AST_JLE,
    AST_JGT,
    AST_JGE,
    AST_JEQ,
    AST_JNE,
    AST_LABEL,
    AST_NONE
};

union ARG {
    int imediate;
    char* label;
    int reg;
};

typedef struct astNode{
    AST_TYPE type;
    ARG arg1;
    ARG arg2;
    ARG arg3;
    char* label;
    astNode* left;
    astNode* right;
} astNode;

astNode* createAstNode(AST_TYPE type, ARG arg1, ARG arg2, ARG arg3, char* label)
{
    astNode* node = NULL;
    node = (astNode*) malloc(sizeof(astNode));
    node->type = type;
    node->arg1 = arg1;
    node->arg2 = arg2;
    node->arg3 = arg3;
    node->label = label;

    return node;
}

extern astNode* astToot;