// TRAB1 IA - 2021-2
// GUSTAVO VALENTE NUNES GRR20182557
// BRUNO EDUARDO FARIAS GRR20186715

#ifndef __INCLUDES__
#define __INCLUDES__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUAD 4
#define QUAD_A 0
#define QUAD_B 1
#define QUAD_C 2
#define QUAD_D 3

#define ADJ_AB 1
#define ADJ_BC 2
#define ADJ_AD 3
#define ADJ_DC 4

typedef struct result
{
  int result;
  int quadrant;
} result_t;

typedef struct state_t
{
  int value;
  int lin;
  int col;
  int visited;
  int id;
  int g_n;
  int f_n;
  int h_n;
  int in_board;
  int quadrant;

  int amount;
} state_t;

typedef struct queue_state_t
{
  struct queue_state_t *prev;
  struct queue_state_t *next;
  struct state_t st;
} queue_state_t;

#endif
