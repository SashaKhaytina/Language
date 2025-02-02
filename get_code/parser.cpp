#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "../tree_s__commands/tree_commands.h"
#include "../math/operations.h"



#define CHECK(op) ((tokens->current_ind < tokens->size) && (tokens->array[tokens->current_ind]->type == OPERATION) && (tokens->array[tokens->current_ind]->value.op_num == op))



static Node* create_node_like_token(Token* token);
static void  check_symb_error      (AllOperations op, Tokens* tokens);
static int   insert_new_func       (Node* node, VariableArr* all_var, FunctionsArr* all_func, int* num_args);
static char* find_name_var         (int var_num, VariableArr* all_var);





static Node* create_node_like_token(Token* token)
{
    if (token->type == NUMBER)       return _NUM(token->value.num);
    if (token->type == VARIABLE)     return _VAR(token->value.var_num);
    if (token->type == CREATED_FUNC) return _FUN(token->value.func_num);

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
                printf("%s' ", op_arr[i].name);
                break; 
            }
        }
        printf("// %d - token\n", tokens->current_ind);
    }
}


static char* find_name_var(int var_num, VariableArr* all_var)
{
    for (size_t i = 0; i < all_var->size; i++)
    {
        if (all_var->arr[i].num == var_num) return all_var->arr[i].name;
    }
}














// (tokens->current_ind < tokens->size) - it is very sad. We can do operation '\n' like '$'. 
// And everywhere (tokens->current_ind < tokens->size)?


Node* GetGraph(Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func)
{
    assert(tokens);
    assert(all_var);


    // Node* val = GetChain(tokens, all_var);
    // Node* val = Get_Created_Func(tokens, all_var, all_func);
    Node* val_func = Get_Chain_Func(tokens, all_var, all_func);

    check_symb_error(MAIN, tokens);
    Node* main_proc = create_node_like_token(tokens->array[tokens->current_ind]);
    tokens->current_ind++;

    Node* val = GetChain(tokens, all_var, all_func);


    check_symb_error(END_PROG, tokens);
    tokens->current_ind++;

    main_proc->left  = val_func;
    main_proc->right = val;


    // bool operation = (tokens->array[tokens->current_ind]->type == OPERATION);
    // if ((tokens->array[tokens->current_ind]->type != OPERATION) || tokens->array[tokens->current_ind]->value.op_num != DOLL) // if node->type not DEFAULT
    // {
    //     printf("ERROR\n");
    // }

    return main_proc;

}





Node* Get_Chain_Func(Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func)
{
    Node* main_proc  = NULL;
    Node* chain_func = NULL;

    bool is_first_func = true;

    while (CHECK(FUNC))
    {
        // printf("YES func\n");
        Node* val = Get_Created_Func(tokens, all_var, all_func);
        
        check_symb_error(SPLIT, tokens);
        if (is_first_func)
        {
            chain_func = create_node_like_token(tokens->array[tokens->current_ind]);
            tokens->current_ind++;
        }
        else
        {
            chain_func->right = create_node_like_token(tokens->array[tokens->current_ind]);
            tokens->current_ind++;
            chain_func = chain_func->right;
        }

        if (is_first_func)
        {
            main_proc = chain_func;
            is_first_func = false;
        }

        chain_func->left = val;
        // chain_func = chain_func->right;

    }

    return main_proc;
}




