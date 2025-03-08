#ifndef __PBM_nums_h
#define __PBM_nums_h
#include "./pbm_types.h"


/**
 * @brief Создаёт систему счисления. Каждый индекс соответствует числу.
 * (Например, передаём "12345", это 5-ричная система счисления, где '5' соответствует числу 4)
 * @param[in] strings Строка с числами ${NotNull}
 * @return Обработанную систему счисления.
 */
struct pbm_nums pbm_nums_create(const char* strings);

/**
 * @brief Инициализирует систему счисления. Каждый индекс соответствует числу.
 * (Например, передаём во второй параметр "0123", это 4-ричная система счисления, где '3' соответствует числу 3)
 * @param[out] nums Структура система счисления ${NotNull}
 * @param[in]  strings Строка с числами ${NotNull}
 */
void pbm_nums_init(struct pbm_nums* nums, const char* strings);


/**
 * @brief Безопасно удаляет struct pbm_nums.
 * Не присваивает NULL значения полям структуры.
 * @param[out] nums Структура система счисления ${Nullable}
 */
void pbm_nums_delete(struct pbm_nums* nums);
#endif