// TRAB1 IA - 2021-2
// GUSTAVO VALENTE NUNES GRR20182557
// BRUNO EDUARDO FARIAS GRR20186715

#include "../include/includes.h"
#include "../include/queue.h"
#include "../include/utils.h"
#include <assert.h>
#include <unistd.h>

queue_state_t *removed_items = NULL;

/**
 * Function to print a queue node
 *
 * @param[in] ptr Pointer to node
 */
void print_fila(void *ptr)
{
  struct queue_state_t *elem = ptr;

  if (!elem)
    return;

  elem->prev ? printf("%d", elem->prev->st.value) : printf("*");
  printf("<%d>", elem->st.value);
  elem->prev ? printf("%d", elem->next->st.value) : printf("*");
}

/**
 * Verify if the state is a goal: every node/cell has the same color
 *
 * @param[in] queue Queue of elements
 * @param[in] tam Quantity of elements
 */
bool goal(struct queue_state_t *queue, int tam)
{
  int n = queue_size((queue_t *)queue);
  // printf("Tamanho fila visited_nodes: %d\n", n);

  if (n < tam)
    return false;

  return true;
}

/**
 * Allocate a new elemento to the queue of states
 *
 * @param[in] elem The elem to be appended to the list
 * @param[in] f Queue of elements
 */
queue_state_t *init_elem(state_t elem, queue_state_t *f)
{
  queue_state_t *root_elem = (queue_state_t *)malloc(sizeof(queue_state_t));
  root_elem->prev = NULL;
  root_elem->next = NULL;
  root_elem->st = elem;

  queue_append((queue_t **)&f, (queue_t *)root_elem);
  return f;
}

/**
 * Verifies if the value1 and neighbor have the same color
 *
 * @param[in] m The data matrix
 * @param[in] f Queue of next possible options
 * @param[in] value1 Actual node
 * @param[in] neighbor Neighbor node
 */
queue_state_t *equals_neighbors(state_t **m, queue_state_t *f, state_t value1,
                                state_t neighbor)
{
  if (value1.value != neighbor.value && value1.value != 0 &&
      neighbor.value != 0 && neighbor.in_board == 0)
  {

    int i = neighbor.lin;
    int j = neighbor.col;
    m[i][j].in_board = 1;
    f = init_elem(neighbor, f);
  }

  return f;
}

/**
 * Verify the neighborhood
 *
 * @param[in] elem Element to search neighborhood
 * @param[in] lin_max Quantity of board lines
 * @param[in] col_max Quantity of board columns
 * @param[in] matrix The data matrix
 * @param[in] possible_next Queue of next possible options
 */
queue_state_t *verify_neighbors(state_t elem, int lin_max, int col_max,
                                state_t **matrix,
                                queue_state_t *possible_next)
{
  int i = elem.lin;
  int j = elem.col;
  if (i > 0 && j > 0 && j < col_max - 1 && i < lin_max - 1)
  {
    possible_next =
        equals_neighbors(matrix, possible_next, matrix[i][j], matrix[i][j + 1]);

    possible_next =
        equals_neighbors(matrix, possible_next, matrix[i][j], matrix[i][j - 1]);

    possible_next =
        equals_neighbors(matrix, possible_next, matrix[i][j], matrix[i + 1][j]);

    possible_next =
        equals_neighbors(matrix, possible_next, matrix[i][j], matrix[i - 1][j]);
    return possible_next;
  }

  if (i == 0)
  {
    possible_next =
        equals_neighbors(matrix, possible_next, matrix[i][j], matrix[i][j + 1]);

    possible_next =
        equals_neighbors(matrix, possible_next, matrix[i][j], matrix[i + 1][j]);
    if (j > 0)
      possible_next = equals_neighbors(matrix, possible_next, matrix[i][j],
                                       matrix[i][j - 1]);
    return possible_next;
  }

  if (i == lin_max - 1)
  {
    possible_next =
        equals_neighbors(matrix, possible_next, matrix[i][j], matrix[i][j + 1]);

    possible_next =
        equals_neighbors(matrix, possible_next, matrix[i][j], matrix[i - 1][j]);
    if (j > 0)
      possible_next = equals_neighbors(matrix, possible_next, matrix[i][j],
                                       matrix[i][j - 1]);
    return possible_next;
  }
  if (j == 0)
  {
    possible_next =
        equals_neighbors(matrix, possible_next, matrix[i][j], matrix[i][j + 1]);

    possible_next =
        equals_neighbors(matrix, possible_next, matrix[i][j], matrix[i + 1][j]);
    if (i > 0)
      possible_next = equals_neighbors(matrix, possible_next, matrix[i][j],
                                       matrix[i - 1][j]);
    return possible_next;
  }

  if (j == col_max - 1)
  {
    possible_next =
        equals_neighbors(matrix, possible_next, matrix[i][j], matrix[i][j - 1]);

    possible_next =
        equals_neighbors(matrix, possible_next, matrix[i][j], matrix[i + 1][j]);
    if (i > 0)
      possible_next = equals_neighbors(matrix, possible_next, matrix[i][j],
                                       matrix[i - 1][j]);

    return possible_next;
  }

  return possible_next;
}

