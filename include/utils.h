#ifndef __UTILS__
#define __UTILS__

#include "includes.h"

int **aloc_matrix(int **matrix, int lin, int col);
struct Graph *create_graph_edges(struct Graph *graph_t, int **matrix, int lin,
                                 int col);
int **read_matriz_from_file(int **matrix, int lin, int col, FILE *board_file);
void print_matrix(int **matrix, int lin, int col);
void desaloc_matrix(int **matrix, int lin, int col);

#endif