Node* Get_Created_Func(Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func)
{
    assert(tokens);
    assert(all_var);

    // printf("CREATED_FUNC\n");


    check_symb_error(FUNC, tokens);
    tokens->current_ind++;
    // printf("func\n");

    Node* op_tok = GetVariable(tokens, all_var);

    // Node* new_func = create_node_like_token();
    // Node* new_func = {};
    
    // new_func->type = CREATED_FUNC;
    // new_func->left  = NULL;
    // new_func->right = NULL;

    op_tok->type = CREATED_FUNC;
    // printf("OK1\n");


    check_symb_error(OPEN_SKOB, tokens);
    tokens->current_ind++;
    // printf("(\n");

    int num_args = 0;

    Node* args = NULL;

    if (tokens->array[tokens->current_ind]->type == VARIABLE)
    {
        // Тут же по-хорошему другие переменные!???????????
        // Node* arg_now = GetVariable(tokens, all_var);
        // num_args++;

        // Node* now_node = {};
        // Node* arg_2 = {};

        // while (CHECK(COMMA))
        // {
        //     now_node = create_node_like_token(tokens->array[tokens->current_ind]);
            
        //     arg_2 = GetVariable(tokens, all_var);
        //     num_args++;


        //     now_node->left = arg_now;
        //     arg_now = arg_2;
        // }

        // now_node->right = arg_2;

        args = Get_Args(tokens, all_var, &num_args);
    }

    op_tok->value.func_num = insert_new_func(op_tok, all_var, all_func, &num_args);


    check_symb_error(CLOSE_SKOB, tokens);
    tokens->current_ind++;
    // printf(")\n");

    check_symb_error(F_OPEN_SKOB, tokens);
    tokens->current_ind++;
    // printf("{\n");

    Node* body = GetChain(tokens, all_var, all_func);

    Node* ret  = Get_Return(tokens, all_var, all_func);
    ret->left = body;

    check_symb_error(F_CLOSE_SKOB, tokens);
    tokens->current_ind++;
    // printf("}\n");


    // Тут нет проверки того, что эта функция уже не была создана!

    // op_tok->value.func_num = insert_new_func(op_tok, all_var, all_func, &num_args);
    // printf("OK func_num\n");
    op_tok->left  = args;
    // printf("OK left\n");
    op_tok->right = ret;
    // printf("OK right\n");


    return op_tok;


}


Node* Get_Return(Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func)
{
    check_symb_error(RETURN, tokens);
    
    Node* op_tok = create_node_like_token(tokens->array[tokens->current_ind]);
    tokens->current_ind++;

    Node* val = GetE_Addition(tokens, all_var, all_func);

    check_symb_error(SPLIT, tokens);
    tokens->current_ind++;

    op_tok->right = val;

    return op_tok;

}






Node* Get_Args(Tokens* tokens, VariableArr* all_var, int* num_args)
{
    // Тут же по-хорошему другие переменные!???????????
    Node* arg_now = GetVariable(tokens, all_var);
    (*num_args)++;

    while (CHECK(POINTCOMMA))
    {
        Node* now_node = create_node_like_token(tokens->array[tokens->current_ind]);
        tokens->current_ind++;
        
        Node* arg_2 = GetVariable(tokens, all_var);
        (*num_args)++;


        now_node->left = arg_now;
        now_node->right = arg_2;
        arg_now = now_node;
    }

    return arg_now;
}















static int insert_new_func(Node* node, VariableArr* all_var, FunctionsArr* all_func, int* num_args)
{
    all_func->size++;

    for (size_t i = 0; i < all_var->size; i++)
    {
        if (all_var->arr[i].num == node->value.var_num) 
        { 
            all_func->arr[all_func->size - 1].name = all_var->arr[i].name;
            // all_var->arr[i].num = -1; // Что тут делать? По сути я не убираю имя функции из списка переменных  ЭТО ДЕЛАТЬ НЕЛЬЗЯ, ИНАЧЕ СЛОМАЕТСЯ  heav_op (где ищем номер)
            break; 
        }
    }
    all_func->arr[all_func->size - 1].num = all_func->size;
    all_func->arr[all_func->size - 1].num_args = *num_args;

    return all_func->size;

}























































// int find_function(char* func_name, FunctionsArr* all_func)
// {
//     for (size_t i = 0; i < all_func->size; i++)
//     {
//         if (strcmp(all_func->arr[i].name, func_name) == 0) 
//         { 
//             free(func_name);
//             return all_func->arr[i].num; 
//         }
//     }