/**
 * Finds cells that have the same color as the color of M[i,j]
 *
 * @param[in] f Queue of visited nodes
 * @param[in] m The matrix
 * @param[in] i Line to be verified
 * @param[in] j Line to be verified
 * @param[in] lin_max Quantity of board lines
 * @param[in] col_max Quantity of board columns
 * @param[in] flag Quantity of board columns
 */
queue_state_t *find_equals(queue_state_t *f, state_t **m, int i, int j,
                           int lin_max, int col_max)
{

  if (f != NULL)
  {
    if (m[i][j].value == f->st.value && m[i][j].visited == 0)
    {
      f = init_elem(m[i][j], f);
      m[i][j].visited = 1;
    }
    else
    {
      return f;
    }
  }
  else
  {
    f = init_elem(m[i][j], f);
    m[i][j].visited = 1;
  }

  if (j < col_max - 1)
    f = find_equals(f, m, i, j + 1, lin_max, col_max);

  if (j > 0)
    f = find_equals(f, m, i, j - 1, lin_max, col_max);

  if (i < lin_max - 1)
    f = find_equals(f, m, i + 1, j, lin_max, col_max);

  if (i > 0)
    f = find_equals(f, m, i - 1, j, lin_max, col_max);

  return f;
}

/**
 * Search for the border (next possible choices)
 *
 * @param[in] matrix The matrix
 * @param[in] visited_nodes The queue of visited nodes
 * @param[in] lin Number of lines
 * @param[in] col Number of colums
 * @param[in] possible_next Queue of possible next choices
 */
queue_state_t *search_boards(state_t **matrix, queue_state_t *visited_nodes,
                             int lin, int col, queue_state_t *possible_next)
{
  queue_state_t *aux = visited_nodes;

  do
  {
    state_t elem = aux->st;

    // Procura no [i][j+1], [i+1][j], etc...
    possible_next = verify_neighbors(elem, lin, col, matrix, possible_next);

    aux = aux->next;
  } while (aux != visited_nodes);

  return possible_next;
}

/**
 * Calculates the heuristic funcion: pythagoras theorem
 *
 * @param[in] elem_i Row of elem
 * @param[in] elem_j Column of elem
 * @param[in] max_lin Number of lines
 * @param[in] max_col Number of colums
 *
 */
int calc_heuristic(int elem_i, int elem_j, int max_lin, int max_col)
{
  int side1 = max_col - elem_j;
  int side2 = max_lin - elem_i;
  int result = (side1 * side1) + (side2 * side2);
  return result;
}

/**
 * Chooses (using a heurist funcion and total cost) the next color
 *
 * @param[in] possible_next Queue of next possible options
 * @param[in] max_lin Quantity of board lines
 * @param[in] max_col Quantity of board columns
 * @param[in] f Queue of visited nodes
 */

state_t chose_next_color(queue_state_t *possible_next, int max_lin, int max_col,
                         queue_state_t *f)
{

  queue_state_t *aux = possible_next;

  state_t best_elem = aux->st;
  int best = best_elem.g_n +
             calc_heuristic(best_elem.lin, best_elem.col, max_lin, max_col);

  state_t new_elem;
  int new_best;
  aux = aux->next;
  do
  {
    new_elem = aux->st;
    new_best = new_elem.g_n +
               calc_heuristic(new_elem.lin, new_elem.col, max_lin, max_col);
    if (new_best <= best)
    {
      best_elem = new_elem;
      best = new_best;
    }
    aux = aux->next;
  } while (aux != possible_next);

  return best_elem;
}

/**
 * Clears the queue
 *
 * @param[in] f Queue to be cleared
 * @param[in] next_color Next color state to ble cleared
 */
