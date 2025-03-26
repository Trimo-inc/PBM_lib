#include "../../include/pbm_BigInt.h"
#include "../../include/tools/base.h"

#include <string.h>
#include <stdlib.h>
#include <math.h>

void pbm__BigInt_2pow_process_reading(const char* ___num, const uint16_t power, struct pbm_BigInt* _Bint)
{
    const pbm_digit_t per_count = PBM_digit_bits / power;

    // Удаление ведущих нулей
    while (*___num == '0' && *(___num + sizeof(*___num)) != '\0')
        ++___num;

    const size_t len = strlen(___num);

    size_t chunk_capacity = (len + per_count - 1) / per_count;
    _Bint->chunks = (pbm_digit_t*)calloc(chunk_capacity, sizeof(pbm_digit_t));
    _Bint->size = chunk_capacity;
    
    for (size_t i = 0; i < len; ++i) {
        #if ARCH == 32
        char digit = (char)pbm___get_c(___num[len - 1 - i]);
        #elif ARCH == 64
        pbm_digit_t digit = (pbm_digit_t)pbm___get_c(___num[len - 1 - i]);
        #endif

        size_t indx = i / per_count;
        size_t bit_pos = (i % per_count) * power;


        _Bint->chunks[indx] |= (digit << bit_pos);
        
    }

}



void pbm__BigInt_10_process_reading(const char* ___num, struct pbm_BigInt* _Bint)
{
    size_t len = strlen(___num);
    size_t chunk_capacity = ceil((double)(len / PBM_log_base));
    _Bint->chunks = calloc(chunk_capacity, sizeof(pbm_digit_t));
    _Bint->size = 0;

    pbm_digit_t shift = 0;
    
    char* const  copy = malloc(len); // Временная переменная (копия ___num)
    copy[len - 1] = '\0';
    strcpy(copy, ___num);
    
    char* str = copy;
    #if (ARCH == 32)
    char bit;
    #elif (ARCH == 64)
    pbm_digit_t bit = 0;
    #endif

    while (*str) {
        #if (ARCH == 32)
        str = pbm__halve_str(str, &bit);
        #elif (ARCH == 64)
        str = pbm__halve_str(str, (char*)&bit);
        #endif
        

        if (shift == PBM_digit_bits) {
            ++_Bint->size;
            shift = 0;
        }       
        #if (ARCH == 32)
        _Bint->chunks[_Bint->size] |= (bit << shift);
        #elif (ARCH == 64)
        _Bint->chunks[_Bint->size] |= (pbm_digit_t)(bit << shift);
        
        #endif
        ++shift;
    }

    
    if (_Bint->size && _Bint->chunks[_Bint->size] == 0) {
        _Bint->chunks[_Bint->size] = 1;
    }
    ++_Bint->size;
    free(copy);

}