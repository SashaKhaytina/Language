#ifndef PARSER
#define PARSER

#include "../language_h.h"
#include "token.h"


Node* GetGraph             (Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func);

Node* GetWhile             (Tokens* tokens, VariableArr* all_var);
Node* GetIf                (Tokens* tokens, VariableArr* all_var);
Node* GetAssigm            (Tokens* tokens, VariableArr* all_var);
Node* GetOp                (Tokens* tokens, VariableArr* all_var);
Node* GetCompare           (Tokens* tokens, VariableArr* all_var);

Node* Get_Chain_Func       (Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func);
Node* Get_Created_Func     (Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func);
Node* Get_Args             (Tokens* tokens, VariableArr* all_var, int* num_args);



Node* GetChain(Tokens* tokens, VariableArr* all_var);

Node* GetNumber            (Tokens* tokens);
Node* GetE_Addition        (Tokens* tokens, VariableArr* all_var);
Node* GetT_Multiplication  (Tokens* tokens, VariableArr* all_var);
Node* GetP_Pow             (Tokens* tokens, VariableArr* all_var);
Node* Get_Heaviest_Oper    (Tokens* tokens, VariableArr* all_var);
Node* GetF_Function_one_arg(Tokens* tokens, VariableArr* all_var);
Node* GetVariable          (Tokens* tokens, VariableArr* all_var);


#endif
