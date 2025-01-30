#include "language_h.h"
#include "dump/for_dump.h"
#include "get_code/input_tree.h"
#include "get_code/token.h"
#include "tree_s__commands/free.h"
#include "tree_s__commands/tree_commands.h"

#include "backend/create_asm_code.h"

#include "math/operations.h"



void print_tree(Node* node, VariableArr* all_var, FunctionsArr* all_func);
void print_node(Node* node, VariableArr* all_var, FunctionsArr* all_func);



int main()
{
    FILE* file = fopen(FILE_CODE, "r");
    Tree tree = {};

    ForDump dumps_counter = 0;

    VariableArr  all_var  = {};
    FunctionsArr all_func = {};

    Tokens tokens = {};


    get_tree(file, &tree, &all_var, &all_func, &tokens);

    print_node(tree.root, &all_var, &all_func);
    printf("\n");

    print_tree(tree.root, &all_var, &all_func);
    printf("\n");

    dump(tree.root, &dumps_counter, &all_var, &all_func);

    // SOLVE - other file!

    solve(tree.root);
    dump(tree.root, &dumps_counter, &all_var, &all_func);
    print_tree(tree.root, &all_var, &all_func);
    printf("\n");



    // create_file_tree(&tree, &all_var);

    // fclose(file);





    // TO ASM!!!!!!!!

    // FILE* file_asm_code = fopen(FILE_ASM_CODE, "w");

    // int flag = 0;
    
    // tree_to_asm(file_asm_code, tree.root, &all_var, &flag);
    // fprintf(file_asm_code, "\nHLT\n");







    // free_tree(tree.root);
    // free_tokens(&tokens);

    // free_val(&all_var);
}





void print_tree(Node* node, VariableArr* all_var, FunctionsArr* all_func)
{   
    if (node == NULL) return;

    if (node->type != OPERATION) print_node(node, all_var, all_func);
    else
    {
        printf("(");
        print_tree(node->left, all_var, all_func);


        print_node(node, all_var, all_func);

        print_tree(node->right, all_var, all_func);
        printf(")");
    }
}




void print_node(Node* node, VariableArr* all_var, FunctionsArr* all_func)
{
    switch (node->type)
    {
    case NUMBER:
    {
        printf("%g", node->value.num);
        break;
    }

    case VARIABLE:
    {
        for (int i = 0; i < all_var->size; i++) 
        {
            if (all_var->arr[i].num == node->value.var_num) { printf("%s", all_var->arr[i].name); break; }
        }
        break;
    }

    case OPERATION:
    {
        for (int i = 0; i < LEN_STRUCT_OP_ARR; i++)
        {
            if (op_arr[i].num == node->value.op_num) { printf("%s", op_arr[i].name); break; }
        }
        break;
    }

    case CREATED_FUNC:
    {
        for (int i = 0; i < all_func->size; i++) 
        {
            if (all_func->arr[i].num == node->value.func_num) { printf("%s", all_func->arr[i].name); break; }
        }
        break;
    }

    default:
    {
        printf("ERROR type node\n");
        break;
    }
    }
}
