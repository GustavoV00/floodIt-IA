#include "../include/error.h"
#include "../include/graph.h"
#include "../include/io.h"

int main(int argc, char *argv[]) {
  int board_arr[3];
  FILE *board_file = NULL;

  // Podemos tirar os if's de errro, para deixar o código menos verboso.

  board_file = open_file(board_file);
  if (board_file) {
    read_board_configs(board_arr, board_file);
    struct Graph *graph_t = create_graph();
    if (graph_t) {
      int lin = board_arr[0];
      int col = board_arr[1];
      int vertices = lin * col;
      int num_colors = board_arr[2];
      void *p = init_graph_values(vertices, graph_t);
      if (p) {
        read_board_data(lin, col, board_file, graph_t);
        close_file(board_file);

      } else {
        error_adj_list();
      }

    } else {
      error_graph();
    }
  } else {
    error_when_open_file(board_file);
  }

  return 0;
}
