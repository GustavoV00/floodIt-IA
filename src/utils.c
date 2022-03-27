#include "../include/graph.h"
#include "../include/includes.h"

int **aloc_matrix(int **matrix, int lin, int col) {

  matrix = malloc(lin * sizeof(int *));
  for (int i = 0; i < lin; i++) {
    matrix[i] = malloc(col * sizeof(int));
  }

  return matrix;
}

struct Graph *create_graph_edges(struct Graph *graph_t, int **matrix, int lin,
                                 int col) {
  int vertice = 0;
  for (int i = 0; i < lin; i++) {
    for (int j = 0; j < col; j++) {
      if (j < col - 1)
        add_edge(graph_t, vertice, vertice + 1, matrix[i][j + 1], matrix[i][j]);

      if (i < lin - 1)
        add_edge(graph_t, vertice, vertice + col, matrix[i + 1][j],
                 matrix[i][j]);
      // 1][j]);
      vertice += 1;
    }
  }

  return graph_t;
}

int **read_matriz_from_file(int **matrix, int lin, int col, FILE *board_file) {
  int aux;
  for (int i = 0; i < lin; i++) {
    for (int j = 0; j < col; j++) {
      fscanf(board_file, "%d ", &aux);
      matrix[i][j] = aux;
    }
  }
  return matrix;
}

void print_matrix(int **matrix, int lin, int col) {
  int aux;
  for (int i = 0; i < lin; i++) {
    for (int j = 0; j < col; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

void desaloc_matrix(int **matrix, int lin, int col) {
  for (int i = 0; i < lin; i++) {
    free(matrix[i]);
  }
  free(matrix);
}
