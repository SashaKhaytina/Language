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

void asm_code_add(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
{
    printf("ADD\n");

    tree_to_asm(file_asm_code, node->left,  all_var, all_func, flag, is_in_func);
    tree_to_asm(file_asm_code, node->right, all_var, all_func, flag, is_in_func);

    fprintf(file_asm_code, "ADD \n"); // PUSH был ранее

    // if      (node->right->type == NUMBER)   fprintf(file_asm_code, "PUSH %lg ", node->left->value.num);
    // else if (node->right->type == VARIABLE) fprintf(file_asm_code, "PUSH [%lg] ", node->left->value.var_num);
}

void asm_code_sub(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
{
    printf("SUB\n");

    tree_to_asm(file_asm_code, node->left,  all_var, all_func, flag, is_in_func);
    tree_to_asm(file_asm_code, node->right, all_var, all_func, flag, is_in_func);

    fprintf(file_asm_code, "SUB \n"); // PUSH был ранее

    // if      (node->right->type == NUMBER)   fprintf(file_asm_code, "PUSH %lg ", node->left->value.num);
    // else if (node->right->type == VARIABLE) fprintf(file_asm_code, "PUSH [%lg] ", node->left->value.var_num);
}


void asm_code_mul(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
{
    tree_to_asm(file_asm_code, node->left,  all_var, all_func, flag, is_in_func);
    tree_to_asm(file_asm_code, node->right, all_var, all_func, flag, is_in_func);

    fprintf(file_asm_code, "MUL \n"); // PUSH был ранее

    // if      (node->right->type == NUMBER)   fprintf(file_asm_code, "PUSH %lg ", node->left->value.num);
    // else if (node->right->type == VARIABLE) fprintf(file_asm_code, "PUSH [%lg] ", node->left->value.var_num);
}


void asm_code_div(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
{
    tree_to_asm(file_asm_code, node->left,  all_var, all_func, flag, is_in_func);
    tree_to_asm(file_asm_code, node->right, all_var, all_func, flag, is_in_func);

    fprintf(file_asm_code, "DIV \n"); // PUSH был ранее

    // if      (node->right->type == NUMBER)   fprintf(file_asm_code, "PUSH %lg ", node->left->value.num);
    // else if (node->right->type == VARIABLE) fprintf(file_asm_code, "PUSH [%lg] ", node->left->value.var_num);
}


void asm_code_input (FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
{
    fprintf(file_asm_code, "\nIN \n");
    
    fprintf(file_asm_code, "POP [%d + REX]\n", node->left->value.var_num);
}


void asm_code_output(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
{
    tree_to_asm(file_asm_code, node->left,  all_var, all_func, flag, is_in_func);

    fprintf(file_asm_code, "OUT \n");

}





void asm_code_if(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
{
    printf("IF\n");


    int flags_now = *flag;
    (*flag)++;
    // tree_to_asm(file_asm_code, node->left,  all_var, all_func, flag, is_in_func); когда тут будет знак сравнения (ОТРИЦАНИЕ НАСТОЯЩЕГО УСЛОВИЯ)
    // fprintf(file_asm_code, "PUSH 0 ");
    // tree_to_asm(file_asm_code, node->left, all_var, all_func, flag, is_in_func);
    // fprintf(file_asm_code, "JNE IF%d\n", flags_now);

    tree_to_asm(file_asm_code, node->left, all_var, all_func, flag, is_in_func);    
    fprintf(file_asm_code, "IF%d\n", flags_now);

    tree_to_asm(file_asm_code, node->right, all_var, all_func, flag, is_in_func);

    fprintf(file_asm_code, "\nIF%d:\n", flags_now);
}


void asm_code_while(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
{
    int flags_now = *flag;
    (*flag)++;


    fprintf(file_asm_code, "\nCYCLE%d:\n", flags_now);

    // Условие
    // tree_to_asm(file_asm_code, node->left,  all_var, all_func, flag, is_in_func); когда тут будет знак сравнения (ОТРИЦАНИЕ НАСТОЯЩЕГО УСЛОВИЯ)
    
    // fprintf(file_asm_code, "PUSH 0 ");
    tree_to_asm(file_asm_code, node->left, all_var, all_func, flag, is_in_func);

    // fprintf(file_asm_code, "JNE BREAK%d\n", flags_now);
    
    fprintf(file_asm_code, "BREAK%d\n", flags_now);

    tree_to_asm(file_asm_code, node->right, all_var, all_func, flag, is_in_func);

    fprintf(file_asm_code, "\nJUMP CYCLE%d\n", flags_now);
    fprintf(file_asm_code, "BREAK%d:\n", flags_now);
}


void asm_code_assigm(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
{
    printf("ASSIGM\n");

    tree_to_asm(file_asm_code, node->right, all_var, all_func, flag, is_in_func);
    fprintf(file_asm_code, "POP [%d + REX]\n", node->left->value.var_num);
}


void asm_code_equal(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
{
    printf("EQUAL\n");

    tree_to_asm(file_asm_code, node->left , all_var, all_func, flag, is_in_func);
    tree_to_asm(file_asm_code, node->right, all_var, all_func, flag, is_in_func);

    fprintf(file_asm_code, "JNE ");

}


void asm_code_more(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
{
    printf("MORE\n");

    tree_to_asm(file_asm_code, node->left , all_var, all_func, flag, is_in_func);
    tree_to_asm(file_asm_code, node->right, all_var, all_func, flag, is_in_func);

    fprintf(file_asm_code, "JNG ");

}


void asm_code_less(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
{
    printf("LESS\n");

    tree_to_asm(file_asm_code, node->left , all_var, all_func, flag, is_in_func);
    tree_to_asm(file_asm_code, node->right, all_var, all_func, flag, is_in_func);

    fprintf(file_asm_code, "JNL ");

}


void asm_code_geq(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
{
    printf("GEQ\n");

    tree_to_asm(file_asm_code, node->left , all_var, all_func, flag, is_in_func);
    tree_to_asm(file_asm_code, node->right, all_var, all_func, flag, is_in_func);

    fprintf(file_asm_code, "JB ");

}


void asm_code_leq(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
{
    printf("LEQ\n");

    tree_to_asm(file_asm_code, node->left , all_var, all_func, flag, is_in_func);
    tree_to_asm(file_asm_code, node->right, all_var, all_func, flag, is_in_func);

    fprintf(file_asm_code, "JA ");

}


void asm_code_split(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
{
    printf("SPLIT\n");


    if (node->left != NULL)  tree_to_asm(file_asm_code, node->left, all_var, all_func, flag, is_in_func);

    fprintf(file_asm_code, "\n");

    if (node->right != NULL) tree_to_asm(file_asm_code, node->right, all_var, all_func, flag, is_in_func);

}











void asm_code_func(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
{
    printf("FUNC\n");

    *is_in_func = true; // кажется везде нужен этот флаг.

    fprintf(file_asm_code, "%s:\n", all_func->arr[node->value.func_num - 1].name);

    fprintf(file_asm_code, "\nPUSH REX "); // REMEMBER
    fprintf(file_asm_code, "\nPUSH REX PUSH %d ADD POP REX\n", MAX_VAR_COUNT); // вложенность
    fprintf(file_asm_code, "\nPOP RCX POP RDX\n"); // RCX - СТАРЫЙ REX,  RDX - АДРЕС ВОЗВРАТА


    if (node->left->type == OPERATION) tree_to_asm(file_asm_code, node->left, all_var, all_func, flag, is_in_func);
    else fprintf(file_asm_code, "POP [%d + REX]", node->left->value.var_num);
    
    fprintf(file_asm_code, "\n");
    
    tree_to_asm(file_asm_code, node->right, all_var, all_func, flag, is_in_func);



    // fprintf(file_asm_code, "POP  REX"); ЭТО НЕ ЗДЕСЬ, а в return. Его надо ставить обязательно!
    // fprintf(file_asm_code, "\nRET\n\n");

}

void asm_code_pointcomma(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
{
    // ДОСТАЮ
    assert(node);

    // кладу в правильном порядке, достаю в другом
    if (node->left->type == VARIABLE) fprintf(file_asm_code, "POP [%d + REX]\n", node->left->value.var_num);
    else tree_to_asm(file_asm_code, node->right, all_var, all_func, flag, is_in_func);

    fprintf(file_asm_code, "POP [%d + REX]\n", node->right->value.var_num);
}


void asm_code_comma(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
{
    // КЛАДУ
    assert(node);

    // кладу в правильном порядке, достаю в другом

    fprintf(file_asm_code, "PUSH [%d + REX]\n", node->right->value.var_num);

    if (node->left->type == VARIABLE) fprintf(file_asm_code, "PUSH [%d + REX]\n", node->left->value.var_num);
    else tree_to_asm(file_asm_code, node->right, all_var, all_func, flag, is_in_func);
}



// void asm_code_endprog(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
// {
//     fprintf(file_asm_code, "\nHLT\n");
// }


void asm_code_main(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
{
    fprintf(file_asm_code, "PUSH 0 POP REX\n");
    
    tree_to_asm(file_asm_code, node->right, all_var, all_func, flag, is_in_func);
    fprintf(file_asm_code, "\nHLT\n\n\n");

    if (node->left != NULL) tree_to_asm(file_asm_code, node->left, all_var, all_func, flag, is_in_func);

}


void asm_code_return(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func)
{
    // fprintf(file_asm_code, "\nPOP RDX\n"); // ЗНАЧЕНИЕ ПРЫЖКА
    
    if (node->left != NULL) tree_to_asm(file_asm_code, node->left, all_var, all_func, flag, is_in_func);

    // fprintf(file_asm_code, "\nPOP REX ");  // ВЕРНУЛИ ЗНАЧЕНИЕ REX ???????????????????????????????????????????????????????????????????????????????????????????????????/

    tree_to_asm(file_asm_code, node->right, all_var, all_func, flag, is_in_func);

    fprintf(file_asm_code, "\nPUSH RCX POP REX\n"); // ВЕРНУЛИ ЗНАЧЕНИЕ REX

    fprintf(file_asm_code, "\nPUSH RDX\n"); // ЗНАЧЕНИЕ ПРЫЖКА

    fprintf(file_asm_code, "\nRET\n\n\n");

}