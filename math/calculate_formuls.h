#ifndef CALCULATE_FORMULS
#define CALCULATE_FORMULS

#include "../language_h.h"


Elem_t calculate_add(Node* node1, Node* node2);
Elem_t calculate_sub(Node* node1, Node* node2);
Elem_t calculate_mul(Node* node1, Node* node2);
Elem_t calculate_div(Node* node1, Node* node2);
Elem_t calculate_sin(Node* node1, Node* node2);
Elem_t calculate_cos(Node* node1, Node* node2);
Elem_t calculate_ln (Node* node1, Node* node2);
Elem_t calculate_pow(Node* node1, Node* node2);

#endif

