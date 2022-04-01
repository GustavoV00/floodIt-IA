#ifndef __INCLUDES__
#define __INCLUDES__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct state_t {
  int value;
  int g_n;
  int lin;
  int col;
  int f_n;
  int visited;
  int h_n;
  int id;
  int in_board;
} state_t;

typedef struct bounds_t {
  struct bounds_t *prev;
  struct bounds_t *next;
  struct state_t st;
} bouds_t;

typedef struct queue_state_t {
  struct queue_state_t *prev;
  struct queue_state_t *next;
  struct state_t st;
} queue_state_t;

#endif
