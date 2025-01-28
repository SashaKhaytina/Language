#ifndef LANDUAGE
#define LANDUAGE

#include <stdio.h>
#include <assert.h>


typedef double Elem_t;
typedef int    ForDump;



const char* const FILE_CODE             = "code.txt";
const char* const FILE_TREE             = "code_tree.txt";
const char* const FILE_ASM_CODE         = "file_asm_code.txt";

const size_t      MAX_NAME_IDENT_SIZE   = 200;
const int         MAX_OPER_SYMBOLS_SIZE = 11;
const int         MAX_TOKEN_S_ARR_SIZE  = 10000;
const int         MAX_VAR_COUNT         = 10;


enum TypeNode
{
    DEFAULT,
    NUMBER,
    VARIABLE,
    OPERATION
};


enum AllOperations
{
    ADD,
    SUB,
    MUL,
    DIV,
    SIN,
    COS,
    POW,
    LN,
    IF,
    WHILE,
    ASSIGM,

    EQUAL,
    // MORE,
    // LESS, 
    GEQ,
    LEQ,

    OPEN_SKOB,
    CLOSE_SKOB, 
    F_OPEN_SKOB, 
    F_CLOSE_SKOB, 

    SPLIT, 


    DOLL,

    ERROR
};


struct Variable
{
    int num;
    char* name; 
};

struct VariableArr
{
    Variable arr[MAX_VAR_COUNT];
    size_t size;
};


union Value
{
    Elem_t num;
    int var_num;
    AllOperations op_num;
};


struct Node
{
    TypeNode type;
    Value    value;
    Node*    left;
    Node*    right;
};

struct Tree
{
    Node* root;
};


// // struct Operation
// // {
// //     AllOperations num;
// //     char          name[10];
// // };

// struct Operation
// {
//     AllOperations num;
//     char          name[10];
//     Elem_t        (*calculate)     (Node* node1, Node* node2); 
//     void          (*triv_calculate)(Node* node, int* diference);
// };



// // const Operation op_arr[] = {
// //                                 {ADD,        "+"  },
// //                                 {SUB,        "-"  },
// //                                 {MUL,        "*"  },
// //                                 {DIV,        "/"  },
// //                                 {SIN,        "sin"},
// //                                 {COS,        "cos"},
// //                                 {POW,        "^"  },
// //                                 {LN ,        "ln" },

// //                                 {OPEN_SKOB,  "("  },
// //                                 {CLOSE_SKOB, ")"  }, 
// //                                 {ASSIGM,     "="  }

// //                                 // {DOLL,       "$",   NULL,     NULL,          NULL} 
// //                             };

// #include "math/calculate_formuls.h"
// #include "math/calculate_trivial.h"

// const Operation op_arr[] = {
//                                 {ADD,        "+",   calculate_add, calculate_triv_add},
//                                 {SUB,        "-",   calculate_sub, calculate_triv_sub},
//                                 {MUL,        "*",   calculate_mul, calculate_triv_mul},
//                                 {DIV,        "/",   calculate_div, calculate_triv_div},
//                                 {SIN,        "sin", calculate_sin, calculate_triv_sin},
//                                 {COS,        "cos", calculate_cos, calculate_triv_cos},
//                                 {POW,        "^",   calculate_pow, calculate_triv_pow},
//                                 {LN ,        "ln",  calculate_ln , calculate_triv_ln },

//                                 {ASSIGM,     "=",   NULL,          NULL},

//                                 {OPEN_SKOB,  "(",   NULL,          NULL},
//                                 {CLOSE_SKOB, ")",   NULL,          NULL}

//                                 // {DOLL,       "$",   NULL,     NULL,          NULL} 
//                             };


// const int LEN_STRUCT_OP_ARR = (int) (sizeof(op_arr) / sizeof(Operation));




#endif
