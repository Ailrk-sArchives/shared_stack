#ifndef SYSTACK_
#define SYSTACK_

#include <sys/types.h>
#include <unistd.h>

typedef struct {
  pid_t pid;
  int push_fd[2];
  int pop_fd[2];
  int msg_fd[2];
} Stack;

typedef enum { PUSH, POP } StackMsg;

void stack_func(Stack *s, int element);
void push(Stack *s, int element);
int pop(Stack *s);
int init_stack(Stack *s, int first);

#endif /* ifndef SYMBOL */
