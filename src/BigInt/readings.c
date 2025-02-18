#include "../../include/pbm_BigInt.h"
#include "../../include/tools/base.h"

#include <string.h>
#include <stdlib.h>

void pbm__BigInt_2pow_process_reading(const char* ___num, const uint16_t power, pbm_BigInt* _Bint)
{
    // Маска для получения только нужных бит из цифры
    uint32_t chunk_mask = (1 << power) - 1;  

    // Вычисляем количество чанков, которые потребуется для записи числа
    size_t num_len = strlen(___num);
    size_t num_chunks = (num_len * power + 31) / 32; // Количество 32-битных чанков

    _Bint->chunks = (uint32_t*)malloc(num_chunks * sizeof(uint32_t));
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



void pbm__BigInt_10_process_reading(const char* ___num, pbm_BigInt* _Bint)
{
    size_t len = strlen(___num);
    size_t num_chunks = (len + 9) / 10; // Каждый чанк вмещает до 10 цифр
    _Bint->chunks = (uint32_t*)malloc(num_chunks * sizeof(uint32_t));

    _Bint->size = num_chunks;

    size_t current_chunk = 0;
    uint32_t current_value = 0;
    size_t digit_count = 0;

    // Проходим по всем цифрам строки
    for (size_t i = len; i-- > 0;) {
        char c = ___num[i];
        current_value = current_value * 10 + (c - '0');
        ++digit_count;

        // Если чанк заполнился (10 цифр, то есть 32 бита), записываем его в структуру
        if (digit_count == 10) {
            _Bint->chunks[current_chunk++] = current_value;
            current_value = 0;
            digit_count = 0;
        }
    }

    // Если осталась неполная группа цифр, записываем оставшиеся цифры в последний чанк
    if (digit_count > 0) {
        _Bint->chunks[current_chunk] = current_value;
    }

}