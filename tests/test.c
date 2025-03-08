#include "../include/pbm_lib.h"

#include <stdio.h>

void test(void) {
    printf("Architecture is %d %d\n", sizeof(void*), PBM_digit_bits);

    enum pbm_err e;
    const char* strs[] = {
    "1234567890700001234567",
    "4294967297",
    "12345678900",
    "13333744860005217",
    "18446744073709551616",
    "1",
    "1223666790471429673200215411579542",
    "29469611466878894144725566641577883900641390559558271790792717420960039123711471008640298676332121543228653836270563658439343545591490408347353197391442346432374720917764845725447313263871608490058977344434378833976291501949964310603274734"
};

    struct pbm_BigInt* Big = pbm_BigInt_create(strs[7], dec, 0, &e); 
    printf("size = %d\n", Big->size);
    for (size_t i = 0; i < Big->size; ++i) {
        pbm_digit_t view = Big->chunks[i];
        printf("%llu*(2^(64))^", view);
        printf("(%d)+", i);
    }
    printf("\n");


    #if 0
    char* str = pbm_BigInt_str(Big);
    printf("Digit: %s", str);
    #endif
}

int main()
{
    test();

    return 0;
}