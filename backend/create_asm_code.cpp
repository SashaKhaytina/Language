#include "create_asm_code.h"




void get_tree_from_file(FILE* file, Tree* tree, VariableArr* all_var)
{

}

// Пусть дерево уже есть.
// Надо из дерева делать ассемблер.

void tree_to_asm(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
{
    // Просто число не может встретиться как и просто переменная. Они будут привязаны к 
    // операции. Надо рассматривать операции
    // if (node->type == NUMBER) fprintf(file, "%lg ", node->value.num);

    if      (node->type == NUMBER)   
    { 
        printf("NUMBER\n"); 
        fprintf(file_asm_code, "PUSH %lg ", node->value.num); 
    }
    else if (node->type == VARIABLE) 
    { 
        printf("VARIABLE\n"); 

        // СЧЕТЧИК ПЕРЕМЕННЫХ += 1
        // fprintf(file_asm_code, "\n PUSH REX PUSH 1 ADD POP REX\n");

        if (!is_in_func) fprintf(file_asm_code, "PUSH [%d] ",       node->value.var_num); 
        else             fprintf(file_asm_code, "PUSH [%d + REX] ", node->value.var_num); // REX - глубина вложенности!!!!!
    }

    else if (node->type == CREATED_FUNC) // запускаем функцию для объявления с правильным номером функции
    {
        asm_code_func(file_asm_code, node, all_var, all_func, flag, is_in_func);
    }

    else if (node->type == CALL_FUNC) // запускаем функцию для объявления с правильным номером функции
    {
        // tree_to_asm(file_asm_code, "PUSH [%d + REX]"); // PUSH переменных
        tree_to_asm(file_asm_code, node->left, all_var, all_func, flag, is_in_func); // PUSH переменных

        fprintf(file_asm_code, "CALL %s ", all_func->arr[node->value.func_num - 1].name);
    }


    // запуск нужной операции
    else
    {
        for (int i = 0; i < LEN_STRUCT_OP_TO_ASM_ARR; i++)
        {
            if (op_to_asm_arr[i].num == node->value.op_num)
            {
                if (op_to_asm_arr[i].asm_code == NULL) break;
                op_to_asm_arr[i].asm_code(file_asm_code, node, all_var, all_func, flag, is_in_func);
                break;
            }
        }
    }
 


}