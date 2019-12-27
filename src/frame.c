#include "frame.h"

Frame_t * init_frame(int localVars, int currentpc, int stackptr)
{
	Frame_t *f = (Frame_t*)malloc(sizeof(Frame_t));
	if(f == NULL) {
    fprintf(stderr, "%s", "ERROR: f == NULL\n");
    destroy_ijvm();
    exit(1);
  }

	f->vars = malloc((size_t)(localVars) * sizeof(word_t));
	if(f->vars == NULL) {
    fprintf(stderr, "%s", "ERROR: f->vars == NULL\n");
    destroy_ijvm();
    exit(1);
  }

	f->pc = currentpc;
	f->var_size = localVars;
	f->stack_pointer = stackptr;
  f->next = NULL;

	return f;
}

Frame_t *current_frame()
{
  Frame_t *f = root;

  while (f->next != NULL) {
    f = f->next;
  }
  return f;
}

Frame_t *previous_frame()
{
  Frame_t *f = root;

  /**
    * we cannot get frame before the last
    * if the current frame is the last frame
    **/
	if(f->next == NULL) {
	  fprintf(stderr, "%s", "ERROR: f->next == NULL\n");
	  destroy_ijvm();
	  exit(1);
	 }
  while ((f->next)->next != NULL) {
    f = f->next;
  }
  return f;
}

void store_var(int i)
{
	Frame_t *f = current_frame();
	if ((i + 1) > f->var_size) {
		f->var_size = (i + 1);
		f->vars = realloc(f->vars, (size_t)(f->var_size) * sizeof(word_t));
	}
	f->vars[i] = pop();
}

void increase_LocalVar(int val, int i)
{
  Frame_t *f = current_frame();

	if ((i + 1) > f->var_size) {
    f->var_size = (i + 1);
    f->vars = realloc(f->vars, (size_t)(f->var_size) * sizeof(word_t));
  }
  f->vars[i] += val;
}

word_t get_local_variable(int i)
{
  return current_frame()->vars[i];
}

void remove_current_frame()
{
  Frame_t *f = current_frame();
  previous_frame()->next = NULL;

  if (f->vars != NULL) {
    free(f->vars);
  }
  if (f != NULL) {
    free(f);
  }
}

void init_method()
{
	Frame_t *f;
	int currentpc;
	int argsCount;
	int localVars;
	int constantLoc;

	increasePCby(SIZE_BYTE);
	currentpc = pc + SIZE_BYTE;
	constantLoc = bytes_to_u_short(&text_block.data[pc]);
	pc = get_constant(constantLoc);
	argsCount = bytes_to_u_short(&text_block.data[pc]);
	increasePCby(SIZE_SHORT);
	localVars = bytes_to_u_short(&text_block.data[pc]);

	f = init_frame(argsCount + localVars, currentpc, stack_size() - argsCount);
	for (int i = argsCount - 1; i > 0; i--) {
		f->vars[i] = pop();
	}
	current_frame()->next = f;
	pc++;
}

void return_method()
{
	Frame_t *f = current_frame();
	word_t result = tos();

	pc = f->pc;
	if(stack_size() < f->stack_pointer) {
    fprintf(stderr, "%s", "ERROR: stack_size() < f->stack_pointer\n");
    destroy_ijvm();
    exit(1);
  }
	while(stack_size() > f->stack_pointer) {
		pop();
	}
	remove_current_frame();
	bipush(result);
}


void destroy_frames()
{
  Frame_t *tmp;
  Frame_t *head = root;

  while (head != NULL)
  {
    tmp = head;
    head = head->next;
    if (tmp->vars != NULL) {
      free(tmp->vars);
    }
    if (tmp != NULL) {
      free(tmp);
    }
  }
}
