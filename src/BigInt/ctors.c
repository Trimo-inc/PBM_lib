#include "pbm_BigInt.h"

void __pbm_BigInt_default_ctor(struct pbm_BigInt *_inum)
{
    _inum->chunks = NULL;
    _inum->size = 0;
    _inum->is_negative = 0;
}