#include "../pbm_lib.h"


#if !__PBM__DEFINED(Natural)
#define __PBM__(Natural)

#include "../pbm_types.h"

/**
 * @brief Структура для хранения огромных целых чисел без знака.
 * Представляет собой нуль натуральное множество одного числа.
 * Всегда положительно.
 */
struct pbm_Natural {
  /**
   * @brief Представляет собой динамический массив чисел по основанию `PBM_ibase`
   * В младших индексах лежат младшие разряды, в старших, соответсвенно, высшие разряды.
   * 
   */
  pbm_digit_t* digits;
  /**
   * Размер массива digits
   */
  size_t _size;
};

/**
 * @brief Основная структура для пользователей-программистов.
 * ${NotNull}
 */
typedef struct pbm_Natural* pbm_Natural_ptr; 


// <<[Функции]>>


// [Конструкторы]
// [По умолчанию]
/**
 * @brief Конструктор по умолчанию.
 * Заполняет структуру нулями.
 * @warning Если `_inatural` уже заполнен, то возможна утечка памяти. 
 * @param[out] _inatural Нуль-Натуральное число 
 */
void _pbm_natural_default_init(pbm_Natural_ptr _inatural);

/**
 * @brief Безопасный конструктор по умолчанию.
 * Заполняет структуру нулями. 
 * \n
 * Внутри вызывает функцию `_pbm_natural_default_init`, но перед этим очищает структуру, убирая утечки памяти.
 * @param[out] _inatural Нуль-Натуральное число 
 */
void _pbm_natural_default_init_s(pbm_Natural_ptr _inatural);


// [Пользовательские]
/**
 * @brief Пользовательский конструктор без копирования чисел.
 * Просто инициализирует структуру нуль-натуральных чисел, как агрегатная инициализация.
 * @warning Если `_inatural` уже заполнен, то возможна утечка памяти. 
 * @param[out] _inatural Нуль-Натуральное число
 * @param[in]  _digits ${NotNull} Числа по основанию `PBM_ibase`. Они лишь присваиваются.
 * @param[in] __size  Размер `_digits`
 */
void __pbm_natural_custom_init(pbm_Natural_ptr _inatural, pbm_digit_t* const _digits, const size_t __size);

/**
 * @brief Пользовательский конструктор с копированием чисел.
 * Просто инициализирует структуру нуль-натуральных чисел, как агрегатная инициализация.
 * \n
 * Внутри использует `__pbm_natural_custom_init`
 * @warning Если `_inatural` уже заполнен, то возможна утечка памяти. 
 * @param[out] _inatural Нуль-Натуральное число
 * @param[in] _digits ${NotNull} Числа по основанию `PBM_ibase`. Они копируются. Не забудьте, что сначала младшие разряды, потом страшие.
 * @param[in] __size  Размер `_digits`
 */
void _pbm_natural_custom_init (pbm_Natural_ptr _inatural, const pbm_digit_t* _digits, const size_t __size);


/**
 * @brief Безопасный пользовательский конструктор без копирования чисел.
 * Просто инициализирует структуру нуль-натуральных чисел, как агрегатная инициализация.
 * \n
 * Внутри использует `__pbm_natural_custom_init` 
 * @param[out] _inatural Нуль-Натуральное число
 * @param[in]  _digits ${NotNull} Числа по основанию `PBM_ibase`. Они лишь присваиваются. 
 * @param[in] __size  Размер `_digits`
 */
void __pbm_natural_custom_init_s(pbm_Natural_ptr _inatural, pbm_digit_t* const _digits, const size_t __size);

/**
 * @brief Безопасный пользовательский конструктор с копированием чисел.
 * Просто инициализирует структуру нуль-натуральных чисел, как агрегатная инициализация.
 * \n
 * Внутри использует `_pbm_natural_custom_init`
 * @param[out] _inatural Нуль-Натуральное число
 * @param[in] _digits ${NotNull} Числа по основанию `PBM_ibase`. Они копируются. Не забудьте, что сначала младшие разряды, потом страшие.
 * @param[in] __size  Размер `_digits`
 */
void _pbm_natural_custom_init_s (pbm_Natural_ptr _inatural, const pbm_digit_t* _digits, const size_t __size);


// [Числовые]
/**
 * @brief Числовой конструктор.
 * @warning Если `_inatural` уже заполнен, то возможна утечка памяти.
 * @param[out] _inatural Нуль-Натуральное число
 * @param[in] _number Число в 10 системе счисления
 */
