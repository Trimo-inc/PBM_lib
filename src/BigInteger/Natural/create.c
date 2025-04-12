#include "pbm_natural.h"
#include <stdlib.h>
#include <string.h>

pbm_Natural_ptr __pbm_natural_create(char *_num_str, const enum pbm_ns _number_system)
{
    pbm_Natural_ptr big = (pbm_Natural_ptr)malloc(sizeof(struct pbm_Natural));

    if ((_number_system & (_number_system - 1)) == 0) {
        uint16_t exp_ = pbm___get2power((uint32_t)_number_system);
        ___pbm_natural_spec_2_read(_num_str, exp_, big);
    } else {
        ___pbm_natural_spec_10_read(_num_str, big);
    }
    return big;
}

pbm_Natural_ptr __pbm_natural_create_s(char *_num_str, const enum pbm_ns _number_system, enum pbm_err* const _error)
{
    pbm_Natural_ptr big = NULL;
    if (_num_str == NULL) {
        if (_error) {
            *_error = IS_NULL;
        }
        return big;
    }

    const char* p = _num_str;
    while (*p != '\0') {
        if (pbm___valid_c(*p, _number_system) == (char)-1) {
            if (_error) {
                *_error = IS_NOT_VALID;
            }
            return big;
        }
        ++p;
    }

    big = __pbm_natural_create(_num_str, _number_system);
    return big;
}

pbm_Natural_ptr _pbm_natural_create(const char *_num_str, const enum pbm_ns _number_system)
{
    const char* copy = ____pbm_strings_copy(_num_str);
    
    pbm_Natural_ptr big = __pbm_natural_create(copy, _number_system);
    free(copy);
    return big;
}

pbm_Natural_ptr _pbm_natural_create_s(const char* _num_str, const enum pbm_ns _number_system, enum pbm_err const* _error)
{
    const char* copy = ____pbm_strings_copy(_num_str);

    pbm_Natural_ptr big = __pbm_natural_create_s(copy, _number_system, _error);
    free(copy);
    return big;
}