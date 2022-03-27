#include "../include/graph.h"
#include "../include/includes.h"

/*
 * Verifica se atingiu o estado objetivo (todos os quadrados do tabuleiro tem a mesma cor)
 */
bool goal(struct Graph *graph_t)
{
#ifdef DEBUG
	printf("Verificando se o tabuleiro inteiro tem a mesma cor...");
#endif

	// pega a cor do primeiro vértice
	int corGoal = graph_t->adj_list[0]->vertex_value;

	// percorre todos os vértices e verifica se possuem a mesma cor
	for (int v = 0; v < graph_t->vertices; v++)
	{
		if (graph_t->adj_list[v]->vertex_value != corGoal)
		{
			return false;
		}
	}

	return true;
}

void check_neighbors(struct node *root_node_t, int *connected_nodes, int connected_nodes_size, struct Graph *graph_t)
{

	/*
	linha 0 	 -> n olha pra cima
	linha n - 1  -> n olha pra baixo
	coluna 0	 -> n olha pra esquerda
	coluna n - 1 -> n olha pra direita
	*/
	for (int i = 0; i < connected_nodes_size; i++)
	{
		int node_id = connected_nodes[i];
		struct node *current_node_t = graph_t->adj_list[node_id];
		struct node *temp = current_node_t;
		while (current_node_t)
		{
			printf("V: %d\n", current_node_t->vertex);
			current_node_t = current_node_t->next;
		}
		printf("\n");
	}
}

int *greedy(struct Graph *graph_t)
{
	int *missing_nodes = malloc(graph_t->vertices * sizeof(int));
	int *result_queue = malloc(graph_t->vertices * sizeof(int));
	int *connected_nodes = malloc(graph_t->vertices * sizeof(int));
	int connect_nodes_size = 0;

	print_graph(graph_t);
	// o 0 indica o nodo. E o valor do nodo, está na própria lista adjâcencia.
	struct node *root_node_t = graph_t->adj_list[0];
	connected_nodes[0] = 0;
	connect_nodes_size++;

	// while (!goal(graph_t))
	// {
	printf("/**************************************/\n");
	check_neighbors(root_node_t, connected_nodes, connect_nodes_size, graph_t);
	printf("/**************************************/\n");
	// if (!color)
	// {
	// 	return -1;
	// }
	// graph_t = change_colors(color);
	// add_move_to_queue(color, result_queue);
	// }
}

/*

		 5 5 4
   2   │ 4 2 3 2 1
   3   │ 1 1 1 4 1
   4   │ 1 4 4 4 3
   5   │ 4 1 4 4 3
   6   │ 3 2 3 3 4
 */
