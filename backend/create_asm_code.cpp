#include "create_asm_code.h"




void get_tree_from_file(FILE* file, Tree* tree, VariableArr* all_var)
{

}

// Пусть дерево уже есть.
// Надо из дерева делать ассемблер.

void tree_to_asm(FILE* file_asm_code, Node* node, VariableArr* all_var, int* flag)
{
    // Просто число не может встретиться как и просто переменная. Они будут привязаны к 
    // операции. Надо рассматривать операции
    // if (node->type == NUMBER) fprintf(file, "%lg ", node->value.num);

    if      (node->type == NUMBER)   { printf("NUMBER\n"); fprintf(file_asm_code, "PUSH %lg ", node->value.num); }
    else if (node->type == VARIABLE) { printf("VARIABLE\n"); fprintf(file_asm_code, "PUSH [%d] ", node->value.var_num); }

    // запуск нужной функции
    else
    {
        for (int i = 0; i < LEN_STRUCT_OP_TO_ASM_ARR; i++)
        {
            if (op_to_asm_arr[i].num == node->value.op_num)
            {
                if (op_to_asm_arr[i].asm_code == NULL) break;
                op_to_asm_arr[i].asm_code(file_asm_code, node, all_var, flag);
                break;
            }
        }
    }
 


}