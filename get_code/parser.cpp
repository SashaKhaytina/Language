#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "../tree_s__commands/tree_commands.h"
#include "../math/operations.h"


static Node* create_node_like_token(Token* token);
static void  check_symb_error      (AllOperations op, Tokens* tokens);


static Node* create_node_like_token(Token* token)
{
    if (token->type == NUMBER)    return _NUM(token->value.num);
    if (token->type == VARIABLE)  return _VAR(token->value.var_num);

    return create_new_node_op(OPERATION, token->value.op_num, NULL, NULL);
}


static void check_symb_error(AllOperations op, Tokens* tokens)
{
    if ((tokens->current_ind >= tokens->size) || (tokens->array[tokens->current_ind]->type != OPERATION) || (tokens->array[tokens->current_ind]->value.op_num != op)) // в Func эта проверка написана по-другому. Кажется, там неправильно
    {
        printf("ERROR SYNTAX. Want '");
        for (int i = 0; i < LEN_STRUCT_OP_ARR; i++)
        {
            if (op_arr[i].num == op)
            {
                printf("%s'\n", op_arr[i].name);
                break; 
            }
        }
    }
}


// (tokens->current_ind < tokens->size) - it is very sad. We can do operation '\n' like '$'. 
// And everywhere (tokens->current_ind < tokens->size)?


// Node* GetGraph(Tokens* tokens, VariableArr* all_var)
// {
//     assert(tokens);
//     assert(all_var);


//     Node* val = GetE_Addition(tokens, all_var);

//     // bool operation = (tokens->array[tokens->current_ind]->type == OPERATION);
//     // if ((tokens->array[tokens->current_ind]->type != OPERATION) || tokens->array[tokens->current_ind]->value.op_num != DOLL) // if node->type not DEFAULT
//     // {
//     //     printf("ERROR\n");
//     // }

//     return val;

// }

Node* GetIf(Tokens* tokens, VariableArr* all_var)
{
    assert(tokens);
    assert(all_var);

    // if ((tokens->array[tokens->current_ind]->type != OPERATION) || (tokens->array[tokens->current_ind]->value.op_num != IF)) // в Func эта проверка написана по-другому. Кажется, там неправильно
    //     printf("ERROR SYNTAX. Want 'if'\n");
    check_symb_error(IF, tokens);
    
    Node* op_tok = create_node_like_token(tokens->array[tokens->current_ind]);
    tokens->current_ind++;
    

    // if ((tokens->array[tokens->current_ind]->type != OPERATION) || (tokens->array[tokens->current_ind]->value.op_num != OPEN_SKOB)) // в Func эта проверка написана по-другому. Кажется, там неправильно
    //     printf("ERROR SYNTAX. Want '('\n");
    check_symb_error(OPEN_SKOB, tokens);
    tokens->current_ind++;


    Node* val_condition = GetE_Addition(tokens, all_var);


    // if ((tokens->array[tokens->current_ind]->type != OPERATION) || (tokens->array[tokens->current_ind]->value.op_num != CLOSE_SKOB)) // в Func эта проверка написана по-другому. Кажется, там неправильно
    //     printf("ERROR SYNTAX. Want ')'\n");
    check_symb_error(CLOSE_SKOB, tokens);
    tokens->current_ind++;


    // if ((tokens->array[tokens->current_ind]->type != OPERATION) || (tokens->array[tokens->current_ind]->value.op_num != F_OPEN_SKOB)) // в Func эта проверка написана по-другому. Кажется, там неправильно
    //     printf("ERROR SYNTAX. Want '{'\n");
    check_symb_error(F_OPEN_SKOB, tokens);
    tokens->current_ind++;

    Node* val_to_do = GetAssigm(tokens, all_var);

    // if ((tokens->current_ind >= tokens->size) || (tokens->array[tokens->current_ind]->type != OPERATION) || (tokens->array[tokens->current_ind]->value.op_num != F_CLOSE_SKOB)) // в Func эта проверка написана по-другому. Кажется, там неправильно
    //     printf("ERROR SYNTAX. Want '}'\n");
    check_symb_error(F_CLOSE_SKOB, tokens);
    tokens->current_ind++;

    
    op_tok->left = val_condition;
    op_tok->right = val_to_do;
    // val = op_tok;

    return op_tok;

}




Node* GetAssigm(Tokens* tokens, VariableArr* all_var)
{
    assert(tokens);
    assert(all_var);

    Node* val_var = GetVariable(tokens, all_var);

    if ((tokens->array[tokens->current_ind]->type != OPERATION) || (tokens->array[tokens->current_ind]->value.op_num != ASSIGM)) // в Func эта проверка написана по-другому. Кажется, там неправильно
        printf("ERROR SYNTAX. Want '='\n");
    
    Node* op_tok = create_node_like_token(tokens->array[tokens->current_ind]);
    tokens->current_ind++;


    Node* val = GetE_Addition(tokens, all_var);

    op_tok->left = val_var;
    op_tok->right = val;
    // val = op_tok;

    return op_tok;

}







Node* GetNumber(Tokens* tokens) 
{
    assert(tokens);


    if (tokens->array[tokens->current_ind]->type == NUMBER) 
    {
        tokens->current_ind++; 
        return create_node_like_token(tokens->array[tokens->current_ind - 1]);
    }
    printf("ERROR SYNTAX. want num in %d tokens\n", tokens->current_ind); // position will be better!
    return NULL;
}


