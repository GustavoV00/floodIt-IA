#include "../include/error.h"
#include "../include/flood_it.h"
#include "../include/graph.h"
#include "../include/io.h"
#include "../include/utils.h"

int main(int argc, char *argv[]) {
  int board_arr[3];
  FILE *board_file = NULL;

  // Podemos tirar os if's de errro, para deixar o código menos verboso.


  board_file = open_file(board_file);

  if (board_file) {

    //read board configurations, such as number of lines, columns and colors
    read_board_configs(board_arr, board_file);

    //creates graph 
    //struct Graph *graph_t = create_graph();


    //if (graph_t) {
      int lin = board_arr[0];
      int col = board_arr[1];
      int num_colors = board_arr[2];
      // void *p = init_graph_values(vertices, graph_t);
      // if (p) {

      // Utilizo uma matriz para fazer a manipulação de estados, e outra com o e
      // tado inicial
      state_t **matrix_data = read_board_data(lin, col, board_file);

      //allocates a auxiliar matrix to hold the initial state
      state_t **matrix_data_aux = aloc_matrix(matrix_data_aux, lin, col);

      //copy the matrix to this auxiliar matrix
      matrix_copy(matrix_data, matrix_data_aux, lin, col);

      // print_matrix(matrix_data_aux, lin, col);

      //A* algorithm
      int *v = a_star(matrix_data, lin, col, num_colors);

      //closes the file
      close_file(board_file);
      //   } else {
      //     error_adj_list();
      //   }
      // } else {
      //   error_graph();
      // }
    //} else {
    //  error_when_open_file(board_file);
    //}
  }

  return 0;
}
