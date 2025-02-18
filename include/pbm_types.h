#ifndef PBM_TYPES_h
#define PBM_TYPES_h
#include <stdint.h>


/**
 * @brief The basic number system
 */
enum pbm_ns {
    bin = 2,
    ter = 3,
    oct = 8,
    dec = 10, // default
    hex = 16
};

#define PBM_default_pbm_ns ((enum pbm_ns)dec)
#define PBM_max_pbm_ns ((enum pbm_ns)hex)



#define PBM__MODVALUE (1000000000U)
#define PBM__BITS_PER_CHUNK (32)

typedef struct {
    uint32_t* chunks;
    size_t size;
    char is_negative;
} pbm_BigInt;

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



#endif