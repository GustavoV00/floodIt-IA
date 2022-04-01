#ifndef __IO__
#define __IO__

#include "graph.h"
#include "includes.h"

FILE *open_file();
void error_when_open_file(FILE *f);
void read_board_configs(int *board_arr, FILE *f);
state_t **read_board_data(int lin, int col, FILE *board_file);
void close_file(FILE *file);

#endif
