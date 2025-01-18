#ifndef FOR_DUMP
#define FOR_DUMP

#include "../language_h.h" 


#include <stdlib.h>
 
const char* const ELEM_TREE_COLOR  = "#D7CF8D";
const char* const SHEET_TREE_COLOR = "#F9EA6B";
const char* const FONT_COLOR       = "#F2EECB";
const char* const DUMP_FILE        = "all_dumps/pictures/log.html";


void dump          (Node* node, ForDump* st_dump, VariableArr* all_var); // draw subtree
void to_do_log_file(ForDump* st_dump);


#endif


