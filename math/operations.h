#ifndef OPERATIONS
#define OPERATIONS

#include "../language_h.h"

// struct Operation
// {
//     AllOperations num;
//     char          name[10];
// };

struct Operation
{
    AllOperations num;
    char          name[20];
    Elem_t        (*calculate)     (Node* node1, Node* node2); 
    void          (*triv_calculate)(Node* node, int* diference);
};



// const Operation op_arr[] = {
//                                 {ADD,        "+"  },
//                                 {SUB,        "-"  },
//                                 {MUL,        "*"  },
//                                 {DIV,        "/"  },
//                                 {SIN,        "sin"},
//                                 {COS,        "cos"},
//                                 {POW,        "^"  },
//                                 {LN ,        "ln" },

//                                 {OPEN_SKOB,  "("  },
//                                 {CLOSE_SKOB, ")"  }, 
//                                 {ASSIGM,     "="  }

//                                 // {DOLL,       "$",   NULL,     NULL,          NULL} 
//                             };

#include "calculate_formuls.h"
#include "calculate_trivial.h"

const Operation op_arr[] = {
                                {ADD,          "+",       calculate_add , calculate_triv_add},
                                {SUB,          "-",       calculate_sub , calculate_triv_sub},
                                {MUL,          "*",       calculate_mul , calculate_triv_mul},
                                {DIV,          "/",       calculate_div , calculate_triv_div},
                                {SIN,          "sin",     calculate_sin , calculate_triv_sin},
                                {COS,          "cos",     calculate_cos , calculate_triv_cos},
                                {POW,          "^",       calculate_pow , calculate_triv_pow},
                                {LN ,          "ln",      calculate_ln  , calculate_triv_ln },
                                {SQRT ,        "sqrt",    calculate_sqrt, NULL},
 
                                {INPUT,        "input",   NULL,           NULL},
                                {OUTPUT,       "output",  NULL,           NULL},
    
                                {IF,           "if",      NULL,           NULL},
                                {WHILE,        "while",   NULL,           NULL},
                                {ASSIGM,       "=",       NULL,           NULL},
    
                                {FUNC,         "func",    NULL,           NULL},
    
                                {EQUAL,        "==",      NULL,           NULL},
                                {NEQUAL,       "!=",      NULL,           NULL},
                                {MORE,         ">",       NULL,           NULL},
                                {LESS,         "<",       NULL,           NULL},
                                {GEQ,          ">=",      NULL,           NULL},
                                {LEQ,          "<=",      NULL,           NULL},
    
                                {OPEN_SKOB,    "(",       NULL,           NULL},
                                {CLOSE_SKOB,   ")",       NULL,           NULL},
                                {F_OPEN_SKOB,  "{",       NULL,           NULL},
                                {F_CLOSE_SKOB, "}",       NULL,           NULL}, 
    
    
                                {SPLIT,        ";",       NULL,           NULL},
                                {COMMA,        ",",       NULL,           NULL},
                                {POINTCOMMA,   ".,",      NULL,           NULL},
 
 
                                {END_PROG,     "ENDPROG", NULL,           NULL},
                                {MAIN,         "MAIN",    NULL,           NULL},
                                {RETURN,       "return",  NULL,           NULL},
 
 
                                {ERROR,        "ERROR",   NULL,           NULL}
                            }; 
 

const int LEN_STRUCT_OP_ARR = (int) (sizeof(op_arr) / sizeof(Operation));




#endif