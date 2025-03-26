#include "pbm_BigInt.h"

void pbm_BigInt_delete(pbm_BigInt_ptr _inum)
{
    if (_inum != NULL) {
        if (_inum->size && _inum->chunks)
            free(_inum->chunks);
        free(_inum);
    }
}