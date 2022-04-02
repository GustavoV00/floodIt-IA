//TRAB1 IA - 2021-2
//GUSTAVO VALENTE NUNES GRR20182557
//BRUNO EDUARDO FARIAS GRR20186715

#ifndef __IO__
#define __IO__

#include "includes.h"

FILE *open_file();
void error_when_open_file(FILE *f);
void read_board_configs(int *board_arr, FILE *f);
state_t **read_board_data(int lin, int col, FILE *board_file);
void close_file(FILE *file);

#endif
