#include "binaryloader.h"

Block_t load_block(FILE *fp)
{
  Block_t tmpBlock;
	size_t size;
	size_t origin;

  if(fread(&origin, sizeof(word_t), 1, fp) != 1) {  //Read Origin
    fprintf(stderr, "%s", "ERROR: fread(&origin, sizeof(word_t), 1, fp) != 1\n");
    destroy_ijvm();
    exit(1);
  }
  origin = (size_t)bswap_32((uint32_t)origin);
  tmpBlock.origin = (word_t)origin;

  if(fread(&size, sizeof(word_t), 1, fp) != 1) {  //Read Block size
    fprintf(stderr, "%s", "ERROR: fread(&size, sizeof(word_t), 1, fp) != 1\n");
    destroy_ijvm();
    exit(1);
  }
	size = (size_t)bswap_32((uint32_t)size);
	tmpBlock.size = (word_t)size;

	tmpBlock.data = (byte_t*)malloc(size * sizeof(byte_t));
  if(fread(tmpBlock.data,sizeof(byte_t), size, fp) != size) {  //Read Data
    fprintf(stderr, "%s", "ERROR: fread(tmpBlock.data,sizeof(byte_t), size, fp) != size\n");
    destroy_ijvm();
    exit(1);
  }
  return tmpBlock;
}

void destroy_block()
{
  if(text_block.data != NULL){
    free(text_block.data);
  }
  if(const_block.data != NULL){
    free(const_block.data);
  }
}
