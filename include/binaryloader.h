#ifndef BINARYLOADER_H
#define BINARYLOADER_H

#include "ijvm.h"
#include "machine.h"
#include <byteswap.h>

typedef struct Block {
  word_t origin;
  word_t size;
  byte_t *data;
} Block_t;

Block_t text_block;
Block_t const_block;

/**
 * Loads a block from the binary, returns the block
 **/
Block_t load_block(FILE *fp);

/**
 * Destroys the block struct, freeing the memory of pointers
 */
void destroy_block(void);

#endif /* BINARYLOADER_H */
