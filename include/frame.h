#ifndef FRAME_H
#define FRAME_H

#include "ijvm.h"
#include "machine.h"
#include "stack.h"

typedef struct Frame
{
  word_t *vars;
  int pc;
  int stack_pointer;
  int var_size;
  struct Frame *next;
}Frame_t;

Frame_t *root;

/**
 * Returns a new frame;
 * localVar  - size allocated for the local variables
 * currentpc - current program counter value
 * stackptr  - current stack pointer value
 **/
Frame_t *init_frame(int localVars, int currentpc, int stackptr);

/**
 * Returns the current frame of the program
 **/
Frame_t *current_frame(void);

/**
 * Return the frame before the last
 **/
Frame_t *previous_frame(void);

/**
 * Store a local variable at index i
 **/
void store_var(int i);

/**
 * Increase the value of a local variable by a constant value
 **/
void increase_LocalVar(int val, int i);

/**
 * Removes the last frame in the linked list
 **/
void remove_current_frame(void);

/**
 * Initiaties new method,
 * creates new frame
 **/
void init_method(void);

/**
 * Returns from method,
 * removes the last frame
 **/
void return_method(void);

/**
 * destory all the frames
 **/
void destroy_frames(void);

#endif /* FRAME_H */
