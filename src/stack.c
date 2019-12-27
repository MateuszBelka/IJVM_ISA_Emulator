#include "stack.h"

void init_stack()
{
  stack.pointer = 0;
	stack.size = INIT_STACK_SIZE;
	stack.data = malloc(INIT_STACK_SIZE * sizeof(word_t));
	if(stack.data == NULL) {
    fprintf(stderr, "%s", "ERROR (init_stack): stack.data == NULL\n");
    destroy_ijvm();
    exit(1);
  }
}

void push(word_t num)
{
  if (stack.pointer >= stack.size)
  {
    stack.size *= 2;
    stack.data = realloc(stack.data, (size_t)stack.size * sizeof(word_t));
    if(stack.data == NULL) {
      fprintf(stderr, "%s", "ERROR (push): stack.data == NULL\n");
      destroy_ijvm();
      exit(1);
    }
  }
  stack.data[stack.pointer++] = num;
}

word_t pop()
{
  if(stack.pointer <= current_frame()->stack_pointer) {
    fprintf(stderr, "%s",
            "ERROR: stack.pointer <= current_frame()->stack_pointer\n");
    destroy_ijvm();
    exit(1);
  }
  /*
  if (stack.pointer < (stack.size / 2))
  {
    //printf("stack.pointer = %d\n", stack.pointer);
    //printf("stack.size = %d\n", stack.size);
    //printf("BEFORE: (size_t)stack.size * sizeof(word_t) = %ld\n", (size_t)stack.size * sizeof(word_t));
    stack.size /= 2;
    //printf("AFTER: (size_t)stack.size * sizeof(word_t) = %ld\n", (size_t)stack.size * sizeof(word_t));
    stack.data = (word_t*)realloc(stack.data, (size_t)stack.size * sizeof(word_t));
    if(stack.data == NULL) {
      fprintf(stderr, "%s", "ERROR (pop): stack.data == NULL\n");
      destroy_ijvm();
      exit(1);
    }
  }
  */
  return stack.data[--stack.pointer];
}

void destroy_stack()
{
  if (stack.data != NULL) {
    free(stack.data);
  }
}

word_t tos()
{
  if(stack.pointer <= current_frame()->stack_pointer) {
    fprintf(stderr, "%s", "ERROR: stack.pointer <= current_frame()->stack_pointer\n");
    destroy_ijvm();
    exit(1);
  }
  return stack.data[stack.pointer - 1];
}

word_t *get_stack()
{
  return stack.data;
}

int stack_size()
{
  /**
    * stack.size doesnt reflect the actual size of stack
    * as there is additional memory allocated to prevent stack overflow
    */
  return stack.pointer;
}
