#include "../../include/tools/base.h"
#include "../../include/pbm_types.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#if defined PBM__TRADITIONAL
#include <math.h>
#endif

pbm_digit_t *_pbm_digit_copy(const pbm_digit_t *_digits, const size_t _size)
{
    const size_t SIZE =  _size * sizeof(pbm_digit_t);
    pbm_digit_t* __digits = (pbm_digit_t*)malloc(SIZE);
    memcpy(__digits, _digits, SIZE);
    return __digits;
}

uint16_t pbm___get2power(uint32_t _num)
{
    uint16_t exponent = 0;
    if (_num) {
        while (_num > 1) {
            _num >>= 1;
            ++exponent;
        } 
    }
    return exponent;
}




char pbm___valid_c(const char _c, const enum pbm_ns _num_system)
{
    char n = -1;
    unsigned char value = (unsigned char)pbm___get_c(_c);
    if (value < (char)_num_system)
        n = (char)value;
    return n;
}


char pbm___get_c(const char _c)
{
    char n = -1;
    if (isdigit(_c)) {
        n = _c - '0';
    } else if (isalpha(_c)) {
        n = (char)toupper(_c) - (char)'A' + (char)10;
    }
    return n;
}



uint8_t pbm___get_order(uint32_t num)
{
    #if defined PBM__TRADITIONAL_
    return (uint8_t)((uint8_t)((float)num) + 1);
    #else
    uint8_t order = 1;
    while (num > 9) {
        num /= 10;
        ++order;
    }
    return order;
    #endif
}




char* pbm__halve_str(char* _str, char* _remainder)
{
    *_remainder = 0;
    char flag = 1; 
    char* ret = _str;

    pbm_digit_t dividend, result;
    for (size_t i = 0; _str[i] != '\0'; ++i) {
        char digit = _str[i] - '0'; 
        dividend = (*_remainder) * 10 + digit;
        result   = dividend / 2;
        *_remainder = dividend % 2;

        _str[i] = (char)(result + '0');
        if (0 == result && flag) {
            ret = _str + i + 1;
        } else flag = 0;
    }
    return ret;
}

char* ____pbm_strings_copy(const char *const _str)
{
    size_t len = strlen(_str);
    char* copy = (char*)malloc(sizeof(char) * (len + 1));
    memcpy(copy, _str, len);
    copy[len] = '\0';
    return copy;
}