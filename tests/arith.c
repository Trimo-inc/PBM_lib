#include "pbm_lib.h"

#include "testing.h"
#include <string.h>
#include <stdlib.h>

static pbm_Natural_ptr n1;
static pbm_Natural_ptr n2;
static pbm_Natural_ptr n3;
static pbm_Natural_ptr n4;

#define DEL(n)  {_pbm_natural_delete(n);}
#define DEL_ALL {_pbm_natural_delete(n1); _pbm_natural_delete(n2); _pbm_natural_delete(n3); _pbm_natural_delete(n4);}

void small_add(void) {
    CTEST(__func__, "for INT", {
        n1 = __pbm_natural_create("10", 10);
        n2 = __pbm_natural_create("34567", 10);
        _pbm_natural_add__int(n1, 34557);
        TEST(_pbm_natural_equal(n1, n2) == true, "10 + 34557 = 34567", "Not adding!");
        _pbm_natural_add__int(n1, PBM_ibase); // Max 
        DEL(n2);
        if (ARCH == 32) {
            n2 = __pbm_natural_create("4295001862", 10);
            TEST(_pbm_natural_equal(n1, n2) == true, "34567 + 4294967295 = 4295001862", "Not adding!");
        }
        if (ARCH == 64) {
            n2 = __pbm_natural_create("18446744073709586182", 10);
            TEST(_pbm_natural_equal(n1, n2) == true, "34567 + 18446744073709551615 = 18446744073709586182", "Not adding!");
        }
        DEL(n1);
        DEL(n2);
    });
    CTEST(__func__, "for NN-num", {
        n1 = __pbm_natural_create("10000000000000000000000", 10);
        n2 = __pbm_natural_create("124345678999135", 10);
        n3 = __pbm_natural_create("10000000124345678999135", 10);
        n4 = _pbm_natural_add(n1, n2);
        TEST(_pbm_natural_equal(n3, n4), "10000000000000000000000 + 124345678999135 = 10000000124345678999135", "No!!!");
        DEL_ALL;
        n1 = __pbm_natural_create("0", 10);
        n2 = _pbm_natural_add(n1, n1);
        TEST(_pbm_natural_equal(n1, n2), "0 + 0 = 0", "");
        DEL(n1); DEL(n2);
        n1 = __pbm_natural_create("98",  10);
        n2 = __pbm_natural_create("2",   10);
        n3 = __pbm_natural_create("100", 10);
        n4 = _pbm_natural_add(n1, n2);
        TEST(_pbm_natural_equal(n3, n4), "98 + 2 = 100", "what???");
        DEL_ALL;
    });
    {
        char ibuff[64];
        char _buff[64];
        for (int i = 0; i < 1000; ++i) {
            size_t _a2 = i + i;
            itoa(i, ibuff, 16);
            itoa(_a2, _buff, 16);
            n1 = __pbm_natural_create(ibuff, 16);
            n2 = __pbm_natural_create(_buff, 16);
            n3 = _pbm_natural_add(n1, n1);
            TEST(_pbm_natural_equal(n2, n3), "Yes!", "NOO!");
            assert(_pbm_natural_equal(n2, n3) == true);
            DEL(n1); DEL(n2); DEL(n3);
        }
    }   
}

void small_mul(void) {
    CTEST(__func__, "for INT", {
        n1 = __pbm_natural_create("100", 10);
        n2 = __pbm_natural_create("200", 10);
        _pbm_natural_mul__int(n1, 2);
        TEST(_pbm_natural_equal(n1, n2), "100 * 2 = 200", "NO!");
        _pbm_natural_mul__int(n1, 7);
        n3 = __pbm_natural_create("1400", 10);
        TEST(_pbm_natural_equal(n1, n3), "200 * 7 = 1400", "NO!");
        _pbm_natural_mul__int(n3, PBM_ibase);
        if (ARCH == 32) {
            n4 = __pbm_natural_create("6012954213000", 10);
            TEST(_pbm_natural_equal(n3, n4), "1400 * (2^32 - 1) = 6012954213000", "NO!");
        }
        if (ARCH == 64) {
            n4 = __pbm_natural_create("25825441703193372261000", 10);
            TEST(_pbm_natural_equal(n3, n4), "1400 * (2^64 - 1) = 25825441703193372261000", "NO!");
        }
        DEL_ALL;
        n1 = __pbm_natural_create("100000000000000000000000000", 10);
        n2 = __pbm_natural_create("100000000000000000000000000000000000", 10);
        _pbm_natural_mul__int(n1,                            1000000000);
        TEST(_pbm_natural_equal(n1, n2), "Okey", "What??");
        n3 = __pbm_natural_create("9999999999999999999999999999999999999999999", 10);
        n4 = __pbm_natural_create("12345678899999999999999999999999999999999998765432110", 10);
        _pbm_natural_mul__int(n3, 1234567890);
        TEST(_pbm_natural_equal(n3, n4), "Okey", "What??");
        DEL_ALL;
    });

    CTEST(__func__, "for two ini", {
        n1 = __pbm_natural_create("100000234", 10);
        n2 = __pbm_natural_create("25", 10);
        n3 = __pbm_natural_create("2500005850", 10);
        n4 = __pbm_natural_base_mul(n1 , n2);
        TEST(_pbm_natural_equal(n3, n4), "Yes!", "No!");
        DEL_ALL;
        n1 = __pbm_natural_size_create(1);
        n2 = __pbm_natural_create("981643127418", 10);
        n3 = __pbm_natural_base_mul(n1, n2);
        TEST(_pbm_natural_equal(n1, n3), "Yes!", "No!");
        n4 = NULL;
        DEL_ALL;
    });
}


#undef DEL
#undef DEL_ALL