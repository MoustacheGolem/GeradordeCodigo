
#include <stdlib.h>
#include <stdio.h>

enum AST_TYPE
{
    AST_DATA,
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
    struct astNode* nodeAppend = createAstNode(AST_APPEND, (union ARG)0, (union ARG)0, (union ARG)0, NULL);
	nodeAppend->left =  left;
	nodeAppend->right = right;
    return nodeAppend;
}

static int cont = 0;

char* getRegister(union ARG arg)
{
    switch (arg.regs)
    {
        case RS:
            return "rd";
        break;
        case AC:
            return "rs1";
        break;
        case AU:
            return "rs2";
        break;
        case ZERO:
            return "zero";
        break;
    }
}

void writeCode(FILE* file, struct astNode* node)
{
    switch(node->type)
    {
        case AST_DATA:
            fprintf(file,"%s: .word 0",cont++, node->label);
        break;
        case AST_ADD:
            fprintf(file,"%3d:  add  %s,%s, %s ",cont++, getRegister(node->arg1),getRegister(node->arg2),getRegister(node->arg3));
        break;
        case AST_ADDI:
            fprintf(file,"%3d:  addi %s,%s, %s ",cont++, getRegister(node->arg1),getRegister(node->arg2),node->arg3.imediate);
        break;
        case AST_SUB:
            fprintf(file,"%3d:  sub  %s,%s, %s ",cont++,getRegister(node->arg1),getRegister(node->arg2),getRegister(node->arg3));
        break; 
        case AST_MUL:
            fprintf(file,"%3d:  mul  %s,%s ,%s ",cont++,getRegister(node->arg1),getRegister(node->arg2),getRegister(node->arg3));
        break;
        case AST_DIV:
            fprintf(file,"%3d:  div  %s,%s, %s ",cont++,getRegister(node->arg1),getRegister(node->arg2),getRegister(node->arg3));
        break;
        // case AST_IN:
        //     fprintf(file,"%3d:  %d,%d(%d) ",cont++,op,r,d,s);
        // break;
        // case AST_OUT:
        //     fprintf(file,"%3d:  %d,%d(%d) ",cont++,op,r,d,s);
        // break;
        case AST_LD:
            fprintf(file,"%3d: ld:  %s,%d(%d) ",cont++,getRegister(node->arg1),node->arg2.imediate,node->arg3.imediate);
        break;
        case AST_ST:
            fprintf(file,"%3d: st:  %s,%d(%d) ",cont++,getRegister(node->arg1),node->arg2.imediate,node->arg3.imediate);
        break;
        case AST_JLT:
            fprintf(file,"%3d: blt:  %s,%s, %d ",cont++,getRegister(node->arg1),getRegister(node->arg2),node->arg3.label);
        break;
        case AST_JLE:
            fprintf(file,"%3d: jle:  %s,%s, %d ",cont++,getRegister(node->arg1),getRegister(node->arg2),node->arg3.label);
        break;
        case AST_JGT:
            fprintf(file,"%3d: jgt:  %s,%s, %d ",cont++,getRegister(node->arg1),getRegister(node->arg2),node->arg3.label);
        break;
        case AST_JGE:
            fprintf(file,"%3d: bge:  %s,%s, %d ",cont++,getRegister(node->arg1),getRegister(node->arg2),node->arg3.label);
        break;
        case AST_JEQ:
            fprintf(file,"%3d: beq  %s,%s, %d ",cont++,getRegister(node->arg1),getRegister(node->arg2),node->arg3.label);
        break;
        case AST_JNE:
            fprintf(file,"%3d: bne:  %s,%s, %d ",cont++,getRegister(node->arg1),getRegister(node->arg2),node->arg3.label);
        break; 
        case AST_LABEL:
            fprintf(file,"%s" , node->label);
        break;
        default:
        break;
    }
}

