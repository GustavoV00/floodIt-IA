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
                           int lin_max, int col_max, int quad, int flag)
{

  if (f != NULL)
  {
    printf("lin: %d || col: %d\n", i, j);
    if (m[i][j].value == f->st.value && m[i][j].visited == 0)
    // if (m[i][j].value == f->st.value && (m[i][j].lin != f->st.lin || m[i][j].col != f->st.col))
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

  // Grows to right
  if (j < col_max - 1 && (quad == QUAD_A || quad == QUAD_D))
  {
    f = find_equals(f, m, i, j + 1, lin_max, col_max, quad, flag);
  }
  // Grows to left
  else if (col_max < j && (quad == QUAD_B || quad == QUAD_C))
  {
    // printf("find_equals: To entrando aqui || quad: %d\n", quad);
    f = find_equals(f, m, i, j - 1, lin_max, col_max, quad, flag);
  }

  if (j > 0)
  {
    f = find_equals(f, m, i, j - 1, lin_max, col_max, quad, flag);
  }

  // Grows up
  if (i < lin_max - 1 && (quad == QUAD_A || quad == QUAD_B))
  {
    f = find_equals(f, m, i + 1, j, lin_max, col_max, quad, flag);
  }

  // Grows down
  else if (lin_max < i && (quad == QUAD_C || quad == QUAD_D))
  {
    f = find_equals(f, m, i - 1, j, lin_max, col_max, quad, flag);
  }

  if (i > 0)
  {
    f = find_equals(f, m, i - 1, j, lin_max, col_max, quad, flag);
  }

  return f;
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

queue_state_t *chose_next_color(queue_state_t *possible_next, int max_lin, int max_col,
                                queue_state_t *f, int num_colors, int quad, state_t **matrix_data)
{
  printf("choose_next_color: entrando\n");
  queue_state_t *visited_nodes_aux = NULL;
  int size = queue_size((queue_t *)possible_next);

  queue_state_t *aux = possible_next;
  printf("size: %d\n", size);

  for (int i = 0; i < size; i++)
  {
    printf("\nexterno: lin: %d || col: %d || value: %d || visisted: %d\n", aux->st.lin, aux->st.col, aux->st.value, aux->st.visited);
    queue_print("possible_next", (queue_t *)possible_next, print_fila);
    printf("\n");
    visited_nodes_aux = find_equals(visited_nodes_aux, matrix_data, aux->st.lin, aux->st.col, max_lin, max_col, quad, 1);
    queue_print("--->visisted_nodes_aux", (queue_t *)visited_nodes_aux, print_fila);
    // queue_print("bbb", (queue_t *)possible_next, print_fila);
    do
    {
      queue_state_t *aux2 = visited_nodes_aux;
      queue_remove((queue_t **)&visited_nodes_aux, (queue_t *)aux2);
      printf("---->do mais interno: lin: %d || col: %d || value: %d || visisted: %d\n", aux2->st.lin, aux2->st.col, aux2->st.value, aux2->st.visited);
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
                             int lin, int col, queue_state_t *possible_next, int num_colors, int quad)
{
  queue_state_t *aux = visited_nodes;

  do
  {
    state_t elem = aux->st;

    // Procura no [i][j+1], [i+1][j], etc...
    possible_next = verify_neighbors(elem, lin, col, matrix, possible_next);

    aux = aux->next;
  } while (aux != visited_nodes);
  queue_print("asdfasdfa", (queue_t *)possible_next, print_fila);
  // queue_print("visited_nodes", (queue_t *)visited_nodes, print_fila);

  aux = possible_next;
  printf("quad: %d\n", quad);
  do
  {
    state_t elem = aux->st;

    printf("lin: %d || col: %d || visited: %d || color: %d\n", elem.lin, elem.col, elem.visited, elem.value);

    aux = aux->next;
  } while (aux != possible_next);
  possible_next = chose_next_color(possible_next, lin, col, visited_nodes, num_colors, quad, matrix);
  printf("sai aqui\n");

  return possible_next;
}

best_color_t best_color(queue_state_t *possible_next, int *colors_count, int quad)
{
  int size = queue_size((queue_t *)possible_next);
  // queue_print("dsfasfda", (queue_t *)possible_next, print_fila);
  int greater = 0;
  int lin = 0;
  int col = 0;
  best_color_t color;
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
  color.color = greater;
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
                                          best_color_t next_color, queue_state_t *visited_nodes)
{
  queue_state_t *aux = f;

  int n = queue_size((queue_t *)f);
  int i = 0;
  while (i < n)
  {

    if (next_color.color == aux->st.value)
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
queue_state_t *color_the_board(queue_state_t *f, state_t **m, best_color_t color)
{
  queue_state_t *aux = f;

  int i;
  int j;
  do
  {
    aux->st.value = color.color;
    i = aux->st.lin;
    j = aux->st.col;

    m[i][j].value = color.color;
    aux = aux->next;
  } while (aux != f);

  return f;
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

best_color_t best_elem_between_quads(best_color_t ncolor_quadA, best_color_t ncolor_quadB, best_color_t ncolor_quadC, best_color_t ncolor_quadD, int num_colors)
{

  if (ncolor_quadA.amount >= ncolor_quadB.amount && ncolor_quadA.amount >= ncolor_quadC.amount && ncolor_quadA.amount >= ncolor_quadD.amount && ncolor_quadA.amount != -1)
  {
    printf("test_A: %d\n", ncolor_quadA.color);
    printf("--> Lin: %d\n", ncolor_quadA.lin);
    printf("--> Col: %d\n", ncolor_quadA.col);
    printf("--> Amount: %d\n\n", ncolor_quadA.amount);
    if (ncolor_quadA.amount < ncolor_quadB.amount + num_colors || ncolor_quadB.amount == -1 || ncolor_quadC.amount == -1 || ncolor_quadD.amount == -1)
      return ncolor_quadA;
    ncolor_quadA.amount = -1;
  }

  if (ncolor_quadB.amount >= ncolor_quadA.amount && ncolor_quadB.amount >= ncolor_quadC.amount && ncolor_quadB.amount >= ncolor_quadD.amount && ncolor_quadB.amount != -1)
  {
    printf("test_B: %d\n", ncolor_quadB.color);
    printf("--> Lin: %d\n", ncolor_quadB.lin);
    printf("--> Col: %d\n", ncolor_quadB.col);
    printf("--> Amount: %d\n", ncolor_quadB.amount);
    if (ncolor_quadB.amount < ncolor_quadC.amount + num_colors || ncolor_quadC.amount == -1 || ncolor_quadD.amount == -1 || ncolor_quadA.amount == -1)
      return ncolor_quadB;
    ncolor_quadB.amount = -1;
  }

  if (ncolor_quadC.amount >= ncolor_quadA.amount && ncolor_quadC.amount >= ncolor_quadB.amount && ncolor_quadC.amount >= ncolor_quadD.amount && ncolor_quadC.amount != -1)
  {
    printf("test_C: %d\n", ncolor_quadC.color);
    printf("--> Lin: %d\n", ncolor_quadC.lin);
    printf("--> Col: %d\n", ncolor_quadC.col);
    printf("--> Amount: %d\n\n", ncolor_quadC.amount);

    if (ncolor_quadC.amount < ncolor_quadD.amount + num_colors || ncolor_quadA.amount == -1 || ncolor_quadB.amount == -1 || ncolor_quadC.amount == -1)
      return ncolor_quadC;

    ncolor_quadC.amount = -1;
  }

  if (ncolor_quadD.amount >= ncolor_quadA.amount && ncolor_quadD.amount >= ncolor_quadB.amount && ncolor_quadD.amount >= ncolor_quadC.amount && ncolor_quadD.amount != -1)
  {
    printf("test_D: %d\n", ncolor_quadD.color);
    printf("--> Lin: %d\n", ncolor_quadD.lin);
    printf("--> Col: %d\n", ncolor_quadD.col);
    printf("--> Amount: %d\n\n", ncolor_quadD.amount);
    if (ncolor_quadD.amount < ncolor_quadA.amount + num_colors || ncolor_quadB.amount == -1 || ncolor_quadC.amount == -1 || ncolor_quadD.amount == -1)
      return ncolor_quadD;
    ncolor_quadD.amount = -1;
  }
  return ncolor_quadA;
}

/**
 * Performs A* algorithm
 *
 * @param[in] matrix_data The matrix of data
 * @param[in] lin Number of lines
 * @param[in] col Number of colums
 * @param[in] num_colors Number of colors
 */
void a_star(state_t **matrix_data, int lin, int col, int num_colors)
{

  queue_state_t *visited_nodes_A = NULL;
  visited_nodes_A = find_equals(visited_nodes_A, matrix_data, 0, 0, lin, col, QUAD_A, 0);

  queue_state_t *visited_nodes_B = NULL;
  visited_nodes_B = find_equals(visited_nodes_B, matrix_data, 0, (col - 1), lin, 0, QUAD_B, 0);

  queue_state_t *visited_nodes_C = NULL;
  visited_nodes_C = find_equals(visited_nodes_C, matrix_data, lin - 1, col - 1, 0, 0, QUAD_C, 0);

  queue_state_t *visited_nodes_D = NULL;
  visited_nodes_D = find_equals(visited_nodes_D, matrix_data, lin - 1, 0, 0, col, QUAD_D, 0);

  result_t *results = malloc(lin * col * sizeof(result_t));

  queue_state_t *possible_next_quadA = NULL;
  queue_state_t *possible_next_quadB = NULL;
  queue_state_t *possible_next_quadC = NULL;
  queue_state_t *possible_next_quadD = NULL;

  queue_print("visited_nodesA", (queue_t *)visited_nodes_A, print_fila);
  queue_print("visited_nodesB", (queue_t *)visited_nodes_B, print_fila);
  queue_print("visited_nodesC", (queue_t *)visited_nodes_C, print_fila);
  queue_print("visited_nodesD", (queue_t *)visited_nodes_D, print_fila);

  best_color_t next_color_quadA;
  best_color_t next_color_quadB;
  best_color_t next_color_quadC;
  best_color_t next_color_quadD;

  next_color_quadA.counter = 0;
  next_color_quadB.counter = 0;
  next_color_quadC.counter = 0;
  next_color_quadD.counter = 0;

  printf("num_colors: %d\n", num_colors);
  int i = 0;
  while (next_color_quadA.amount != -1 || next_color_quadB.amount != -1 || next_color_quadC.amount != -1 || next_color_quadD.amount != -1)
  // while (i < 12)
  {
    int *colors_count_a = malloc(sizeof(int) * num_colors);
    int *colors_count_b = malloc(sizeof(int) * num_colors);
    int *colors_count_c = malloc(sizeof(int) * num_colors);
    int *colors_count_d = malloc(sizeof(int) * num_colors);

    if (possible_next_quadA != NULL || i == 0)
    {
      next_color_quadA.amount = 0;
      possible_next_quadA = search_boards(matrix_data, visited_nodes_A, lin, col, possible_next_quadA, num_colors, QUAD_A);
      printf("arroz\n");
      next_color_quadA = best_color(possible_next_quadA, colors_count_a, QUAD_A);
    }
    else
      next_color_quadA.amount = -1;

    if (possible_next_quadB != NULL || i == 0)
    {
      next_color_quadB.amount = 0;
      possible_next_quadB = search_boards(matrix_data, visited_nodes_B, lin / 2, col, possible_next_quadB, num_colors, QUAD_B);
      next_color_quadB = best_color(possible_next_quadB, colors_count_b, QUAD_B);
    }
    else
      next_color_quadB.amount = -1;

    if (possible_next_quadC != NULL || i == 0)
    {
      next_color_quadC.amount = 0;
      possible_next_quadC = search_boards(matrix_data, visited_nodes_C, lin, col, possible_next_quadC, num_colors, QUAD_C);
      next_color_quadC = best_color(possible_next_quadC, colors_count_c, QUAD_C);
    }
    else
      next_color_quadC.amount = -1;

    if (possible_next_quadD != NULL || i == 0)
    {
      next_color_quadD.amount = 0;
      possible_next_quadD = search_boards(matrix_data, visited_nodes_D, lin, col, possible_next_quadD, num_colors, QUAD_D);
      next_color_quadD = best_color(possible_next_quadD, colors_count_d, QUAD_D);
    }
    else
      next_color_quadD.amount = -1;

    best_color_t next_color = best_elem_between_quads(next_color_quadA, next_color_quadB, next_color_quadC, next_color_quadD, num_colors);
    results[i].result = next_color.color;
    results[i].quadrant = next_color.quadrant;

    queue_print("visited_nodes_quadA", (queue_t *)visited_nodes_A, print_fila);
    queue_print("visited_nodes_quadB", (queue_t *)visited_nodes_B, print_fila);
    queue_print("visited_nodes_quadC", (queue_t *)visited_nodes_C, print_fila);
    queue_print("visited_nodes_quadD", (queue_t *)visited_nodes_D, print_fila);

    printf("\n");

    queue_print("possible_nextA", (queue_t *)possible_next_quadA, print_fila);
    queue_print("possible_nextB", (queue_t *)possible_next_quadB, print_fila);
    queue_print("possible_nextC", (queue_t *)possible_next_quadC, print_fila);
    queue_print("possible_nextD", (queue_t *)possible_next_quadD, print_fila);

    printf("Jogadas: %d\n", i);
    print_matrix(matrix_data, lin, col);

    if (next_color.quadrant == QUAD_A && possible_next_quadA != NULL)
    {
      visited_nodes_A = color_the_board(visited_nodes_A, matrix_data, next_color);
      possible_next_quadA = remove_all_possible_colors(possible_next_quadA, next_color, visited_nodes_A);
      next_color_quadA.counter += 1;
    }
    else if (next_color.quadrant == QUAD_B && possible_next_quadB != NULL)
    {
      visited_nodes_B = color_the_board(visited_nodes_B, matrix_data, next_color);
      possible_next_quadB = remove_all_possible_colors(possible_next_quadB, next_color, visited_nodes_B);
      next_color_quadB.counter += 1;
    }
    else if (next_color.quadrant == QUAD_C && possible_next_quadC != NULL)
    {
      visited_nodes_C = color_the_board(visited_nodes_C, matrix_data, next_color);
      possible_next_quadC = remove_all_possible_colors(possible_next_quadC, next_color, visited_nodes_C);
      next_color_quadC.counter += 1;
    }
    else if (next_color.quadrant == QUAD_D && possible_next_quadD != NULL)
    {
      visited_nodes_D = color_the_board(visited_nodes_D, matrix_data, next_color);
      possible_next_quadD = remove_all_possible_colors(possible_next_quadD, next_color, visited_nodes_D);
      next_color_quadD.counter += 1;
    }

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

  int colors[3] = {matrix_data[0][col - 1].value, matrix_data[lin - 1][0].value, matrix_data[lin - 1][col - 1].value};

  results[i].result = colors[0];
  results[i].quadrant = QUAD_B;

  i += 1;

  results[i].result = colors[1];
  results[i].quadrant = QUAD_D;

  i += 1;

  results[i].result = colors[2];
  results[i].quadrant = QUAD_C;

  for (int k = 0; k < lin; k++)
  {
    for (int j = 0; j < col; j++)
    {
      matrix_data[k][j].value = colors[2];
    }
  }

  print_matrix(matrix_data, lin, col);
  print_final_result(i, results, lin, col);
}
