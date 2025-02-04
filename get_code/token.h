#ifndef TOKEN
#define TOKEN

#include "../language_h.h"

#define _NUM_T(num) create_new_token_num(NUMBER,    num)
#define _VAR_T(num) create_new_token_var(VARIABLE,  num)
#define _OP_T (num) create_new_token_op (OPERATION, num)

struct Token
{
    TypeNode type;
    Value    value;
};

struct Tokens
{
    Token** array;
    size_t size; 
    size_t current_ind;
};

int find_variable      (char* var_name, VariableArr* all_var);
int insert_new_variable(char* var_name, VariableArr* all_var);

void get_token  (Tokens* tokens, char* arr_file_tree, VariableArr* all_var);
void print_token(Tokens* tokens, VariableArr* all_var);
void init_token (Tokens* tokens, size_t len_text);

Token* create_new_token_num(TypeNode type, Elem_t num);
Token* create_new_token_var(TypeNode type, int var_num);
Token* create_new_token_op (TypeNode type, AllOperations op_num);


#endif
