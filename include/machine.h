#ifndef MACHINE_H
#define MACHINE_H

#define SIZE_WORD  4
#define SIZE_SHORT 2
#define SIZE_BYTE  1

#include "ijvm.h"
#include "binaryloader.h"
#include "stack.h"
#include "util.h"
#include "instructions.h"
#include "frame.h"

int pc;     //Program counter
FILE *in;   //Input file
FILE *out;  //Output file

FILE *get_input(void);
FILE *get_output(void);
#endif /* MACHINE_H */
