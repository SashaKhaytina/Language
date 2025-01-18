#ifndef FREE
#define FREE

#include "../language_h.h"
#include "../get_code/token.h"


void free_tree           (Node* node);
void free_val            (VariableArr* all_var);
void free_tokens         (Tokens* tokens);
void free_needless_tokens(Tokens* tokens);



#endif 
