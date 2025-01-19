#include "calculate_formuls.h"

#include <math.h>
#include "../tree_s__commands/free.h"



Elem_t calculate_add(Node* node1, Node* node2)
{
    assert(node1);
    assert(node2);


    Elem_t val = node1->value.num + node2->value.num;

    free_tree(node1); // this is num. What is better to use here (free or free_tree)? (free_tree better for debug maybe)
    free_tree(node2);

    return val;
}


Elem_t calculate_sub(Node* node1, Node* node2)
{
    assert(node1);
    assert(node2);

    Elem_t val = node1->value.num - node2->value.num;

    free_tree(node1);
    free_tree(node2);

    return val;
}


Elem_t calculate_mul(Node* node1, Node* node2)
{
    assert(node1);
    assert(node2);

    Elem_t val = node1->value.num * node2->value.num;

    free_tree(node1);
    free_tree(node2);

    return val;
}


Elem_t calculate_div(Node* node1, Node* node2)
{
    assert(node1);
    assert(node2);
    
    Elem_t val = node1->value.num / node2->value.num;

    free_tree(node1);
    free_tree(node2);

    return val;
}


Elem_t calculate_sin(Node* node1, Node* node2)
{
    assert(!node1); // NULL
    assert(node2);

    Elem_t val = sin((double) node2->value.num);

    free_tree(node2);

    return val;
}


Elem_t calculate_cos(Node* node1, Node* node2)
{
    assert(!node1); // NULL
    assert(node2);

    Elem_t val = cos((double) node2->value.num);

    free_tree(node2);

    return val;
}


Elem_t calculate_pow(Node* node1, Node* node2)
{
    assert(node1);
    assert(node2);

    Elem_t val = pow((double) node1->value.num, (double) node2->value.num);

    free_tree(node1);
    free_tree(node2);

    return val;
}


Elem_t calculate_ln(Node* node1, Node* node2)
{
    assert(!node1); // NULL
    assert(node2);

    Elem_t val = log((double) node2->value.num);

    free_tree(node2);

    return val;
}

