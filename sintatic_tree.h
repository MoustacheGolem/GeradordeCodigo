
#include <stdlib.h>
#include <stdio.h>

enum AST_TYPE
{
    AST_SECTION,
    AST_DATA,
    AST_ADD,
    AST_LI,
    AST_SUB, 
    AST_MUL,
    AST_DIV,
    AST_AND, 
    AST_OR, 
    AST_LT, 
    AST_GT, 
    AST_LE, 
    AST_GE, 
    AST_EQ, 
    AST_DIF, 
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
    AST_HALT,
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
    enum REG regs;
};


typedef struct astNode{
    enum AST_TYPE type;
    union ARG arg1;
    union ARG arg2;
    union ARG arg3;
    char* label;
    struct astNode* left;
    struct astNode* right;
} astNode;

struct astNode* createAstNode(enum AST_TYPE type, union ARG arg1, union ARG arg2, union ARG arg3, char* label)
{
    struct astNode* node = NULL;
    node = (struct astNode*) malloc(sizeof(astNode));
    node->type = type;
    node->arg1 = arg1;
    node->arg2 = arg2;
    node->arg3 = arg3;
    node->label = label;
    node->left = NULL;
    node->right = NULL;

    return node;
}

struct astNode* appendNodes(struct astNode* left, struct astNode* right)
{   
    //create node with args = 0
    struct astNode* nodeAppend = createAstNode(AST_APPEND, (union ARG)0, (union ARG)0, (union ARG)0, "");
	nodeAppend->left = left;
	nodeAppend->right = right;
    return nodeAppend;
}

static int cont = 0;


