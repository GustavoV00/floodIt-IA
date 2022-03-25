#include "libs/io.h"
#include "libs/includes.h"

FILE *open_file(FILE *board_file)
{
	board_file = fopen("tests/exemplo_mapa_30_30_10.txt", "r");
	if (board_file)
		return board_file;

	return NULL;
}

void error_when_open_file(FILE *f)
{
	printf("%p\n", f);
	printf("Error when open file");
}

void read_board_configs(int *board_arr, FILE *f)
{
	int v0, v1, v2;
	fscanf(f, "%d %d %d", &v0, &v1, &v2);
	board_arr[0] = v0;
	board_arr[1] = v1;
	board_arr[2] = v2;
}

void read_board_data(int *board_arr, FILE *board_file)
{
	printf("1");
	printf("1");

	int vertices = board_arr[0] + board_arr[1];
	bool is_directed = false;
	graph_init(vertices, is_directed);
}

void close_file(FILE *file) { fclose(file); }
