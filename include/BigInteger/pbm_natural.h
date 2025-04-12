#include "pbm_lib.h"


#ifndef ____PBM_____HEADER_____NATURAL
#define ____PBM_____HEADER_____NATURAL
#include "pbm_types.h"

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
 * \n
 * Для удаления используйте функцию `_pbm_natural_delete`
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
 * @param[out] _inatural Нуль-Натуральное число ${Dynamic} 
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
 * @param[out] _inatural Нуль-Натуральное число ${Dynamic}
 * @param[in]  _digits ${NotNull} Числа по основанию `PBM_ibase`. Они лишь присваиваются. 
 * @param[in] __size  Размер `_digits`
 */
void __pbm_natural_custom_init_s(pbm_Natural_ptr _inatural, pbm_digit_t* const _digits, const size_t __size);

/**
 * @brief Безопасный пользовательский конструктор с копированием чисел.
 * Просто инициализирует структуру нуль-натуральных чисел, как агрегатная инициализация.
 * \n
 * Внутри использует `_pbm_natural_custom_init`
 * @param[out] _inatural Нуль-Натуральное число ${Dynamic}
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
 * @param[out] _inatural Нуль-Натуральное число ${Dynamic}
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
 * @param[out] _inatural Нуль-Натуральное число. В него идёт копирование `_inatural_copy` ${Dynamic}
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
 * @param[out] _inatural Нуль-Натуральное число. Очищается и затем в него идёт перемещение `_inatural_move`. ${Dynamic}
 * @param[in]  _inatural_copy Нуль-Натуральное число, с которого полностью скопируются данные. Сам он не меняется.
 */
void __pbm_natural_move_init_s(pbm_Natural_ptr _inatural, const pbm_Natural_ptr _inatural_move);

/**
 * @brief Конструктор перемещения.
 * `_inatural` будет иметь полную копию `_inatural_move`
 * \n
 * Внутри вызывает `__pbm_natural_move_init` 
 * @warning Если `_inatural` уже заполнен, то возможна утечка памяти.
 * @param[out] _inatural Нуль-Натуральное число. Очищается и в него идёт копирование `_inatural_move`
 * @param[in]  _inatural_copy Нуль-Натуральное число, с которого полностью скопируются данные. Потом данные становится в NULL
 */
void _pbm_natural_move_init(pbm_Natural_ptr _inatural, pbm_Natural_ptr _inatural_move);

/**
 * @brief Конструктор перемещения.
 * `_inatural` будет иметь полную копию `_inatural_move`
 * \n
 * Внутри вызывает `__pbm_natural_move_init_s` 
 * @param[out] _inatural Нуль-Натуральное число. В него идёт копирование `_inatural_copy` ${Dynamic}
 * @param[in]  _inatural_copy Нуль-Натуральное число, с которого полностью скопируются данные. Потом данные становится в NULL
 */
void _pbm_natural_move_init_s(pbm_Natural_ptr _inatural, pbm_Natural_ptr _inatural_move);



// [Деструкторы]

/**
 * @brief Безопасное удаление
 * @param[out] _inatural ${Nullable} ${Dynamic} Нуль-Натуральное число
 * @warning Не забудьте потом выставить вашу переменную в NULL
 */
void _pbm_natural_delete(pbm_Natural_ptr _inatural);

/**
 * @brief Безопасное удаление на стеке. Очищает `_intural->_size` и `_intural->digits`, после этого их значения не зануляются.
 * @param[out] _inatural ${Nullable} ${Dynamic | Stack} Нуль-Натуральное число.
 * \n
 * Если ${Dynamic} -> после вызова используйте free(...)
 */
void __pbm_natural_stack_delete(struct pbm_Natural* _inatural);




// <<[Вспомогательные функции]>>
// Безопасных функций нет, ибо пустая трата времени. Предполагаеся, что они используются только нашей библиотекой.
/**
 * @brief Из строки-числа переводит в Нуль-Натуральное число
 * @param[out] __num_str ${NotNull} Строка, хранящяя число в 10 системе счисления. Изменяется, но не переаллоцируется.
 * @param[out] _inatural Нуль-Натуральное число. 
 */
void ___pbm_natural_spec_10_read(char* __num_str, pbm_Natural_ptr _inatural);

/**
 * @brief Из строки-числа переводит в Нуль-Натуральное число
 * @param[in] __num_str  ${NotNull} Строка, хранящяя число в 2 системе счисления.
 * @param[in] _power     Степень двойки. \em HEX = 16 = 2^4 -> 4
 * @param[out] _inatural Нуль-Натуральное число. 
 */
void ___pbm_natural_spec_2_read(const char* __num_str, const uint16_t _power, pbm_Natural_ptr _inatural);





// <<[Функции]>>
// Для инициализации через строки.

/**
 * @brief Создаёт структуру большого Нуль-Натурального числа.
 * Она не проверяет на правильность записи в строке с нужной системой счисления. 
 * @param[out] _num_str ${NotNull} Строка с числом, записанным в системе счисления `_number_system`. Изменяется, но не переаллоцируется.
 * @param[in]  _number_system Система счисления, в которой записана строка `_num_str`
 * @return Нуль-Натуральное число, если NULL, то была ошибка при создании структуры. ${Nullable} | ${Dynamic}
 */
pbm_Natural_ptr __pbm_natural_create(char* _num_str, const enum pbm_ns _number_system);

/**
 * @brief Создаёт структуру большого Нуль-Натурального числа.
 * Она проверяет на правильность записи в строке с нужной системой счисления. 
 * @param[out] _num_str ${NotNull} Строка с числом, записанным в системе счисления `_number_system`. Изменяется, но не переаллоцируется.
 * @param[in]  _number_system  Система счисления, в которой записана строка `_num_str` ${Nullable} если действительно нет ошибок. 
 * @param[in,out] _error       Код ошибки, если успешно, то равно '0'
 * @return Нуль-Натуральное число, если NULL, то была ошибка при создании структуры. ${Nullable} | ${Dynamic}
 */
pbm_Natural_ptr __pbm_natural_create_s(char* _num_str, const enum pbm_ns _number_system, enum pbm_err* const _error);

/**
 *@brief Создаёт структуру большого Нуль-Натурального числа.
 * Она не проверяет на правильность записи в строке с нужной системой счисления.
 * \n
 * Внутри вызывает `__pbm_natural_create` 
 * @param[out] _num_str ${NotNull} Строка с числом, записанным в системе счисления `_number_system`. Оно полностью копируется.
 * @param[in]  _number_system Система счисления, в которой записана строка `_num_str`
 * @return Нуль-Натуральное число, если NULL, то была ошибка при создании структуры. ${Nullable} | ${Dynamic}
 */
pbm_Natural_ptr _pbm_natural_create(const char* _num_str, const enum pbm_ns _number_system);

/**
 * @brief Безопасно создаёт структуру большого Нуль-Натурального числа.
 * Она проверяет на правильность записи в строке с нужной системой счисления. 
 * @param[out] _num_str ${NotNull} Строка с числом, записанным в системе счисления `_number_system`. Оно полностью копируется.
 * @param[in]  _number_system  Система счисления, в которой записана строка `_num_str` ${Nullable} если действительно нет ошибок.
 * @param[in,out] _error       Код ошибки, если успешно, то равно '0'
 * @return Нуль-Натуральное число, если NULL, то была ошибка при создании структуры. ${Nullable} | ${Dynamic}
 */
pbm_Natural_ptr _pbm_natural_create_s(const char* _num_str, const enum pbm_ns _number_system, enum pbm_err const* _error);

#endif