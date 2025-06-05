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


void bit_lshift(void) {
    CTEST("logic_lshift", "Natural for small test", {
        n1 = __pbm_natural_create("000000000000001", 2);
        _pbm_natural_bit_logic_lshift__int(n1, 1);
        n2 = __pbm_natural_create("000000000000010", 2);
        TEST(_pbm_natural_equal(n1, n2) == true, "Great!", "Not equal from %s", __func__);
        _pbm_natural_bit_logic_lshift__int(n1, 1);
        n3 = __pbm_natural_create("000000000000100", 2);
        TEST(_pbm_natural_equal(n1, n3) == true, "Great!", "Not equal from %s", __func__);
        _pbm_natural_bit_logic_lshift__int(n1, 10);
        n4 = __pbm_natural_create("001000000000000", 2);
        TEST(_pbm_natural_equal(n1, n4) == true, 0, "Not equal from %s", __func__);
        DEL_ALL;
    });
    CTEST("logic_lshift", "Natural for big number test", {
        n1 = __pbm_natural_create("100000000010100100100010000100001111100000000000001100000000000001100010000000010000000000001100000111000000100000000000100000100100100000010000100101001000010101000101010101000001010000000010100", 2);
        _pbm_natural_bit_logic_lshift__int(n1, 74);
        n2 = __pbm_natural_create("10000000001010010010001000010000111110000000000000110000000000000110001000000001000000000000110000011100000010000000000010000010010010000001000010010100100001010100010101010100000101000000001010000000000000000000000000000000000000000000000000000000000000000000000000000", 2);
        TEST(_pbm_natural_equal(n1, n2) == true, "Great!", "Not equal from %s", __func__);
        DEL_ALL;
    });

}
#undef DEL
#undef DEL_ALL