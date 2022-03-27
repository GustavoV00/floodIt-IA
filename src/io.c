#include "../include/io.h"
#include "../include/graph.h"
#include "../include/utils.h"

FILE *open_file(FILE *board_file) {
  board_file = fopen("tests/exemplo_mapa_5_5_4.txt", "r");
  if (board_file)
    return board_file;

  return NULL;
}

void read_board_configs(int *board_arr, FILE *f) {
  int v0, v1, v2;
  fscanf(f, "%d %d %d", &v0, &v1, &v2);
  board_arr[0] = v0;
  board_arr[1] = v1;
  board_arr[2] = v2;
}

struct Graph *read_board_data(int lin, int col, FILE *board_file,
                              struct Graph *graph_t) {
  int **matrix = aloc_matrix(matrix, lin, col);
  matrix = read_matriz_from_file(matrix, lin, col, board_file);
  // print_matrix(matrix, lin, col);

  graph_t = create_graph_edges(graph_t, matrix, lin, col);
  desaloc_matrix(matrix, lin, col);
  return graph_t;
}

void close_file(FILE *file) { fclose(file); }
