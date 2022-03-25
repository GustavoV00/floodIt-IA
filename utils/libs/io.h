#ifndef __IO__
#define __IO__

#include "includes.h"

FILE *open_file();
void error_when_open_file(FILE *f);
void read_board_configs(int *board_arr, FILE *f);
void close_file(FILE *file);

#endif
