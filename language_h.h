#ifndef LANDUAGE
#define LANDUAGE

#include <stdio.h>
#include <assert.h>


typedef double Elem_t;
typedef int    ForDump;



const char* const FILE_CODE             = "code.txt";
const size_t      MAX_NAME_IDENT_SIZE   = 200;
const int         MAX_OPER_SYMBOLS_SIZE = 2;
const int         MAX_TOKEN_S_ARR_SIZE  = 100;
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
    OPEN_SKOB,
    CLOSE_SKOB, 
    // DOLL 
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


struct Operation
{
    AllOperations num;
    char          name[10];
};



const Operation op_arr[] = {
                                {ADD,        "+"  },
                                {SUB,        "-"  },
                                {MUL,        "*"  },
                                {DIV,        "/"  },
                                {SIN,        "sin"},
                                {COS,        "cos"},
                                {POW,        "^"  },
                                {LN ,        "ln" },

                                {OPEN_SKOB,  "("  },
                                {CLOSE_SKOB, ")"  }

                                // {DOLL,       "$",   NULL,     NULL,          NULL} 
                            };

const int LEN_STRUCT_OP_ARR = (int) (sizeof(op_arr) / sizeof(Operation));




#endif
