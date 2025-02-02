#ifndef PARSER
#define PARSER

#include "../language_h.h"
#include "token.h"


Node* GetGraph             (Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func);

Node* GetWhile             (Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func);
Node* GetIf                (Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func);
Node* GetAssigm            (Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func);
Node* GetOp                (Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func);
Node* GetCompare           (Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func);

Node* Get_Chain_Func       (Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func);
Node* Get_Created_Func     (Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func);
Node* Get_Args             (Tokens* tokens, VariableArr* all_var, int* num_args);
Node* Get_Return           (Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func);



Node* GetChain(Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func);

Node* GetNumber            (Tokens* tokens);
Node* GetE_Addition        (Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func);
Node* GetT_Multiplication  (Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func);
Node* GetP_Pow             (Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func);
Node* Get_Heaviest_Oper    (Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func);
Node* GetF_Function_one_arg(Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func);
Node* Get_My_Func          (Tokens* tokens, VariableArr* all_var, FunctionsArr* all_func, Function this_func);
Node* GetVariable          (Tokens* tokens, VariableArr* all_var);





#endif
