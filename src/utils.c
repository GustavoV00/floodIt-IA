#include "../include/graph.h"
#include "../include/includes.h"

/**
* Allocates state_t matrix with lin x col
* @param[in] matrix Pointer to matrix
* @param[in] lin Number of lines
* @param[in] col Number of colums
* @param[out] state_t matrix
*/
state_t **aloc_matrix(state_t **matrix, int lin, int col) {

  matrix = malloc(lin * sizeof(state_t *));
  for (int i = 0; i < lin; i++) {
    matrix[i] = malloc(col * sizeof(state_t));
  }

  return matrix;
}

/*
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
*/

/**
* Reads the matrix from the file
* @param[in] matrix
* @param[in] lin Number of lines
* @param[in] col Number of colums
* @param[in] board_file File with board data
*/
state_t **read_matriz_from_file(state_t **matrix, int lin, int col,
                                FILE *board_file) {
  int aux;
  int id = 0;
  for (int i = 0; i < lin; i++) {
    for (int j = 0; j < col; j++) {
      fscanf(board_file, "%d ", &aux);
      matrix[i][j].value = aux;
      matrix[i][j].g_n = i + j;
      matrix[i][j].lin = i;
      matrix[i][j].col = j;
      matrix[i][j].visited = 0;
      matrix[i][j].in_board = 0;
    }
  }
  return matrix;
}

/**
* Prints the matrix
* @param[in] matrix The matrix to be printed
* @param[in] lin Number of lines
* @param[in] col Number of colums
*/
void print_matrix(state_t **matrix, int lin, int col) {
  int aux;
  for (int i = 0; i < lin; i++) {
    for (int j = 0; j < col; j++) {
      // printf("(%d, %d)", matrix[i][j].value, matrix[i][j].g_n);
      printf("%d ", matrix[i][j].value);
    }
    printf("\n");
  }
}

/**
* Copy matrix src_mat to dest_mat matrix
* @param[in] src_mat Source matrix
* @param[in] dest_mat Target matrix
* @param[in] lin Number of lines
* @param[in] col Number of colums
*/
void matrix_copy(state_t **src_mat, state_t **dest_mat, int lin, int col) {
  memcpy(dest_mat, src_mat, lin * col * sizeof(int));
}

/**
* Desallocates the memory used by the matrix
* @param[in] matrix The matrix to be desallocated
* @param[in] lin Number of lines
* @param[in] col Number of colums
*/
void desaloc_matrix(state_t **matrix, int lin, int col) {
  for (int i = 0; i < lin; i++) {
    free(matrix[i]);
  }
  free(matrix);
}
