#include "../include/pbm_lib.h"

#include "testing.h"
#include <string.h>
#include <stdlib.h>

extern FILE* _log; 



int main(void)
{
	_log = stdout;

	bit_and();
	bit_or();
	bit_xor();
	bit_lshift();
	bit_rshift();
	small_add();
	small_mul();
	return 0;
}