#ifndef TOOLS_BASE_h
#define TOOLS_BASE_h

#include <stdint.h>
#include "../pbm_types.h"

/**
 * @brief Вытаскивает показатель степени из числа: 2^power = _num
 * @param[in] _num Число должно быть равно степени двойки, например, 8 или 16.
 * И не равно 0
 * @return Показатель степени
 */
uint16_t pbm___get2power(uint32_t _num);


/**
 * @brief Проверяет, что текущий символ соответствует системе счисления
 * @param[in] _c Символ
 * @param[in] _num_system Система счисления
 * @return Число равное данной системе счисления (например, для 'B' == 11).
 * Если не действительно число, то возращается -1
 */
char pbm___valid_c(const char _c, const enum pbm_ns _num_system);

/**
 * @brief Аналогична функции "pbm___valid_c"
 * @param[in] _c Символ. Предполагается, что число действительно. Диапазон [0-9]U[A-F]
 * @return Число (Например, для 'A' == 10, для '4' == 4). Если не входит в диапазон, то -1
 */
char pbm___get_c(const char _c);

/**
 * @brief Находит разряд данного числа
 * @param[in] num Число
 * @return Разряд (uint8_t: потому что в uint32_t максимальный разряд == 10)
 */
uint8_t pbm___get_order(uint32_t num);

#endif