void _pbm_natural_i_init(pbm_Natural_ptr _inatural, pbm_digit_t _number);

/**
 * @brief Безопасный числовой конструктор.
 * \n
 * Внутри вызывает `_pbm_natural_i_init`
 * @param[out] _inatural Нуль-Натуральное число
 * @param[in] _number Число в 10 системе счисления
 */
void _pbm_natural_i_init_s(pbm_Natural_ptr _inatural, pbm_digit_t _number);


// [Копирующие]

/**
 * @brief Конструктор копирования.
 * `_inatural` будет лишь иметь те же значения, указатели будут другими. То есть будет выделение памяти. 
 * @warning Если `_inatural` уже заполнен, то возможна утечка памяти.
 * @param[out] _inatural Нуль-Натуральное число. В него идёт копирование `_inatural_copy`
 * @param[in]  _inatural_copy Нуль-Натуральное число, с которого скопируются данные, будет выделена новый кусочек памяти.
 */
void _pbm_natural_copy_init(pbm_Natural_ptr _inatural, const pbm_Natural_ptr _inatural_copy);

/**
 * @brief Безопасный конструктор копирования.
 * `_inatural` будет лишь иметь те же значения, указатели будут другими. То есть будет выделение памяти.
 * \n
 * Внутри вызывает `_pbm_natural_copy_init`
 * @param[out] _inatural Нуль-Натуральное число. В него идёт копирование `_inatural_copy`
 * @param[in]  _inatural_copy Нуль-Натуральное число, с которого скопируются данные, будет выделена новый кусочек памяти.
 */
void _pbm_natural_copy_init_s(pbm_Natural_ptr _inatural, const pbm_Natural_ptr _inatural_copy);


// [Перемещение]

/**
 * @brief Конструктор перемещения.
 * `_inatural` будет иметь полную копию `_inatural_move`
 * @warning Если `_inatural` уже заполнен, то возможна утечка памяти.
 * @param[out] _inatural Нуль-Натуральное число. В него идёт копирование `_inatural_copy`
 * @param[in]  _inatural_copy Нуль-Натуральное число, с которого полностью скопируются данные. Сам он не меняется.
 */
void __pbm_natural_move_init(pbm_Natural_ptr _inatural, const pbm_Natural_ptr _inatural_move);

/**
 * @brief Безопасный конструктор перемещения.
 * `_inatural` будет иметь полную копию `_inatural_move`
 * \n
 * Внутри вызывает `__pbm_natural_move_init`
 * @param[out] _inatural Нуль-Натуральное число. В него идёт копирование `_inatural_copy`
 * @param[in]  _inatural_copy Нуль-Натуральное число, с которого полностью скопируются данные. Сам он не меняется.
 */
void __pbm_natural_move_init_s(pbm_Natural_ptr _inatural, const pbm_Natural_ptr _inatural_move);

/**
 * @brief Конструктор перемещения.
 * `_inatural` будет иметь полную копию `_inatural_move`
 * \n
 * Внутри вызывает `__pbm_natural_move_init` 
 * @warning Если `_inatural` уже заполнен, то возможна утечка памяти.
 * @param[out] _inatural Нуль-Натуральное число. В него идёт копирование `_inatural_copy`
 * @param[in]  _inatural_copy Нуль-Натуральное число, с которого полностью скопируются данные. Потом становится в NULL
 */
void _pbm_natural_move_init(pbm_Natural_ptr _inatural, pbm_Natural_ptr _inatural_move);

/**
 * @brief Конструктор перемещения.
 * `_inatural` будет иметь полную копию `_inatural_move`
 * \n
 * Внутри вызывает `__pbm_natural_move_init_s` 
 * @param[out] _inatural Нуль-Натуральное число. В него идёт копирование `_inatural_copy`
 * @param[in]  _inatural_copy Нуль-Натуральное число, с которого полностью скопируются данные. Потом становится в NULL
 */
void _pbm_natural_move_init_s(pbm_Natural_ptr _inatural, pbm_Natural_ptr _inatural_move);

// [Деструкторы]

/**
 * @brief Безопасное удаление.
 * @param[out] _inatural ${Nullable} Нуль-Натуральное число. После успеха становится в NULL
 */
void _pbm_natural_delete(pbm_Natural_ptr _inatural);

#endif