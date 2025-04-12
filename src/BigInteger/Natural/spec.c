#include "pbm_natural.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
void ___pbm_natural_spec_10_read(char *__num_str, pbm_Natural_ptr _inatural)
{
    {
    const size_t len = strlen(__num_str);
    const size_t chunk_capacity = ceil((double)(len / PBM_log_base)); 

    _inatural->digits = (pbm_digit_t*)calloc(chunk_capacity, sizeof(pbm_digit_t));
    _inatural->_size = 0;
    }

    pbm_digit_t shift = 0, bit = 0;

    while (*__num_str) {
        __num_str = pbm__halve_str(__num_str, (char*)&bit);

        if (shift == PBM_digit_bits) {
            ++_inatural->_size; 
            shift = 0;
        }
        _inatural->digits[_inatural->_size] |= (pbm_digit_t)(bit << shift);
        ++shift;
    }

    if (_inatural->_size && _inatural->digits[_inatural->_size] == 0) {
        _inatural->digits[_inatural->_size] = 1;
    }
    ++_inatural->_size;
}


void ___pbm_natural_spec_2_read(const char *__num_str, const uint16_t _power, pbm_Natural_ptr _inatural)

{
    while (*__num_str == '0' && *(__num_str + sizeof(*__num_str)) != '\0') {
        ++__num_str; // Пропуск ведущих нулей
    }
    
    const uint16_t per_digits = PBM_digit_bits / _power;
    const size_t len = strlen(__num_str);
    {
    const size_t chunk_capacity = (len + per_digits - 1) / per_digits;
    _inatural->digits = (pbm_digit_t*)calloc(chunk_capacity, sizeof(pbm_digit_t));
    }
    
    pbm_digit_t bit_pos;
    for (size_t i = 0; i < len; ++i) {
        #if (ARCH == 32)
            char digit = pbm___get_c(__num_str[len - i - 1]);
        #elif (ARCH == 64)
            pbm_digit_t digit = (pbm_digit_t)pbm___get_c(__num_str[len - i - 1]);
        #endif

        _inatural->_size = i / per_digits;
        bit_pos = (i % per_digits) * _power;
        
        _inatural->digits[_inatural->_size] |= (digit << bit_pos); 
    }
    ++_inatural->_size;
}