#include "pbm_lib.h"

#include "testing.h"
#include <string.h>
#include <stdlib.h>


extern FILE*  _log;
static pbm_Natural_ptr n1;
static pbm_Natural_ptr n2;
static pbm_Natural_ptr n3;
static pbm_Natural_ptr n4;

#define DEL(n)  {_pbm_natural_delete(n);}
#define DEL_ALL {_pbm_natural_delete(n1); _pbm_natural_delete(n2); _pbm_natural_delete(n3); _pbm_natural_delete(n4); }

static const char bstr_n1[] = "1111101001000101000000000000000000011010110000010000100010101010101000001100000";
static const char bstr_n2[] = "0000000000000001000000000000000111100001100001010010100000000000000000110010100";

void bit_and(void) {
    CTEST(__func__, "Small test",
    {
        n1 = _pbm_natural_create("101001000101", 2);
        n2 = _pbm_natural_create("110001111100", 2);
        n3 = _pbm_natural_create("100001000100", 2);
        n4 = _pbm_natural_bit_and(n1, n2);
        TEST(_pbm_natural_equal(n3, n4) == true, 0, "Not equal");
        DEL_ALL;
    });
    CTEST(__func__, "Big test",
    {
        n1 = _pbm_natural_create(bstr_n1, 2);
        n2 = _pbm_natural_create(bstr_n2, 2);
        n3 = _pbm_natural_create("0000000000000001000000000000000000000000100000010000100000000000000000000000000", 2);
        n4 = _pbm_natural_bit_and(n1, n2);
        TEST(_pbm_natural_equal(n3, n4) == true, "The big numbers equal", "Not equal");
        DEL_ALL;
    });
}


void bit_or(void) {
    CTEST(__func__, "Small test",
    {
        n1 = _pbm_natural_create("101001000101", 2);
        n2 = _pbm_natural_create("110001111100", 2);
        n3 = _pbm_natural_create("111001111101", 2);
        n4 = _pbm_natural_bit_or(n1, n2);
        TEST(_pbm_natural_equal(n3, n4) == true, 0, "Not equal");
        DEL_ALL;
    });
    CTEST(__func__, "Big test",
    {
        n1 = _pbm_natural_create(bstr_n1, 2);
        n2 = _pbm_natural_create(bstr_n2, 2);
        n3 = _pbm_natural_create("1111101001000101000000000000000111111011110001010010100010101010101000111110100", 2);
        n4 = _pbm_natural_bit_or(n1, n2);
        TEST(_pbm_natural_equal(n3, n4) == true, "The big numbers equal", "Not equal");
        DEL_ALL;
    });
}


void bit_xor(void) {
    CTEST(__func__, "Small test",
    {
        n1 = _pbm_natural_create("101001000101", 2);
        n2 = _pbm_natural_create("110001111100", 2);
        n3 = _pbm_natural_create("011000111001", 2);
        n4 = _pbm_natural_bit_xor(n1, n2);
        TEST(_pbm_natural_equal(n3, n4) == true, 0, "Not equal");
        DEL_ALL;
    });
    CTEST(__func__, "Big test",
    {
        n1 = _pbm_natural_create(bstr_n1, 2);
        n2 = _pbm_natural_create(bstr_n2, 2);
        n3 = _pbm_natural_create("1111101001000100000000000000000111111011010001000010000010101010101000111110100", 2);
        n4 = _pbm_natural_bit_xor(n1, n2);
        TEST(_pbm_natural_equal(n3, n4) == true, "The big numbers equal", "Not equal");
        DEL_ALL;
    });
}
#undef DEL
#undef DEL_ALL