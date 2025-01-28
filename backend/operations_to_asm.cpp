#include "operations_to_asm.h"

#include "create_asm_code.h"

// ПЕРЕМЕННЫЕ:
// У каждой переменной есть ее номер. 
// Тогда в оперативной памяти: (значение ячейки - значение переменной)
// Для первой переменной - [1]
// Для второй переменной - [2]
//
//
//

void asm_code_add(FILE* file_asm_code, Node* node, VariableArr* all_var, int* flag)
{
    printf("ADD\n");

    tree_to_asm(file_asm_code, node->left,  all_var, flag);
    tree_to_asm(file_asm_code, node->right, all_var, flag);

    fprintf(file_asm_code, "ADD \n"); // PUSH был ранее

    // if      (node->right->type == NUMBER)   fprintf(file_asm_code, "PUSH %lg ", node->left->value.num);
    // else if (node->right->type == VARIABLE) fprintf(file_asm_code, "PUSH [%lg] ", node->left->value.var_num);
}

void asm_code_sub(FILE* file_asm_code, Node* node, VariableArr* all_var, int* flag)
{
    printf("SUB\n");

    tree_to_asm(file_asm_code, node->left,  all_var, flag);
    tree_to_asm(file_asm_code, node->right, all_var, flag);

    fprintf(file_asm_code, "SUB \n"); // PUSH был ранее

    // if      (node->right->type == NUMBER)   fprintf(file_asm_code, "PUSH %lg ", node->left->value.num);
    // else if (node->right->type == VARIABLE) fprintf(file_asm_code, "PUSH [%lg] ", node->left->value.var_num);
}


void asm_code_mul(FILE* file_asm_code, Node* node, VariableArr* all_var, int* flag)
{
    tree_to_asm(file_asm_code, node->left,  all_var, flag);
    tree_to_asm(file_asm_code, node->right, all_var, flag);

    fprintf(file_asm_code, "MUL \n"); // PUSH был ранее

    // if      (node->right->type == NUMBER)   fprintf(file_asm_code, "PUSH %lg ", node->left->value.num);
    // else if (node->right->type == VARIABLE) fprintf(file_asm_code, "PUSH [%lg] ", node->left->value.var_num);
}


void asm_code_div(FILE* file_asm_code, Node* node, VariableArr* all_var, int* flag)
{
    tree_to_asm(file_asm_code, node->left,  all_var, flag);
    tree_to_asm(file_asm_code, node->right, all_var, flag);

    fprintf(file_asm_code, "DIV \n"); // PUSH был ранее

    // if      (node->right->type == NUMBER)   fprintf(file_asm_code, "PUSH %lg ", node->left->value.num);
    // else if (node->right->type == VARIABLE) fprintf(file_asm_code, "PUSH [%lg] ", node->left->value.var_num);
}


void asm_code_if(FILE* file_asm_code, Node* node, VariableArr* all_var, int* flag)
{
    printf("IF\n");


    int flags_now = *flag;
    (*flag)++;
    // tree_to_asm(file_asm_code, node->left,  all_var, flag); когда тут будет знак сравнения (ОТРИЦАНИЕ НАСТОЯЩЕГО УСЛОВИЯ)
    // fprintf(file_asm_code, "PUSH 0 ");
    // tree_to_asm(file_asm_code, node->left, all_var, flag);
    // fprintf(file_asm_code, "JNE IF%d\n", flags_now);

    tree_to_asm(file_asm_code, node->left, all_var, flag);    
    fprintf(file_asm_code, "IF%d\n", flags_now);

    tree_to_asm(file_asm_code, node->right, all_var, flag);

    fprintf(file_asm_code, "\nIF%d:\n", flags_now);
}


void asm_code_while(FILE* file_asm_code, Node* node, VariableArr* all_var, int* flag)
{
    int flags_now = *flag;
    (*flag)++;


    fprintf(file_asm_code, "\nCYCLE%d:\n", flags_now);

    // Условие
    // tree_to_asm(file_asm_code, node->left,  all_var, flag); когда тут будет знак сравнения (ОТРИЦАНИЕ НАСТОЯЩЕГО УСЛОВИЯ)
    
    // fprintf(file_asm_code, "PUSH 0 ");
    tree_to_asm(file_asm_code, node->left, all_var, flag);

    // fprintf(file_asm_code, "JNE BREAK%d\n", flags_now);
    
    fprintf(file_asm_code, "BREAK%d\n", flags_now);

    tree_to_asm(file_asm_code, node->right, all_var, flag);

    fprintf(file_asm_code, "\nJUMP CYCLE%d\n", flags_now);
    fprintf(file_asm_code, "BREAK%d:\n", flags_now);
}


void asm_code_assigm(FILE* file_asm_code, Node* node, VariableArr* all_var,int* flag)
{
    printf("ASSIGM\n");

    tree_to_asm(file_asm_code, node->right, all_var, flag);
    fprintf(file_asm_code, "POP[%d]\n", node->left->value.var_num);
}


void asm_code_equal(FILE* file_asm_code, Node* node, VariableArr* all_var,int* flag)
{
    printf("EQUAL\n");

    tree_to_asm(file_asm_code, node->left , all_var, flag);
    tree_to_asm(file_asm_code, node->right, all_var, flag);

    fprintf(file_asm_code, "JNE ");

}


void asm_code_more(FILE* file_asm_code, Node* node, VariableArr* all_var,int* flag)
{
    printf("MORE\n");

    tree_to_asm(file_asm_code, node->left , all_var, flag);
    tree_to_asm(file_asm_code, node->right, all_var, flag);

    fprintf(file_asm_code, "JNG ");

}


void asm_code_less(FILE* file_asm_code, Node* node, VariableArr* all_var,int* flag)
{
    printf("LESS\n");

    tree_to_asm(file_asm_code, node->left , all_var, flag);
    tree_to_asm(file_asm_code, node->right, all_var, flag);

    fprintf(file_asm_code, "JNL ");

}


void asm_code_geq(FILE* file_asm_code, Node* node, VariableArr* all_var,int* flag)
{
    printf("GEQ\n");

    tree_to_asm(file_asm_code, node->left , all_var, flag);
    tree_to_asm(file_asm_code, node->right, all_var, flag);

    fprintf(file_asm_code, "JB ");

}


void asm_code_leq(FILE* file_asm_code, Node* node, VariableArr* all_var,int* flag)
{
    printf("LEQ\n");

    tree_to_asm(file_asm_code, node->left , all_var, flag);
    tree_to_asm(file_asm_code, node->right, all_var, flag);

    fprintf(file_asm_code, "JA ");

}


void asm_code_split(FILE* file_asm_code, Node* node, VariableArr* all_var,int* flag)
{
    printf("SPLIT\n");


    tree_to_asm(file_asm_code, node->left, all_var, flag);

    fprintf(file_asm_code, "\n");

    if (node->right != NULL) tree_to_asm(file_asm_code, node->right, all_var, flag);

}