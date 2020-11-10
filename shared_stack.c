#include "shared_stack.h"
#include <pthread.h>

static const int MAGIC_NUM = -0x431;

// @capacity uppser bound of the stack. If it's 0,
//           create stack without upperbound.
void ss_init_stack(SharedStack *s, long capacity) {
  const int first = MAGIC_NUM;
  pthread_mutex_init(&s->mutex, NULL);
  pthread_mutex_init(&s->full_lock, NULL);
  pthread_mutex_init(&s->empty_lock, NULL);
  s->size = 0;
  pthread_mutex_lock(&s->full_lock);
  pthread_mutex_lock(&s->empty_lock);
  init_stack(&s->stack, first);
}

void ss_push(SharedStack *s, int element) {
  pthread_mutex_lock(&s->mutex);
  {
    if (s->capacity > 0) { // a bounded stack.
      if (s->size == s->capacity - 1) {
        pthread_mutex_lock(&s->full_lock);
      }
    }

    push(&s->stack, element);
    s->size++;
    pthread_mutex_unlock(&s->empty_lock);
  }
  pthread_mutex_unlock(&s->mutex);
}

int ss_pop(SharedStack *s) {
  int result;
  pthread_mutex_lock(&s->mutex);
  {
    if (s->size <= 1) {
      pthread_mutex_lock(&s->empty_lock);
    }
    s->size--;
    result = pop(&s->stack);
    if (s->capacity > 0) {
      pthread_mutex_unlock(&s->full_lock);
    }
  }
  pthread_mutex_unlock(&s->mutex);
  return result;
}
