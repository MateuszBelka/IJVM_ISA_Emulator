#include "instructions.h"

void bipush(word_t a)
{
  push(a);
}

void iadd()
{
  word_t a, b;
  a = pop();
  b = pop();
  push(a + b);
}

void isub()
{
  word_t a, b;
  a = pop();
  b = pop();
  push(b - a);
}

void iand()
{
  word_t a, b;
  a = pop();
  b = pop();
  //& is bitwise and operator
  push(a & b);
}

void ior()
{
  word_t a, b;
  a = pop();
  b = pop();
  //| is bitwise and operator
  push(a | b);
}

void iswap()
{
  word_t a, b;
  a = pop();
  b = pop();
  push(a);
  push(b);
}

void iout()
{
	char a = (char)pop();
	fputc(a, get_output());
}

void input()
{
	int input;

	input = fgetc(get_input());
	if (input == -1 || input == 255) {
		push(0);
  } else {
		push(input);
  }
}

void idup()
{
	push(tos());
}

bool ifeq()
{
	return (pop() == 0);
}

bool iflt()
{
	return (pop() < 0);
}

bool icmpeq()
{
	word_t a, b;
	a = pop();
	b = pop();
	return (a == b);
}

void branch(short offset, Branch branch_type)
{
	if (branch_type == go_to) {
		increasePCby(offset-SIZE_BYTE);
  } else if (branch_type == i_feq && ifeq()) {
		increasePCby(offset-SIZE_BYTE);
  } else if (branch_type == i_flt && iflt()) {
		increasePCby(offset-SIZE_BYTE);
  } else if (branch_type == i_cmpeq && icmpeq()) {
		increasePCby(offset-SIZE_BYTE);
  } else {
		increasePCby(SIZE_SHORT);
  }
  if(pc >= text_block.size) {
    fprintf(stderr, "%s", "ERROR: pc >= text_block.size\n");
    destroy_ijvm();
    exit(1);
  }
}

bool execute_wide()
{
	increasePCby(SIZE_BYTE);
	switch(text_block.data[pc])
	{
		case OP_BIPUSH:
			bipush(bytes_to_short(&text_block.data[pc+1]));
			increasePCby(SIZE_SHORT);
		break;
		case OP_ILOAD:
			push(get_local_variable(bytes_to_u_short(&text_block.data[pc+1])));
			increasePCby(SIZE_SHORT);
		break;
		case OP_ISTORE:
			store_var(bytes_to_u_short(&text_block.data[pc+1]));
			increasePCby(SIZE_SHORT);
		break;
		case OP_IINC:
			increase_LocalVar(bytes_to_short(&text_block.data[pc+3]),
                        bytes_to_short(&text_block.data[pc+1]));
			increasePCby(SIZE_WORD);
		break;
		default:
			return false;
		break;
	}
	return true;
}

bool execute_instruction()
{
	switch(text_block.data[pc])
	{
    case OP_BIPUSH:
      //printf("BIPUSH\n");
      bipush((int8_t)text_block.data[pc+1]);
      increasePCby(SIZE_BYTE);
    break;
    case OP_IADD:
      //printf("ADD\n");
      iadd();
    break;
    case OP_ISUB:
      //printf("SUB\n");
      isub();
    break;
    case OP_IAND:
      //printf("AND\n");
      iand();
    break;
    case OP_IOR:
      //printf("OR\n");
      ior();
    break;
    case OP_SWAP:
			//printf("SWAP\n");
			iswap();
		break;
    case OP_POP:
			//printf("POP\n");
			pop();
		break;
    case OP_OUT:
			//printf("OUT\n");
			iout();
		break;
    case OP_IN:
			//printf("IN\n");
			input();
		break;
    case OP_HALT:
			//printf("HALT\n");
			return false;
		break;
    case OP_DUP:
			//printf("DUP\n");
			idup();
		break;
    case OP_GOTO:
      //printf("GOTO\n");
			branch(bytes_to_short(&text_block.data[pc+1]), go_to);
		break;
    case OP_IFEQ:
			//printf("IFEQ\n");
			branch(bytes_to_short(&text_block.data[pc+1]), i_feq);
		break;
		case OP_IFLT:
			//printf("IFLT\n");
			branch(bytes_to_short(&text_block.data[pc+1]), i_flt);
		break;
		case OP_ICMPEQ:
			//printf("ICMPEQ\n");
			branch(bytes_to_short(&text_block.data[pc+1]), i_cmpeq);
		break;
    case OP_IINC:
			//printf("IINC\n");
			increase_LocalVar((int8_t)text_block.data[pc+2], (int8_t)text_block.data[pc+1]);
			increasePCby(SIZE_SHORT);
		break;
    case OP_ILOAD:
			//printf("ILOAD\n");
			push(get_local_variable(text_block.data[pc+1]));
			increasePCby(SIZE_BYTE);
		break;
    case OP_ISTORE:
			//printf("ISTORE\n");
			store_var(text_block.data[pc+1]);
			increasePCby(SIZE_BYTE);
		break;
    case OP_LDC_W:
			//printf("LDC_W\n");
			bipush(get_constant(bytes_to_u_short(&text_block.data[pc+1])));
			increasePCby(SIZE_SHORT);
		break;
    case OP_ERR:
			fprintf(stderr, "ERROR\n");
			return false;
		break;
    case OP_INVOKEVIRTUAL:
      //printf("INVOKEVIRTUAL\n");
      init_method();
		break;
    case OP_IRETURN:
      //printf("RETURN\n");
      return_method();
		break;
    case OP_NOP:
			//printf("NOP\n");
		break;
    case OP_WIDE:
      //printf("WIDE\n");
      execute_wide();
		break;
	}
	return true;
}
