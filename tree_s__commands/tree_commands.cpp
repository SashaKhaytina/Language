#include "tree_commands.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "../math/operations.h"





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
            for (int i = 0; i < LEN_STRUCT_OP_ARR; i++)
            {
                if (op_arr[i].num == current_node->value.op_num)
                {
                    if (op_arr[i].calculate == NULL) break;
                    current_node->value.num = op_arr[i].calculate(current_node->left, current_node->right);
                    break;
                }
            }

            current_node->type = NUMBER;
            current_node->left = NULL;
            current_node->right = NULL;

            (*diference)++;
        }
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

