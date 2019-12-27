#ifndef UTIL_H
#define UTIL_H

#include "ijvm.h"
#include "binaryloader.h"

/* debug print */
#ifdef DEBUG

#define dprintf(...) \
    fprintf(stderr,  __VA_ARGS__)
#else
#define dprintf(...)
#endif /* DEBUG */


/**
 * Converts bytes to a word
 **/
word_t bytes_to_word(byte_t *bytes);

/**
 * converts bytes to a short
 **/
short bytes_to_short(byte_t *bytes);

/**
 * converts bytes to an unsigned short
 **/
unsigned short bytes_to_u_short(byte_t *bytes);

/**
 * Convert big endian to little endian
 **/
uint32_t swap_uint32(uint32_t num);

/**
 * Reads a word from the binary, returns true if the word is the magic word
 **/
bool CheckMagicNumber(FILE * binary);

/**
  * increase program counter by value of i
  */
void increasePCby(int i);
#endif /* UTIL_H */
