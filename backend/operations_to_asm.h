#ifndef OPER_TO_ASM
#define OPER_TO_ASM

#include "../language_h.h"
    
void asm_code_add       (FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);
void asm_code_sub       (FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);
void asm_code_mul       (FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);
void asm_code_div       (FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);
    
void asm_code_input     (FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);
void asm_code_output    (FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);
    
void asm_code_if        (FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);
void asm_code_while     (FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);
void asm_code_assigm    (FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);
void asm_code_equal     (FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);
void asm_code_more      (FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);
void asm_code_less      (FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);
void asm_code_geq       (FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);
void asm_code_leq       (FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);
    
void asm_code_split     (FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);
    
void asm_code_func      (FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);
void asm_code_comma     (FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);
void asm_code_pointcomma(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);

// void asm_code_endprog   (FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);
void asm_code_main      (FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);
void asm_code_return(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);

#endif