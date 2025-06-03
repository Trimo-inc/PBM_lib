#include "../include/pbm_lib.h"

#include "testing.h"
#include <string.h>
#include <stdlib.h>

extern FILE* _log; 



int main(void)
{
	_log = stdout;

	bit_and();
	return 0;
}