//     return NO_THIS_VAR; 
// }


// int insert_new_variable(char* var_name, VariableArr* all_var)
// {
//     all_var->size++;

//     all_var->arr[all_var->size - 1].num = (int)all_var->size;
//     all_var->arr[all_var->size - 1].name = var_name;

//     return (int)all_var->size;
// }





























































































































Node* GetIf(Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func)
{
    assert(tokens);
    assert(all_var);


    check_symb_error(IF, tokens);
    
    Node* op_tok = create_node_like_token(tokens->array[tokens->current_ind]);
    tokens->current_ind++;
    

    check_symb_error(OPEN_SKOB, tokens);
    tokens->current_ind++;


    // Node* val_condition = GetE_Addition(tokens, all_var);
    Node* val_condition = GetCompare(tokens, all_var, all_func);



    check_symb_error(CLOSE_SKOB, tokens);
    tokens->current_ind++;

    check_symb_error(F_OPEN_SKOB, tokens);
    tokens->current_ind++;


    Node* val_to_do = GetChain(tokens, all_var, all_func);


    check_symb_error(F_CLOSE_SKOB, tokens);
    tokens->current_ind++;

    
    op_tok->left = val_condition;
    op_tok->right = val_to_do;

    return op_tok;
}




Node* GetWhile(Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func)
{
    assert(tokens);
    assert(all_var);


    check_symb_error(WHILE, tokens);
    
    Node* op_tok = create_node_like_token(tokens->array[tokens->current_ind]);
    tokens->current_ind++;
    

    check_symb_error(OPEN_SKOB, tokens);
    tokens->current_ind++;


    // Node* val_condition = GetE_Addition(tokens, all_var);
    Node* val_condition = GetCompare(tokens, all_var, all_func);


    check_symb_error(CLOSE_SKOB, tokens);
    tokens->current_ind++;

    check_symb_error(F_OPEN_SKOB, tokens);
    tokens->current_ind++;


    Node* val_to_do = GetChain(tokens, all_var, all_func);


    check_symb_error(F_CLOSE_SKOB, tokens);
    tokens->current_ind++;

    
    op_tok->left = val_condition;
    op_tok->right = val_to_do;

    return op_tok;
}







Node* GetAssigm(Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func)
{
    assert(tokens);
    assert(all_var);

    Node* val_var = GetVariable(tokens, all_var);

    // if ((tokens->array[tokens->current_ind]->type != OPERATION) || (tokens->array[tokens->current_ind]->value.op_num != ASSIGM)) // в Func эта проверка написана по-другому. Кажется, там неправильно
    if (!CHECK(ASSIGM))  
        printf("ERROR SYNTAX. Want '='\n");
    
    Node* op_tok = create_node_like_token(tokens->array[tokens->current_ind]);
    tokens->current_ind++;


    Node* val = GetE_Addition(tokens, all_var, all_func);

    op_tok->left = val_var;
    op_tok->right = val;
    // val = op_tok;

    return op_tok;

}


Node* GetIO(Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func)
{
    assert(tokens);
    assert(all_var);


    if (!(CHECK(INPUT) || CHECK(OUTPUT)))  
        printf("ERROR SYNTAX. Want 'input' or 'output'\n");


    Node* op_tok = create_node_like_token(tokens->array[tokens->current_ind]);
    tokens->current_ind++;


    Node* val_var = GetVariable(tokens, all_var);

    // if ((tokens->array[tokens->current_ind]->type != OPERATION) || (tokens->array[tokens->current_ind]->value.op_num != ASSIGM)) // в Func эта проверка написана по-другому. Кажется, там неправильно
    

    op_tok->left = val_var;

    return op_tok;

}


