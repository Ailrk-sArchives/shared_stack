#include "shared_stack.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *work(void *s) {

  SharedStack *p = (SharedStack *)s;
  pthread_t tid = pthread_self();
  for (int i = 0; i < 10; i++) {
    int value = ss_pop(p);
    printf("[worker thread %lu]: get value %d, stack size %lu \n", tid, value,
           p->size);
    usleep(100000);
  }
  pthread_exit(NULL);
}

void *producer(void *s) {
  SharedStack *p = (SharedStack *)s;
  pthread_t tid = pthread_self();
  for (int i = 0; i < 35; i++) {
    int value = random() % 100;
    ss_push(p, value);
    printf("[producer %lu]: put value %d, stack size %lu \n", tid, value,
           p->size);
    usleep(100000);
  }
  pthread_exit(NULL);
}

int main(void) {
#ifdef DEBUG
  printf("==== DEBUG MODE ====");
#endif

  SharedStack s;
  ss_init_stack(&s, 5);

  pthread_t producer_id, worker1_id, worker2_id, worker3_id;
  pthread_create(&producer_id, NULL, producer, (void *)&s);
  sleep(1);

  pthread_create(&worker1_id, NULL, work, (void *)&s);
  pthread_create(&worker2_id, NULL, work, (void *)&s);
  pthread_create(&worker3_id, NULL, work, (void *)&s);

  pthread_join(producer_id, NULL);
  pthread_join(worker1_id, NULL);
  pthread_join(worker2_id, NULL);
  pthread_join(worker3_id, NULL);
  return 0;
}
