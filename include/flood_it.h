// TRAB1 IA - 2023
// GUSTAVO VALENTE NUNES GRR20182557

#ifndef __FLOOD_IT__
#define __FLOOD_IT__

#include "includes.h"

//------------------------------------------------------------------------------
// Imprime a fila
void print_fila(void *ptr);

//------------------------------------------------------------------------------
// Verifica se chegou no objetivo
bool goal(struct queue_state_t *queue, int tam);

//------------------------------------------------------------------------------
// Aloca memória para um elemento na fila
queue_state_t *init_elem(state_t elem, queue_state_t *f);

//------------------------------------------------------------------------------
// Valida se os vizinhos são iguais (Utilizado pelo verify_neighboors)
queue_state_t *equals_neighbors(state_t **m, queue_state_t *f, state_t value1, state_t neighbor);

//------------------------------------------------------------------------------
// Procura pelas bordas (utilizado pelo search_boards)
queue_state_t *verify_neighbors(state_t elem, int lin_max, int col_max, state_t **matrix, queue_state_t *possible_next);

//------------------------------------------------------------------------------
// Algoritmo utilizado pelo choose_next_color para encontrar as cores de forma recursiva
queue_state_t *find_equals(queue_state_t *f, state_t **m, int i, int j, int lin_max, int col_max);

//------------------------------------------------------------------------------
// Mesmo que o search_boards, mas pega os vizinhos e procura se esses vizinhos possuem vizinhos da mesma cor (De forma recursiva)
queue_state_t *choose_next_color(queue_state_t *possible_next, int max_lin, int max_col, queue_state_t *f, int num_colors, int quad, state_t **matrix_data);

//------------------------------------------------------------------------------
// Coloca os vizinhos em possíveis valores próximos
queue_state_t *search_boards(state_t **matrix, queue_state_t *visited_nodes, int lin, int col, queue_state_t *possible_next, int num_colors, int quad);

//------------------------------------------------------------------------------
// Cálcula a heurística
int calc_heuristic(int elem_i, int elem_j, int max_lin, int max_col);

//------------------------------------------------------------------------------
// Algorítimo que arruma os valores para calcular a heurística
state_t best_color(queue_state_t *possible_next, int max_lin, int max_col, int flag, int quad, int num_colors);

//------------------------------------------------------------------------------
// Remove dos próximos possíveis e insere nos visitados
queue_state_t *remove_all_possible_colors(queue_state_t *f, state_t next_color, queue_state_t *visited_nodes);

//------------------------------------------------------------------------------
// Faz a coloração do tabuleiro
queue_state_t *color_the_board(queue_state_t *f, state_t **m, state_t color, int quad);

//------------------------------------------------------------------------------
// Resolver do A* para o floodit
void a_star(state_t **matrix_data, int lin, int col, int num_colors);

//------------------------------------------------------------------------------
// Imprime os resultados finais do jogo
void print_final_result(int qtdMoves, result_t *results, int lin, int col);

#endif
