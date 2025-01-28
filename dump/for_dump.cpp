#include "for_dump.h"

#include "../math/operations.h"

#include <stdio.h>


static void create_png        (int num);
static void graph_create_edge (Node* node, FILE* file);       
static void graph_create_point(Node* node, FILE* file, VariableArr* all_var);     


static void graph_create_point(Node* node, FILE* file, VariableArr* all_var)
{   
    if (node == NULL) return;

    if (node->type == OPERATION)
    {
        for (int i = 0; i < LEN_STRUCT_OP_ARR; i++)
        {
            // if (op_arr[i].num == node->value.op_num) { fprintf(file, "POINT_%p[shape=Mrecord, label = \"POINT_%p | type - OPERATION(%d) | %s\", style=\"filled\",fillcolor=\"%s\"]\n", node, node, node->value.op_num, op_arr[i].name, ELEM_TREE_COLOR); break; }
            if (op_arr[i].num == node->value.op_num) 
            {
                if (node->value.op_num == EQUAL || node->value.op_num == MORE || node->value.op_num == LESS || node->value.op_num == GEQ || node->value.op_num == LEQ) // node->value.op_num == MORE || node->value.op_num == LESS || 
                {
                    fprintf(file, "POINT_%p[shape=Mrecord, label = \"POINT_%p | type - OPERATION(%d) | \\%s\", style=\"filled\",fillcolor=\"%s\"]\n", node, node, node->value.op_num, op_arr[i].name, ELEM_TREE_COLOR); 
                    break;
                }
                else
                {
                fprintf(file, "POINT_%p[shape=Mrecord, label = \"POINT_%p | type - OPERATION(%d) | %s\", style=\"filled\",fillcolor=\"%s\"]\n", node, node, node->value.op_num, op_arr[i].name, ELEM_TREE_COLOR); 
                break; 
                }
            }

        }
    }
    else if (node->type == NUMBER) fprintf(file, "POINT_%p[shape=Mrecord, label = \"POINT_%p | type - NUMBER (%d) | value - %g\", style=\"filled\",fillcolor=\"%s\"]\n", node, node, node->type, node->value.num, ELEM_TREE_COLOR);
    else // Var
    {
        char* name_var = NULL;
        for (size_t i = 0; i < all_var->size; i++)
        {
            if (all_var->arr[i].num == node->value.var_num) { name_var = all_var->arr[i].name; break;}
        }

        fprintf(file, "POINT_%p[shape=Mrecord, label = \"POINT_%p | type - VARIABLE (%d) | value - %s (num - %d))\", style=\"filled\",fillcolor=\"%s\"]\n", node, node, node->type, name_var, node->value.var_num, ELEM_TREE_COLOR);
    }

    
    graph_create_point(node->left, file, all_var);
    graph_create_point(node->right, file, all_var);
}   


static void graph_create_edge(Node* node, FILE* file) 
{   
    if (node == NULL) return;

    if (node->left) fprintf(file, "POINT_%p -> POINT_%p\n", node, node->left);
    if (node->right) fprintf(file, "POINT_%p -> POINT_%p\n", node, node->right);

    graph_create_edge(node->left, file);
    graph_create_edge(node->right, file);

}


static void create_png(int num)
{
    char command_create_png[200] = {};
    sprintf(command_create_png, "dot all_dumps/pictures/image%d%d.dot -Tpng -o all_dumps/pictures/pic%d%d.png", num / 10, num % 10, num / 10, num % 10);
    system(command_create_png);
}




void dump(Node* node, ForDump* dumps_counter, VariableArr* all_var) // draw subtree
{
    (*dumps_counter)++;
    int number_of_dump = *dumps_counter;

    char sample[] = "all_dumps/pictures/image00.dot";
    sample[24] = (char) ('0' + ((int) number_of_dump / 10));
    sample[25] = (char) ('0' + ((int) number_of_dump % 10));

    FILE* file = fopen(sample, "w");

    fprintf(file, "digraph\n{\nbgcolor=\"%s\";\nrankdir = TB;\n", FONT_COLOR);

    graph_create_point(node, file, all_var);

    graph_create_edge(node, file);

    fprintf(file, "}\n");

    fclose(file);

    create_png(number_of_dump);

}


void to_do_log_file(ForDump* dumps_counter)
{
    FILE* file = fopen(DUMP_FILE, "w");

    fprintf(file, "<pre>\n");
    fprintf(file, "<style>body {background-color:%s}</style>\n\n", FONT_COLOR);


    for (int i = 1; i <= *dumps_counter; i++)
    {        
        char sample[] = "all_dumps/pictures/pic00.png";
        sample[23] = (char) ('0' + ((int) i / 10));
        sample[24] = (char) ('0' + ((int) i % 10));

        fprintf(file, "<big><big><div align=\"center\">Tree (print %d) &#128578;</div></big></big>\n\n", i); 

        fprintf(file, "<div align=\"center\"><img src=\"%s\"></div>\n\n\n", sample);

    }
 
    fclose(file);
}
