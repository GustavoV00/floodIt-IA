// TRAB1 IA - 2021-2
// GUSTAVO VALENTE NUNES GRR20182557

#include "../include/io.h"
#include "../include/utils.h"

/**
 * Open and returns file
 * @param[in] board_file Board file
 */
FILE *open_file(FILE *board_file)
{
  board_file = stdin;
  if (board_file)
    return board_file;

  perror("Erro ao abrir arquivo!\n");
  return NULL;
}

/**
 * Read board data
 * board_arr[0] = number of board lines
 * board_arr[1] = number of board columns
 * board_arr[2] = number of board colors
 *
 * @param[in] board_arr Array with board data
 * @param[in] f File with board data (stdin)
 */
void read_board_configs(int *board_arr, FILE *f)
{
  int v0, v1, v2;
  fscanf(f, "%d %d %d", &v0, &v1, &v2);
  board_arr[0] = v0;
  board_arr[1] = v1;
  board_arr[2] = v2;
}

/**
 * Read board data, alocates a matrix and fills it
 * @param[in] lin Number of lines
 * @param[in] col Number of colums
 * @param[in] board_file File with board data
 * @param[in] size_quadrant_x Lines that separated the quadrants
 * @param[in] size_quadrant_y Lines that separated the quadrants
 * @param[in] board_file File with board data
 * @param[out] representations of board cell
 */
state_t **read_board_data(int lin, int col, FILE *board_file)
{
  // alocates matrix lin x col
  state_t **matrix = NULL;
  matrix = aloc_matrix(matrix, lin, col);

  // fills the matrix with file board
  matrix = read_matriz_from_file(matrix, lin, col, board_file);
  print_matrix_quadrant(matrix, lin, col);

  // desaloc_matrix(matrix, lin, col);

  return matrix;
}

/**
 * Closes the file
 *
 * @param[in] file File to be closed
 */
void close_file(FILE *file) { fclose(file); }
