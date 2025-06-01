#ifndef __PBM_TYPES_h
#define __PBM_TYPES_h
#include <stdint.h>

#if (ARCH == 64)
/* 64-bits on linux or windows */
typedef uint64_t pbm_digit_t; 
#define PBM_ibase (0xFFFFFFFFFFFFFFFF)
#define PBM_log_base (19.27)

#endif

#if (ARCH == 32)
/* 32-bits on linux or windows*/
typedef uint32_t pbm_digit_t; 
#define PBM_ibase ((uint32_t)4294967295) 
#define PBM_log_base (9.63)

#endif

#if (ARCH == 64)
// 64 bits
#define PBM_digit_bits ((sizeof(pbm_digit_t) * 8))
#elif (ARCH == 32)
// 32 bits
#define PBM_digit_bits ((sizeof(pbm_digit_t) * 8))
#endif
  





/**
 * @brief Базовые системы счисления.
 */
enum pbm_ns {
    bin = 2,
    ter = 3,
    qua = 4,  // Quaternary 
    oct = 8,
    dec = 10, // default
    hex = 16
};

#define PBM_default_pbm_ns ((enum pbm_ns)dec)
#define PBM_max_pbm_ns ((enum pbm_ns)hex)



/**
 * @brief Хранит огромное целое число.
 * 
 */
struct pbm_BigInt {
    pbm_digit_t* chunks;
    size_t size;
    char is_negative;
};

/**
 * @brief Указатель на структуру pbm_BigInt.
 * Предполагается, что объект будет в куче.
 */
typedef struct pbm_BigInt* pbm_BigInt_ptr; 


typedef char* bin_str;
typedef char* oct_str;
typedef char* dec_str;
typedef char* hex_str;

enum pbm_err {
    NO = 0,
    IS_NULL,
    NUM_SYSTEM,
    VERY_BIG_NUM,
    MEMORY,
    IS_NOT_VALID
};


/**
 * @brief Составляет структуру по хранению системы счисления.
 * Нужен, чтобы заполнить свою систему счисления со своими знаками.
 */
struct pbm_nums {
    char* data;
    /**
     * @brief Представляет разряд системы счисления, а также длину массива.
     */
    size_t size;
};

#ifndef __cplusplus
    typedef char bool;
    #define true  (1)
    #define false (0)
#endif

#endif