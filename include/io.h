// TRAB1 IA - 2023
// GUSTAVO VALENTE NUNES GRR20182557

#ifndef __IO__
#define __IO__

#include "includes.h"

FILE *open_file(FILE *board_file);
void read_board_configs(int *board_arr, FILE *f);
state_t **read_board_data(int lin, int col, FILE *board_file);
void close_file(FILE *file);

#endif
