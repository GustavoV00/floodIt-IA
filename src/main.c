#include "../utils/libs/io.h"

int main(int argc, char *argv[])
{
	int board_arr[3];
	FILE *board_file = NULL;

	board_file = open_file(board_file);
	if (board_file)
	{
		read_board_configs(board_arr, board_file);
		read_board_data(board_arr, board_file);
		close_file(board_file);
		// aStar();
	}
	else
	{
		error_when_open_file(board_file);
	}

	return 0;
}
