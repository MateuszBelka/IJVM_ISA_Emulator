#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "ijvm.h"
#include "machine.h"
#include "stack.h"
#include "binaryloader.h"

typedef enum Branch{i_feq, go_to, i_flt, i_cmpeq}Branch; //Branch types

/**
  * Push a byte onto stack
  **/
void bipush(word_t a);

/**
  * Pop two words from stack;
  * push their sum
  **/
void iadd(void);

/**
  * Pop two words from stack;
  * subtract the top word from the second to top word,
  * push the answer;
  **/
void isub(void);

/**
  * Pop two words from stack;
  * push bit-wise AND
  **/
void iand(void);

/**
  * Pop two words from stack;
  * push bit-wise OR.
  **/
void ior(void);

/**
 * Swap the two top words on the stack
 **/
void iswap(void);

/**
 * Pop word oﬀ stack and print it to standard out
 **/
void iout(void);

/**
 * Copy top word on stack and push onto stack
 **/
void idup(void);

/**
 * Pop word from stack and branch if it is zero
 **/
bool ifeq(void);

/**
 * Pop word from stack and branch if it is less than zero
 **/
bool iflt(void);

/**
 * Pop two words from stack and branch if they are equal
 **/
bool icmpeq(void);

/**
 * Decides whether to branch and changes the pc with offset
 **/
void branch(short offset, Branch branch_type);

/**
 * Executes a wide instruction, return false if failed
 **/
bool execute_wide(void);

/**
  * list of translations of instructions from ijvm to c
  **/
bool execute_instruction(void);

#endif /* INSTRUCTIONS_H */
