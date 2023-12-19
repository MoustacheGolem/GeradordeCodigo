
#include <stdlib.h>
#include <stdio.h>

enum AST_TYPE
{
    AST_SECTION,
    AST_DATA,
    AST_ADD,
    AST_ADDI,
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
    if(node == NULL)
    {
        return;
    }

    switch(node->type)
    {
        case AST_SECTION:
            fprintf(file,"%s\n", node->label);
        break;
        case AST_DATA:
            fprintf(file,"%s: .word 0\n", node->label);
        break;
        case AST_ADD:
            fprintf(file,"add  %s,%s, %s \n", getRegister(node->arg1),getRegister(node->arg2),getRegister(node->arg3));
        break;
        case AST_ADDI:
            fprintf(file,"addi %s,%s, %d \n", getRegister(node->arg1),getRegister(node->arg2), node->arg3.imediate);
        break;
        case AST_SUB:
            fprintf(file,"sub  %s,%s, %s \n",getRegister(node->arg1),getRegister(node->arg2),getRegister(node->arg3));
        break; 
        case AST_MUL:
            fprintf(file,"mul  %s,%s ,%s \n",getRegister(node->arg1),getRegister(node->arg2),getRegister(node->arg3));
        break;
        case AST_DIV:
            fprintf(file,"div  %s,%s, %s \n",getRegister(node->arg1),getRegister(node->arg2),getRegister(node->arg3));
        break;
        case AST_AND:
            fprintf(file,"and  %s,%s, %s \n",getRegister(node->arg1),getRegister(node->arg2),getRegister(node->arg3));
        break;
        case AST_OR:
            fprintf(file,"or  %s,%s, %s \n",getRegister(node->arg1),getRegister(node->arg2),getRegister(node->arg3));
        break;
        case AST_LT:
            fprintf(file,"slt  %s,%s, %s \n",getRegister(node->arg1),getRegister(node->arg2),getRegister(node->arg3));
        break;
        case AST_GT:
            fprintf(file,"slt  %s,%s, %s \n",getRegister(node->arg2),getRegister(node->arg1),getRegister(node->arg3));
        break;
        case AST_LE:
            fprintf(file,"slt  %s,%s, %s \n",getRegister(node->arg2),getRegister(node->arg1),getRegister(node->arg3));
            fprintf(file,"xori  %s,%s, %d \n",getRegister(node->arg1),getRegister(node->arg1),1);
            break;
        case AST_GE:
            fprintf(file,"slt  %s,%s, %s \n",getRegister(node->arg1),getRegister(node->arg2),getRegister(node->arg3));
            fprintf(file,"xori  %s,%s, %d \n",getRegister(node->arg1),getRegister(node->arg1),1);
        break;
        case AST_EQ:
            fprintf(file,"seq  %s,%s, %s \n",getRegister(node->arg1),getRegister(node->arg2),getRegister(node->arg3));
        break;
        case AST_DIF:
            fprintf(file,"sne  %s,%s, %s \n",getRegister(node->arg1),getRegister(node->arg2),getRegister(node->arg3));
        break;
        case AST_IN:
            fprintf(file,"la a0, 0\n");
            fprintf(file,"li a1, bugger\n");
            fprintf(file,"li a2, 4 \n");
            fprintf(file,"li a7, 63\n");
            fprintf(file,"ecall\n");
        break;
        case AST_OUT:
            fprintf(file,"la  a1, %s\n", getRegister(node->arg1));
            fprintf(file,"li a2, 4\n");
            fprintf(file,"li a0, 1 \n");
            fprintf(file,"li a7, 64\n");
            fprintf(file,"ecall\n");
        break;
        case AST_LD:
            fprintf(file,"la  %s, %s\n",getRegister(node->arg3), node->label );
            fprintf(file,"lw  %s, %d(%s) \n",getRegister(node->arg1),node->arg2.imediate,getRegister(node->arg3));
        break;
        case AST_ST:
            fprintf(file,"la  %s, %s\n",getRegister(node->arg3), node->label);
            fprintf(file,"sw  %s, %d(%s) \n",getRegister(node->arg1),node->arg2.imediate,getRegister(node->arg3));
        break;
        case AST_JLT:
            fprintf(file,"blt  %s, %s, %s \n",getRegister(node->arg1),getRegister(node->arg2),node->arg3.label);
        break;
        case AST_JLE:
            fprintf(file,"ble  %s, %s, %s \n",getRegister(node->arg1),getRegister(node->arg2),node->arg3.label);
        break;
        case AST_JGT:
            fprintf(file,"bgt %s, %s, %s \n",getRegister(node->arg1),getRegister(node->arg2),node->arg3.label);
        break;
        case AST_JGE:
            fprintf(file,"bge  %s, %s, %s \n",getRegister(node->arg1),getRegister(node->arg2),node->arg3.label);
        break;
        case AST_JEQ:
            fprintf(file,"beq  %s, %s, %s \n",getRegister(node->arg1),getRegister(node->arg2),node->arg3.label);
        break;
        case AST_JNE:
            fprintf(file,"bne  %s, %s, %s \n",getRegister(node->arg1),getRegister(node->arg2),node->arg3.label);
        break; 
        case AST_LABEL:
            fprintf(file,"%s: \n" , node->label);
        break;
        case AST_HALT:
            fprintf(file,"li  a7, 93");
            fprintf(file,"ecall\n");
        break;
        default:
        break;
    }
}

