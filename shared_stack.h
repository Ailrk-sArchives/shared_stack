#ifndef SHARED_STACK_
#define SHARED_STACK_

#include "systack.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct {
  Stack stack;
  pthread_mutex_t mutex;
  pthread_mutex_t full_lock;
  pthread_mutex_t empty_lock;
  long capacity; // upperbound
  size_t size;   // current elements in stack
} SharedStack;

void ss_init_stack(SharedStack *s, long capacity);
void ss_push(SharedStack *s, int element);
int ss_pop(SharedStack *s);
#endif /* ifndef SYMBOL */
