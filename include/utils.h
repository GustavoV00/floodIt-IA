//TRAB1 IA - 2021-2
//GUSTAVO VALENTE NUNES GRR20182557
//BRUNO EDUARDO FARIAS GRR20186715

#ifndef __UTILS__
#define __UTILS__

#include "includes.h"

state_t **aloc_matrix(state_t **matrix, int lin, int col);
state_t **read_matriz_from_file(state_t **matrix, int lin, int col, FILE *board_file);
void print_matrix(state_t **matrix, int lin, int col);
void matrix_copy(state_t **src_mat, state_t **dest_mat, int lin, int col);
void desaloc_matrix(state_t **matrix, int lin, int col);

#endif
