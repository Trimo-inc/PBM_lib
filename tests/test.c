#include "../include/pbm_lib.h"

#include <stdio.h>


void __print(const pbm_Natural_ptr big) {
    for (size_t i = 0; i < big->_size; ++i) {
        #if ARCH == 32
        printf("digit[%u] = ", i);
        printf("%u\n", big->digits[i]);
        #elif ARCH == 64
        printf("digit[%llu] = ", i);
        printf("%llu\n", big->digits[i]);
        #endif
    }
}

void __print_pow(const pbm_Natural_ptr big) {
    for (size_t i = 0; i < big->_size; ++i) {
        #if ARCH == 32
        printf("(%u)*((2^%u)^%u)+", big->digits[i], PBM_digit_bits, i);
        #elif ARCH == 64
        printf("(%llu)*((2^%llu)^%llu)+", big->digits[i], PBM_digit_bits, i);
        #endif
    }
    printf("0\n");
}

void _print_pow(pbm_BigInt_ptr big) {
    for (size_t i = 0; i < big->size; ++i) {
        #if ARCH == 32
        printf("(%u)*((2^%u)^%u)+", big->chunks[i], PBM_digit_bits, i);
        #elif ARCH == 64
        printf("(%llu)*((2^%llu)^%llu)+", big->chunks[i], PBM_digit_bits, i);
        #endif
    }
    printf("0\n");
}

void test()
{
    const char* ten = "121399999999999999999999999910000000000000000000000000000012237947584";
    #if 1
    struct pbm_Natural* n = _pbm_natural_create(ten, dec);
    // _pbm_natural_default_init(n); Утечка, следует для стека
    __print_pow(n);
    _pbm_natural_default_init_s(n);
    #endif
    enum pbm_err ns;
    pbm_BigInt_ptr b =  pbm_BigInt_create_s(ten, dec, 0, &ns);
    _print_pow(b);
}





int main()
{
    test();

    return 0;
}