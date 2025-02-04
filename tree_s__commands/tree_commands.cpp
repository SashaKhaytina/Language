#include "tree_commands.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "../math/operations.h"


static void print_tree_in_file(FILE* file, Node* node, size_t deep, VariableArr* all_var, FunctionsArr* all_func);
static void fprint_node       (FILE* file, Node* node, VariableArr* all_var, FunctionsArr* all_func);




Node* create_new_node_num(TypeNode type, Elem_t num, Node* left, Node* right)
{
    Node* new_node = (Node*) calloc(1, sizeof(Node));

    new_node->type      = NUMBER;
    new_node->value.num = num;
    new_node->left      = left;
    new_node->right     = right;

    return new_node;
}


Node* create_new_node_var(TypeNode type, int var_num, Node* left, Node* right)
{
    Node* new_node = (Node*) calloc(1, sizeof(Node));

    new_node->type          = VARIABLE;
    new_node->value.var_num = var_num;
    new_node->left          = left;
    new_node->right         = right;

    return new_node;
}


Node* create_new_node_op(TypeNode type, AllOperations op_num, Node* left, Node* right)
{
    Node* new_node = (Node*) calloc(1, sizeof(Node));

    new_node->type         = OPERATION;
    new_node->value.op_num = op_num;
    new_node->left         = left;
    new_node->right        = right;

    return new_node;
}


Node* create_new_node_func(TypeNode type, int func_num, Node* left, Node* right)
{
    Node* new_node = (Node*) calloc(1, sizeof(Node));

    new_node->type           = CREATED_FUNC;
    new_node->value.func_num = func_num;
    new_node->left           = left;
    new_node->right          = right;

    return new_node;
}





TypeNode solve_subtree(Node* current_node, int* diference)
{
    if (current_node == NULL) return DEFAULT;
    if (current_node->type == OPERATION)
    {
        bool is_null = (current_node->left == NULL);

        bool condition_left  = (is_null || (solve_subtree(current_node->left, diference) == NUMBER));
        bool condition_right = (solve_subtree(current_node->right, diference) == NUMBER);

        if (condition_left && condition_right)
        {
            bool is_changed = false;
            for (int i = 0; i < LEN_STRUCT_OP_ARR; i++)
            {
                if (op_arr[i].num == current_node->value.op_num)
                {
                    if (op_arr[i].calculate == NULL) break;
                    current_node->value.num = op_arr[i].calculate(current_node->left, current_node->right);
                    is_changed = true;
                    break;
                }
            }

            if (is_changed)
            {
                current_node->type = NUMBER;
                current_node->left = NULL;
                current_node->right = NULL;

                (*diference)++;
            }
        }
    }

    else if (current_node->type == CREATED_FUNC || current_node->type == CALL_FUNC)
    {
        solve_subtree(current_node->left,  diference);
        solve_subtree(current_node->right, diference);
    }

    return current_node->type;
}





void trivial_solver(Node* current_node, int* diference)
{
    if (current_node == NULL) return;

    trivial_solver(current_node->left, diference);
    trivial_solver(current_node->right, diference);

    if (current_node->type == OPERATION)
    {
        for (int i = 0; i < LEN_STRUCT_OP_ARR; i++)
        {
            if (op_arr[i].num == current_node->value.op_num)
            {
                if (op_arr[i].triv_calculate == NULL) break;
                op_arr[i].triv_calculate(current_node, diference);
                break;
            }
        }
    }
}


void solve(Node* current_node)
{
    int diference = 1;
    while (diference != 0)
    {
        diference = 0;
        
        trivial_solver(current_node, &diference);

        solve_subtree(current_node, &diference);
    }

}




















// Написать нормально вывод в файл. 

// void create_file_tree(Tree* tree, VariableArr* all_var, FunctionsArr* all_func)
// {
//     FILE* file = fopen(FILE_TREE, "w");

//     print_tree_in_file(file, tree->root, 0, all_var, all_func);

//     fclose(file);
// }


static void print_tree_in_file(FILE* file, Node* node, size_t deep, VariableArr* all_var, FunctionsArr* all_func)
{   
    char tabs[MAX_DEEP_TREE] = {};
    for (size_t i = 0; i < deep; i++) tabs[i] = '\t';
    
    if (node == NULL) return;

    fprintf(file, "%s{", tabs);
    fprint_node(file, node, all_var, all_func);
    fprintf(file, "\n");

    print_tree_in_file(file, node->left, deep + 1, all_var, all_func);
    print_tree_in_file(file, node->right, deep + 1, all_var, all_func);
    fprintf(file, "%s}\n", tabs);
}





static void fprint_node(FILE* file, Node* node, VariableArr* all_var, FunctionsArr* all_func)
{
    switch (node->type)
    {
    case NUMBER:
    {
        fprintf(file, "%g", node->value.num);
        break;
    }

    case VARIABLE:
    {
        for (int i = 0; i < all_var->size; i++) 
        {
            if (all_var->arr[i].num == node->value.var_num) { fprintf(file, "%s", all_var->arr[i].name); break; }
        }
        break;
    }

    case OPERATION:
    {
        for (int i = 0; i < LEN_STRUCT_OP_ARR; i++)
        {
            if (op_arr[i].num == node->value.op_num) { fprintf(file, "%s", op_arr[i].name); break; }
        }
        break;
    }
    
    case CREATED_FUNC: case CALL_FUNC:
    {
        for (int i = 0; i < all_func->size; i++) 
        {
            if (all_func->arr[i].num == node->value.func_num) { fprintf(file, "%s", all_func->arr[i].name); break; }
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