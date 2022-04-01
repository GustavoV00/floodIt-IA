#include "../include/graph.h"
#include "../include/includes.h"
#include "../include/queue.h"
#include "../include/utils.h"

void print_fila(void *ptr) {
  struct queue_state_t *elem = ptr;

  if (!elem)
    return;

  elem->prev ? printf("%d", elem->prev->st.value) : printf("*");
  printf("<%d>", elem->st.value);
  elem->prev ? printf("%d", elem->next->st.value) : printf("*");
}

bool goal(struct queue_state_t *queue, int tam) {

  if (queue_size((queue_t *)queue) != tam)
    return false;

  return true;
}

queue_state_t *init_elem(state_t elem, queue_state_t *f) {
  queue_state_t *root_elem = (queue_state_t *)malloc(sizeof(queue_state_t));
  root_elem->prev = NULL;
  root_elem->next = NULL;
  root_elem->st = elem;

  queue_append((queue_t **)&f, (queue_t *)root_elem);
  return f;
}

queue_state_t *equals_neighbors(state_t **m, queue_state_t *f, state_t value1,
                                state_t neighbor) {
  if (value1.value != neighbor.value)
    f = init_elem(neighbor, f);

  return f;
}

// VERIFICA OS VIZINHOS
queue_state_t *verify_neighbors(state_t elem, int lin_max, int col_max,
                                state_t **matrix,
                                queue_state_t *possible_next) {
  int i = elem.lin;
  int j = elem.col;
  if (i == 0) {
    possible_next =
        equals_neighbors(matrix, possible_next, matrix[i][j], matrix[i][j + 1]);

    possible_next =
        equals_neighbors(matrix, possible_next, matrix[i][j], matrix[i + 1][j]);
    if (j > 0)
      possible_next = equals_neighbors(matrix, possible_next, matrix[i][j],
                                       matrix[i][j - 1]);
    return possible_next;
  }
  if (i == lin_max) {
    possible_next =
        equals_neighbors(matrix, possible_next, matrix[i][j], matrix[i][j + 1]);
    possible_next =
        equals_neighbors(matrix, possible_next, matrix[i][j], matrix[i - 1][j]);
    if (j > 0)
      possible_next = equals_neighbors(matrix, possible_next, matrix[i][j],
                                       matrix[i][j - 1]);
    return possible_next;
  }
  if (j == 0) {
    possible_next =
        equals_neighbors(matrix, possible_next, matrix[i][j], matrix[i][j + 1]);
    possible_next =
        equals_neighbors(matrix, possible_next, matrix[i][j], matrix[i + 1][j]);
    if (i > 0)
      possible_next = equals_neighbors(matrix, possible_next, matrix[i][j],
                                       matrix[i - 1][j]);
  }
  return possible_next;

  if (j == col_max) {
    possible_next =
        equals_neighbors(matrix, possible_next, matrix[i][j], matrix[i][j - 1]);
    possible_next =
        equals_neighbors(matrix, possible_next, matrix[i][j], matrix[i + 1][j]);
    if (i > 1)
      possible_next = equals_neighbors(matrix, possible_next, matrix[i][j],
                                       matrix[i + 1][j]);

    return possible_next;
  }
  printf("Deu merda aqui\n");
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

queue_state_t *find_equals(queue_state_t *f, state_t **m, int i, int j,
                           int lin_max, int col_max, int flag) {

  if (f != NULL) {
    // printf("%d || %d e %d \n", m[i][j].value, i, j);
    // if (m[i][j].visited == 1) {
    if (m[i][j].value == f->st.value && m[i][j].visited == 0) {
      printf("%d || %d e %d \n", m[i][j].value, i, j);
      f = init_elem(m[i][j], f);
      m[i][j].visited = 1;
    } else {
      return f;
    }
  } else {
    f = init_elem(m[i][j], f);
    printf("%d || %d e %d \n", m[i][j].value, i, j);
    m[i][j].visited = 1;
  }

  if (j < col_max)
    f = find_equals(f, m, i, j + 1, lin_max, col_max, flag);

  if (j > 0)
    f = find_equals(f, m, i, j - 1, lin_max, col_max, flag);

  if (i < lin_max)
    f = find_equals(f, m, i + 1, j, lin_max, col_max, flag);

  if (i > 0)
    f = find_equals(f, m, i - 1, j, lin_max, col_max, flag);

  return f;
}

queue_state_t *search_boards(state_t **matrix, queue_state_t *results, int lin,
                             int col, queue_state_t *possible_next) {
  queue_state_t *aux = results;

  // Melhorar isso aqui mais tarde, sem utilizar o queue_size
  do {
    state_t elem = aux->st;
    // printf("m[%d][%d]: %d\n", elem.lin, elem.col, elem.value);

    // Procura no [i][j+1], [i+1][j], etc...
    possible_next = verify_neighbors(elem, lin, col, matrix, possible_next);

    aux = aux->next;
  } while (aux != results);

  return possible_next;
}

int calc_heuristic(int elem_i, int elem_j, int max_lin, int max_col) {
  int side1 = max_col - elem_j;
  int side2 = max_lin - elem_i;
  int result = (side1 * side1) + (side2 * side2);
  return result;
}

state_t chose_next_color(queue_state_t *possible_next, int max_lin, int max_col,
                         queue_state_t *f) {
  printf("\n");

  queue_state_t *aux = possible_next;

  state_t best_elem = aux->st;
  int best = best_elem.g_n +
             calc_heuristic(best_elem.lin, best_elem.col, max_lin, max_col);

  state_t new_elem;
  int new_best;
  aux = aux->next;
  do {
    if (aux->st.value != f->st.value) {
      new_elem = aux->st;
      new_best = new_elem.g_n +
                 calc_heuristic(new_elem.lin, new_elem.col, max_lin, max_col);
      if (new_best < best) {
        best_elem = new_elem;
        best = new_best;
      }
    }
    aux = aux->next;
  } while (aux != possible_next);

  return best_elem;
}

queue_state_t *remove_all_possible_colors(queue_state_t *f) {
  queue_state_t *aux = f->prev;
  int n = queue_size((queue_t *)f);
  printf("%d\n", n);
  int i = 0;
  while (i < n) {
    queue_remove((queue_t **)&f, (queue_t *)aux);
    // free(aux);
    f = f->prev;
    aux = f;
    i += 1;
  }

  return f;
}

queue_state_t *color_the_board(queue_state_t *f, state_t **m, state_t color) {
  queue_state_t *aux = f;

  int i;
  int j;
  do {
    aux->st.value = color.value;
    i = aux->st.lin;
    j = aux->st.col;

    m[i][j].value = color.value;
    m[i][j].visited = 0;
    // printf("f[%d][%d]: %d\n", i, j, aux->st.value);
    // printf("Matrix[%d][%d]: %d\n", i, j, m[i][j].value);
    aux = aux->next;
  } while (aux != f);
  f = init_elem(color, f);

  return f;
}

int *a_star(state_t **matrix_data, state_t **matrix_data_aux, int lin, int col,
            int num_colors) {

  // print_matrix(matrix_data_aux, lin, col);
  queue_state_t *possible_next = NULL;
  queue_state_t *results = NULL;
  // results = init_elem(matrix_data_aux[0][0], results);

  queue_state_t *aux = results;
  int flag = 1;
  results = find_equals(aux, matrix_data_aux, 0, 0, lin, col, flag);
  // results = find_equals(aux, matrix_data_aux, 1, 0, lin, col, flag);

  queue_print("Results: ", (queue_t *)results, print_fila);
  int i = 0;
  int n = 3;
  while (i < n) {

    print_matrix(matrix_data_aux, lin, col);
    possible_next =
        search_boards(matrix_data_aux, results, lin, col, possible_next);
    queue_print("PossibleNext: ", (queue_t *)possible_next, print_fila);
    state_t next_color = chose_next_color(possible_next, lin, col, results);
    // add_next_state_to_board()
    printf("NextColor: %d\n", next_color.value);
    results = color_the_board(results, matrix_data_aux, next_color);

    possible_next = remove_all_possible_colors(possible_next);
    queue_print("PossibleNext: ", (queue_t *)possible_next, print_fila);

    // scanf("Text state: %d", &flag);
    // if (flag == 0) {
    //   break;
    // }

    // remove_all_possible_colors()
    // state_t *next_elem = calc_heuristic(possible_next);
    // print_matrix(matrix_data_aux, lin, col);
    aux = results;
    results = find_equals(aux, matrix_data_aux, 0, 0, lin, col, flag);
    // queue_print("Results: : ", (queue_t *)results, print_fila);
    i += 1;
  }

  return NULL;
}

/*

         5 5 4
   2   │ 4 4 3 2 1
   3   │ 4 1 1 4 1
   4   │ 1 4 4 4 3
   5   │ 4 1 4 4 3
   6   │ 3 2 3 3 4
 */
