// TRAB1 IA - 2021-2
// GUSTAVO VALENTE NUNES GRR20182557
// BRUNO EDUARDO FARIAS GRR20186715

#include "../include/includes.h"
#include "../include/queue.h"
#include "../include/utils.h"
#include <assert.h>
#include <unistd.h>

queue_state_t *removed_items = NULL;
int ADJ_ALL = 0;

// int adj = -1;

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
      neighbor.value != 0 && neighbor.in_board == 0 && neighbor.visited == 0)
  {
    int i = neighbor.lin;
    int j = neighbor.col;
    m[i][j].in_board = 1;
    m[i][j].visited = 1;
    f = init_elem(neighbor, f);
    printf("to entrando aquiaaa\n");
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
  printf("lin: %d || col: %d\n", i, j);
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
                           int lin_max, int col_max, int quad)
{

  if (f != NULL)
  {
    // printf("lin: %d || col: %d || quad: %d\n", i, j, quad);
    if (m[i][j].value == f->st.value && m[i][j].visited == 0)
    // if (m[i][j].value == f->st.value && (m[i][j].lin != f->st.lin || m[i][j].col != f->st.col))
    {
      f = init_elem(m[i][j], f);
      m[i][j].visited = 1;
      // m[i][j].quadrant = quad;
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
    // m[i][j].quadrant = quad;
  }

  // Grows to right
  if (j < col_max - 1 && (quad == QUAD_A || quad == QUAD_D))
  {
    f = find_equals(f, m, i, j + 1, lin_max, col_max, quad);
  }
  // Grows to left
  else if (col_max < j && (quad == QUAD_B || quad == QUAD_C))
  {
    // printf("find_equals: To entrando aqui || quad: %d\n", quad);
    f = find_equals(f, m, i, j - 1, lin_max, col_max, quad);
  }

  if (j > 0)
  {
    f = find_equals(f, m, i, j - 1, lin_max, col_max, quad);
  }

  // Grows up
  if (i < lin_max - 1 && (quad == QUAD_A || quad == QUAD_B))
  {
    f = find_equals(f, m, i + 1, j, lin_max, col_max, quad);
  }

  // Grows down
  else if (lin_max < i && (quad == QUAD_C || quad == QUAD_D))
  {
    f = find_equals(f, m, i - 1, j, lin_max, col_max, quad);
  }

  if (i > 0)
  {
    f = find_equals(f, m, i - 1, j, lin_max, col_max, quad);
  }

  return f;
}

/**
 * Chooses (using a heurist funcion and total cost) the next color
 *
 * @param[in] possible_next Queue of next possible options
 * @param[in] max_lin Quantity of board lines
 * @param[in] max_col Quantity of board columns
 * @param[in] f Queue of visited nodes
 */

queue_state_t *choose_next_color(queue_state_t *possible_next, int max_lin, int max_col,
                                 queue_state_t *f, int num_colors, int quad, state_t **matrix_data)
{
  printf("choose_next_color: entrando\n");
  queue_state_t *visited_nodes_aux = NULL;
  int size = queue_size((queue_t *)possible_next);

  queue_state_t *aux = possible_next;
  printf("size: %d\n", size);

  for (int i = 0; i < size; i++)
  {
    // printf("\nexterno: lin: %d || col: %d || value: %d || visisted: %d\n", aux->st.lin, aux->st.col, aux->st.value, aux->st.visited);
    // queue_print("possible_next", (queue_t *)possible_next, print_fila);
    printf("\n");
    visited_nodes_aux = find_equals(visited_nodes_aux, matrix_data, aux->st.lin, aux->st.col, max_lin, max_col, quad);
    // queue_print("--->visisted_nodes_aux", (queue_t *)visited_nodes_aux, print_fila);
    // queue_print("bbb", (queue_t *)possible_next, print_fila);
    do
    {
      queue_state_t *aux2 = visited_nodes_aux;
      queue_remove((queue_t **)&visited_nodes_aux, (queue_t *)aux2);
      // printf("---->do mais interno: lin: %d || col: %d || value: %d || visisted: %d\n", aux2->st.lin, aux2->st.col, aux2->st.value, aux2->st.visited);
      if (aux2->st.visited == 0)
      {
        aux2->st.visited = 1;
        queue_append((queue_t **)&possible_next, (queue_t *)aux2);
      }

    } while (visited_nodes_aux != NULL);

    aux = aux->next;
  }
  printf("choose_next_color: saindo\n");

  // The most counted color

  // Count the amount of the neighboors colors
  // colors[elem.value] = queue_size((queue_t *)visited_nodes);
  // printf("colors: %d\n", colors[elem.value]);

  // printf("greater_index%d : %d\n", quad, greater_index);
  return possible_next;
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
                             int lin, int col, queue_state_t *possible_next, int quad, int num_colors)
{
  queue_state_t *aux = visited_nodes;

  do
  {
    state_t elem = aux->st;

    // Procura no [i][j+1], [i+1][j], etc...
    possible_next = verify_neighbors(elem, lin, col, matrix, possible_next);

    aux = aux->next;
  } while (aux != visited_nodes);
  aux = possible_next;
  printf("quad: %d\n", quad);
  queue_print("asdfasdfa", (queue_t *)possible_next, print_fila);
  if (possible_next != NULL)
  {
    do
    {
      state_t elem = aux->st;

      printf("lin: %d || col: %d || visited: %d || color: %d\n", elem.lin, elem.col, elem.visited, elem.value);

      aux = aux->next;
    } while (aux != possible_next);
    possible_next = choose_next_color(possible_next, lin, col, visited_nodes, num_colors, quad, matrix);
  }
  printf("sai aqui\n");

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
  printf("result_test = (%d * %d) + (%d * %d) = %d\n", side1, side1, side2, side2, result);
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

state_t best_color(queue_state_t *possible_next, int max_lin, int max_col, int flag, int *colors_count, int quad, int num_colors)
{

  if (flag == 0)
  {
    queue_state_t *aux = possible_next;

    state_t best_elem = aux->st;
    best_elem.h_n = calc_heuristic(best_elem.lin, best_elem.col, max_lin, max_col);
    int best = best_elem.g_n + best_elem.h_n;
    best_elem.f_n = best;

    state_t new_elem;
    int new_best;
    aux = aux->next;
    do
    {
      new_elem = aux->st;
      new_elem.h_n = calc_heuristic(best_elem.lin, best_elem.col, max_lin, max_col);
      new_best = new_elem.g_n + new_elem.h_n;
      new_elem.f_n = new_best;
      if (new_best <= best)
      {
        best_elem = new_elem;
        best = new_best;
      }
      aux = aux->next;
    } while (aux != possible_next);

    printf("best_elemn: %d || color: %d || lin: %d || col: %d\n", best_elem.f_n, best_elem.value, best_elem.lin, best_elem.col);
    return best_elem;
  }
  for (int i = 0; i < num_colors; i++)
  {
    colors_count[i] = 0;
  }

  int size = queue_size((queue_t *)possible_next);
  // queue_print("dsfasfda", (queue_t *)possible_next, print_fila);
  int greater = 0;
  int lin = 0;
  int col = 0;
  state_t color;
  queue_state_t *aux2 = possible_next;
  for (int i = 0; i < size; i++)
  {
    printf("quad:%d || Color_count: %d || amount: %d || color: %d\n", quad, colors_count[aux2->st.value], color.amount, aux2->st.value);
    colors_count[aux2->st.value] += 1;
    printf("quad:%d || Color_count: %d || amount: %d || color: %d\n", quad, colors_count[aux2->st.value], color.amount, aux2->st.value);
    if (colors_count[aux2->st.value] > colors_count[greater])
    {
      greater = aux2->st.value;
      lin = aux2->st.lin;
      col = aux2->st.col;
    }
    aux2 = aux2->next;
  }
  color.amount = colors_count[greater];
  color.value = greater;
  color.quadrant = quad;
  color.lin = lin;
  color.col = col;
  printf("sai aqui2\n");

  printf("\n");
  return color;
}

/**
 * Clears the queue
 *
 * @param[in] f Queue to be cleared
 * @param[in] next_color Next color state to ble cleared
 */
queue_state_t *remove_all_possible_colors(queue_state_t *f,
                                          state_t next_color, queue_state_t *visited_nodes)
{
  queue_state_t *aux = f;

  int n = queue_size((queue_t *)f);
  int i = 0;
  while (i < n)
  {

    if (next_color.value == aux->st.value)
    {
      queue_state_t *aux2 = aux;
      // removed_items = init_elem(aux2->st, removed_items);

      aux = aux->prev;
      queue_remove((queue_t **)&f, (queue_t *)aux2);
      queue_append((queue_t **)&visited_nodes, (queue_t *)aux2);

      assert(fila_correta(f));             // estrutura continua correta
      assert(fila_correta(visited_nodes)); // estrutura continua correta
      // assert(aux2->prev == NULL); // testa elemento removido
      // assert(aux2->next == NULL); // testa elemento removido
      // free(aux2);
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
queue_state_t *color_the_board(queue_state_t *f, state_t **m, state_t color, int quad)
{
  queue_state_t *aux = f;

  int i;
  int j;
  do
  {
    aux->st.value = color.value;
    i = aux->st.lin;
    j = aux->st.col;

    // aux->st.quadrant = quad;
    m[i][j].quadrant = quad;
    m[i][j].value = color.value;

    aux = aux->next;
  } while (aux != f);

  aux = f;

  do
  {

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
                                      state_t **matrix_data, int lin, int col, int quad)
{

  while (removed_items)
  {
    queue_state_t *aux = removed_items;
    queue_state_t *aux2 = visited_nodes;
    // queue_print("Removed items: ", (queue_t *)removed_items, print_fila);
    aux = removed_items;
    visited_nodes =
        find_equals(aux2, matrix_data, aux->st.lin, aux->st.col, lin, col, quad);
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
void print_final_result(int qtdMoves, result_t *results, int lin, int col)
{
  printf("%d\n", qtdMoves);
  for (int i = 0; i < qtdMoves; i++)
  {
    if (results[i].result != 0)
    {
      switch (results[i].quadrant)
      {
      case QUAD_A:
        printf("a ");
        break;
      case QUAD_B:
        printf("b ");
        break;
      case QUAD_C:
        printf("c ");
        break;
      case QUAD_D:
        printf("d ");
        break;
      }
      printf("%d ", results[i].result);
    }
  }
  printf("\n");
}

state_t best_elem_between_quads(state_t ncolor_quadA, state_t ncolor_quadB, state_t ncolor_quadC, state_t ncolor_quadD, int flag, int num_colors)
{
  if (flag == 0)
  {
    if (ncolor_quadA.f_n >= ncolor_quadB.f_n && ncolor_quadA.f_n >= ncolor_quadC.f_n && ncolor_quadA.f_n >= ncolor_quadD.f_n && ncolor_quadA.f_n != -1)
    {
      printf("test_A: %d\n", ncolor_quadA.f_n);
      ncolor_quadA.quadrant = QUAD_A;
      return ncolor_quadA;
    }

    if (ncolor_quadB.f_n >= ncolor_quadA.f_n && ncolor_quadB.f_n >= ncolor_quadC.f_n && ncolor_quadB.f_n >= ncolor_quadD.f_n && ncolor_quadB.f_n != -1)
    {
      printf("test_B: %d\n", ncolor_quadB.f_n);
      ncolor_quadB.quadrant = QUAD_B;
      return ncolor_quadB;
    }

    if (ncolor_quadC.f_n >= ncolor_quadA.f_n && ncolor_quadC.f_n >= ncolor_quadB.f_n && ncolor_quadC.f_n >= ncolor_quadD.f_n && ncolor_quadC.f_n != -1)
    {
      printf("test_C: %d\n", ncolor_quadC.f_n);
      ncolor_quadC.quadrant = QUAD_C;
      return ncolor_quadC;
    }

    if (ncolor_quadD.f_n >= ncolor_quadA.f_n && ncolor_quadD.f_n >= ncolor_quadB.f_n && ncolor_quadD.f_n >= ncolor_quadC.f_n && ncolor_quadD.f_n != -1)
    {
      printf("test_D: %d\n", ncolor_quadD.f_n);
      ncolor_quadD.quadrant = QUAD_D;
      return ncolor_quadD;
    }
  }
  else
  {
    if (ncolor_quadA.amount >= ncolor_quadB.amount && ncolor_quadA.amount >= ncolor_quadC.amount && ncolor_quadA.amount >= ncolor_quadD.amount && ncolor_quadA.amount != -1)
    {
      printf("test_A: %d\n", ncolor_quadA.value);
      printf("--> Lin: %d\n", ncolor_quadA.lin);
      printf("--> Col: %d\n", ncolor_quadA.col);
      printf("--> Amount: %d\n\n", ncolor_quadA.amount);
      return ncolor_quadA;
    }

    if (ncolor_quadB.amount >= ncolor_quadA.amount && ncolor_quadB.amount >= ncolor_quadC.amount && ncolor_quadB.amount >= ncolor_quadD.amount && ncolor_quadB.amount != -1)
    {
      printf("test_B: %d\n", ncolor_quadB.value);
      printf("--> Lin: %d\n", ncolor_quadB.lin);
      printf("--> Col: %d\n", ncolor_quadB.col);
      printf("--> Amount: %d\n", ncolor_quadB.amount);
      return ncolor_quadB;
    }

    if (ncolor_quadC.amount >= ncolor_quadA.amount && ncolor_quadC.amount >= ncolor_quadB.amount && ncolor_quadC.amount >= ncolor_quadD.amount && ncolor_quadC.amount != -1)
    {
      printf("test_C: %d\n", ncolor_quadC.value);
      printf("--> Lin: %d\n", ncolor_quadC.lin);
      printf("--> Col: %d\n", ncolor_quadC.col);
      printf("--> Amount: %d\n\n", ncolor_quadC.amount);

      return ncolor_quadC;
    }

    if (ncolor_quadD.amount >= ncolor_quadA.amount && ncolor_quadD.amount >= ncolor_quadB.amount && ncolor_quadD.amount >= ncolor_quadC.amount && ncolor_quadD.amount != -1)
    {
      printf("test_D: %d\n", ncolor_quadD.value);
      printf("--> Lin: %d\n", ncolor_quadD.lin);
      printf("--> Col: %d\n", ncolor_quadD.col);
      printf("--> Amount: %d\n\n", ncolor_quadD.amount);
      return ncolor_quadD;
    }
    return ncolor_quadA;
  }
}

queue_state_t *append_all(queue_state_t *q1, queue_state_t *q2)
{
  if (q2 != NULL)
  {
    queue_state_t *aux = q2;
    do
    {
      queue_state_t *elem = aux;

      queue_remove((queue_t **)&aux, (queue_t *)elem);
      // q1 = init_elem(elem->st, q1);
      queue_append((queue_t **)&q1, (queue_t *)elem);

    } while (aux != NULL);
  }

  return q1;
}

queue_state_t *delete_all(queue_state_t *q)
{
  if (q != NULL)
  {
    queue_state_t *aux = q;
    do
    {
      queue_state_t *elem = aux;
      queue_remove((queue_t **)&aux, (queue_t *)elem);
    } while (aux != NULL);
  }

  return NULL;
}

int verify_adjacent_quads(int lin, int col, state_t **m, queue_state_t *v_a, queue_state_t *v_b, queue_state_t *v_c, queue_state_t *v_d, queue_state_t *p_a, queue_state_t *p_b, queue_state_t *p_c, queue_state_t *p_d)
{
  if (ADJ_ALL == 1)
    return -1;
  printf("verify_adjacent_quads\n");
  for (int i = 0; i < col - 1; i++)
  {
    printf("quadrants: %d e %d || lin: %d || col: %d || color: %d\n", m[0][i].quadrant, m[0][i + 1].quadrant, 0, i, m[0][i].value);
    if (m[0][i].quadrant != -1 && m[0][i + 1].quadrant != -1 && m[0][i].quadrant != m[0][i + 1].quadrant)
    {
      printf("A e B vizinhos\n");
      // ADJ_AB_FLAG = 1;
      return ADJ_AB;
    }
    if (m[lin - 1][i].quadrant != -1 && m[lin - 1][i + 1].quadrant != -1 && m[lin - 1][i].quadrant != m[lin - 1][i + 1].quadrant)
    {
      printf("D e C vizinhos\n");
      // ADJ_DC_FLAG = 1;
      return ADJ_DC;
    }
  }

  for (int i = 0; i < lin - 1; i++)
  {
    printf("quadrants: %d e %d || lin: %d || col: %d || color: %d\n", m[0][i].quadrant, m[0][i + 1].quadrant, 0, i, m[0][i].value);
    if (m[i][0].quadrant != -1 && m[i + 1][0].quadrant != -1 && m[i][0].quadrant != m[i + 1][0].quadrant)
    {
      printf("A e D vizinhos\n");
      return ADJ_AD;
    }
    if (m[i][col - 1].quadrant != -1 && m[i + 1][col - 1].quadrant != -1 && m[i][col - 1].quadrant != m[i + 1][col - 1].quadrant)
    {
      printf("B e C vizinhos\n");
      return ADJ_BC;
    }
  }
  return -1;
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

  queue_state_t *visited_nodes_A = NULL;
  visited_nodes_A = find_equals(visited_nodes_A, matrix_data, 0, 0, lin, col, QUAD_A);

  queue_state_t *visited_nodes_B = NULL;
  visited_nodes_B = find_equals(visited_nodes_B, matrix_data, 0, (col - 1), lin, 0, QUAD_B);

  queue_state_t *visited_nodes_C = NULL;
  visited_nodes_C = find_equals(visited_nodes_C, matrix_data, lin - 1, col - 1, 0, 0, QUAD_C);

  queue_state_t *visited_nodes_D = NULL;
  visited_nodes_D = find_equals(visited_nodes_D, matrix_data, lin - 1, 0, 0, col, QUAD_D);

  queue_state_t *possible_next_quadA = NULL;
  queue_state_t *possible_next_quadB = NULL;
  queue_state_t *possible_next_quadC = NULL;
  queue_state_t *possible_next_quadD = NULL;

  result_t *results = malloc(lin * col * sizeof(result_t));

  state_t next_color_quadA;
  state_t next_color_quadB;
  state_t next_color_quadC;
  state_t next_color_quadD;

  int colors_count[num_colors];

  int left_condition = -1;
  // int quad = choose_quadrant(matrix_data, lin, col, num_colors);

  queue_print("visited_nodesA", (queue_t *)visited_nodes_A, print_fila);
  queue_print("visited_nodesB", (queue_t *)visited_nodes_B, print_fila);
  queue_print("visited_nodesC", (queue_t *)visited_nodes_C, print_fila);
  queue_print("visited_nodesD", (queue_t *)visited_nodes_D, print_fila);

  int i = 0;
  int flag = 0;
  // int n = 7;
  // while (next_color_quadA.f_n != left_condition || next_color_quadB.f_n != left_condition || next_color_quadC.f_n != left_condition || next_color_quadD.f_n != left_condition)
  while (i < 140)
  {
    printf("Jogadas: %d\n", i);
    print_matrix(matrix_data, lin, col);
    if (visited_nodes_B == NULL && visited_nodes_C == NULL && visited_nodes_D == NULL && possible_next_quadB == NULL && possible_next_quadC == NULL && possible_next_quadD == NULL)
    {
      printf("ADJ_all\n");
      flag = 1;
      ADJ_ALL = 1;
    }

    int adj = verify_adjacent_quads(lin, col, matrix_data, visited_nodes_A, visited_nodes_B, visited_nodes_C, visited_nodes_D, possible_next_quadA, possible_next_quadB, possible_next_quadC, possible_next_quadD);
    if (adj == ADJ_AB)
    {
      state_t aux_next_color = visited_nodes_B->st;
      visited_nodes_A = append_all(visited_nodes_A, visited_nodes_B);
      visited_nodes_B = NULL;

      possible_next_quadA = append_all(possible_next_quadA, possible_next_quadB);
      possible_next_quadB = NULL;

      possible_next_quadA = remove_all_possible_colors(possible_next_quadA, aux_next_color, visited_nodes_A);
      visited_nodes_A = color_the_board(visited_nodes_A, matrix_data, aux_next_color, QUAD_A);
    }
    else if (adj == ADJ_DC)
    {

      state_t aux_next_color = visited_nodes_C->st;
      if (possible_next_quadD != NULL || visited_nodes_D != NULL)
      {
        visited_nodes_D = append_all(visited_nodes_D, visited_nodes_C);
        visited_nodes_C = NULL;

        possible_next_quadD = append_all(possible_next_quadD, possible_next_quadC);
        possible_next_quadC = NULL;

        possible_next_quadD = remove_all_possible_colors(possible_next_quadD, aux_next_color, visited_nodes_D);
        visited_nodes_D = color_the_board(visited_nodes_D, matrix_data, aux_next_color, QUAD_D);
      }
      else if (visited_nodes_C != NULL || possible_next_quadC != NULL)
      {
        visited_nodes_A = append_all(visited_nodes_A, visited_nodes_C);
        visited_nodes_C = NULL;

        possible_next_quadA = append_all(possible_next_quadA, possible_next_quadC);
        possible_next_quadC = NULL;

        possible_next_quadA = remove_all_possible_colors(possible_next_quadA, aux_next_color, visited_nodes_A);
        visited_nodes_A = color_the_board(visited_nodes_A, matrix_data, aux_next_color, QUAD_A);
      }
      else
      {
        visited_nodes_A = append_all(visited_nodes_A, visited_nodes_B);
        visited_nodes_B = NULL;

        possible_next_quadA = append_all(possible_next_quadA, possible_next_quadB);
        possible_next_quadB = NULL;

        possible_next_quadA = remove_all_possible_colors(possible_next_quadA, aux_next_color, visited_nodes_A);
        visited_nodes_A = color_the_board(visited_nodes_A, matrix_data, aux_next_color, QUAD_A);
      }
    }
    else if (adj == ADJ_BC)
    {
      if (possible_next_quadB != NULL || visited_nodes_B != NULL)
      {
        printf("adj_bc2\n");
        state_t aux_next_color = visited_nodes_C->st;
        visited_nodes_B = append_all(visited_nodes_B, visited_nodes_C);
        visited_nodes_C = NULL;

        possible_next_quadB = append_all(possible_next_quadB, possible_next_quadC);
        possible_next_quadC = NULL;

        possible_next_quadB = remove_all_possible_colors(possible_next_quadB, aux_next_color, visited_nodes_B);
        visited_nodes_B = color_the_board(visited_nodes_B, matrix_data, aux_next_color, QUAD_B);
      }
      else if (possible_next_quadC != NULL || visited_nodes_C != NULL)
      {
        printf("adj_bc2\n");
        state_t aux_next_color = visited_nodes_C->st;
        visited_nodes_A = append_all(visited_nodes_A, visited_nodes_C);
        visited_nodes_C = NULL;

        possible_next_quadA = append_all(possible_next_quadA, possible_next_quadC);
        possible_next_quadC = NULL;

        possible_next_quadA = remove_all_possible_colors(possible_next_quadA, aux_next_color, visited_nodes_A);
        visited_nodes_A = color_the_board(visited_nodes_A, matrix_data, aux_next_color, QUAD_A);
      }
      else
      {
        state_t aux_next_color = visited_nodes_D->st;
        visited_nodes_A = append_all(visited_nodes_A, visited_nodes_D);
        visited_nodes_D = NULL;

        possible_next_quadA = append_all(possible_next_quadA, possible_next_quadD);
        possible_next_quadD = NULL;

        possible_next_quadA = remove_all_possible_colors(possible_next_quadA, aux_next_color, visited_nodes_A);
        visited_nodes_A = color_the_board(visited_nodes_A, matrix_data, aux_next_color, QUAD_A);
      }
    }
    else if (adj == ADJ_AD)
    {
      state_t aux_next_color = visited_nodes_D->st;
      visited_nodes_A = append_all(visited_nodes_A, visited_nodes_D);
      visited_nodes_D = NULL;

      possible_next_quadA = append_all(possible_next_quadA, possible_next_quadD);
      possible_next_quadD = NULL;

      possible_next_quadA = remove_all_possible_colors(possible_next_quadA, aux_next_color, visited_nodes_A);
      visited_nodes_A = color_the_board(visited_nodes_A, matrix_data, aux_next_color, QUAD_A);
    }
    else
    {
      if (possible_next_quadA != NULL || i == 0)
      {
        possible_next_quadA = search_boards(matrix_data, visited_nodes_A, lin, col, possible_next_quadA, QUAD_A, num_colors);
        if (possible_next_quadA != NULL)
          next_color_quadA = best_color(possible_next_quadA, lin / 2, col / 2, flag, colors_count, QUAD_A, num_colors);
        else
          next_color_quadA.f_n = left_condition;
      }
      else
        next_color_quadA.f_n = left_condition;

      // printf("\n");

      if ((possible_next_quadB != NULL || i == 0))
      {
        possible_next_quadB = search_boards(matrix_data, visited_nodes_B, lin, col, possible_next_quadB, QUAD_B, num_colors);
        if (possible_next_quadB != NULL)
          next_color_quadB = best_color(possible_next_quadB, lin / 2, col / 2, flag, colors_count, QUAD_B, num_colors);
        else
          next_color_quadB.f_n = left_condition;
      }
      else
        next_color_quadB.f_n = left_condition;

      if (possible_next_quadC != NULL || i == 0)
      {
        possible_next_quadC = search_boards(matrix_data, visited_nodes_C, lin, col, possible_next_quadC, QUAD_C, num_colors);
        if (possible_next_quadC != NULL)
          next_color_quadC = best_color(possible_next_quadC, lin / 2, col / 2, flag, colors_count, QUAD_C, num_colors);
        else
          next_color_quadC.f_n = left_condition;
      }
      else
        next_color_quadC.f_n = left_condition;

      if (possible_next_quadD != NULL || i == 0)
      {
        possible_next_quadD = search_boards(matrix_data, visited_nodes_D, lin, col, possible_next_quadD, QUAD_D, num_colors);
        if (possible_next_quadD != NULL)
          next_color_quadD = best_color(possible_next_quadD, lin / 2, col / 2, flag, colors_count, QUAD_D, num_colors);
        else
          next_color_quadD.f_n = left_condition;
      }
      else
        next_color_quadD.f_n = left_condition;

      state_t next_color = best_elem_between_quads(next_color_quadA, next_color_quadB, next_color_quadC, next_color_quadD, flag, num_colors);

      printf("Jogadas: %d\n", i);
      print_matrix(matrix_data, lin, col);

      printf("quad_A f_n: %d\n", next_color_quadA.f_n);
      printf("quad_B f_n: %d\n", next_color_quadB.f_n);
      printf("quad_C f_n: %d\n", next_color_quadC.f_n);
      printf("quad_D f_n: %d\n", next_color_quadD.f_n);

      printf("next_color: %d\n", next_color.value);
      printf("next_quadrant: %d\n", next_color.quadrant);
      printf("coord: (%d,%d)\n", next_color.lin, next_color.col);
      printf("quad: (%d)\n", next_color.quadrant);

      results[i].result = next_color.value;
      results[i].quadrant = next_color.quadrant;
      matrix_data[next_color.lin][next_color.col].quadrant = next_color.quadrant;

      if (next_color.quadrant == QUAD_A)
      {
        possible_next_quadA = remove_all_possible_colors(possible_next_quadA, next_color, visited_nodes_A);
        visited_nodes_A = color_the_board(visited_nodes_A, matrix_data, next_color, QUAD_A);
      }
      else if (next_color.quadrant == QUAD_B)
      {
        possible_next_quadB = remove_all_possible_colors(possible_next_quadB, next_color, visited_nodes_B);
        visited_nodes_B = color_the_board(visited_nodes_B, matrix_data, next_color, QUAD_B);
      }
      else if (next_color.quadrant == QUAD_C)
      {
        possible_next_quadC = remove_all_possible_colors(possible_next_quadC, next_color, visited_nodes_C);
        visited_nodes_C = color_the_board(visited_nodes_C, matrix_data, next_color, QUAD_C);
      }
      else if (next_color.quadrant == QUAD_D)
      {
        possible_next_quadD = remove_all_possible_colors(possible_next_quadD, next_color, visited_nodes_D);
        visited_nodes_D = color_the_board(visited_nodes_D, matrix_data, next_color, QUAD_D);
      }
    }
    print_matrix_quadrant(matrix_data, lin, col);
    printf("\n");

    queue_print("visited_nodes_quadA", (queue_t *)visited_nodes_A, print_fila);
    queue_print("visited_nodes_quadB", (queue_t *)visited_nodes_B, print_fila);
    queue_print("visited_nodes_quadC", (queue_t *)visited_nodes_C, print_fila);
    queue_print("visited_nodes_quadD", (queue_t *)visited_nodes_D, print_fila);

    printf("\n");

    queue_print("possible_nextA", (queue_t *)possible_next_quadA, print_fila);
    queue_print("possible_nextB", (queue_t *)possible_next_quadB, print_fila);
    queue_print("possible_nextC", (queue_t *)possible_next_quadC, print_fila);
    queue_print("possible_nextD", (queue_t *)possible_next_quadD, print_fila);

    i += 1;
  }

  print_matrix(matrix_data, lin, col);
  print_final_result(i, results, lin, col);

  return NULL;
}