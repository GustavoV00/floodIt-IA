#ifndef __GRAPH__
#define __GRAPH__

#include "../include/includes.h"

struct node {
  int vertex; // id do nodo
  int value;
  struct node *next;
};

struct Graph {
  int vertices;
  struct node **adj_list;
};

struct Graph *create_graph();
struct Graph *init_graph_values(int vertices, struct Graph *graph_t);
struct node *create_node(int v, int value1, int value2);
void add_edge(struct Graph *graph, int src, int dest, int value1, int value2);
void print_graph(struct Graph *graph_t);
void destroy_graph(struct Graph *graph_t);

#endif
