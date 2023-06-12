// TRAB1 IA - 2023
// GUSTAVO VALENTE NUNES GRR20182557

#include "../include/error.h"
#include "../include/flood_it.h"
#include "../include/io.h"
#include "../include/utils.h"

int main(int argc, char *argv[])
{
  int board_arr[3];
  FILE *board_file = NULL;

  board_file = open_file(board_file);

  if (board_file)
  {

    // read board configurations, such as number of lines, columns and colors
    read_board_configs(board_arr, board_file);

    int lin = board_arr[0];
    int col = board_arr[1];

    if (lin < 4 || col < 4)
    {
      perror("The min of lines or colums is 4, is needed at leats four quadrants\n");
      return -1;
    }

    int num_colors = board_arr[2];

    // There are two matrix, one to do a manipulation and other with initial states.
    state_t **matrix_data = read_board_data(lin, col, board_file);

    // A* algorithm
    a_star(matrix_data, lin, col, num_colors);

    // // closes the file
    // close_file(board_file);
  }

  return 0;
}