Node* GetOp(Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func)
{
    assert(tokens);
    assert(all_var);


    Node* val = NULL;

    if (CHECK(IF))
    {
        val = GetIf(tokens, all_var, all_func);
    }
    else if (CHECK(WHILE))
    {
        val = GetWhile(tokens, all_var, all_func);
    }
    else if (CHECK(INPUT) || CHECK(OUTPUT))
    {
        val = GetIO(tokens, all_var, all_func);
    }
    else
    {
        val = GetAssigm(tokens, all_var, all_func);
    }

    check_symb_error(SPLIT, tokens);

    Node* op_tok = create_node_like_token(tokens->array[tokens->current_ind]);
    tokens->current_ind++;

    op_tok->left  = val;
    op_tok->right = NULL;

    return op_tok;
}


Node* GetCompare(Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func)
{
    assert(tokens);
    assert(all_var);


    Node* val = GetE_Addition(tokens, all_var, all_func);

    if (!(CHECK(EQUAL) || CHECK(NEQUAL) || CHECK(MORE) || CHECK(LESS) || CHECK(GEQ) || CHECK(LEQ))) printf("ERROR SYNTAX. Want compare symbol\n"); //|| CHECK(MORE) || CHECK(LESS)

    Node* op_tok = create_node_like_token(tokens->array[tokens->current_ind]);
    tokens->current_ind++;

    Node* val2 = GetE_Addition(tokens, all_var, all_func);

    op_tok->left  = val;
    op_tok->right = val2;

    return op_tok;
}