Node* GetE_Addition(Tokens* tokens, VariableArr* all_var) 
{
    assert(tokens);
    assert(all_var);


    Node* val = GetT_Multiplication(tokens, all_var);

    while ((tokens->current_ind < tokens->size) 
            &&
            ((tokens->array[tokens->current_ind]->type == OPERATION) && 
            ((tokens->array[tokens->current_ind]->value.op_num == ADD) || 
             (tokens->array[tokens->current_ind]->value.op_num == SUB))))
    {
        Node* op_tok = create_node_like_token(tokens->array[tokens->current_ind]);
        tokens->current_ind++;

        Node* val2 = GetT_Multiplication(tokens, all_var);

        op_tok->left = val;
        op_tok->right = val2;
        val = op_tok;
    }

    return val;
}


Node* GetT_Multiplication(Tokens* tokens, VariableArr* all_var) 
{
    assert(tokens);
    assert(all_var);


    Node* val = GetP_Pow(tokens, all_var);

    while ((tokens->current_ind < tokens->size)                        
            &&
           ((tokens->array[tokens->current_ind]->type == OPERATION)  && 
          ((tokens->array[tokens->current_ind]->value.op_num == MUL) || 
           (tokens->array[tokens->current_ind]->value.op_num == DIV))))
    {
        Node* op_tok = create_node_like_token(tokens->array[tokens->current_ind]);
        tokens->current_ind++;

        Node* val2 = GetP_Pow(tokens, all_var);

        op_tok->left = val;
        op_tok->right = val2;
        val = op_tok;

    }

    return val;
}




Node* GetP_Pow(Tokens* tokens, VariableArr* all_var)
{
    assert(tokens);
    assert(all_var); 


    Node* val = Get_Heaviest_Oper(tokens, all_var);

    while ((tokens->current_ind < tokens->size)                       
            &&
            tokens->array[tokens->current_ind]->type == OPERATION && 
            tokens->array[tokens->current_ind]->value.op_num == POW)
    {
        Node* op_tok = create_node_like_token(tokens->array[tokens->current_ind]);
        tokens->current_ind++;

        Node* val2 = Get_Heaviest_Oper(tokens, all_var);
        
        
        op_tok->left = val;
        op_tok->right = val2;
        val = op_tok;           // A^B^C = (A^B)^C
    }

    return val;
}




Node* Get_Heaviest_Oper(Tokens* tokens, VariableArr* all_var)
{
    assert(tokens);
    assert(all_var); 


    if ((tokens->array[tokens->current_ind]->type == OPERATION))
    {
        if (tokens->array[tokens->current_ind]->value.op_num == OPEN_SKOB) 
        {
            tokens->current_ind++;
            Node* val = GetE_Addition(tokens, all_var);
            
            if ((tokens->array[tokens->current_ind]->type == OPERATION) && 
                (tokens->array[tokens->current_ind]->value.op_num != CLOSE_SKOB)) 
                printf("ERROR SYNTAX. Want ')'\n"); 

            tokens->current_ind++;


            return val;

        }
        else
        {
            Node* val = GetF_Function_one_arg(tokens, all_var);
            if (val != NULL) return val;
        }
    }
    
    else if (tokens->array[tokens->current_ind]->type == VARIABLE) return GetVariable(tokens, all_var);
    else                                                           return GetNumber(tokens);
    return NULL;
}


Node* GetF_Function_one_arg(Tokens* tokens, VariableArr* all_var) 
{

    // Так как тут будет прием еще собственных (написанных) функций, то надо будет сделать функцию, которая по кол-ву аргументов делает эту "запись" (в дерево). 
    // (И тогда для каждой функции храним кол-во аргументов)
    assert(tokens);
    assert(all_var);


    if ((tokens->array[tokens->current_ind]->value.op_num == SIN) || 
        (tokens->array[tokens->current_ind]->value.op_num == COS) || 
        (tokens->array[tokens->current_ind]->value.op_num == LN))
    {

        Node* op_tok = create_node_like_token(tokens->array[tokens->current_ind]);
        tokens->current_ind++;

        if ((tokens->array[tokens->current_ind]->type == OPERATION) && 
            (tokens->array[tokens->current_ind]->value.op_num != OPEN_SKOB)) 
            printf("ERROR SYNTAX. Want '('\n");
        tokens->current_ind++;

        Node* val = GetE_Addition(tokens, all_var); 

        if ((tokens->array[tokens->current_ind]->type == OPERATION) && 
            (tokens->array[tokens->current_ind]->value.op_num != CLOSE_SKOB)) 
            printf("ERROR SYNTAX. Want ')'\n");
        tokens->current_ind++;


        op_tok->left = NULL; 
        op_tok->right = val;

        return op_tok;

    }

    return NULL;
}


Node* GetVariable(Tokens* tokens, VariableArr* all_var) 
{
    assert(tokens);
    assert(all_var);


    if (tokens->array[tokens->current_ind]->type == VARIABLE) 
    {
        tokens->current_ind++; 
        return create_node_like_token(tokens->array[tokens->current_ind - 1]);
    }
    printf("ERROR SYNTAX. Want var\n");
    return NULL; 
}



// void print_node_now(Node* cur_node, VariableArr* all_var)
// {
//     assert(cur_node);
//     if (cur_node->type == NUMBER) printf("%d\n", cur_node->value.num);
//     if (cur_node->type == VARIABLE) printf("%s\n", all_var->arr[cur_node->value.var_num - 1].name);
//     if (cur_node->type == OPERATION) printf("%s\n", op_arr[cur_node->value.op_num].name);
//     // printf("TOKEN[%d] (Node) = {%d - type, %d - value}\n", i, tokens->array[i].type, tokens->array[i].value);
// }



