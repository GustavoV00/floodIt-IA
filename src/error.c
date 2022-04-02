#include "../include/graph.h"

/**
* Print error when opening a file
*
* @param[in] f File with wrong opening
*/
void error_when_open_file(FILE *f) {
  printf("%p\n", f);
  printf("Error when open file!");
}

/** Print error on graphs */
//void error_graph() { printf("Error to create graph!"); }

//void error_adj_list() { printf("Error to create adj_list!\n"); }
