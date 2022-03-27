#include "../include/graph.h"
#include "../include/includes.h"

/* Create the graph and verify if exist
 * if exist, return the graph
 * if not exist, return NULL and exist the program
 */
struct Graph *create_graph() {
  struct Graph *graph = malloc(sizeof(struct Graph));
  if (!graph)
    return NULL;

  return graph;
}

/*
 * Inicialize the data, and fill with it
 * graph_t -> vertices: Is the vertices
 * graph_t -> adj_list: Is the adjacesnte list (All the initial data is NULL).
 */
struct Graph *init_graph_values(int vertices, struct Graph *graph_t) {
  printf("Amount of vertices: %d\n", vertices);
  graph_t->vertices = vertices;
  graph_t->adj_list = malloc(vertices * sizeof(struct node));
  if (!graph_t->adj_list) {
    return NULL;
  }

  for (int i = 0; i < vertices; ++i) {
    graph_t->adj_list[i] = NULL;
  }

  return graph_t;
}

/*
 * We create a node, and return the node;
 */
struct node *create_node(int v, int value1, int value2) {
  struct node *new_node_t = malloc(sizeof(struct node));
  new_node_t->vertex = v;
  new_node_t->value = value1 == -1 ? value2 : value1;
  new_node_t->next = NULL;
  return new_node_t;
}

/*
 * Connect to nodes.
 * A -> B
 * B -> A
 */
void add_edge(struct Graph *graph_t, int src, int dest, int value1,
              int value2) {
  // add edge from src to dest
  struct node *new_node_t = create_node(dest, value1, -1);
  new_node_t->next = graph_t->adj_list[src];
  graph_t->adj_list[src] = new_node_t;

  // add edge from dest to src
  new_node_t = create_node(src, -1, value2);
  new_node_t->next = graph_t->adj_list[dest];
  graph_t->adj_list[dest] = new_node_t;
}

/*
 * Print the graph
 */
void print_graph(struct Graph *graph_t) {
  int v;
  for (v = 0; v < graph_t->vertices; v++) {
    struct node *temp = graph_t->adj_list[v];
    struct node *temp2 = graph_t->adj_list[v];
    printf("\n Vertex %d\n: ", v);
    while (temp) {
      printf("%d -> ", temp->vertex);
      temp = temp->next;
    }
    printf("\n: ");

    while (temp2) {
      printf("%d -> ", temp2->value);
      temp2 = temp2->next;
    }
    printf("\n");
  }
}

/*
 * Free all graph nodes
 */
void destroy_graph(struct Graph *graph_t) {
  for (int i = 0; i < graph_t->vertices; i++) {
    free(graph_t->adj_list[i]);
  }
  free(graph_t->adj_list);
}
