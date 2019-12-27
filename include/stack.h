#ifndef STACK_H
#define STACK_H

#define INIT_STACK_SIZE 16

#include "ijvm.h"
#include "frame.h"

typedef struct Stack {
  word_t *data;
  int pointer;
  int size;
}Stack_t;

Stack_t stack;

/**
 * Initialze the stack
 **/
void init_stack(void);

/**
 * Pushes a new word to the stack
 **/
void push(word_t num);

/**
 * Returns the last word push to the stack and removes it
 **/
word_t pop(void);

/**
 * Destroy the stack, freeing the memory of pointers
 **/
void destroy_stack(void);


#endif /* STACK_H */
