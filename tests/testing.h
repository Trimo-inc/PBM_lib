#ifndef ____PBM_____HEADER_____TESTING
#define ____PBM_____HEADER_____TESTING

#include <stdio.h>
#include <assert.h>

#if defined(_POSIX_C_SOURCE) || defined(__linux__)
    #include <sys/time.h>
    #define USE_GETTIMEOFDAY
#else
    #include <time.h>
#endif



FILE* _log; // It'is logger output

/**
 * @brief Создаёт тест (CreateTest)
 * @param name   Имя теста
 * @param brief  Короткое описание теста (Ставьте 0, если не хотите его писать)
 * @param block_ Блок кода, который будет в данном тесте.
 */
#define CTEST(name, brief, block_) do {                                          \
    fprintf(_log, "======START======\n");                                        \
    fprintf(_log, "Name:  %s\n", name);                                          \
    fprintf(_log, "Brief: %s\n", (brief == NULL) ? ("None") : brief);            \
    block_;                                                                      \
    fprintf(_log, "=======END=======\n\n");                                      \
} while(0);


#define TEST(expr, msg, ...) do {                                               \
if (expr) {                                                                     \
    fprintf(_log, "[+]:is expression \"%s\"\n", #expr);                         \
    if (msg != 0)                                                               \
        fprintf(_log, "\t%s\n", (char*)msg);                                    \
}                                                                               \
else {                                                                          \
    fprintf(_log, "[-]:is expression \"%s\"\n", #expr);                         \
    fprintf(_log, __VA_ARGS__ );                                                \
    fprintf(_log, "\n");                                                        \
}}                                                                              \
while(0);


#define TIME_TEST(block_) do {                                                  \
    clock_t start = clock();                                                    \
    block_;                                                                     \
    clock_t end   = clock();                                                    \
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;                 \
    fprintf(_log,                                                               \
        "[PROGRAM]:<%s>\n%s\nTime spend: %.8f seconds\n\n",                     \
        __func__, #block_, time_spent);                                         \
}                                                                               \
while(0);


#define TIME_TEST_RANGE(block_, range) assert(range > 0); do {                  \
    clock_t total = 0;                                                          \
    for(uint32_t i = 0; i < range; ++i) {                                       \
        clock_t start = clock();                                                \
        block_;                                                                 \
        clock_t end   = clock();                                                \
        total += (end - start);                                                 \
    }                                                                           \
    double arv_time = (double)total / CLOCKS_PER_SEC / range;                   \
    fprintf(_log,                                                               \
        "[TIME_TEST_RANGE]:<%s:%d> Average time for %d runs: %.8f seconds\n\n", \
        __func__, __LINE__, range, arv_time);                                   \
}                                                                               \
while(0);


#include "pbm_lib.h"
void __print_natural_pow(const pbm_Natural_ptr big);
void bit_and(void);
void bit_or(void);
void bit_xor(void);
void bit_lshift(void);
void bit_rshift(void);

#endif
