#include "calculate_trivial.h"

#include <stdlib.h>
#include <math.h>
#include "../tree_s__commands/free.h"


const double DELTA = 1e-5;


static bool is_null(Node* current_node);
static bool is_one (Node* current_node);

static void add_node_value(Node* node, Node* node2);
static void shift_subtree (Node* node, Node* needed_node);



static bool is_null(Node* current_node)
{
    if (current_node == NULL) return false;

    if ((current_node->type == NUMBER) && (fabs(current_node->value.num) < DELTA)) return true;
    return false;
}

static bool is_one(Node* current_node)
{
    if (current_node == NULL) return false;

    if ((current_node->type == NUMBER) && (fabs(current_node->value.num - 1) < DELTA)) return true;
    return false;
}

static void add_node_value(Node* node, Node* node2)
{
    if      (node->type == NUMBER)    node->value.num     = node2->value.num;
    else if (node->type == VARIABLE)  node->value.var_num = node2->value.var_num;
    else if (node->type == OPERATION) node->value.op_num  = node2->value.op_num;
}

static void shift_subtree(Node* node, Node* needed_node)
{
    Node* left  = node->left;
    Node* right = node->right;

    node->type = needed_node->type;
    add_node_value(node, needed_node);
    node->left  = needed_node->left;
    node->right = needed_node->right;

    free(left);
    free(right);
}



void calculate_triv_add(Node* node, int* diference)
{
    assert(node);


    if (is_null(node->left))
    {
        (*diference)++;

        shift_subtree(node, node->right);

        return;
    }

    else if (is_null(node->right))
    {
        (*diference)++;

        shift_subtree(node, node->left);

        return;
    }
}


void calculate_triv_sub(Node* node, int* diference)
{
    assert(node);


    if (is_null(node->right))
    {
        (*diference)++;

        shift_subtree(node, node->left);

        return;
    }


    return;
}


void calculate_triv_mul(Node* node, int* diference)
{
    assert(node);


    if (is_null(node->left) || is_null(node->right))
    {
        (*diference)++;

        free_tree(node->left);
        free_tree(node->right);

        node->type      = NUMBER;
        node->value.num = 0;
        node->left      = NULL;
        node->right     = NULL;

        return;
    }

    else if (is_one(node->left))
    {
        (*diference)++;

        shift_subtree(node, node->right);

        return;
    }

    else if (is_one(node->right))
    {
        (*diference)++;

        shift_subtree(node, node->left);

        return;
    }
}


void calculate_triv_div(Node* node, int* diference)
{
    assert(node);


    if (is_one(node->right))
    {
        (*diference)++;

        shift_subtree(node, node->left);

        return;
    }
}


void calculate_triv_sin(Node* node, int* diference)
{
    assert(node);


    if (is_null(node->right))
    {
        (*diference)++;

        free_tree(node->right);

        node->type      = NUMBER;
        node->value.num = 0;
        node->left      = NULL;
        node->right     = NULL;

        return;
    }
}


void calculate_triv_cos(Node* node, int* diference)
{
    assert(node);


    if (is_null(node->right))
    {
        (*diference)++;

        free_tree(node->right);

        node->type      = NUMBER;
        node->value.num = 1;
        node->left      = NULL;
        node->right     = NULL;

        return;
    }
}



void calculate_triv_ln(Node* node, int* diference)
{
    assert(node);


    if (is_one(node->right))
    {
        (*diference)++;

        free_tree(node->right);

        node->type      = NUMBER;
        node->value.num = 0;
        node->left      = NULL;
        node->right     = NULL;

        return;
    }
}


void calculate_triv_pow(Node* node, int* diference)
{
    assert(node);


    if (is_null(node->left))
    {
        (*diference)++;

        free_tree(node->left);
        free_tree(node->right);

        node->type      = NUMBER;
        node->value.num = 1;
        node->left      = NULL;
        node->right     = NULL;

        return;
    }
}
