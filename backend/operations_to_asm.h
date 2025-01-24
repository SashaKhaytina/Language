#ifndef OPER_TO_ASM
#define OPER_TO_ASM

#include "../language_h.h"

void asm_code_add   (FILE* file_asm_code, Node* node, VariableArr* all_var, int* flag);
void asm_code_sub   (FILE* file_asm_code, Node* node, VariableArr* all_var, int* flag);
void asm_code_mul   (FILE* file_asm_code, Node* node, VariableArr* all_var, int* flag);
void asm_code_div   (FILE* file_asm_code, Node* node, VariableArr* all_var, int* flag);
void asm_code_if    (FILE* file_asm_code, Node* node, VariableArr* all_var, int* flag);
void asm_code_while (FILE* file_asm_code, Node* node, VariableArr* all_var, int* flag);
void asm_code_assigm(FILE* file_asm_code, Node* node, VariableArr* all_var,int* flag);
void asm_code_split (FILE* file_asm_code, Node* node, VariableArr* all_var,int* flag);




#endif