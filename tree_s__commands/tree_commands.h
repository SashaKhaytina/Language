#ifndef TREE_COMMANDS
#define TREE_COMMANDS

#include "../language_h.h"



#define _LEFT  current_node->left
#define _RIGHT current_node->right

#define _NUM(num)         create_new_node_num (NUMBER,    num,      NULL, NULL)
#define _VAR(var_num)     create_new_node_var (VARIABLE,  var_num,  NULL, NULL)
#define _FUN(var_num)     create_new_node_func(VARIABLE,  var_num,  NULL, NULL)


#define _ADD(left, right) create_new_node_op (OPERATION, ADD, left, right)
#define _SUB(left, right) create_new_node_op (OPERATION, SUB, left, right)
#define _MUL(left, right) create_new_node_op (OPERATION, MUL, left, right)
#define _DIV(left, right) create_new_node_op (OPERATION, DIV, left, right)
#define _POW(left, right) create_new_node_op (OPERATION, POW, left, right)
#define _SIN(arg)         create_new_node_op (OPERATION, SIN, NULL, arg)
#define _COS(arg)         create_new_node_op (OPERATION, COS, NULL, arg)
#define  _LN(arg)         create_new_node_op (OPERATION, LN,  NULL, arg)

#define _DIFF(arg)        diff       (arg, file, all_var)
#define _COPY(arg)        copy_branch(arg)


const int MAX_DEEP_TREE = 10000;



Node* create_new_node_num (TypeNode type, Elem_t num,           Node* left, Node* right); 
Node* create_new_node_var (TypeNode type, int var_num,          Node* left, Node* right); 
Node* create_new_node_op  (TypeNode type, AllOperations op_num, Node* left, Node* right); 
Node* create_new_node_func(TypeNode type, int func_num,         Node* left, Node* right);


void solve(Node* current_node);

TypeNode solve_subtree (Node* current_node, int* diference); 
void     trivial_solver(Node* current_node, int* diference);


// void create_file_tree(Tree* tree, VariableArr* all_var, FunctionsArr* all_func);


#endif
