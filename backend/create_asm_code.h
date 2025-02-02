#ifndef CREATE_ASM
#define CREATE_ASM

#include "../language_h.h"

// TO DO ADEKVATNIE NAME!!!!!
struct Operation_to_asm
{
    AllOperations num;
    char          name[20];
    void          (*asm_code)(FILE* file_asm_code, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);
};

#include "operations_to_asm.h"

const Operation_to_asm op_to_asm_arr[] = {
                                {ADD,          "+",        asm_code_add},
                                {SUB,          "-",        asm_code_sub},
                                {MUL,          "*",        asm_code_mul},
                                {DIV,          "/",        asm_code_div},
                                {SIN,          "sin",      NULL}, // ?
                                {COS,          "cos",      NULL}, // ?
                                {POW,          "^",        NULL}, // ? :|
                                {LN ,          "ln",       NULL}, // ?

                                {INPUT,        "input",    asm_code_input},
                                {OUTPUT,       "output",   asm_code_output},
   
                                {IF,           "if",       asm_code_if},
                                {WHILE,        "while",    asm_code_while},
                                {ASSIGM,        "=",       asm_code_assigm},

                                {FUNC,         "func",     asm_code_func},
   
                                {EQUAL,         "==",      asm_code_equal},
                                {NEQUAL,        "!=",      asm_code_nequal},
                                {MORE,          ">",       asm_code_more},
                                {LESS,          "<",       asm_code_less},
                                {GEQ,           ">=",      asm_code_geq},
                                {LEQ,           "<=",      asm_code_leq},
   
   
                                {OPEN_SKOB,     "(",       NULL}, // их нет в дереве!
                                {CLOSE_SKOB,    ")",       NULL}, // их нет в дереве!
                                {F_OPEN_SKOB,   "{",       NULL}, // их нет в дереве!
                                {F_CLOSE_SKOB,  "}",       NULL}, // их нет в дереве!


                                {SPLIT,         ";",       asm_code_split},
                                {COMMA,         ",",       asm_code_comma},
                                {POINTCOMMA,    ".,",      asm_code_pointcomma},


                                // {END_PROG,      "ENDPROG", asm_code_endprog},
                                {MAIN,          "MAIN",    asm_code_main},
                                {RETURN,       "return",   asm_code_return},
                            };

const int LEN_STRUCT_OP_TO_ASM_ARR = (int) (sizeof(op_to_asm_arr) / sizeof(Operation_to_asm));





void tree_to_asm(FILE* file, Node* node, VariableArr* all_var, FunctionsArr* all_func, int* flag, bool* is_in_func);

#endif