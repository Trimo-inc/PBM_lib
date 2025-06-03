#include "testing.h"
#include "pbm_lib.h"

extern FILE* _log;

void __print_natural_pow(const pbm_Natural_ptr big) {
    for (size_t i = 0; i < big->_size; ++i) {
        #if ARCH == 32
        fprintf(_log, "(%u)*((2^%u)^%u)+", big->digits[i], (unsigned int)PBM_digit_bits, (unsigned int)i);
        #elif ARCH == 64
        fprintf(_log, "(%llu)*((2^%llu)^%llu)+", big->digits[i], PBM_digit_bits, i);
        #endif
    }
    fprintf(_log, "0\n");
}