#include "include/pbm_lib.h"

#include <stdio.h>


int main()
{
    printf("Hi");
    enum pbm_err e;
    pbm_BigInt Big = pbm_BigInt_create("123456789012", hex, 0, &e); 
    char* str = pbm_BigInt_str(&Big);
    printf("Hello: %s", str);

    return 0;
}