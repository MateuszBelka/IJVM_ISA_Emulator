#include "util.h"

word_t bytes_to_word(byte_t *bytes)
{
  word_t result = (word_t)((bytes[0] << 24) |
                  (bytes[1] << 16) |
                  (bytes[2] << 8) |
                  bytes[3]);
  return result;
}

short bytes_to_short(byte_t *bytes)
{
	short result = (short)((bytes[0] << 8) | bytes[1]);
	return result;
}

unsigned short bytes_to_u_short(byte_t *bytes)
{
	unsigned short result = (unsigned short)((bytes[0] << 8) | bytes[1]);
	return result;
}

uint32_t swap_uint32(uint32_t num)
{
  return ((num>>24)&0xff) |
  ((num<<8)&0xff0000) |
  ((num>>8)&0xff00) |
  ((num<<24)&0xff000000);
}

bool CheckMagicNumber(FILE *fp) {
  uint32_t mn; //candidate for magic number
  if((fread(&mn, sizeof(uint32_t), 1, fp)) != 1) {
    fprintf(stderr, "%s", "ERROR: fread(&mn, sizeof(uint32_t), 1, fp) != 1\n");
    destroy_ijvm();
    exit(1);
  }
  mn = swap_uint32(mn);
  if (mn != MAGIC_NUMBER) { return 0; }
  return 1;
}

void increasePCby(int i)
{
  pc += i;
}

byte_t *get_text()
{
  return text_block.data;
}

int text_size()
{
  return text_block.size;
}

int get_program_counter()
{
  return pc;
}

word_t get_constant(int i)
{
  long offset;
  if(i >= const_block.size) {
    fprintf(stderr, "%s", "ERROR: i >= const_block.size\n");
    destroy_ijvm();
    exit(1);
  }
  offset = i * (int)sizeof(word_t);
  return bytes_to_word(&const_block.data[offset]);
}

byte_t get_instruction()
{
  return text_block.data[pc];
}
