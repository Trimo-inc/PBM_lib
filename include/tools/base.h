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


/**
 * @brief Делит строку-число пополам
 * @author [Trimo] Списал реализацию
 * @author [Denis (not Trimo)] Сделал реализацию
 * @param[out] _str ${NotNull} & {Предполагается, что вся строка хранит числа}. Строка с числами. {Изменяется} 
 * @param[out] _remainder ${NotNull} Остаток от последней цифры {Изменяется}
 * @return Указатель на текущую строку
 */
char* pbm__halve_str(char* _str, char* _remainder);





/**
 * @brief Генерирует запись числа N
 * @param[in] _Bint {NotNull} Наше число
 * @return Запись числа N. {Dynamic}
 * Например, для N = "1234567890700001234567" результат 66*(2^(32))^(2)+3977395090*(2^(32))^(1)+349851271*(2^(32))^(0)
 */
char* _pbm_generator_(const pbm_BigInt_ptr _Bint);
#endif