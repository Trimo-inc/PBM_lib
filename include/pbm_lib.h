#ifndef ____PBM____LIB_h
#define ____PBM____LIB_h ____PBM__HEADER____


/*
Генерирует макрос для заголовочных файлов по нужному шаблону
*/
#define __PBM__(name) (____PBM____LIB_h##name)

/*
Проверяет, существует ли определение
*/
#define __PBM__DEFINED(def) (defined(____PBM____LIB_h##def))

/*
Включает все необходимые заголовки
*/
#include "pbm_types.h"
#include "pbm_BigInt.h"
#include "pbm_nums.h"
#include "tools/base.h"


#endif