Node* GetChain(Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func)
{
    Node* op_tok = GetOp(tokens, all_var, all_func);
    Node* op_now = op_tok;

    // ???????????????????????????????????????????????? (is this okey?)
    while(CHECK(IF) || CHECK(WHILE) || CHECK(INPUT) || CHECK(OUTPUT) || ((tokens->current_ind < tokens->size) && (tokens->array[tokens->current_ind]->type == VARIABLE)))
    {
        Node* val = GetOp(tokens, all_var, all_func);

        op_now->right = val;
        op_now = val;
    }

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


Node* GetE_Addition(Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func) 
{
    assert(tokens);
    assert(all_var);


    Node* val = GetT_Multiplication(tokens, all_var, all_func);

    // while ((tokens->current_ind < tokens->size) 
    //         &&
    //         ((tokens->array[tokens->current_ind]->type == OPERATION) && 
    //         ((tokens->array[tokens->current_ind]->value.op_num == ADD) || 
    //          (tokens->array[tokens->current_ind]->value.op_num == SUB))))
    while (CHECK(ADD) || CHECK(SUB))
    {
        Node* op_tok = create_node_like_token(tokens->array[tokens->current_ind]);
        tokens->current_ind++;

        Node* val2 = GetT_Multiplication(tokens, all_var, all_func);

        op_tok->left = val;
        op_tok->right = val2;
        val = op_tok;
    }

    return val;
}


Node* GetT_Multiplication(Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func) 
{
    assert(tokens);
    assert(all_var);


    Node* val = GetP_Pow(tokens, all_var, all_func);

    // while ((tokens->current_ind < tokens->size)                        
    //         &&
    //        ((tokens->array[tokens->current_ind]->type == OPERATION)  && 
    //       ((tokens->array[tokens->current_ind]->value.op_num == MUL) || 
    //        (tokens->array[tokens->current_ind]->value.op_num == DIV))))
    while (CHECK(MUL) || CHECK(DIV))
    {
        Node* op_tok = create_node_like_token(tokens->array[tokens->current_ind]);
        tokens->current_ind++;

        Node* val2 = GetP_Pow(tokens, all_var, all_func);

        op_tok->left = val;
        op_tok->right = val2;
        val = op_tok;

    }

    return val;
}




Node* GetP_Pow(Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func)
{
    assert(tokens);
    assert(all_var); 


    Node* val = Get_Heaviest_Oper(tokens, all_var, all_func);

    // while ((tokens->current_ind < tokens->size)                       
    //         &&
    //         tokens->array[tokens->current_ind]->type == OPERATION && 
    //         tokens->array[tokens->current_ind]->value.op_num == POW)
    while (CHECK(POW))
    {
        Node* op_tok = create_node_like_token(tokens->array[tokens->current_ind]);
        tokens->current_ind++;

        Node* val2 = Get_Heaviest_Oper(tokens, all_var, all_func);
        
        
        op_tok->left = val;
        op_tok->right = val2;
        val = op_tok;           // A^B^C = (A^B)^C
    }

    return val;
}




Node* Get_Heaviest_Oper(Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func)
{
    assert(tokens);
    assert(all_var); 


    if ((tokens->array[tokens->current_ind]->type == OPERATION))
    {
        // if (tokens->array[tokens->current_ind]->value.op_num == OPEN_SKOB)
        if (CHECK(OPEN_SKOB)) 
        {
            tokens->current_ind++;
            Node* val = GetE_Addition(tokens, all_var, all_func);
            
            // if ((tokens->array[tokens->current_ind]->type == OPERATION) && 
            //     (tokens->array[tokens->current_ind]->value.op_num != CLOSE_SKOB))
            if (!CHECK(CLOSE_SKOB)) 
                printf("ERROR SYNTAX. Want ')'\n"); 

            tokens->current_ind++;


            return val;

        }
        else
        {
            Node* val = GetF_Function_one_arg(tokens, all_var, all_func);
            if (val != NULL) return val;
        }
    }


    // ПРОВЕРЬ ЭТО!!!!!!!!!!!
    
    else if (tokens->array[tokens->current_ind]->type == VARIABLE)
    {
        // проверить есть ли это имя в функциях
        for (size_t i = 0; i < all_func->size; i++)
        {
            if (strcmp(all_func->arr[i].name, find_name_var(tokens->array[tokens->current_ind]->value.var_num, all_var)) == 0) 
            {
                return Get_My_Func(tokens, all_var, all_func, all_func->arr[i]);
            }
        }
        
        return GetVariable(tokens, all_var); // тут изменится! (проверить имя на функцию!!!!!)
    }

    else return GetNumber(tokens);
    return NULL;
}


Node* GetF_Function_one_arg(Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func) 
{

    // Так как тут будет прием еще собственных (написанных) функций, то надо будет сделать функцию, которая по кол-ву аргументов делает эту "запись" (в дерево). 
    // (И тогда для каждой функции храним кол-во аргументов)
    assert(tokens);
    assert(all_var);


    // if ((tokens->array[tokens->current_ind]->value.op_num == SIN) || 
    //     (tokens->array[tokens->current_ind]->value.op_num == COS) || 
    //     (tokens->array[tokens->current_ind]->value.op_num == LN))
    if (CHECK(SIN) || CHECK(COS) || CHECK(LN) || CHECK(SQRT))
    {

        Node* op_tok = create_node_like_token(tokens->array[tokens->current_ind]);
        tokens->current_ind++;

        // if ((tokens->array[tokens->current_ind]->type == OPERATION) && 
        //     (tokens->array[tokens->current_ind]->value.op_num != OPEN_SKOB)) 
        if (!CHECK(OPEN_SKOB))
            printf("ERROR SYNTAX. Want '('\n");
        tokens->current_ind++;

        Node* val = GetE_Addition(tokens, all_var, all_func); 

        // if ((tokens->array[tokens->current_ind]->type == OPERATION) && 
        //     (tokens->array[tokens->current_ind]->value.op_num != CLOSE_SKOB)) 
        if (!CHECK(CLOSE_SKOB))
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




Node* Get_My_Func(Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func, Function this_func)
{
    assert(tokens);
    assert(all_var);
    assert(all_func);


    Node* func_name = GetVariable(tokens, all_var); // Надо ли новый тип ячейки???????????????????????????????????
    // кажется, надо новый тип
    func_name->type           = CALL_FUNC;
    func_name->value.func_num = this_func.num;


    // Function this_func = {};
    
    // // Нашли функцию в списке
    // for (size_t i = 0; i < all_func->size; i++)
    // {
    //     if (strcmp(all_func->arr[i].name, find_name_var(func_name->value.var_num, all_var)) == 0) 
    //     {
    //         this_func = all_func->arr[i];
    //         break; 
    //     }
    // }


    check_symb_error(OPEN_SKOB, tokens);
    tokens->current_ind++;

    Node* val = NULL;

    if (this_func.num_args != 0)
    {
        // val = GetVariable(tokens, all_var);
        val = GetE_Addition(tokens, all_var, all_func);

        for (int i = 0; i < this_func.num_args - 1; i++)
        {
            check_symb_error(COMMA, tokens);
            Node* op_node = create_node_like_token(tokens->array[tokens->current_ind]);
            tokens->current_ind++;

            // Node* val2 = GetVariable(tokens, all_var);
            Node* val2 = GetE_Addition(tokens, all_var, all_func);

            op_node->left  = val;
            op_node->right = val2;

            val = op_node;
        }
    }

    check_symb_error(CLOSE_SKOB, tokens);
    tokens->current_ind++;

    func_name->left = val;

    return func_name;


} 



// static char* find_name_var(int var_num, VariableArr* all_var)
// {
//     for (size_t i = 0; i < all_var->size; i++)
//     {
//         if (all_var->arr[i].num == var_num) return all_var->arr[i].name;
//     }
// }




// Node* Get_My_Func(Tokens* tokens, VariableArr* all_var) 
// {

//     // Так как тут будет прием еще собственных (написанных) функций, то надо будет сделать функцию, которая по кол-ву аргументов делает эту "запись" (в дерево). 
//     // (И тогда для каждой функции храним кол-во аргументов)
//     assert(tokens);
//     assert(all_var);


//     // if ((tokens->array[tokens->current_ind]->value.op_num == SIN) || 
//     //     (tokens->array[tokens->current_ind]->value.op_num == COS) || 
//     //     (tokens->array[tokens->current_ind]->value.op_num == LN))
//     if (CHECK(SIN) || CHECK(COS) || CHECK(LN))
//     {

//         Node* op_tok = create_node_like_token(tokens->array[tokens->current_ind]);
//         tokens->current_ind++;

//         // if ((tokens->array[tokens->current_ind]->type == OPERATION) && 
//         //     (tokens->array[tokens->current_ind]->value.op_num != OPEN_SKOB)) 
//         if (!CHECK(OPEN_SKOB))
//             printf("ERROR SYNTAX. Want '('\n");
//         tokens->current_ind++;

//         Node* val = GetE_Addition(tokens, all_var); 

//         // if ((tokens->array[tokens->current_ind]->type == OPERATION) && 
//         //     (tokens->array[tokens->current_ind]->value.op_num != CLOSE_SKOB)) 
//         if (!CHECK(CLOSE_SKOB))
//             printf("ERROR SYNTAX. Want ')'\n");
//         tokens->current_ind++;


//         op_tok->left = NULL; 
//         op_tok->right = val;

//         return op_tok;

//     }

//     return NULL;
// }










// void print_node_now(Node* cur_node, VariableArr* all_var)
// {
//     assert(cur_node);
//     if (cur_node->type == NUMBER) printf("%d\n", cur_node->value.num);
//     if (cur_node->type == VARIABLE) printf("%s\n", all_var->arr[cur_node->value.var_num - 1].name);
//     if (cur_node->type == OPERATION) printf("%s\n", op_arr[cur_node->value.op_num].name);
//     // printf("TOKEN[%d] (Node) = {%d - type, %d - value}\n", i, tokens->array[i].type, tokens->array[i].value);
// }



