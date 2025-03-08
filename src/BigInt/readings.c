#include "../../include/pbm_BigInt.h"
#include "../../include/tools/base.h"

#include <string.h>
#include <stdlib.h>
#include <math.h>

void pbm__BigInt_2pow_process_reading(const char* ___num, const uint16_t power, struct pbm_BigInt* _Bint)
{
    // Вычисляем количество чанков, которые потребуется для записи числа
    size_t num_len = strlen(___num);
    size_t num_chunks = (num_len * power + 31) / 32; // Количество 32-битных чанков

    //_Bint->chunks = (uint32_t*)malloc(num_chunks * sizeof(uint32_t));
    if (!_Bint->chunks) {
        return;
    }
    
    _Bint->size = num_chunks;


    uint32_t current_chunk = 0;
    size_t chunk_index = 0;
    
 
    for (size_t i = 0; i < num_len; ++i) {
        uint32_t digit_value = pbm___get_c(___num[i]);

        // Добавляем цифру в текущий чанк
        current_chunk = (current_chunk << power) | digit_value;

        // Если текущий чанк заполнился (32 бита), сохраняем его и начинаем новый
        if ((i + 1) * power >= 32 || i == num_len - 1) {
            _Bint->chunks[chunk_index++] = current_chunk;
            current_chunk = 0;  // Сбрасываем чанк
        }
    }
    
}



void pbm__BigInt_10_process_reading(const char* ___num, struct pbm_BigInt* _Bint)
{
    size_t len = strlen(___num);
    size_t chunk_capacity = ceil((double)(len / PBM_log_base));
    _Bint->chunks = calloc(chunk_capacity, sizeof(pbm_digit_t));
    _Bint->size = 0;

    #if (ARCH == 32)
    unsigned char shift = 0;
    #elif (ARCH == 64)
    pbm_digit_t shift = 0;
    #endif


    
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
        str = pbm__halve_str(str, (char*)&bit);

        

        if (shift == PBM_digit_bits) {
            ++_Bint->size;
            shift = 0;
        }       
        
        _Bint->chunks[_Bint->size] |= (pbm_digit_t)(bit << shift);
        
        ++shift;
    }

    
    if (_Bint->size && _Bint->chunks[_Bint->size] == 0) {
        _Bint->chunks[_Bint->size] = 1;
    }
    ++_Bint->size;
    free(copy);

}