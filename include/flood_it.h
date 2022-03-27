#ifndef __FLOOD_IT__
#define __FLOOD_IT__

#include "../include/graph.h"

bool goal(struct Graph *graph_t);
void check_neighbors(struct node *root_node_t, int *connected_nodes, int connected_nodes_size, struct Graph *graph_t);
int *greedy(struct Graph *graph_t);

#endif
