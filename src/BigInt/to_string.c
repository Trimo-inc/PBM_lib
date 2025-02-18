#include "../../include/pbm_BigInt.h"
#include "../../include/tools/base.h"
#include <stdlib.h>

char* pbm_BigInt_str(const pbm_BigInt* num)
{
    size_t size = (
    num->size + pbm___get_order(*num->chunks) + num->is_negative); // + 1

    char* const str = (char*)malloc(size * sizeof(uint32_t));
    if (!str)
        return (char*)str; 
    if (num->is_negative) {
        *str = '-';
    }
    --size;
    str[size--] = '\0';
    // Обходим кусочки num->chunks
    for (size_t i = num->size; i-- > 0;) {
        uint32_t chunk = num->chunks[i];

        // Делим столбиком и преобразуем число в строку
        while (chunk > 0) {
            str[size--] = (chunk % 10) + '0';
            chunk /= 10;
        }
    }
    return str;
}