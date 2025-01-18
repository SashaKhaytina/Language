#include "free.h"

#include <stdio.h>
#include <stdlib.h>

void free_tree(Node* node)
{
    assert(node);

    if (node->left  != NULL) { free_tree(node->left);  node->left  = NULL; }
    if (node->right != NULL) { free_tree(node->right); node->right = NULL; }

    free(node);    
}


void free_val(VariableArr* all_var)
{
    for (size_t i = 0; i < all_var->size; i++)
    {
        free(all_var->arr[i].name); all_var->arr[i].name = NULL;
    }
}


void free_tokens(Tokens* tokens)
{
    free(tokens->array); tokens->array = NULL;
}


void free_needless_tokens(Tokens* tokens)
{
    for (size_t i = 0; i < tokens->size; i++)
    {
        // if (tokens->array[i]->type == OPERATION && (tokens->array[i]->value.op_num == OPEN_SKOB || tokens->array[i]->value.op_num == CLOSE_SKOB))
        // {
        //     free((tokens->array[i])); tokens->array[i] = NULL;
        // }
        free((tokens->array[i])); tokens->array[i] = NULL;
    }
}
