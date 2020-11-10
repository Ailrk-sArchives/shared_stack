#ifndef SHARED_STACK_
#define SHARED_STACK_

#include "systack.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  Stack stack;
  pthread_mutex_t mutex;
  pthread_cond_t full_cv;
  pthread_cond_t empty_cv;
  long capacity; // upperbound
  size_t size;   // current elements in stack
} SharedStack;

void ss_init_stack(SharedStack *s, long capacity);
void ss_push(SharedStack *s, int element);
int ss_pop(SharedStack *s);
#endif /* ifndef SYMBOL */
