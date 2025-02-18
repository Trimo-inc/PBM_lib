#include "../../include/pbm_BigInt.h"
#include "../../include/tools/base.h"

pbm_BigInt pbm_BigInt_create(const char *_num, const enum pbm_ns _num_system, const char _is_negative, enum pbm_err *_err)
{
    pbm_BigInt bi;
    if (_num == NULL || _err == NULL) {
        if (_err)
            *_err = IS_NULL;
        return bi;
    }

    /*
    Проверяем, что строка действительна
    */
    {
        const char* p_num = _num;
        while (*p_num) {
            if (pbm___valid_c(*p_num, _num_system) == -1) {
                *_err = IS_NOT_VALID;
                return bi;
            }
            ++p_num;
        }
    }
    if ((_num_system & (_num_system - 1)) == 0) {
        /* Система счисления является степенью двойки =>
        => мы можем оптимизировать процесс
        */
        uint16_t exp_ = pbm___get2power((uint32_t)_num_system);
        pbm__BigInt_2pow_process_reading(_num, exp_, &bi); 
    } else {
        if (_num_system == dec)
            pbm__BigInt_10_process_reading(_num, &bi);
    }  

    bi.is_negative = _is_negative;

    return bi;
}