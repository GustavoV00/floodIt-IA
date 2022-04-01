#include "../include/graph.h"
#include "../include/includes.h"
#include "../include/queue.h"
#include "../include/utils.h"
#include <assert.h>
#include <unistd.h>

queue_state_t *removed_items = NULL;

void print_fila(void *ptr) {
  struct queue_state_t *elem = ptr;

  if (!elem)
    return;

  elem->prev ? printf("%d", elem->prev->st.value) : printf("*");
  printf("<%d>", elem->st.value);
  elem->prev ? printf("%d", elem->next->st.value) : printf("*");
}

bool goal(struct queue_state_t *queue, int tam) {
  int n = queue_size((queue_t *)queue);
  printf("Tamanho fila visited_nodes: %d\n", n);

  if (n < tam)
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
  if (value1.value != neighbor.value && value1.value != 0 &&
      neighbor.value != 0 && neighbor.in_board == 0) {
    neighbor.in_board = 1;
    f = init_elem(neighbor, f);
  }

  return f;
}

// VERIFICA OS VIZINHOS
queue_state_t *verify_neighbors(state_t elem, int lin_max, int col_max,
                                state_t **matrix,
                                queue_state_t *possible_next) {
  int i = elem.lin;
  int j = elem.col;
  if (i > 0 && j > 0 && j < col_max - 1 && i < lin_max - 1) {
    // printf("Deu merda aqui\n");
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
  if (i == lin_max - 1) {
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
    return possible_next;
  }

  if (j == col_max - 1) {
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

queue_state_t *find_equals(queue_state_t *f, state_t **m, int i, int j,
                           int lin_max, int col_max) {

  if (f != NULL) {
    // printf("%d || %d e %d \n", m[i][j].value, i, j);
    // if (m[i][j].visited == 1) {
    if (m[i][j].value == f->st.value && m[i][j].visited == 0) {
      // printf("%d || %d e %d \n", m[i][j].value, i, j);
      f = init_elem(m[i][j], f);
      m[i][j].visited = 1;
    } else {
      return f;
    }
  } else {
    f = init_elem(m[i][j], f);
    // printf("%d || %d e %d \n", m[i][j].value, i, j);
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

queue_state_t *search_boards(state_t **matrix, queue_state_t *visited_nodes,
                             int lin, int col, queue_state_t *possible_next) {
  queue_state_t *aux = visited_nodes;

  do {
    state_t elem = aux->st;
    // printf("m[%d][%d]: %d\n", elem.lin, elem.col, elem.value);

    // Procura no [i][j+1], [i+1][j], etc...
    possible_next = verify_neighbors(elem, lin, col, matrix, possible_next);

    aux = aux->next;
  } while (aux != visited_nodes);

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
    new_elem = aux->st;
    new_best = new_elem.g_n +
               calc_heuristic(new_elem.lin, new_elem.col, max_lin, max_col);
    if (new_best <= best) {
      best_elem = new_elem;
      best = new_best;
    }
    aux = aux->next;
    // printf("To aqui\n");
  } while (aux != possible_next);

  return best_elem;
}

queue_state_t *remove_all_possible_colors(queue_state_t *f,
                                          state_t next_color) {
  queue_state_t *aux = f;

  // while (f) {
  //   aux = f;
  //   // printf("Elemento a ser removido: %d\n", aux->st.value);
  //   queue_remove((queue_t **)&f, (queue_t *)aux);
  //   assert(fila_correta(f));   // estrutura continua correta
  //   assert(aux->prev == NULL); // testa elemento removido
  //   assert(aux->next == NULL); // testa elemento removido
  // }
  int n = queue_size((queue_t *)f);
  int i = 0;
  while (i < n) {

    if (next_color.value == aux->st.value) {
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

  // printf("Estou aqui\n");
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
    // m[i][j].visited = 0;
    // printf("f[%d][%d]: %d\n", i, j, aux->st.value);
    // printf("Matrix[%d][%d]: %d\n", i, j, m[i][j].value);
    aux = aux->next;
  } while (aux != f);
  // f = init_elem(color, f);

  return f;
}

queue_state_t *addItemsToVisitedNodes(queue_state_t *visited_nodes,
                                      state_t **matrix_data, int lin, int col) {

  while (removed_items) {
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

int *a_star(state_t **matrix_data, int lin, int col, int num_colors) {

  queue_state_t *destructor = malloc(2 * sizeof(queue_state_t));
  queue_state_t *possible_next = NULL;
  queue_state_t *visited_nodes = NULL;
  int *results = malloc(lin * col * sizeof(int));
  // visited_nodes = init_elem(matrix_data[0][0], visited_nodes);

  queue_state_t *aux = visited_nodes;
  int flag = 1;
  visited_nodes = find_equals(aux, matrix_data, 0, 0, lin, col);
  // visited_nodes = find_equals(aux, matrix_data, 1, 0, lin, col, flag);

  queue_print("visited_nodes: ", (queue_t *)visited_nodes, print_fila);
  int i = 0;
  int n = 7;
  while (!goal(visited_nodes, lin * col)) {
    // while (i < n) {
    printf("Jogadas: %d\n", i);

    // print_matrix(matrix_data, lin, col);
    possible_next =
        search_boards(matrix_data, visited_nodes, lin, col, possible_next);
    queue_print("PossibleNext: ", (queue_t *)possible_next, print_fila);
    state_t next_color =
        chose_next_color(possible_next, lin, col, visited_nodes);
    results[i] = next_color.value;

    printf("NextColor: %d\n", next_color.value);
    visited_nodes = color_the_board(visited_nodes, matrix_data, next_color);
    possible_next = remove_all_possible_colors(possible_next, next_color);
    visited_nodes =
        addItemsToVisitedNodes(visited_nodes, matrix_data, lin, col);
    // queue_print("visited_nodes: ",
    // (queue_t *)visited_nodes,
    // print_fila); visited_nodes =
    // remove_all_possible_colors(visited_nodes);
    // queue_print("Colors after remove
    // best color: ", (queue_t
    // *)possible_next,
    //             print_fila);

    // scanf("Text state: %d", &flag);
    // if (flag == 0) {
    //   break;
    // }

    // remove_all_possible_colors()
    // state_t *next_elem =
    // calc_heuristic(possible_next);
    // print_matrix(matrix_data, lin,
    // col); aux = visited_nodes;
    queue_print("visited_nodes: : ", (queue_t *)visited_nodes, print_fila);
    i += 1;
    // sleep(1);
  }

  printf("Jogadas totais: %d\n", i);
  // print_matrix(matrix_data, lin, col);
  printf("\n");
  printf("Resultado: \n");
  for (int i = 0; i < lin * col; i++) {
    if (results[i] != 0)
      printf("%d ", results[i]);
  }
  printf("\n");

  return NULL;
}
