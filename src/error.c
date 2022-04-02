//TRAB1 IA - 2021-2
//GUSTAVO VALENTE NUNES GRR20182557
//BRUNO EDUARDO FARIAS GRR20186715

#include "../include/includes.h"

/**
* Print error when opening a file
*
* @param[in] f File with wrong opening
*/
void error_when_open_file(FILE *f) {
  printf("%p\n", f);
  printf("Error when open file!");
}

