#include "pbm_lib.h"


#ifndef ____PBM_____HEADER_____NATURAL
#define ____PBM_____HEADER_____NATURAL
#include "pbm_types.h"

/**
 * @brief Структура для хранения огромных целых чисел без знака.
 * Представляет собой нуль натуральное число.
 * Всегда положительно.
 */
struct pbm_Natural {
  /**
   * @brief Представляет собой динамический массив чисел по основанию `PBM_ibase`
   * В младших индексах лежат младшие разряды, в старших, соответственно, высшие разряды.
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
/*
Если перед именем функции стоит '__', значит излишнее копирование избегается
Если перед именем функции стоит '_', значит будет копирование
*/
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
 * Просто инициализирует структуру нуль-натурального числа, как агрегатная инициализация.
 * @warning Если `_inatural` уже заполнен, то возможна утечка памяти. 
 * @param[out] _inatural Нуль-Натуральное число
 * @param[in]  _digits Числа по основанию `PBM_ibase`. Они лишь присваиваются.
 * @param[in] __size  Размер `_digits`
 */
void __pbm_natural_custom_init(pbm_Natural_ptr _inatural, pbm_digit_t* const _digits, const size_t __size);

/**
 * @brief Пользовательский конструктор с копированием чисел.
 * Просто инициализирует структуру нуль-натурального числа, как агрегатная инициализация.
 * \n
 * Внутри использует `__pbm_natural_custom_init`
 * @warning Если `_inatural` уже заполнен, то возможна утечка памяти. 
 * @param[out] _inatural Нуль-Натуральное число
 * @param[in] _digits Числа по основанию `PBM_ibase`. Они копируются. Не забудьте, что сначала младшие разряды, потом старшие. ${Nullable}
 * @param[in] __size  Размер `_digits`
 */
void _pbm_natural_custom_init (pbm_Natural_ptr _inatural, const pbm_digit_t* _digits, const size_t __size);


/**
 * @brief Безопасный пользовательский конструктор без копирования чисел.
 * Просто инициализирует структуру нуль-натуральных чисел, как агрегатная инициализация.
 * \n
 * Внутри использует `__pbm_natural_custom_init` 
 * @param[out] _inatural Нуль-Натуральное число ${Dynamic}
 * @param[in]  _digits Числа по основанию `PBM_ibase`. Они лишь присваиваются. 
 * @param[in] __size  Размер `_digits`
 */
void __pbm_natural_custom_init_s(pbm_Natural_ptr _inatural, pbm_digit_t* const _digits, const size_t __size);

/**
 * @brief Безопасный пользовательский конструктор с копированием чисел.
 * Просто инициализирует структуру нуль-натуральных чисел, как агрегатная инициализация.
 * \n
 * Внутри использует `_pbm_natural_custom_init`
 * @param[out] _inatural Нуль-Натуральное число 
 * @param[in] _digits Числа по основанию `PBM_ibase`. Они копируются. Не забудьте, что сначала младшие разряды, потом старшие.
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
 * @brief Безопасно перемещает поля структуры из `_inatural_move` в `_inatural`. Не копирует их.
 * @param[out] _inatural Сначала очищает структуру с помощью `_pbm_natural_stack_delete`.
 * Потом заполняется данными из `_inatural_move`
 * @param[in] _inatural_move Перемещает все свои данные (массив чисел и размер) в структуру `_inatural`
 */
void __pbm_natural_move_s(pbm_Natural_ptr _inatural, const pbm_Natural_ptr _inatural_move);

/**
 * @brief Конструктор перемещения.
 * `_inatural` будет иметь полную копию `_inatural_move`
 * @warning Если `_inatural` уже заполнен, то возможна утечка памяти.
 * @param[out] _inatural Нуль-Натуральное число. В него идёт копирование `_inatural_copy`
 * @param[in]  _inatural_copy Нуль-Натуральное число, с которого полностью скопируются данные. Сам он не меняется.
 */
void __pbm_natural_move_init(pbm_Natural_ptr* _inatural, const pbm_Natural_ptr* _inatural_move);

/**
 * @brief Безопасный конструктор перемещения.
 * `_inatural` будет иметь полную копию `_inatural_move`
 * \n
 * Внутри вызывает `__pbm_natural_move_init`
 * @param[out] _inatural Нуль-Натуральное число. Очищается и затем в него идёт перемещение `_inatural_move`. ${Dynamic}
 * @param[in]  _inatural_copy Нуль-Натуральное число, с которого полностью скопируются данные. Сам он не меняется.
 */
void __pbm_natural_move_init_s(pbm_Natural_ptr* _inatural, const pbm_Natural_ptr* _inatural_move);

/**
 * @brief Конструктор перемещения.
 * `_inatural` будет иметь полную копию `_inatural_move`
 * \n
 * Внутри вызывает `__pbm_natural_move_init` 
 * @warning Если `_inatural` уже заполнен, то возможна утечка памяти.
 * @param[out] _inatural Нуль-Натуральное число. Очищается и в него идёт копирование `_inatural_move`
 * @param[in]  _inatural_copy Нуль-Натуральное число, с которого полностью скопируются данные. Потом данные становится в NULL
 */
void _pbm_natural_move_init(pbm_Natural_ptr* _inatural, pbm_Natural_ptr* _inatural_move);

/**
 * @brief Конструктор перемещения.
 * `_inatural` будет иметь полную копию `_inatural_move`
 * \n
 * Внутри вызывает `__pbm_natural_move_init_s` 
 * @param[out] _inatural Нуль-Натуральное число. В него идёт копирование `_inatural_copy` ${Dynamic}
 * @param[in]  _inatural_copy Нуль-Натуральное число, с которого полностью скопируются данные. Потом данные становится в NULL
 */
void _pbm_natural_move_init_s(pbm_Natural_ptr* _inatural, pbm_Natural_ptr* _inatural_move);



// [Деструкторы]

/**
 * @brief Безопасное удаление
 * @param[out] _inatural ${Nullable} ${Dynamic} Нуль-Натуральное число
 * @warning Не забудьте потом выставить вашу переменную в NULL
 */
void _pbm_natural_delete(pbm_Natural_ptr _inatural);

/**
 * @brief Безопасное удаление на стеке. Очищает `_inatural->_size` и `_inatural->digits`, после этого их значения не зануляются. В них лежит мусор.
 * @param[out] _inatural ${Nullable} ${Dynamic | Stack} Нуль-Натуральное число.
 * \n
 * Если ${Dynamic} -> после вызова используйте free(...)
 */
void __pbm_natural_stack_delete(struct pbm_Natural* _inatural);




// <<[Вспомогательные функции]>>
// Безопасных функций нет, ибо пустая трата времени. Предполагается, что они используются только нашей библиотекой.
/**
 * @brief Из строки-числа переводит в Нуль-Натуральное число
 * @param[out] __num_str ${NotNull} Строка, хранящая число в 10 системе счисления. Изменяется, но не переаллоцируется.
 * @param[out] _inatural Нуль-Натуральное число. 
 */
void ___pbm_natural_spec_10_read(char* __num_str, pbm_Natural_ptr _inatural);

/**
 * @brief Из строки-числа переводит в Нуль-Натуральное число
 * @param[in] __num_str  ${NotNull} Строка, хранящая число в 2 системе счисления.
 * @param[in] _power     Степень двойки. \em HEX = 16 = 2^4 -> 4
 * @param[out] _inatural Нуль-Натуральное число. 
 */
void ___pbm_natural_spec_2_read(const char* __num_str, const uint16_t _power, pbm_Natural_ptr _inatural);





// <<[Функции]>>
// Для инициализации через строки.

/**
 * @brief Тоже конструктор по-умолчанию.
 * Внутри вызывает `_pbm_natural_default_init`, но в отличии от неё уже создаёт структуру, т.е. выделяет память под структуру.
 * @return ${Dynamic} Структура Нуль-Натурального числа, заполненная нулями.
 * Для удаления используйте `_pbm_natural_delete(...)`
 */
pbm_Natural_ptr __pbm_natural_default_create(void);

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
 * @param[in] _num_str ${NotNull} Строка с числом, записанным в системе счисления `_number_system`. Оно полностью копируется.
 * @param[in]  _number_system Система счисления, в которой записана строка `_num_str`
 * @return Нуль-Натуральное число, если NULL, то была ошибка при создании структуры. ${Nullable} | ${Dynamic}
 */
pbm_Natural_ptr _pbm_natural_create(const char* _num_str, const enum pbm_ns _number_system);

/**
 * @brief Безопасно создаёт структуру большого Нуль-Натурального числа.
 * Она проверяет на правильность записи в строке с нужной системой счисления. 
 * @param[in] _num_str ${NotNull} Строка с числом, записанным в системе счисления `_number_system`. Оно полностью копируется.
 * @param[in]  _number_system  Система счисления, в которой записана строка `_num_str` ${Nullable} если действительно нет ошибок.
 * @param[in,out] _error       Код ошибки, если успешно, то равно '0'
 * @return Нуль-Натуральное число, если NULL, то была ошибка при создании структуры. ${Nullable} | ${Dynamic}
 */
pbm_Natural_ptr _pbm_natural_create_s(const char* _num_str, const enum pbm_ns _number_system, enum pbm_err const* _error);

// Нормализация числа
/**
 * @brief Нормализует число, а именно удаляет ненужные нули (Если есть)
 * @param[out] _inatural Нуль-Натуральное число. Убирает лишние нули, меняет размер, меняет массив чисел (переаллоцируется)
 */
void _pbm_natural_normalization(pbm_Natural_ptr _inatural);



// <<[Функции]>>
// Преобразования в строки.

#if 0
/**
 * @brief Создаёт строку по основанию `_number_system` из большого числа.
 * @param[out] _buffer ${Nullable | NotInitialization} Строка, в которую запишутся данные. ${Change} ${Dynamic}
 * @param[out] _size   Указатель на размер данных. ${Change}
 * @param[in]  _inatural Структура Нуль-Натурального числа, из которого берутся данные.
 * @param[in]  _number_system Система счисления, из которой образуется наша строка.
 * @return Ничего не возвращает, но `_buffer` становится ${Dynamic} или {$Nullable}, если не хватка памяти  
 */
void _pbm_natural_to_str(char* _buffer, size_t *_size, const pbm_Natural_ptr _inatural, const enum pbm_ns _number_system); 

/**
 * @brief Преобразует из Нуль-Натурального числа строку, записанной в десятеричной системе счисления.
 * @param[out] _inatural Нуль-Натуральное число. Предполагается, что оно корректно
 * @param[out] __size    Указатель на размер строки. ${Change}
 * @return ${Dynamic | Nullable} Строка с необходимыми преобразованиями
 */
char* ___pbm_natural_to_decimal(const pbm_Natural_ptr _inatural, size_t * __size);
#endif



// <<[Функции]>>
// Базовые операции над числами

// Приведение типов
/**
 * @brief Приведение к типу `bool`, аналогично, как с обычным `int`
 * @param[in] _inatural Нуль-Натуральное число
 * @return Булевое значение: Всё, что не ноль - true
 */
bool _pbm_natural__bool(const pbm_Natural_ptr _inatural);


// Сравнения чисел

/**
 * @brief Проверяет на равенство двух больших Натуральных чисел
 * @param[in] _inatural_1 Первое Нуль-Натуральное число
 * @param[in] _inatural_2 Второе Нуль-Натуральное число
 * @return Булевое значение: _inatural_1 == _inatural_2 (первое число равно второму числу)
 */
bool _pbm_natural_equal(const pbm_Natural_ptr _inatural_1, const pbm_Natural_ptr _inatural_2);

/**
 * @brief Проверяет на неравенство двух больших Натуральных чисел
 * @param[in] _inatural_1 Первое Нуль-Натуральное число
 * @param[in] _inatural_2 Второе Нуль-Натуральное число
 * @return Булевое значение: _inatural_1 != _inatural_2 (первое число не равно второму числу)
 */
bool _pbm_natural_not_equal(const pbm_Natural_ptr _inatural_1, const pbm_Natural_ptr _inatural_2);


/**
 * @brief Проверяет на большинство двух больших Натуральных чисел
 * @param[in] _inatural_1 Первое Нуль-Натуральное число
 * @param[in] _inatural_2 Второе Нуль-Натуральное число
 * @return Булевое значение: _inatural_1 > _inatural_2 (первое число больше второго числа)
 */
bool _pbm_natural_more(const pbm_Natural_ptr _inatural_1, const pbm_Natural_ptr _inatural_2);

/**
 * @brief Проверяет на меньшинство двух больших Натуральных чисел
 * @param[in] _inatural_1 Первое Нуль-Натуральное число
 * @param[in] _inatural_2 Второе Нуль-Натуральное число
 * @return Булевое значение: _inatural_1 < _inatural_2 (первое число меньше второго числа)
 */
bool _pbm_natural_less(const pbm_Natural_ptr _inatural_1, const pbm_Natural_ptr _inatural_2);


/**
 * @brief Проверяет на большинство или равенство двух больших Натуральных чисел
 * @param[in] _inatural_1 Первое Нуль-Натуральное число
 * @param[in] _inatural_2 Второе Нуль-Натуральное число
 * @return Булевое значение: _inatural_1 >= _inatural_2 (первое число больше или равно второму числу)
 */
bool _pbm_natural_more_or_equal(const pbm_Natural_ptr _inatural_1, const pbm_Natural_ptr _inatural_2);

/**
 * @brief Проверяет на меньшинство или равенство двух больших Натуральных чисел
 * @param[in] _inatural_1 Первое Нуль-Натуральное число
 * @param[in] _inatural_2 Второе Нуль-Натуральное число
 * @return Булевое значение: _inatural_1 >= _inatural_2 (первое число меньше или равно второму числу)
 */
bool _pbm_natural_less_or_equal(const pbm_Natural_ptr _inatural_1, const pbm_Natural_ptr _inatural_2);



// Битовые операции над одним числом
#if defined(____PBM_bit_not)
/**
 * @brief Реверсирует биты у большого числа.
 * @param[out] _inatural Нуль-Натуральное число, биты которого нужно поменять. 0 -> 1; 1 -> 0;
 * @return Результат и есть параметр `_inatural`
 */
void _pbm_natural_bit_not(pbm_Natural_ptr _inatural);
#endif

/**
 * @brief т операцию `побитового И` между Нуль-Натуральным числом и простым числом.
 * @param[out] _inatural Нуль-Натуральное число, к которому применяется битовое И. ${Change}
 * @param[in]  _inum     Число, которое используется для побитового И.
 * \n
 * Вы можете использовать отрицательные числа, но они могут быть идентичны себе же.
 * @return Ничего не возвращает. Результат операции является параметр `_inatural`
 */
void _pbm_natural_bit_and__int(pbm_Natural_ptr _inatural, const pbm_digit_t _inum);

/**
 * @brief т операцию `побитового И` между двумя Нуль-Натуральными числами.
 * @param[in] _inatural_1 Первое Нуль-Натуральное число
 * @param[in] _inatural_2 Второе Нуль-Натуральное число
 * @return ${Dynamic | Nullable} Результат, аналогичный между числами (result = _inatural_1 & _inatural_2)
 */
pbm_Natural_ptr _pbm_natural_bit_and(const pbm_Natural_ptr _inatural_1, const pbm_Natural_ptr _inatural_2);
#endif