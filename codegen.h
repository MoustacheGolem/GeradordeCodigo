#include "sintatic_tree.h"

char* getRegister(union ARG arg)
{
    switch (arg.regs)
    {
        case RS:
            return "s1";
        break;
        case AC:
            return "s2";
        break;
        case AU:
            return "s3";
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
        case AST_LI:
            fprintf(file,"li %s, %d \n", getRegister(node->arg1), node->arg3.imediate);
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
            fprintf(file,"slt  %s,%s, %s \n",getRegister(node->arg1),getRegister(node->arg3),getRegister(node->arg2));
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
            fprintf(file,"li a7, 5\n");
            fprintf(file,"ecall\n");
            fprintf(file,"mv s1, a0\n");
        break;
        case AST_OUT:
            // printf("%s \n",node->label);
            fprintf(file,"mv a0, %s \n", getRegister(node->arg1));
            fprintf(file,"li a7, 1\n");
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
            fprintf(file,"li a7, 11 \n");
            fprintf(file,"li a0, \'\\n\' \n");
            fprintf(file,"ecall\n");
    
            fprintf(file,"li a7, 10 \n");
            fprintf(file,"ecall\n");
        break;
        default:
        break;
    }
}
