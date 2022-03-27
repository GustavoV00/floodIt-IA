#include "../include/graph.h"

void error_when_open_file(FILE *f) {
  printf("%p\n", f);
  printf("Error when open file!");
}

void error_graph() { printf("Error to create graph!"); }

void error_adj_list() { printf("Error to create adj_list!\n"); }
