#include "systack.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void stack_func(Stack *s, int element) {
  StackMsg signal;
  while (1) {
    read(s->msg_fd[0], &signal, sizeof(signal));
    switch (signal) {
    case PUSH:;
      int new_element;
      read(s->push_fd[0], &new_element, sizeof(new_element));
      stack_func(s, new_element);
      break;
    case POP:
      write(s->pop_fd[1], &element, sizeof(element));
      return;
    }
  }
}

void push(Stack *s, int element) {
  write(s->push_fd[1], &element, sizeof(element));
  StackMsg signal = PUSH;
  write(s->msg_fd[1], &signal, sizeof(signal));
}

int pop(Stack *s) {
  StackMsg signal = POP;
  int element;
  write(s->msg_fd[1], &signal, sizeof(signal));
  read(s->pop_fd[0], &element, sizeof(element));
  return element;
}

int init_stack(Stack *s, int first) {
  if (pipe(s->push_fd) != 0)
    return -1;
  if (pipe(s->pop_fd) != 0)
    return -1;
  if (pipe(s->msg_fd) != 0)
    return -1;

#ifdef DEBUG
  printf("push_fd is [%d, %d] \n", s->push_fd[0], s->push_fd[1]);
  printf("pop_fd is [%d, %d] \n", s->pop_fd[0], s->pop_fd[1]);
  printf("msg_fd is [%d, %d] \n", s->msg_fd[0], s->msg_fd[1]);
#endif

  if ((s->pid = fork()) == 0) {
    close(s->push_fd[1]);
    close(s->pop_fd[0]);
    close(s->msg_fd[1]);
    stack_func(s, first);
    exit(0);
  } else {
    close(s->push_fd[0]);
    close(s->pop_fd[1]);
    close(s->msg_fd[0]);
    return 0;
  }
}
