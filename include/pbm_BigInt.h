#ifndef __PBM_BIGINT_h
#define __PBM_BIGINT_h
#include "./pbm_types.h"


// Базовые операции над struct pbm_BigInt

/**
 * @brief Создаёт структуру для хранения больших целых чисел.
 * Безопасная версия.
 * @param[in] _num Строка с числом ${NotNull}
 * @param[in] _num_system Система счисления, в которой представлено ваше число
 * @param[in] _is_negative Будет ли число отрицательным (0 - если нет)
 * @param[out,in] _err Код ошибки, если равен == 0, то число образовалось
 * ${NotNull}
 * @return NULL || инициализированную структуру
 */
pbm_BigInt_ptr pbm_BigInt_create_s(
    const char* _num,
    const enum pbm_ns _num_system,
    const char _is_negative,
    enum pbm_err* _err
);

/**
 * @brief Безопасно удаляет struct pbm_BigInt
 * @param[out] _inum ${Nullable} 
 */
void pbm_BigInt_delete(pbm_BigInt_ptr _inum);


/*
<<[Конструкторы]>>
*/

/**
 * @brief Базовый конструктор для огромного числа
 * Зануляет структуру
 * @param[out] _inum Наше число ${NotNull}
 */
void __pbm_BigInt_default_ctor(struct pbm_BigInt* _inum);

/**
 * @brief Конструктор копирования
 * @param[out] _inum Заполняет данную структуру значениями из другой
 * @param[in]  _icnum Копируется 
 */
void __pbm_BigInt_copy_ctor(struct pbm_BigInt* _inum, const struct pbm_BigInt* _icnum);






/**
 * @brief Складывает два числа, игнорируя знак, помещая результат в параметр "a"
 * @param[out] a Слагаемое и сумма (записывается результат)
 * @param[in]  b Слагаемое
 */
void pbm_BigInt_base_add(pbm_BigInt_ptr a, const pbm_BigInt_ptr b);

/**
 * @brief Вычитает два числа, игнорируя знак, помещая результат в параметр "a"
 * @param[out] a Уменьшаемое и разность (записывается результат)
 * @param[in]  b Вычитаемое
 */
void pbm_BigInt_base_sub(pbm_BigInt_ptr a, const pbm_BigInt_ptr b);


/**
 * @brief Умножает два числа, игнорируя знак, помещая результат в параметр "a"
 * @param[out] a Множитель и произведение (записывается результат)
 * @param[in]  b Множитель
 */
void pbm_BigInt_base_mul(pbm_BigInt_ptr a, const pbm_BigInt_ptr b);


/**
 * @brief Делит два числа, игнорируя знак, помещая результат в параметр "a"
 * @param[out] a Делимое и частное (записывается результат)
 * @param[in]  b Делитель
 */
void pbm_BigInt_base_div(pbm_BigInt_ptr a, const pbm_BigInt_ptr b);




/*

<<[Дополнительные функции для базовых операций]>>

*/


/**
 * @brief Читает из строки числа с системой счисления степени двойки и записывает в структуру.
 * @param[in]  ___num Число в виде строки. Предполагается, что число в виде строки действительно
 * @param[in]  power  Степень двойки (для 16-ричной это 4 (2^4 == 16))
 * @param[out] _Bint  Структура, в которую идёт запись целого числа. ${NotNull}
 */
void pbm__BigInt_2pow_process_reading(
    const char* ___num, const uint16_t power, struct pbm_BigInt* _Bint);


/**
 * @brief Преобразует строку в структуру pbm_BigInt
 * Имеет внутри копирование параметра ___num
 * @param[in] ___num Строка с числом в десятичной системе
 * @param[out] _Bint Структура для хранения числа
 */
void pbm__BigInt_10_process_reading(const char* ___num, struct pbm_BigInt* _Bint);


/**
 * @brief Преобразует из строки в структуру pbm_BigInt.
 * @param[out] ___num_str ${NotNull} Строка изменяется, но не переаллоцируется. Строка в десятичном основании
 * @param[in]  ___len_str Длина строки ___num_str
 * @param[out] __inum     ${NotNull} Наше число
 */
void __pbm__BigInt_10_process_reading(
    char* ___num_str, size_t __len_str, struct pbm_BigInt* __inum);


/*

Полезные функции

*/ 

/**
 * @brief Преобразует число в строку
 * @param[in] num Число
 * @return Строка с числом в десятичной системе счисления
 */
char* pbm_BigInt_str(const pbm_BigInt_ptr num);
#endif