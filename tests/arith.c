#include "pbm_lib.h"

#include "testing.h"
#include <string.h>
#include <stdlib.h>

static pbm_Natural_ptr n1;
static pbm_Natural_ptr n2;
static pbm_Natural_ptr n3;

#define DEL(n)  {_pbm_natural_delete(n);}
#define DEL_ALL {_pbm_natural_delete(n1); _pbm_natural_delete(n2); _pbm_natural_delete(n3);}

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
}


#undef DEL
#undef DEL_ALL