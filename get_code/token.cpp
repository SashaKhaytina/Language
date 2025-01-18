#include "token.h"

#include <malloc.h>
#include <ctype.h>
#include <string.h>

#include "../tree_s__commands/tree_commands.h"


const int NO_THIS_VAR = -1;


static void pass_spaces       (int* point_current_letter, char* arr_file_tree);
static void get_word          (int* current_symbol, char* arr_file_tree, Tokens* tokens, VariableArr* all_var);
static void get_num           (int* current_symbol, char* arr_file_tree, Tokens* tokens);
static void get_oper          (int* current_symbol, char* arr_file_tree, Tokens* tokens);
static bool find_and_create_op(Tokens* tokens, char* name);



static void pass_spaces(int* point_current_letter, char* arr_file_tree)
{
    while ((arr_file_tree[*point_current_letter] == '\t') || (arr_file_tree[*point_current_letter] == '\n') || (arr_file_tree[*point_current_letter] == ' ')) *point_current_letter += 1;
}



static void get_num(int* current_symbol, char* arr_file_tree, Tokens* tokens)
{
    Elem_t val_num = 0;

    sscanf(arr_file_tree + *current_symbol, "%lg", &val_num);

    bool not_was_point = true;
    while (isdigit(arr_file_tree[*current_symbol]) != 0 || arr_file_tree[*current_symbol] == '.')
    {
        if (arr_file_tree[*current_symbol] == '.')
        {
            if (not_was_point) not_was_point = false;
            else               printf("ERROR NUMBER");
        }
        (*current_symbol)++;
    }

    tokens->array[tokens->size] = _NUM_T(val_num);
    tokens->size++;

}


static void get_word(int* current_symbol, char* arr_file_tree, Tokens* tokens, VariableArr* all_var)
{
    int len_word = 0;
    char temporary_name[MAX_NAME_IDENT_SIZE] = {};

    while (isalpha(arr_file_tree[*current_symbol]) != 0)
    {
        temporary_name[len_word] = arr_file_tree[*current_symbol]; 
        len_word++;
        (*current_symbol)++;
    }

    char* name = (char*) calloc((size_t)(len_word + 1), sizeof(char));
    strcpy(name, temporary_name);

    bool is_oper = find_and_create_op(tokens, name);


    if (!is_oper)    // It is Variable 
    {

        int num_var = find_variable(name, all_var);
        if  (num_var == NO_THIS_VAR) num_var = insert_new_variable(name, all_var);

        tokens->array[tokens->size] = _VAR_T(num_var);
        tokens->size++;

    }
    else
    {
        free(name);
    }

}


static void get_oper(int* current_symbol, char* arr_file_tree, Tokens* tokens)
{
    // cycle while (NO num, NO letter, NO space ) (becouse op - no 1 symbol)
    char op[MAX_OPER_SYMBOLS_SIZE] = {};   
    op[0] = arr_file_tree[*current_symbol];
    (*current_symbol)++;

    bool is_oper = find_and_create_op(tokens, op);

    if (!is_oper) printf("SYNTAX ERROR\n");
}




void init_token(Tokens* tokens, size_t len_text)
{
    tokens->array = (Token**) calloc(len_text, sizeof(Token*));
    tokens->size = 0;
    tokens->current_ind = 0;
}


void get_token(Tokens* tokens, char* arr_file_tree, VariableArr* all_var)
{
    int current_symbol = 0;

    // while (arr_file_tree[current_symbol] != '\0') // see parser.cpp
    while (arr_file_tree[current_symbol] != '\n')
    {
        pass_spaces(&current_symbol, arr_file_tree);

        if      (isdigit(arr_file_tree[current_symbol]) != 0)
        {
            get_num(&current_symbol, arr_file_tree, tokens);
        }
        else if (isalpha(arr_file_tree[current_symbol]) != 0)
        {
            get_word(&current_symbol, arr_file_tree, tokens, all_var);
        }
        else
        {
            get_oper(&current_symbol, arr_file_tree, tokens);
        }
    }
}




int find_variable(char* var_name, VariableArr* all_var)
{
    for (size_t i = 0; i < all_var->size; i++)
    {
        if (strcmp(all_var->arr[i].name, var_name) == 0) 
        { 
            free(var_name);
            return all_var->arr[i].num; 
        }
    }

    return NO_THIS_VAR; 
}


int insert_new_variable(char* var_name, VariableArr* all_var)
{
    all_var->size++;

    all_var->arr[all_var->size - 1].num = (int)all_var->size;
    all_var->arr[all_var->size - 1].name = var_name;

    return (int)all_var->size;
}


static bool find_and_create_op(Tokens* tokens, char* name)
{
    bool is_oper = false;

    for (int i = 0; i < LEN_STRUCT_OP_ARR; i++)
    {
        if (strcmp(op_arr[i].name, name) == 0)
        {
            tokens->array[tokens->size] = create_new_token_op(OPERATION, op_arr[i].num);
            tokens->size++;

            is_oper = true;

            break; 
        }
    }

    return is_oper;
}


void print_token(Tokens* tokens, VariableArr* all_var)
{
    for (size_t i = 0; i < tokens->size; i++)
    {
        if (tokens->array[i]->type == NUMBER)    printf("%lg", tokens->array[i]->value.num);
        if (tokens->array[i]->type == VARIABLE)  printf("%s", all_var->arr[tokens->array[i]->value.var_num - 1].name);
        if (tokens->array[i]->type == OPERATION) printf("%s", op_arr[tokens->array[i]->value.op_num].name);
    }
}













Token* create_new_token_num(TypeNode type, Elem_t num)
{
    Token* token = (Token*) calloc(1, sizeof(Token));

    token->type      = NUMBER;
    token->value.num = num;

    return token;
}


Token* create_new_token_var(TypeNode type, int var_num)
{
    Token* token = (Token*) calloc(1, sizeof(Token));

    token->type          = VARIABLE;
    token->value.var_num = var_num;

    return token;
}


Token* create_new_token_op(TypeNode type, AllOperations op_num)
{
    Token* token = (Token*) calloc(1, sizeof(Token));

    token->type         = OPERATION;
    token->value.op_num = op_num;

    return token;
}








// void print_token(Tokens* tokens, VariableArr* all_var)
// {
//     for (size_t i = 0; i < tokens->size; i++)
//     {
//         if (tokens->array[i]->type == NUMBER)    printf("%lg", tokens->array[i]->value.num);
//         if (tokens->array[i]->type == VARIABLE)  printf("%s", all_var->arr[tokens->array[i]->value.var_num - 1].name);
//         if (tokens->array[i]->type == OPERATION) printf("%s", op_arr[tokens->array[i]->value.op_num].name);
//     }
// }
