#include "shared_stack.h"
#include <pthread.h>

static const int MAGIC_NUM = -0x431;

// @capacity uppser bound of the stack. If it's 0,
//           create stack without upperbound.
void ss_init_stack(SharedStack *s, long capacity) {
  const int first = MAGIC_NUM;
  pthread_mutex_init(&s->mutex, NULL);
  pthread_cond_init(&s->full_cv, NULL);
  pthread_cond_init(&s->empty_cv, NULL);
  s->size = 0;
  s->capacity = capacity;
  init_stack(&s->stack, first);
}

static void ss_size_(SharedStack *s, int *out) {
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, NULL);
  pthread_mutex_lock(&mutex);
  { *out = s->size == 0; }
  pthread_mutex_unlock(&mutex);
}

void ss_push(SharedStack *s, int element) {
  pthread_mutex_lock(&s->mutex);
  {
    if (s->capacity > 0) {             // a bounded stack.
      while (s->size == s->capacity) { // full
        pthread_cond_wait(&s->empty_cv, &s->mutex);
      }
    }

    push(&s->stack, element);
    s->size++;
    if (s->size == 1) {
      pthread_cond_signal(&s->empty_cv);
    }
  }
  pthread_mutex_unlock(&s->mutex);
}

int ss_pop(SharedStack *s) {
  int result;
  int empty;
  ss_size_(s, &empty);
  pthread_mutex_lock(&s->mutex);
  {
    while (s->size == 0) {
      pthread_cond_wait(&s->empty_cv, &s->mutex);
    }

    result = pop(&s->stack);
    s->size--;

    if (s->capacity > 0) {
      if (s->size == s->capacity) {
        pthread_cond_signal(&s->full_cv);
      }
    }
  }
  pthread_mutex_unlock(&s->mutex);
  return result;
}
