#ifndef ____PBM_____HEADER_____TESTING
#define ____PBM_____HEADER_____TESTING

#include <stdio.h>
#include <assert.h>
#ifdef __linux__
    #include <sys/time.h>
#else
    #include <time.h>
#endif

FILE* _log; // It'is logger output

#define TEST(expr, ...) do {                                                    \
if (expr) {                                                                     \
    fprintf(_log, "[+]:<%s> is expression \"%s\"\n", __func__, #expr);          \
}                                                                               \
else {                                                                          \
    fprintf(_log, "[-]:<%s> is expression \"%s\"\n", __func__, #expr);          \
    fprintf(_log, __VA_ARGS__ );                                                \
    fprintf(_log, "\n");                                                        \
}}                                                                              \
while(0);


#ifdef __linux__
#define TIME_TEST(block_) do {                                                  \
    struct timeval start, end;                                                  \
    gettimeofday(&start, NULL);                                                 \
    block_;                                                                     \
    gettimeofday(&end, NULL);                                                   \
    long seconds = end.tv_sec - start.tv_sec;                                   \
    long micros = end.tv_usec - start.tv_usec;                                  \
    fprintf(                                                                    \
        _log,                                                                   \
        "[PROGRAM]:<%s>\n%s\nTime spend: %ld.%08ld seconds\n",                  \
        __func__, #block_, seconds, micros);                                    \
} while(0); 
#else
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
#endif

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
        "[PROGRAM]:<%s>\n%s\nAverage time for %d runs: %.8f seconds\n\n",       \
        __func__, #block_, range, arv_time);                                    \
}                                                                               \
while(0);



void __print_natural_pow(const pbm_Natural_ptr big) {
    for (size_t i = 0; i < big->_size; ++i) {
        #if ARCH == 32
        fprintf(_log, "(%u)*((2^%u)^%u)+", big->digits[i], (unsigned int)PBM_digit_bits, (unsigned int)i);
        #elif ARCH == 64
        fprintf(_log, "(%llu)*((2^%llu)^%llu)+", big->digits[i], PBM_digit_bits, i);
        #endif
    }
    fprintf(_log, "0\n");
}
#endif
