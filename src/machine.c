#include "machine.h"

bool step()
{
  bool halt = execute_instruction();
  pc++;
  return halt;
}

bool finished()
{
  return 0;
  // TODO: implement me
}

void run()
{
  while(step() && pc <= text_block.size)
  {
    //step until returns false;
  }
  return;
}

int init_ijvm(char *binary_file)
{
  FILE *fp;

  //check if you can open file successfully
  if ((fp = fopen(binary_file, "rb")) == NULL) { return -1; }
  if (CheckMagicNumber(fp) != 1) {
    fprintf(stderr, "%s", "ERROR: CheckMagicNumber(fp) != 1\n");
    destroy_ijvm();
    exit(1);
  }

  //put data in the blocks
  pc = 0;
  set_input(stdin);
  set_output(stdout);

  const_block = load_block(fp);
  text_block = load_block(fp);

  root = init_frame(0,0,0);
  init_stack();

  fclose(fp);
  return 0;
}

void destroy_ijvm()
{
  destroy_block();
  destroy_stack();
  destroy_frames();
}

void set_input(FILE *fp)
{
  in = fp;
}

void set_output(FILE *fp)
{
  out = fp;
}

FILE *get_input()
{
  return in;
}

FILE *get_output()
{
  return out;
}
