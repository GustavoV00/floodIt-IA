// TRAB1 IA - 2021-2
// GUSTAVO VALENTE NUNES GRR20182557
// BRUNO EDUARDO FARIAS GRR20186715

#ifndef __FLOOD_IT__
#define __FLOOD_IT__

#include "includes.h"

void print_fila(void *ptr);
bool goal(struct queue_state_t *queue, int tam);
queue_state_t *init_elem(state_t elem, queue_state_t *f);
queue_state_t *equals_neighbors(state_t **m, queue_state_t *f, state_t value1, state_t neighbor);
queue_state_t *verify_neighbors(state_t elem, int lin_max, int col_max, state_t **matrix, queue_state_t *possible_next);
queue_state_t *find_equals(queue_state_t *f, state_t **m, int i, int j, int lin_max, int col_max, int quad);

queue_state_t *chose_next_color(queue_state_t *possible_next, int max_lin, int max_col, queue_state_t *f, int num_colors, int quad, state_t **matrix_data);
queue_state_t *search_boards(state_t **matrix, queue_state_t *visited_nodes, int lin, int col, queue_state_t *possible_next, int num_colors, int quad);

int calc_heuristic(int elem_i, int elem_j, int max_lin, int max_col);
queue_state_t *best_color(queue_state_t *possible_next, int max_lin, int max_col);

queue_state_t *remove_all_possible_colors(queue_state_t *f, state_t next_color);
queue_state_t *color_the_board(queue_state_t *f, state_t **m, state_t color);
queue_state_t *addItemsToVisitedNodes(queue_state_t *visited_nodes, state_t **matrix_data, int lin, int col);
void a_star(state_t **matrix_data, int lin, int col, int num_colors);
void print_final_result(int qtdMoves, int *results, int lin, int col);

#endif
