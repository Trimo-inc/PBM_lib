#include "../../include/pbm_BigInt.h"
#include "../../include/tools/base.h"
#include <stdlib.h>
// TODO: Не работает, смотри также про size_str и запись реверсивна
char* pbm_BigInt_str(const pbm_BigInt_ptr num)
{
    
    const size_t num_un1 = num->size - 1;
    const uint8_t order = (pbm___get_order(num->chunks[num_un1]));
    // Определяем точный размер без учёта терминального нуля
    size_t size_str = (
        (num_un1) * 10 + order + num->is_negative
    ); 


    char* const str = (char*)malloc(size_str + 1);
    if (!str)
        return (char*)str;

    char* str2 = str;
    if (num->is_negative) {
        *str = '-';
        ++str2;
    }
    str[size_str--] = '\0';

    // Обходим кусочки num->chunks
    for (uint32_t i = num_un1; i != UINT32_MAX; --i ) {
        uint32_t chunk = num->chunks[i];

        // Делим столбиком и преобразуем число в строку
        while (chunk > 0) {
            *str2 = (chunk % 10) + '0';
            chunk /= 10;
            ++str2;
        }
    }
    return str;
}