queue_state_t *remove_all_possible_colors(queue_state_t *f,
                                          state_t next_color)
{
  queue_state_t *aux = f;

  int n = queue_size((queue_t *)f);
  int i = 0;
  while (i < n)
  {

    if (next_color.value == aux->st.value)
    {
      queue_state_t *aux2 = aux;
      removed_items = init_elem(aux2->st, removed_items);
      aux = aux->prev;
      queue_remove((queue_t **)&f, (queue_t *)aux2);

      assert(fila_correta(f));    // estrutura continua correta
      assert(aux2->prev == NULL); // testa elemento removido
      assert(aux2->next == NULL); // testa elemento removido
      free(aux2);
    }

    i += 1;
    aux = aux->next;
  }

  return f;
}

/**
 * Paints the board with color
 *
 * @param[in] f Queue of visited nodes
 * @param[in] m Matrix data
 * @param[in] color Element that has the color to paint the board
 */
queue_state_t *color_the_board(queue_state_t *f, state_t **m, state_t color)
{
  queue_state_t *aux = f;

  int i;
  int j;
  do
  {
    aux->st.value = color.value;
    i = aux->st.lin;
    j = aux->st.col;

    m[i][j].value = color.value;
    aux = aux->next;
  } while (aux != f);

  return f;
}

/**
 * Add itens to a queue of visited nodes
 *
 * @param[in] visited_nodes Queue of visited nodes
 * @param[in] matrix_data Matrix data
 * @param[in] lin Number of lines
 * @param[in] col Number of colums
 */
queue_state_t *addItemsToVisitedNodes(queue_state_t *visited_nodes,
                                      state_t **matrix_data, int lin, int col)
{

  while (removed_items)
  {
    queue_state_t *aux = removed_items;
    queue_state_t *aux2 = visited_nodes;
    // queue_print("Removed items: ", (queue_t *)removed_items, print_fila);
    aux = removed_items;
    visited_nodes =
        find_equals(aux2, matrix_data, aux->st.lin, aux->st.col, lin, col);
    queue_remove((queue_t **)&removed_items, (queue_t *)aux);
    free(aux);
  }
  return visited_nodes;
}

/**
 * Print result as requested
 *
 * @param[in] qtdMoves Quantity of steps
 * @param[in] results Array of colors changed
 * @param[in] lin Number of lines
 * @param[in] col Number of colums
 */
void print_final_result(int qtdMoves, int *results, int lin, int col)
{
  printf("%d\n", qtdMoves);
  for (int i = 0; i < lin * col; i++)
  {
    if (results[i] != 0)
      printf("%d ", results[i]);
  }
  printf("\n");
}

/**
 * Performs A* algorithm
 *
 * @param[in] matrix_data The matrix of data
 * @param[in] lin Number of lines
 * @param[in] col Number of colums
 * @param[in] num_colors Number of colors
 */
int *a_star(state_t **matrix_data, int lin, int col, int num_colors)
{

  queue_state_t *destructor = malloc(2 * sizeof(queue_state_t));
  queue_state_t *possible_next = NULL;
  queue_state_t *visited_nodes = NULL;
  int *results = malloc(lin * col * sizeof(int));

  queue_state_t *aux = visited_nodes;
  int flag = 1;
  visited_nodes = find_equals(aux, matrix_data, 0, 0, lin, col);

  // queue_print("visited_nodes: ", (queue_t *)visited_nodes, print_fila);
  int i = 0;
  int n = 7;
  while (!goal(visited_nodes, lin * col))
  {
    // printf("Jogadas: %d\n", i);
    // print_matrix(matrix_data, lin, col);

    possible_next = search_boards(matrix_data, visited_nodes, lin, col, possible_next);
    // queue_print("PossibleNext: ", (queue_t *)possible_next, print_fila);

    state_t next_color = chose_next_color(possible_next, lin, col, visited_nodes);
    // printf("NextColor: %d\n", next_color.value);

    results[i] = next_color.value;

    visited_nodes = color_the_board(visited_nodes, matrix_data, next_color);
    possible_next = remove_all_possible_colors(possible_next, next_color);

    visited_nodes = addItemsToVisitedNodes(visited_nodes, matrix_data, lin, col);
    // queue_print("visited_nodes: : ", (queue_t *)visited_nodes, print_fila);

    i += 1;
  }

  print_final_result(i, results, lin, col);

  return NULL;
}
