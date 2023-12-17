
#include <stdlib.h>
#include <stdio.h>

enum AST_TYPE
{
    AST_ADD,
    AST_ADDI,
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
    AST_NONE,
    AST_ERROR,
    AST_APPEND
};

enum REG {
    RS,
    AC,
    AU,
    ZERO
};

union ARG {
    int imediate;
    char* label;
    REG regs;
};


ac = 1

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

astNode* appendNodes(astNode* left, astNode* right;)
{
    astNode* nodeAppend = createAstNode(AST_APPEND, AST_NONE, AST_NONE, AST_NONE, "");
	nodeAppend.left = $1;
	nodeAppend.right = $2;
    return nodeAppend;
}

extern astNode* astRoot;